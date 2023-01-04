#ifndef SMARTCALC_MATHCALC_VIEW_GRAPH_H
#define SMARTCALC_MATHCALC_VIEW_GRAPH_H

#include "../../Controller/Controller.h"
#include <QDialog>
namespace Ui {
class Graph;
}

namespace s21 {
class Graph : public QDialog {
  Q_OBJECT

public:
  explicit Graph(Controller *controller, QWidget *parent = nullptr);
  ~Graph();

public slots:
  void GetGraphInfo(std::string str);

private:
  Ui::Graph *ui;
  Controller *controller;
  std::string expression;
  void PlotGraph();
  void ConfigurePlot();
};
} // namespace s21
#endif // SMARTCALC_MATHCALC_VIEW_GRAPH_H
