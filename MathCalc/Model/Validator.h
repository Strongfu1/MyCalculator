#ifndef S21_VALIDATOR
#define S21_VALIDATOR
#include <regex>
#include <stack>
namespace s21 {
class Validator {
public:
  Validator() {}
  ~Validator() {}
  bool Validate(std::string str);

private:
  const std::regex num{"^\\(*((\\d+\\.?\\d*)|x)\\)*",
                       std::regex_constants::ECMAScript};
  const std::regex oper{"^[\\*\\+\\-/\\^%]\\(*",
                        std::regex_constants::ECMAScript};
  const std::regex func{"^(log|ln|sin|cos|tan|acos|asin|atan|sqrt)\\(",
                        std::regex_constants::ECMAScript};
  bool ValNum(std::string str);
  bool ValOper(std::string str);
  bool ValFunc(std::string str);
  bool CheckParenthesis(const std::string &str);
  std::smatch matched;
};

} // namespace s21
#endif
