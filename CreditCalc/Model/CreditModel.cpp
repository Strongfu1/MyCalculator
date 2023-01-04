#include "CreditModel.h"
using namespace s21;
inline void CreditModel::DataResize(int months) {
  data.percent.resize(months);
  data.sum.resize(months);
}

const CreditData &CreditModel::Annuitet(int months, double sum,
                                        double percent) {
  DataResize(months);
  data.payment =
      sum * (percent + percent / (std::pow(1 + percent, months) - 1));
  for (int i = 0; i < months; ++i) {
    data.percent[i] = sum * percent;
    sum += data.percent[i] - data.payment;
    data.sum[i] = sum;
  }
  return data;
}

const CreditData &CreditModel::Differentiate(int months, double sum,
                                             double percent) {
  DataResize(months);
  data.payment = sum / months;
  for (int i = 0; i < months; ++i) {
    data.percent[i] = sum * percent;
    sum -= data.payment;
    data.sum[i] = sum;
  }
  return data;
}
