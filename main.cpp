#include <QApplication>

#include "MathCalc/View/MathView.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::MathView w;
  w.show();
  return a.exec();
}
