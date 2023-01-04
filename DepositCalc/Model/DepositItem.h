#ifndef SMARTCALC_DEPOSITCALC_MODEL_DEPOSITITEM_H
#define SMARTCALC_DEPOSITCALC_MODEL_DEPOSITITEM_H
#include <QDate>
namespace s21 {
struct DepositData {
  DepositData(QDate date, double sum, double change, double taxes)
      : date(date), sum(sum), change(change), taxes(taxes){};
  QDate date;
  double sum;
  double change;
  double taxes;
};
} // namespace s21
#endif // SMARTCALC_DEPOSITCALC_MODEL_DEPOSITITEM_H
