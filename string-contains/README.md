# string-contains

## Prototype

```cpp
bool contains(std::string const& pattern, std:: const& text)
```

## Contract

Whatever the inputs ```text``` and ```pattern```,

returns ```true``` if and only if there is an index, ```idx```, such that ```text[idx : idx+pattern.size] == pattern```

## Property based status

### With [```implem.1.inl.hpp```](https://github.com/dubzzz/property-based-testing-cpp/blob/master/string-contains/implem.1.inl.hpp)

```
[ RUN      ] Contains_Property.BAlwaysInABC
Using configuration: seed=4519302130323994423
/property-based-testing-cpp/rapidcheck/extras/gtest/include/rapidcheck/gtest.h:29: Failure
Failed
Falsifiable after 1 tests

std::tuple<std::string, std::string, std::string>:
("", "", "")

/property-based-testing-cpp/string-contains/main.cpp:30:
RC_ASSERT(contains(b, a + b + c))

Expands to:
false

[  FAILED  ] Contains_Property.BAlwaysInABC (1 ms)
```

### With [```implem.2.inl.hpp```](https://github.com/dubzzz/property-based-testing-cpp/blob/master/string-contains/implem.2.inl.hpp)

```
[ RUN      ] Contains_Property.BAlwaysInABC
Using configuration: seed=10510925648685648787
/property-based-testing-cpp/rapidcheck/extras/gtest/include/rapidcheck/gtest.h:29: Failure
Failed
Falsifiable after 10 tests and 3 shrinks

std::tuple<std::string, std::string, std::string>:
("", "a", "")

/property-based-testing-cpp/string-contains/main.cpp:30:
RC_ASSERT(contains(b, a + b + c))

Expands to:
false

[  FAILED  ] Contains_Property.BAlwaysInABC (5 ms)
```

### With [```implem.3.inl.hpp```](https://github.com/dubzzz/property-based-testing-cpp/blob/master/string-contains/implem.3.inl.hpp)

```
[ RUN      ] Contains_Property.BAlwaysInABC
Using configuration: seed=13133008835883874659
/property-based-testing-cpp/rapidcheck/extras/gtest/include/rapidcheck/gtest.h:29: Failure
Failed
Falsifiable after 22 tests and 4 shrinks

std::tuple<std::string, std::string, std::string>:
("", "aa", "")

/property-based-testing-cpp/string-contains/main.cpp:39:
RC_ASSERT(contains(b, a + b + c))

Expands to:
false

[  FAILED  ] Contains_Property.BAlwaysInABC (5 ms)
```
