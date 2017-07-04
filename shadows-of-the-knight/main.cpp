#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

#include <cmath>
#include <cstddef>

#include "space.hpp"
#include "implem.inl.hpp"

// Running tests

TEST(ShadowsOfTheKnight, ALotOfJumps)
{
  Space space = SpaceBuilder{}
      .withDimension(4, 8)
      .withSolution(3, 7)
      .withCurrent(2, 3)
      .build();
  locate_in_space(space, 40);
  ASSERT_TRUE(space.solved());
}

TEST(ShadowsOfTheKnight, LessJumps)
{
  Space space = SpaceBuilder{}
      .withDimension(25, 33)
      .withSolution(2, 29)
      .withCurrent(24, 2)
      .build();
  locate_in_space(space, 49);
  ASSERT_TRUE(space.solved());
}

TEST(ShadowsOfTheKnight, LesserJumps)
{
  Space space = SpaceBuilder{}
      .withDimension(40, 60)
      .withSolution(38, 38)
      .withCurrent(6, 6)
      .build();
  locate_in_space(space, 32);
  ASSERT_TRUE(space.solved());
}

TEST(ShadowsOfTheKnight, Tower)
{
  Space space = SpaceBuilder{}
      .withDimension(1, 80)
      .withSolution(0, 36)
      .withCurrent(0, 1)
      .build();
  locate_in_space(space, 6);
  ASSERT_TRUE(space.solved());
}

TEST(ShadowsOfTheKnight, CorrectCutting)
{
  Space space = SpaceBuilder{}
      .withDimension(50, 50)
      .withSolution(22, 22)
      .withCurrent(0, 0)
      .build();
  locate_in_space(space, 6);
  ASSERT_TRUE(space.solved());
}

TEST(ShadowsOfTheKnight, Evasive)
{
  Space space = SpaceBuilder{}
      .withDimension(100, 100)
      .withSolution(0, 1)
      .withCurrent(5, 98)
      .build();
  locate_in_space(space, 7);
  ASSERT_TRUE(space.solved());
}

TEST(ShadowsOfTheKnight, NotThere)
{
  Space space = SpaceBuilder{}
      .withDimension(9999, 9999)
      .withSolution(9754, 2531)
      .withCurrent(54, 77)
      .build();
  locate_in_space(space, 14);
  ASSERT_TRUE(space.solved());
}

RC_GTEST_PROP(ShadowsOfTheKnight, ShouldAlwaysReachTheTarget, ())
{
  auto w = *rc::gen::inRange(std::size_t(1), std::size_t(10000)).as("grid width");
  auto h = *rc::gen::inRange(std::size_t(1), std::size_t(10000)).as("grid height");
  
  auto inRangeGen = rc::gen::apply([](std::size_t x, std::size_t y) { return std::make_pair(x, y); }
      , rc::gen::inRange(std::size_t(), w)
      , rc::gen::inRange(std::size_t(), h)
  );
  auto current  = *inRangeGen.as("start position");
  auto solution = *inRangeGen.as("target position");
  std::size_t max_guesses = std::lround(std::ceil(std::log(std::max(h, w))/std::log(2)));
  
  Space space = SpaceBuilder{}
      .withDimension(w, h)
      .withSolution(solution.first, solution.second)
      .withCurrent(current.first, current.second)
      .build();
  locate_in_space(space, max_guesses);
  
  RC_ASSERT(space.solved());
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

