#ifndef SMARTCALC_CONTROLLER_CONTROLLER_H
#define SMARTCALC_CONTROLLER_CONTROLLER_H
#include <cmath>
#include <iostream>
#include <memory>

#include "../CreditCalc/Model/CreditItems.h"
#include "../DepositCalc/Model/DepositItem.h"
namespace s21 {
class MathModel;
class CreditModel;
class DepositModel;
struct DepositData;
class Controller {
public:
  Controller();
  ~Controller();

  const CreditData &Credit(int months, double sum, double percent, int type);
  const std::vector<DepositData> &
  Deposit(double sum, double percent, QDate start_date, int months,
          double taxes, std::vector<std::pair<QDate, double>> &transactions,
          bool capital);
  double Calculate(std::string str, double x_value);
  std::vector<std::pair<double, double>>
  GetGraphPoints(std::string str, double start, double finish);

private:
  // Using pImpl to get faster compile time and to get stable ABI
  std::unique_ptr<MathModel> math;
  std::unique_ptr<CreditModel> credit;
  std::unique_ptr<DepositModel> deposit;
};
} // namespace s21

#endif // SMARTCALC_CONTROLLER_CONTROLLER_H
