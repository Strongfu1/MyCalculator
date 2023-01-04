#include "Controller.h"

#include "../CreditCalc/Model/CreditModel.h"
#include "../DepositCalc/Model/DepositModel.h"
#include "../MathCalc/Model/MathModel.h"
namespace s21 {

Controller::Controller()
    : math(std::make_unique<MathModel>()),
      credit(std::make_unique<CreditModel>()),
      deposit(std::make_unique<DepositModel>()) {}

Controller::~Controller(){};

const CreditData &Controller::Credit(int months, double sum, double percent,
                                     int type) {
  if (type == kAnnuitet)
    return credit->Annuitet(months, sum, percent);
  else
    return credit->Differentiate(months, sum, percent);
}

const std::vector<DepositData> &Controller::Deposit(
    double sum, double percent, QDate start_date, int months, double taxes,
    std::vector<std::pair<QDate, double>> &transactions, bool capital) {
  return deposit->Deposit(sum, percent / 100, start_date, months, taxes / 100,
                          transactions, capital);
}

double Controller::Calculate(std::string str, double x_value) {
  str = math->RemoveUnaryMinus(str);
  if (math->Validate(str))
    return math->Calculation(math->PolishNotation(str), x_value);
  else
    return std::nan("");
}

std::vector<std::pair<double, double>>
Controller::GetGraphPoints(std::string str, double start, double finish) {
  str = math->RemoveUnaryMinus(str);
  std::vector<std::pair<double, double>> dots;
  if (math->Validate(str)) {
    std::list<std::string> rpn = math->PolishNotation(str);
    long double step = (finish - start) / 1000000;
    dots.reserve(1000000);
    while (start < finish) {
      dots.emplace_back(start, math->Calculation(rpn, start));
      start += step;
    }
  }
  return dots;
}

} // namespace s21
