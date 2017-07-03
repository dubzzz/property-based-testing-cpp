# shadows-of-the-knight

## Prototype

```cpp
void locate_in_space(Space& space, std::size_t rounds)
```

## Contract

This example is based on the exercise [Shadows of the knight - episode 1](https://www.codingame.com/training/medium/shadows-of-the-knight-episode-1) of CodinGame website.

Given a Space having the following methods:

```cpp
class Space
{
public:
  std::size_t dimension_x() const; // dimensions of the grid
  std::size_t dimension_y() const;
  
  std::size_t previous_x() const;  // last known location
  std::size_t previous_y() const;
  
  std::string const& hint() const; // direction to the target (U=Up, D=Down, L=Left, R=Right)
  bool solved() const;             // is it the position of the target? equivalent to hint == ""
  
  void move(std::size_t x, std::size_t y); // update position
};
```

And a limited amount of tries, you need to reach a target in the grid.
