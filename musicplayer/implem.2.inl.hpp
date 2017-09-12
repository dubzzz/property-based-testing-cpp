#include <algorithm>
#include <string>
#include <vector>

class MusicPlayer
{ 
  std::vector<std::string> _tracks;
  bool _is_playing;
  std::size_t _playing;

public:
  MusicPlayer(std::initializer_list<std::string> tracks)
      : _tracks(tracks.begin(), tracks.end())
      , _is_playing()
      , _playing()
  {}
  
  template <class Iterator>
  MusicPlayer(Iterator const& beg, Iterator const& end)
      : _tracks(beg, end)
      , _is_playing()
      , _playing()
  {}

  bool is_playing() const { return _is_playing; }
  std::string track_name() const { return _tracks[_playing]; }

  void play() { _is_playing = true; }
  void pause() { _is_playing = false; }

  void add_track(std::string const& track, std::size_t position)
  {
    _tracks.push_back(track);
    std::rotate(
        std::next(_tracks.begin(), position)
        , std::next(_tracks.begin(), _tracks.size() -1)
        , _tracks.end());
  }

  void next()
  {
	  if (++_playing == _tracks.size())
	  {
		  _playing = 0;
	  }
  }
  void jump(std::size_t position) { _playing = position; }
};
