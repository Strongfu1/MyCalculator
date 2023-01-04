QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QT_LOGGING_RULES="*.debug=true"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MathCalc/Model/Validator.cpp \
    MathCalc/View/Graph.cpp \
    MathCalc/View/qcustomplot.cpp \
    main.cpp \
    Controller/Controller.cpp \
    MathCalc/Model/MathModel.cpp \
    MathCalc/View/MathView.cpp \
    CreditCalc/Model/CreditModel.cpp \
    CreditCalc/View/CreditView.cpp \
    DepositCalc/Model/DepositModel.cpp \
    DepositCalc/View/DepositView.cpp


HEADERS += \
    DepositCalc/Model/DepositItem.h \
    MathCalc/Model/Validator.h \
    MathCalc/View/Graph.h \
    MathCalc/View/qcustomplot.h \
    Other/Button.h \
    Other/ColorButton.h \
    Controller/Controller.h \
    MathCalc/Model/MathModel.h \
    MathCalc/View/MathView.h \
    CreditCalc/Model/CreditItems.h \
    CreditCalc/Model/CreditModel.h \
    CreditCalc/View/CreditView.h \
    DepositCalc/Model/DepositModel.h \
    DepositCalc/View/DepositView.h \

FORMS += \
    MathCalc/View/Graph.ui \
    MathCalc/View/MathView.ui \
    CreditCalc/View/CreditView.ui \
    DepositCalc/View/DepositView.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icons/Icons.qrc

DISTFILES += \
    Icons/Icon.icns
