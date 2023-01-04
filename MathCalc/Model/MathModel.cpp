#include "MathModel.h"

#include <iostream>
#include <stack>
#include <string>
#include <vector>
namespace s21 {
typedef double (*unop)(double);
typedef double (*binop)(double, double);
MathModel::MathModel() : validator(new Validator) {}
MathModel::~MathModel() { delete validator; }

std::string MathModel::RemoveUnaryMinus(std::string str) {
  std::string out;
  auto i = str.begin();
  if (*i == '-')
    out.push_back('0');
  out.push_back(*i++);
  while (i != str.end()) {
    if (*i == '-' && *(i - 1) == '(')
      out.push_back('0');
    out.push_back(*i);
    ++i;
  }
  return out;
}

bool MathModel::Validate(const std::string &str) {
  return validator->Validate(str);
}
static void GetNumber(std::list<std::string> &l, const std::string &str,
                      size_t &i) {
  char *number_end;
  std::strtod(str.c_str() + i, &number_end);
  int shift = number_end - str.c_str() - i;
  l.push_back(str.substr(i, shift));
  i += shift - 1;
}
template <typename T>
static bool FindOper(std::unordered_map<char, T> &map, char c) {
  return map.find(c) != map.end();
}

template <typename T> T PopVal(std::stack<T> &s) {
  T value = s.top();
  s.pop();
  return value;
}

void MathModel::ProcessUnOp(const std::string &str, size_t &i,
                            std::stack<char> &symbols) {
  switch (str[i]) {
  case 'l':
    if (!std::strncmp("ln", str.c_str() + i, 2))
      symbols.push('n');
    else if (!std::strncmp("log", str.c_str() + i, 3))
      symbols.push('l');
    break;
  case 'a':
    if (!std::strncmp("asin", str.c_str() + i, 4))
      symbols.push('r');
    else if (!std::strncmp("acos", str.c_str() + i, 4))
      symbols.push('o');
    else if (!std::strncmp("atan", str.c_str() + i, 4))
      symbols.push(str[i]);
    break;
  case 's':
    if (!std::strncmp("sqrt", str.c_str() + i, 4))
      symbols.push('q');
    else if (!std::strncmp("sin", str.c_str() + i, 3))
      symbols.push(str[i]);
    break;
  case 'c':
    if (!std::strncmp("cos", str.c_str() + i, 3))
      symbols.push(str[i]);
    break;
  case 't':
    if (!std::strncmp("tan", str.c_str() + i, 3))
      symbols.push(str[i]);
    break;
  default:
    break;
  }
  i += func_len[symbols.top()];
}

void MathModel::ProcessBinOp(const std::string &str, size_t &i,
                             std::stack<char> &symbols,
                             std::list<std::string> &rpn) {
  if (str[i] == '(') {
    symbols.push(str[i]);
  } else if (str[i] == ')') {
    while (!symbols.empty() && symbols.top() != '(') {
      rpn.push_back(std::string(1, PopVal(symbols)));
    }
    symbols.pop();
  } else if (symbols.empty() || priority[symbols.top()] < priority[str[i]]) {
    symbols.push(str[i]);
  } else {
    while (!symbols.empty() && priority[symbols.top()] >= priority[str[i]])
      rpn.push_back(std::string(1, PopVal(symbols)));
    symbols.push(str[i]);
  }
}

std::list<std::string> MathModel::PolishNotation(const std::string &str) {
  std::list<std::string> rpn;
  std::stack<char> symbols;

  for (size_t i = symbols.size(); i < str.length(); ++i) {
    if (std::isdigit(str[i])) {
      GetNumber(rpn, str, i);
    } else if (str[i] == 'x') {
      rpn.push_back("x");
    } else {
      if (FindOper(binop_hash, str[i])) {
        ProcessBinOp(str, i, symbols, rpn);
      } else if (FindOper(unop_hash, str[i])) {
        ProcessUnOp(str, i, symbols);
      }
    }
  }
  while (!symbols.empty())
    rpn.push_back(std::string(1, PopVal(symbols)));
  return rpn;
}

static void CalcBinOp(std::stack<double> &digit, binop func) {
  double lhs, rhs;
  lhs = PopVal(digit);
  rhs = PopVal(digit);
  digit.push(func(lhs, rhs));
}

static void CalcUnOp(std::stack<double> &digit, unop func) {
  digit.push(func(PopVal(digit)));
}

double MathModel::Calculation(std::list<std::string> rpn, double x_value) {
  std::stack<double> digit;
  while (!rpn.empty()) {
    if (std::strtod(rpn.front().c_str(), nullptr) ||
        std::isdigit(rpn.front()[0]))
      digit.push(std::strtod(rpn.front().c_str(), NULL));
    else if (rpn.front()[0] == 'x')
      digit.push(x_value);
    else if (FindOper(binop_hash, rpn.front()[0]))
      CalcBinOp(digit, binop_hash[rpn.front()[0]]);
    else
      CalcUnOp(digit, unop_hash[rpn.front()[0]]);

    rpn.pop_front();
  }

  return PopVal(digit);
}

} // namespace s21
