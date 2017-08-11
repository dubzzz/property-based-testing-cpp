#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include "implem.inl.hpp"

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
