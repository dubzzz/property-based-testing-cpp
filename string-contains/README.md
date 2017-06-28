# string-contains

## Prototype

```cpp
bool contains(std::string const& pattern, std:: const& text)
```

## Contract

Whatever the inputs ```text``` and ```pattern```,

returns ```true``` if and only if there is an index, ```idx```, such that ```text[idx : idx+pattern.size] == pattern```
