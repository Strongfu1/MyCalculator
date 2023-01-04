#include "MathView.h"

#include <QDebug>
#include <iostream>

#include "ui_MathView.h"
namespace s21 {
MathView::MathView(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MathView), controller(new Controller) {
  ui->setupUi(this);
  deposit = new DepositView(controller, this);
  credit = new CreditView(controller, this);
  graph = new Graph(controller, this);
  //  setFixedSize(QSize(420, 481));       // MAC
  setFixedSize(QSize(420, 502)); // LINUX
  ConnectButtons();
}

MathView::~MathView() {
  delete ui;
  delete controller;
  delete deposit;
  delete credit;
  delete graph;
}

void MathView::ConnectButtons() {
  QLineEdit *&text_area = ui->text_area;
  auto insertText = [&]() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    text_area->insert(button->text());
  };

  for (auto button : findChildren<QPushButton *>()) {
    connect(button, &QPushButton::clicked, this, insertText);
  }

  connect(ui->arrow, &QToolButton::clicked, text_area, &QLineEdit::backspace);
  connect(ui->special, &QToolButton::clicked, text_area, &QLineEdit::clear);
  connect(ui->equals, &QToolButton::clicked, this, &MathView::Calculate);
  connect(ui->graph, &QToolButton::clicked, this, &MathView::MakeGraph);
  connect(this, &MathView::SendGraphInfo, graph, &Graph::GetGraphInfo);

  for (auto action : ui->menu_design->actions()) {
    connect(action, &QAction::triggered, this, &MathView::ChangeDesign);
    connect(action, &QAction::triggered, deposit, &DepositView::ChangeDesign);
    connect(action, &QAction::triggered, credit, &CreditView::ChangeDesign);
  }

  for (auto action : ui->menu_calc->actions()) {
    connect(action, &QAction::triggered, this, &MathView::ChangeWindow);
  }
}

void MathView::ChangeDesign() {
  const QString design = sender()->objectName();
  const std::map<QString, QString> m{{"SeaMelody", "37,150,190"},
                                     {"Panda", "20,201,160"},
                                     {"Koi", "234,176,112"},
                                     {"Sakura", "239,1,120"}};
  const QString &color = m.at(design);

  this->setStyleSheet(
      "s21--Button, #arrow,#special,#x_value {border-image:url(:/" + design +
      "/Key.png);}" + "s21--ColorButton{border-image:url(:/" + design +
      "/ColorKey.png);}" + "#mul, #degree{text-align:top;padding-top:25px;}" +
      "QPushButton:pressed,QToolButton:pressed{color:rgb(" + color + ");}");

  ui->text_area->setStyleSheet("#text_area{border-image: url(:/" + design +
                               "/text_area.png) }");

  ui->equals->setStyleSheet("#equals{background-color:transparent;padding-"
                            "bottom:95;padding-left:5;border-image:url(:/" +
                            design + "/VerticalKey.png);}");
  ui->graph->setStyleSheet("#graph{border-image:url(:/" + design +
                           "/SpecialKey.png);}");
  ui->zero->setStyleSheet(
      "#zero{text-align:left, top;padding-left:15;padding-top:12;border-image: "
      "url(:/" +
      design + "/Zero.png);}");
}

void MathView::ChangeWindow() {
  QWidget *active = QApplication::activeWindow();

  if (active->objectName()[0] != sender()->objectName()[0]) {
    active->hide();
    switch (sender()->objectName()[0].toLatin1()) {
    case 'D': // Deposit
      deposit->show();
      break;
    case 'C': // Credit
      credit->show();
      break;
    default: // Math
      this->show();
      break;
    }
  }
}

void MathView::Calculate() {
  if (!ui->text_area->text().isEmpty()) {
    double answer = controller->Calculate(ui->text_area->text().toStdString(),
                                          ui->x_value->value());
    if (std::isnan(answer))
      ui->text_area->setText("Error");
    else
      ui->text_area->setText(QString::number(answer));
  }
}

void MathView::MakeGraph() {
  emit SendGraphInfo(ui->text_area->text().toStdString());
  graph->exec();
}
} // namespace s21
