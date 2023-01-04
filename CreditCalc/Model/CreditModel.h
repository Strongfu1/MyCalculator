#ifndef SMARTCALC_CREDITCALC_MODEL_CREDITMODEL_H
#define SMARTCALC_CREDITCALC_MODEL_CREDITMODEL_H
#include <cmath>
#include <vector>

#include "CreditItems.h"
namespace s21 {

class CreditModel {
public:
  CreditModel() = default;
  ~CreditModel() = default;

  const CreditData &Annuitet(int months, double sum, double percent);
  const CreditData &Differentiate(int months, double sum, double percent);

private:
  void DataResize(int months);
  CreditData data;
};
} // namespace s21

#endif // CREDITMODEL_H
