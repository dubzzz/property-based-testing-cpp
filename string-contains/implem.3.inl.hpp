#include <string>

bool starts_with(const char* pattern, const char* text)
{
  for ( ; *pattern == *text ; ++pattern, ++text);
  return !*pattern;
}

bool contains(const char* pattern, const char* text)
{
  if (!*pattern) return true;
  
  for ( ; *text && ! starts_with(pattern, text) ; ++text);
  return !!*text;
}

bool contains(std::string const& pattern, std::string const& text)
{
  return contains(pattern.c_str(), text.c_str());
}

