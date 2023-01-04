#ifndef SMARTCALC_MATHCALC_MODEL_MATHMODEL_H
#define SMARTCALC_MATHCALC_MODEL_MATHMODEL_H
#include <cmath>
#include <list>
#include <string>
#include <unordered_map>

#include "Validator.h"
namespace s21 {
class MathModel {
  typedef double (*unop)(double);
  typedef double (*binop)(double, double);

public:
  MathModel();
  ~MathModel();
  MathModel(const MathModel &) = delete;
  MathModel(MathModel &&) = delete;
  MathModel &operator=(const MathModel &) = delete;
  MathModel &operator=(MathModel &&) = delete;
  bool Validate(const std::string &str);
  std::string RemoveUnaryMinus(std::string str);
  std::list<std::string> PolishNotation(const std::string &str);
  double Calculation(std::list<std::string> rpn, double x_value);

private:
  Validator *validator;
  std::unordered_map<char, unop> unop_hash{
      {'c', std::cos},  {'s', std::sin},   {'t', std::tan},
      {'o', std::acos}, {'r', std::asin},  {'a', std::atan},
      {'n', std::log},  {'l', std::log10}, {'q', std::sqrt}};
  std::unordered_map<char, binop> binop_hash{
      {'+', [](double lhs, double rhs) { return lhs + rhs; }},
      {'-', [](double lhs, double rhs) { return rhs - lhs; }},
      {'*', [](double rhs, double lhs) { return rhs * lhs; }},
      {'/', [](double lhs, double rhs) { return rhs / lhs; }},
      {'^', [](double lhs, double rhs) { return std::pow(rhs, lhs); }},
      {'%', [](double lhs, double rhs) { return std::fmod(rhs, lhs); }},
      {'(', nullptr},
      {')', nullptr}};

  std::unordered_map<char, int> priority{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2},
                                         {'%', 2}, {'^', 3}, {'s', 4}, {'n', 4},
                                         {'l', 4}, {'q', 4}, {'r', 4}, {'o', 4},
                                         {'a', 4}, {'c', 4}, {'t', 4}};

  std::unordered_map<char, int> func_len{{'n', 1}, {'l', 2}, {'q', 3},
                                         {'r', 3}, {'o', 3}, {'a', 3},
                                         {'c', 2}, {'s', 2}, {'t', 2}};
  void ProcessBinOp(const std::string &str, size_t &i,
                    std::stack<char> &symbols, std::list<std::string> &rpn);
  void ProcessUnOp(const std::string &str, size_t &i,
                   std::stack<char> &symbols);
};
} // namespace s21
#endif // SMARTCALC_MODEL_MATHCALC_MATHMODEL_H
