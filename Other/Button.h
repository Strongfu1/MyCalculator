#ifndef SMARTCALC_OTHER_BUTTON_H
#define SMARTCALC_OTHER_BUTTON_H
#include <QPushButton>
namespace s21 {
class Button : public QPushButton {
  Q_OBJECT
public:
  Button(QWidget *parent = nullptr) : QPushButton(parent) {}
  ~Button(){};
};
} // namespace s21
#endif // SMARTCALC_OTHER_BUTTON_H
