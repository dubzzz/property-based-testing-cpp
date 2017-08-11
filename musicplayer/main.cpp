#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>
#include <rapidcheck/state.h>

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <unordered_set>
#include <vector>

#include "implem.inl.hpp"

// Running tests

TEST(MusicPlayer, StartInPauseModeOnFirstTrack)
{
	MusicPlayer p{ "track:aaa", "track:bbb" };
	ASSERT_FALSE(p.is_playing());
	ASSERT_EQ("track:aaa", p.track_name());
}

TEST(MusicPlayer, PlayOnlyChangePlayingStatusNotTheTrack)
{
	MusicPlayer p{ "track:aaa", "track:bbb" };
	p.play();
	p.play();
	ASSERT_TRUE(p.is_playing());
	ASSERT_EQ("track:aaa", p.track_name());
}
TEST(MusicPlayer, MultiplePlaySameAsSinglePlay)
{
	MusicPlayer p{ "track:aaa", "track:bbb" };
	p.play();
	p.play();
	ASSERT_TRUE(p.is_playing());
	ASSERT_EQ("track:aaa", p.track_name());
}

TEST(MusicPlayer, PauseOnlyChangePlayingStatusNotTheTrack)
{
	MusicPlayer p{ "track:aaa", "track:bbb" };
	p.play();
	p.pause();
	ASSERT_FALSE(p.is_playing());
	ASSERT_EQ("track:aaa", p.track_name());
}

TEST(MusicPlayer, NextDoesNotChangePlayingStatus)
{
	MusicPlayer p{ "track:aaa", "track:bbb", "track:ccc" };
	p.next();
	ASSERT_FALSE(p.is_playing());
	p.play();
	p.next();
	ASSERT_TRUE(p.is_playing());
}

TEST(MusicPlayer, NextDoesCircularTraversalOfTracks)
{
	MusicPlayer p{ "track:aaa", "track:bbb", "track:ccc" };
	p.next();
	ASSERT_EQ("track:bbb", p.track_name());
	p.next();
	ASSERT_EQ("track:ccc", p.track_name());
	p.next();
	ASSERT_EQ("track:aaa", p.track_name());
}

TEST(MusicPlayer, AddedTrackAreInstantlyAvailable)
{
	MusicPlayer p{ "track:aaa", "track:bbb", "track:ccc" };
	p.add_track("track:ddd", 1);
	p.add_track("track:eee", 0);
	p.add_track("track:fff", 5);

	p.jump(0);
	ASSERT_EQ("track:eee", p.track_name());
	p.jump(2);
	ASSERT_EQ("track:ddd", p.track_name());
	p.jump(5);
	ASSERT_EQ("track:fff", p.track_name());
}

TEST(MusicPlayer, AddTrackDoesNotImplyPlayingStatusOrTrack)
{
	MusicPlayer p{ "track:aaa", "track:bbb", "track:ccc" };
	p.play();
	p.next();
	p.add_track("track:ddd", 2);
	ASSERT_TRUE(p.is_playing());
	ASSERT_EQ("track:bbb", p.track_name());
}

// Property-based testing

struct MusicPlayerModel
{
  bool is_playing;
  std::size_t num_tracks;
  std::unordered_set<std::string> tracks_already_seen; //our model forbid to append twice the same track

  MusicPlayerModel()
      : is_playing(false)
      , num_tracks()
      , tracks_already_seen()
  {}
};
using MusicPlayerCommand = rc::state::Command<MusicPlayerModel, MusicPlayer>;

struct PlayCommand : MusicPlayerCommand
{
  void checkPreconditions(MusicPlayerModel const& /*m*/) const override {}
  void apply(MusicPlayerModel& m) const override { m.is_playing = true; }
  void run(MusicPlayerModel const& /*m*/, MusicPlayer& p) const override
  {
    p.play();
    RC_ASSERT(p.is_playing());
  }
  void show(std::ostream& os) const override { os << "Play"; }
};

struct PauseCommand : MusicPlayerCommand
{
  void checkPreconditions(MusicPlayerModel const& /*m*/) const override {}
  void apply(MusicPlayerModel& m) const override { m.is_playing = false; }
  void run(MusicPlayerModel const& /*m*/, MusicPlayer& p) const override
  {
    p.pause();
    RC_ASSERT(!p.is_playing());
  }
  void show(std::ostream& os) const override { os << "Pause"; }
};

struct NextCommand : MusicPlayerCommand
{
  void checkPreconditions(MusicPlayerModel const& /*m*/) const override {}
  void apply(MusicPlayerModel& m) const override {}
  void run(MusicPlayerModel const& m, MusicPlayer& p) const override
  {
    auto track_before = p.track_name();
    p.next();
    RC_ASSERT(m.is_playing == p.is_playing());
    if (m.num_tracks == 1)
    {
      RC_ASSERT(track_before == p.track_name());
    }
    else
    {
      RC_ASSERT(track_before != p.track_name());
    }
  }
  void show(std::ostream& os) const override { os << "Next"; }
};

struct AddTrackCommand : MusicPlayerCommand
{
  std::size_t position = *rc::gen::arbitrary<std::size_t>();
  std::string trackName = *rc::gen::arbitrary<std::string>();
  void checkPreconditions(MusicPlayerModel const& m) const override
  {
    RC_PRE(m.tracks_already_seen.end() == m.tracks_already_seen.find(trackName));
  }
  void apply(MusicPlayerModel& m) const override
  {
    ++m.num_tracks;
    m.tracks_already_seen.insert(trackName);
  }
  void run(MusicPlayerModel const& m, MusicPlayer& p) const override
  {
    auto track_before = p.track_name();
    p.add_track(trackName, position % (m.num_tracks +1)); //old model
    RC_ASSERT(m.is_playing == p.is_playing());
    RC_ASSERT(track_before == p.track_name());
  }
  void show(std::ostream& os) const override { os << "AddTrack(" << trackName << ", " << position << ")"; }
};

RC_GTEST_PROP(MusicPlayer, CheckProperties, (std::set<std::string> initial_tracks))
{
  RC_PRE(!initial_tracks.empty());

  MusicPlayer p(initial_tracks.begin(), initial_tracks.end());
  
  MusicPlayerModel m;
  ++m.num_tracks = initial_tracks.size();
  std::copy(
      initial_tracks.begin()
      , initial_tracks.end()
      , std::inserter(m.tracks_already_seen, m.tracks_already_seen.begin()));

  rc::state::check(m, p, rc::state::gen::execOneOfWithArgs<PlayCommand, PauseCommand, NextCommand, AddTrackCommand>());
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
