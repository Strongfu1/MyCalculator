#ifndef SMARTCALC_CREDITCALC_MODEL_CREDITITEMS_H
#define SMARTCALC_CREDITCALC_MODEL_CREDITITEMS_H
#include <vector>
namespace s21 {
enum CreditType { kAnnuitet = 0, kDifferentiate };

struct CreditData {
  std::vector<double> sum;
  std::vector<double> percent;
  double payment;
};
} // namespace s21
#endif // SMARTCALC_CREDITCALC_MODEL_CREDITITEMS_H
