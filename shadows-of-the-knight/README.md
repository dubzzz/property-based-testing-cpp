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

## Property based status

### With [```implem.1.inl.hpp```](https://github.com/dubzzz/property-based-testing-cpp/blob/master/shadows-of-the-knight/implem.1.inl.hpp)

This implementation is enough to make all tests green (for tests visible to the user in CodinGame).
Replacing `y_max = y0 -1` by `y_max = y0` is enough to pass all the tests even the hidden ones.

```
[ RUN      ] ShadowsOfTheKnight.ShouldAlwaysReachTheTarget
Using configuration: seed=15157045376141439530
/property-based-testing-cpp/rapidcheck/extras/gtest/include/rapidcheck/gtest.h:29: Failure
Failed
Falsifiable after 9 tests and 5 shrinks

std::tuple<unsigned long, unsigned long>:
(8, 8)

start position:
(0, 1)

target position:
(1, 0)

/property-based-testing-cpp/shadows-of-the-knight/main.cpp:107:
RC_ASSERT(space.solved())

Expands to:
false

[  FAILED  ] ShadowsOfTheKnight.ShouldAlwaysReachTheTarget (15 ms)
```

## Other languages

JavaScript: https://runkit.com/dubzzz/property-based-testing-example-shadows-of-the-knight

