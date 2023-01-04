#ifndef SMARTCALC_OTHER_COLORBUTTON_H
#define SMARTCALC_OTHER_COLORBUTTON_H
#include <QPushButton>
namespace s21 {
class ColorButton : public QPushButton {
  Q_OBJECT
public:
  ColorButton(QWidget *parent = nullptr) : QPushButton(parent) {}
  ~ColorButton(){};
};
} // namespace s21
#endif // SMARTCALC_OTHER_COLORBUTTON_H
