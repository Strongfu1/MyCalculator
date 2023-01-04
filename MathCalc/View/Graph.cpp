#include "Graph.h"
#include "ui_Graph.h"
namespace s21 {
Graph::Graph(Controller *controller, QWidget *parent)
    : QDialog(parent), ui(new Ui::Graph), controller(controller) {
  ui->setupUi(this);
  setFixedSize(544, 385);
  connect(ui->calculate, &QToolButton::clicked, this, &Graph::PlotGraph);
  ConfigurePlot();
}

void Graph::ConfigurePlot() {
  ui->graph->addGraph();
  ui->graph->xAxis->setLabel("x");
  ui->graph->yAxis->setLabel("y");
  ui->graph->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssDot);
  ui->graph->graph(0)->setPen(QPen(QBrush(Qt::red), 2));
  ui->graph->setInteraction(QCP::iRangeZoom, true);
  ui->graph->setInteraction(QCP::iRangeDrag, true);
}

Graph::~Graph() { delete ui; }

void Graph::GetGraphInfo(std::string str) { expression = std::move(str); }

void Graph::PlotGraph() {
  ui->graph->graph(0)->data()->clear();
  std::vector<std::pair<double, double>> dots = controller->GetGraphPoints(
      expression, ui->min_x->value(), ui->max_x->value());
  if (!dots.empty()) {
    ui->graph->xAxis->setRange(ui->min_x->value(), ui->max_x->value());
    ui->graph->yAxis->setRange(ui->min_y->value(), ui->max_y->value());
    for (auto &i : dots) {
      ui->graph->graph(0)->addData(i.first, i.second);
    }
    ui->graph->replot();
  }
}
} // namespace s21
