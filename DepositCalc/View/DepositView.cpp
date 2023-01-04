#include "DepositView.h"

#include <QAction>

#include "../Model/DepositItem.h"
#include "ui_DepositView.h"
namespace s21 {
DepositView::DepositView(Controller *controller, QWidget *parent)
    : QDialog(parent), ui(new Ui::DepositView), controller(controller) {
  ui->setupUi(this);
  ConnectButtons();
}

DepositView::~DepositView() { delete ui; }

void DepositView::ConnectButtons() {
  connect(ui->new_add, &QPushButton::clicked, this, [this]() {
    AddTransaction(
        qobject_cast<QVBoxLayout *>(ui->add_scroll_area_widgets->layout()));
  });
  connect(ui->new_withdraw, &QPushButton::clicked, this, [this]() {
    AddTransaction(qobject_cast<QVBoxLayout *>(
        ui->withdraw_scroll_area_widgets->layout()));
  });
  connect(ui->deposit_length, &QSpinBox::valueChanged, this,
          &DepositView::UpdateTransactionMaxDate);
  connect(ui->deposit_date, &QDateEdit::dateChanged, this,
          &DepositView::UpdateTransactionMinDate);
  connect(ui->calculate, &QPushButton::clicked, this, &DepositView::Calculate);
}

void DepositView::UpdateTransactionMaxDate() {
  QDate max_date =
      ui->deposit_date->date().addMonths(ui->deposit_length->value());
  for (auto i : transactions_hash.values()) {
    qobject_cast<QDateEdit *>(i->itemAt(0)->widget())->setMaximumDate(max_date);
  }
}

void DepositView::UpdateTransactionMinDate() {
  QDate min_date = ui->deposit_date->date();
  for (auto i : transactions_hash.values()) {
    qobject_cast<QDateEdit *>(i->itemAt(0)->widget())->setMinimumDate(min_date);
  }
  UpdateTransactionMaxDate();
}

static QDateEdit *NewTransDate(QDate min, int deposit_length) {
  QDateEdit *date_edit = new QDateEdit;
  date_edit->setCalendarPopup(true);
  date_edit->setFixedSize(102, 21);
  date_edit->setDisplayFormat("d/M/yyyy");
  date_edit->setMinimumDate(min);
  date_edit->setMaximumDate(min.addMonths(deposit_length));
  return date_edit;
}

static QToolButton *NewTransDelete() {
  QToolButton *button = new QToolButton;
  button->setText("X");
  button->setFixedSize(21, 21);
  return button;
}

static QDoubleSpinBox *NewTransSpinBox() {
  QDoubleSpinBox *spin_box = new QDoubleSpinBox;
  spin_box->setFixedSize(98, 25);
  spin_box->setMinimum(1);
  spin_box->setMaximum(1e308);
  spin_box->setSingleStep(1000);
  spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);
  return spin_box;
}

void DepositView::DeleteTransactionLayout() {
  QHBoxLayout *layout =
      transactions_hash.take(qobject_cast<QToolButton *>(sender()));
  QLayoutItem *item;

  while ((item = layout->takeAt(0)))
    delete item->widget();

  delete layout;
}

QHBoxLayout *DepositView::NewTransaction() {
  QHBoxLayout *layout = new QHBoxLayout;
  layout->setSpacing(6);

  QToolButton *trans_delete = NewTransDelete();
  connect(trans_delete, &QToolButton::clicked, this,
          &DepositView::DeleteTransactionLayout);

  transactions_hash.insert(trans_delete, layout);

  layout->addWidget(
      NewTransDate(ui->deposit_date->date(), ui->deposit_length->value()));
  layout->addWidget(NewTransSpinBox());
  layout->addWidget(trans_delete);

  return layout;
}

void DepositView::AddTransaction(QVBoxLayout *layout_to_add) {
  QHBoxLayout *transaction = NewTransaction();
  layout_to_add->addLayout(transaction);
}

void DepositView::ChangeDesign() {
  this->setStyleSheet("#DepositView {border-image: url(:/" +
                      sender()->objectName() +
                      "/Deposit.png) 0 0 0 0 stretch stretch;}");
}

void DepositView::GetTransactions(std::vector<std::pair<QDate, double>> &vec,
                                  QVBoxLayout *layout, int type) {
  for (auto i : layout->findChildren<QHBoxLayout *>()) {
    vec.emplace_back(
        qobject_cast<QDateEdit *>(i->itemAt(0)->widget())->date(),
        qobject_cast<QDoubleSpinBox *>(i->itemAt(1)->widget())->value() * type);
  }
}

void DepositView::Calculate() {
  std::vector<std::pair<QDate, double>> transactions;
  GetTransactions(
      transactions,
      qobject_cast<QVBoxLayout *>(ui->add_scroll_area_widgets->layout()), 1);
  GetTransactions(
      transactions,
      qobject_cast<QVBoxLayout *>(ui->withdraw_scroll_area_widgets->layout()),
      -1);
  const std::vector<DepositData> &data = controller->Deposit(
      ui->deposit_sum->value(), ui->deposit_percent->value(),
      ui->deposit_date->date(), ui->deposit_length->value(), ui->taxes->value(),
      transactions, ui->capitalization->isChecked());

  if (!data.size()) {
    ui->total_sum->setText("ERROR");
    return;
  }
  ui->total_sum->setText(
      QString::number(data.back().sum - ui->deposit_sum->value()));
  ui->table->clearContents();
  ui->table->setRowCount(ui->deposit_length->value() + transactions.size());
  auto new_item = [](QString str) -> QTableWidgetItem * {
    return new QTableWidgetItem(str);
  };

  for (int i = 0; i < ui->table->rowCount(); ++i) {
    ui->table->setItem(i, 0, new_item(data[i].date.toString("dd.MM.yyyy")));
    ui->table->setItem(i, 1, new_item(QString::number(data[i].change)));
    ui->table->setItem(i, 2, new_item(QString::number(data[i].sum)));
    ui->table->setItem(i, 3, new_item(QString::number(data[i].taxes)));
  }
}

} // namespace s21
