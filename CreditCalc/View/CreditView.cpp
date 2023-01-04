#include "CreditView.h"

#include "ui_CreditView.h"
using namespace s21;
CreditView::CreditView(Controller *controller, QWidget *parent)
    : QDialog(parent), ui(new Ui::CreditView), controller(controller) {
  ui->setupUi(this);
  ui->credit_type_group->setId(ui->annuitet, kAnnuitet);
  ui->credit_type_group->setId(ui->differentiated, kDifferentiate);
  connect(ui->calculate, &QToolButton::clicked, this, &CreditView::Calculate);
}

CreditView::~CreditView() { delete ui; }

void CreditView::ChangeDesign() {
  this->setStyleSheet("#CreditView {border-image: url(:/" +
                      sender()->objectName() +
                      "/Credit.png) 0 0 0 0 stretch stretch;}");
}

void CreditView::Calculate() {
  const CreditData &data = controller->Credit(
      ui->time->value(), ui->credit_sum->value(),
      ui->percent->value() / (100 * 12), ui->credit_type_group->checkedId());

  ui->table->clearContents();
  ui->table->setRowCount(ui->time->value());
  auto new_item = [](double num) -> QTableWidgetItem * {
    return new QTableWidgetItem(QString::number(num));
  };

  for (int i = 0; i < ui->time->value(); ++i) {
    ui->table->setItem(i, 0, new_item(data.payment));
    ui->table->setItem(i, 1, new_item(data.percent[i]));
    ui->table->setItem(i, 2, new_item(data.sum[i]));
  }
  ui->table->item(ui->time->value() - 1, 2)->setText("0");
}
