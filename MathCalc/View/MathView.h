#ifndef SMARTCALC_MATHCALC_VIEW_MATHVIEW_H
#define SMARTCALC_MATHCALC_VIEW_MATHVIEW_H
#include <QMainWindow>
#include <QPushButton>
#include <memory>

#include "../../Controller/Controller.h"
#include "../../CreditCalc/View/CreditView.h"
#include "../../DepositCalc/View/DepositView.h"
#include "../../Other/Button.h"
#include "../../Other/ColorButton.h"
#include "Graph.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MathView;
}
QT_END_NAMESPACE

namespace s21 {
class MathView : public QMainWindow {
  Q_OBJECT

public:
  MathView(QWidget *parent = nullptr);
  ~MathView();

private:
  Ui::MathView *ui;
  Controller *controller;
  DepositView *deposit;
  CreditView *credit;
  Graph *graph;

  void ConnectButtons();
  void ChangeDesign();
  void ChangeWindow();
  void Calculate();
  void MakeGraph();
signals:
  void SendGraphInfo(std::string str);
};
} // namespace s21

#endif // SMARTCALC_MATHCALC_VIEW_MATHVIEW_H
