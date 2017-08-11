# musicplayer

## Story

Inspired by the story of https://labs.spotify.com/2015/06/25/rapid-check/, I wanted to give it a try through an example.

Lets assume we are building a music player having the following characteristics:
- Player has to be initialized with a non-empty list of tracks
- Play: if not playing, resumes where it first stopped or starts playing, otherwise, does nothing
- Pause: pauses the currently playing music
- Next: moves to next track (regarding ordering scheme in place), does not impact playing mode status, starts the music at its beginning
- Add Track At Position: adds a track at a given position into the playlist (basically we can imagine some kind of drag-and-drop)

For the sake of this example, we will simplify the notion of track and position in the track:
- track will be considered as a simple label
- position in the track will not be taken into account (as a consequence moving to next track results in a call to Next)
