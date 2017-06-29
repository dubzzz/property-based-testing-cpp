#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <cstddef>
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

RC_GTEST_PROP(Contains_Property, NoNullBAlwaysInABC, (std::string a, std::string b, std::string c))
{
  RC_ASSERT(contains(b, a + b + c));
}

RC_GTEST_PROP(Contains_Property, BAlwaysInABC, ())
{
  auto gen = rc::gen::container<std::string>(rc::gen::arbitrary<char>());
  std::string a = *gen;
  std::string b = *gen;
  std::string c = *gen;
  RC_ASSERT(contains(b, a + b + c));
}

bool property_if_only_if(std::string const& pattern, std::string const& text)
{
  for (std::size_t idx {} ; idx != text.size() ; ++idx)
    if (text.substr(idx, pattern.size()) == pattern)
      return true;
  return pattern.empty();
}

RC_GTEST_PROP(Contains_Property, NoNullIfAndOnlyIfIndexSuchThatSubstringIsPattern, (std::string pattern, std::string text))
{
  RC_ASSERT(property_if_only_if(pattern, text) == contains(pattern, text));
}

RC_GTEST_PROP(Contains_Property, IfAndOnlyIfIndexSuchThatSubstringIsPattern, ())
{
  auto gen = rc::gen::container<std::string>(rc::gen::arbitrary<char>());
  std::string pattern = *gen;
  std::string text = *gen;
  RC_ASSERT(property_if_only_if(pattern, text) == contains(pattern, text));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
