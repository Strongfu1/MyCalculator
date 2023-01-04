#ifndef SMARTCALC_DEPOSITCALC_VIEW_DEPOSITVIEW_H
#define SMARTCALC_DEPOSITCALC_VIEW_DEPOSITVIEW_H

#include <QDialog>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QToolButton>

#include "../../Controller/Controller.h"

namespace Ui {
class DepositView;
}
namespace s21 {

class DepositView : public QDialog {
  Q_OBJECT

public:
  explicit DepositView(Controller *controller, QWidget *parent = nullptr);
  ~DepositView();
public slots:
  void ChangeDesign();

private:
  Ui::DepositView *ui;
  Controller *controller;
  QHash<QToolButton *, QHBoxLayout *> transactions_hash;
  void ConnectButtons();

  QHBoxLayout *NewTransaction();
  void AddTransaction(QVBoxLayout *);
  void DeleteTransactionLayout();
  void UpdateTransactionMaxDate();
  void UpdateTransactionMinDate();
  void GetTransactions(std::vector<std::pair<QDate, double>> &vec,
                       QVBoxLayout *layout, int type);
  void Calculate();
};
} // namespace s21

#endif // SMARTCALC_DEPOSITCALC_VIEW_DEPOSITVIEW_H
