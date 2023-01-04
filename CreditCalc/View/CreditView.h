#ifndef SMARTCALC_CREDITCALC_VIEW_CREDITVIEW_H
#define SMARTCALC_CREDITCALC_VIEW_CREDITVIEW_H

#include <QDialog>

#include "../../Controller/Controller.h"
namespace Ui {
class CreditView;
}
namespace s21 {

class CreditView : public QDialog {
  Q_OBJECT

public:
  explicit CreditView(Controller *controller, QWidget *parent = nullptr);
  ~CreditView();
public slots:
  void ChangeDesign();

private:
  Ui::CreditView *ui;
  Controller *controller;

  void Calculate();
};
} // namespace s21
#endif // SMARTCALC_CREDITCALC_VIEW_CREDITVIEW_H
