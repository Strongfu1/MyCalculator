#ifndef SMARTCALC_DEPOSITCALC_MODEL_DEPOSITMODEL_H
#define SMARTCALC_DEPOSITCALC_MODEL_DEPOSITMODEL_H
#include "DepositItem.h"
namespace s21 {
class DepositModel {
  using TransIter = std::vector<std::pair<QDate, double>>::iterator;

public:
  DepositModel() = default;
  ~DepositModel() = default;

  const std::vector<DepositData> &
  Deposit(double sum, double percent, QDate start_date, int months,
          double taxes, std::vector<std::pair<QDate, double>> &transactions,
          bool capital);

private:
  std::vector<DepositData> data;
  void ProcessTransaction(TransIter &it, double &sum, QDate &date);
  void AddToData(QDate date, double sum, double added, double taxes = 0);
};

} // namespace s21

#endif // SMARTCALC_MODEL_DEPOSITCALC_DEPOSITMODEL_H
