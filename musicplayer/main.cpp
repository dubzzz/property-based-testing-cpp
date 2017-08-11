#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

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

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
