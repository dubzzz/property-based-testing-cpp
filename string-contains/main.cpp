#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <string>
#include "implem.inl.hpp"

TEST(Contains, StartsWith)
{
  ASSERT_TRUE(contains("he", "hello world"));
}
TEST(Contains, SomewhereInside)
{
  ASSERT_TRUE(contains("g", "omg!!!"));
}
TEST(Contains, ContainsEmptyString)
{
  ASSERT_TRUE(contains("", "whatever"));
}
TEST(Contains, NoMatch)
{
  ASSERT_FALSE(contains("no", "other"));
}
TEST(Contains, LargerPattern)
{
  ASSERT_FALSE(contains("no", ""));
}

/*TEST(ContainsBug, Implem1)
{
  ASSERT_TRUE(contains("", ""));
}
TEST(ContainsBug, Implem2)
{
  ASSERT_TRUE(contains("a", "a"));
}*/

RC_GTEST_PROP(Contains_Property, BAlwaysInABC, ())
{
  auto gen = rc::gen::container<std::string>(rc::gen::arbitrary<char>());
  std::string a = *gen;
  std::string b = *gen;
  std::string c = *gen;
  RC_ASSERT(contains(b, a + b + c));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
