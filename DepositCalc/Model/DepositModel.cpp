#include "DepositModel.h"
namespace s21 {
using TransIter = std::vector<std::pair<QDate, double>>::iterator;

inline static QDate SetNextMonth(QDate date) {
  date = date.addMonths(1);
  date.setDate(date.year(), date.month(), 1);
  return date;
}

inline static bool HasTransactionsThisMonth(const TransIter &it,
                                            const TransIter &end, QDate date) {
  return it != end && it->first.month() == date.month() && it->first <= date;
}

inline static double CountDividends(QDate current, QDate to, double sum,
                                    double percent) {
  return sum / current.daysInYear() * current.daysTo(to) * percent;
}

inline void DepositModel::ProcessTransaction(TransIter &it, double &sum,
                                             QDate &date) {
  sum += it->second;
  AddToData(it->first, sum, it->second);
  date = it->first;
  ++it;
}

const std::vector<DepositData> &DepositModel::Deposit(
    double sum, double percent, QDate start_date, int months, double taxes,
    std::vector<std::pair<QDate, double>> &transactions, bool capital) {
  data.clear();

  std::stable_sort(transactions.begin(), transactions.end(),
                   [](const std::pair<QDate, double> &lhs,
                      const std::pair<QDate, double> &rhs) {
                     return lhs.first < rhs.first;
                   });
  auto it = transactions.begin();
  auto end = transactions.end();
  for (int i = 0; i < months; ++i) {
    QDate curr_date = start_date.addMonths(i);
    QDate next_month = SetNextMonth(curr_date);
    long double added = 0;
    double curr_taxes = 0;

    while (HasTransactionsThisMonth(it, end, next_month.addDays(-1))) {
      added += CountDividends(curr_date, it->first, sum, percent);
      ProcessTransaction(it, sum, curr_date);
      if (sum < 0) {
        data.clear();
        return data;
      }
    }
    added += CountDividends(curr_date, next_month, sum, percent);
    while (HasTransactionsThisMonth(it, end, start_date.addMonths(i + 1))) {
      added += CountDividends(curr_date, it->first, sum, percent);
      ProcessTransaction(it, sum, curr_date);
      if (sum < 0) {
        data.clear();
        return data;
      }
    }
    added +=
        CountDividends(curr_date, start_date.addMonths(i + 1), sum, percent);
    if (taxes != 0) {
      curr_taxes = added * taxes;
      added -= curr_taxes;
    }
    if (capital)
      sum += added;
    AddToData(start_date.addMonths(i + 1), sum, added, curr_taxes);
  }
  return data;
}

inline void DepositModel::AddToData(QDate date, double sum, double added,
                                    double taxes) {
  data.emplace_back(std::move(date), std::move(sum), std::move(added),
                    std::move(taxes));
}

} // namespace s21
