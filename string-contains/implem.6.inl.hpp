#include <string>

bool starts_with(const char* pattern, const char* pattern_end, const char* text, const char* text_end)
{
  for ( ; pattern != pattern_end && text != text_end && *pattern == *text ; ++pattern, ++text);
  return pattern == pattern_end;
}

bool contains(const char* pattern, const char* pattern_end, const char* text, const char* text_end)
{
  if (pattern == pattern_end) return true;
  
  for ( ; text != text_end && ! starts_with(pattern, pattern_end, text, text_end) ; ++text);
  return text != text_end;
}

bool contains(std::string const& pattern, std::string const& text)
{
  return contains(pattern.c_str()
      , pattern.c_str() + pattern.size()
      , text.c_str()
      , text.c_str() + text.size());
}

