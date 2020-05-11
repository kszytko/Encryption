#pragma once
#include <algorithm>

bool isPalindrome(const std::string & text){
  return std::search(text.begin(), text.end(), text.rbegin(), text.rend()) == text.begin();
}
