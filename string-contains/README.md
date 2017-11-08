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

### With [```implem.4.inl.hpp```](https://github.com/dubzzz/property-based-testing-cpp/blob/master/string-contains/implem.4.inl.hpp)

Adaptation of the generators in order to generate std::string containing '\0'.

```
[ RUN      ] Contains_Property.BAlwaysInABC
Using configuration: seed=454853540105607962
/property-based-testing-cpp/rapidcheck/extras/gtest/include/rapidcheck/gtest.h:29: Failure
Failed
Falsifiable after 11 tests and 4 shrinks

std::string:
"\0"

std::string:
"\x1"

std::string:
""

/property-based-testing-cpp/string-contains/main.cpp:43:
RC_ASSERT(contains(b, a + b + c))

Expands to:
false

[  FAILED  ] Contains_Property.BAlwaysInABC (6 ms)
```

### With [```implem.5.inl.hpp```](https://github.com/dubzzz/property-based-testing-cpp/blob/master/string-contains/implem.5.inl.hpp)

Exactly follows the property stated in the rules as property to be checked.

```
[ RUN      ] Contains_Property.IfAndOnlyIfIndexSuchThatSubstringIsPattern
/property-based-testing-cpp/rapidcheck/extras/gtest/include/rapidcheck/gtest.h:29: Failure
Failed
Falsifiable after 4 tests

std::string:
"\0\0"

std::string:
"\0"

/property-based-testing-cpp/string-contains/main.cpp:70:
RC_ASSERT(property_if_only_if(pattern, text) == contains(pattern, text))

Expands to:
false == true

[  FAILED  ] Contains_Property.IfAndOnlyIfIndexSuchThatSubstringIsPattern (1 ms)
```

## Other languages

JavaScript: https://runkit.com/dubzzz/property-based-example-contains

