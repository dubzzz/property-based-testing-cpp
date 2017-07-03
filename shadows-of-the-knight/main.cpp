#include "gtest/gtest.h"
#include <rapidcheck/gtest.h>

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

/*RC_GTEST_PROP(TEST_NAME, Random2DSpace, (std::size_t const& w, std::size_t const &h))
{
  RC_PRE(w > static_cast<std::size_t>(0) && h > static_cast<std::size_t>(0));
  std::size_t x = *rc::gen::inRange(std::size_t(), w);
  std::size_t y = *rc::gen::inRange(std::size_t(), h);
    
  Space<2, RcAssert> space({{w, h}}, {{x, y}});
  auto answer = locate_in_space(space);
  ASSERT_TRUE(space.is_solution(answer));
}*/

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

