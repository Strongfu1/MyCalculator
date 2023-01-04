#include "Validator.h"

namespace s21 {
bool Validator::Validate(std::string str) {
  if (!CheckParenthesis(str))
    return false;
  if (std::isdigit(str[0]) || str[0] == 'x' || str[0] == '(') {
    if (ValNum(str))
      return true;
  }
  if ((str[0] >= 'a' && str[0] <= 'z') || str[0] == '(')
    return ValFunc(str);
  return false;
}

bool Validator::ValNum(std::string str) {
  if (!str.length())
    return true;
  if (std::regex_search(str, matched, num))
    return ValOper(str.substr(matched[0].length()));
  return false;
}

bool Validator::ValOper(std::string str) {
  if (!str.length())
    return true;
  if (std::regex_search(str, matched, oper)) {
    int size = matched[0].length();
    if (ValNum(str.substr(size)))
      return true;
    else
      return ValFunc(str.substr(size));
  }
  return false;
}

bool Validator::ValFunc(std::string str) {
  if (!str.length())
    return true;
  if (std::regex_search(str, matched, func)) {
    int size = matched[0].length();
    if (ValNum(str.substr(size)))
      return true;
    return ValFunc(str.substr(size));
  }
  return false;
}

bool Validator::CheckParenthesis(const std::string &str) {
  auto it = str.begin();
  std::stack<char> s;
  while (it != str.end() && *it != '(' && *it != ')') {
    ++it;
  }
  while (it != str.end()) {
    if (*it == '(')
      s.push('(');
    else if (*it == ')') {
      if (s.empty())
        return false;
      s.pop();
    }
    ++it;
  }
  return (s.empty());
}

} // namespace s21
