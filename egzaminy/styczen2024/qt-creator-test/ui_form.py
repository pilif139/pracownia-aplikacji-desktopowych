# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'form.ui'
##
## Created by: Qt User Interface Compiler version 6.10.3
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QGroupBox, QHBoxLayout, QLabel,
    QLineEdit, QMainWindow, QMenuBar, QRadioButton,
    QSizePolicy, QStatusBar, QVBoxLayout, QWidget)

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(800, 600)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.horizontalLayout = QHBoxLayout(self.centralwidget)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.verticalLayout = QVBoxLayout()
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.numerLabel = QLabel(self.centralwidget)
        self.numerLabel.setObjectName(u"numerLabel")

        self.horizontalLayout_2.addWidget(self.numerLabel)

        self.numerLineEdit = QLineEdit(self.centralwidget)
        self.numerLineEdit.setObjectName(u"numerLineEdit")

        self.horizontalLayout_2.addWidget(self.numerLineEdit)


        self.verticalLayout.addLayout(self.horizontalLayout_2)

        self.horizontalLayout_21 = QHBoxLayout()
        self.horizontalLayout_21.setObjectName(u"horizontalLayout_21")
        self.imieLabel = QLabel(self.centralwidget)
        self.imieLabel.setObjectName(u"imieLabel")

        self.horizontalLayout_21.addWidget(self.imieLabel)

        self.imieLineEdit = QLineEdit(self.centralwidget)
        self.imieLineEdit.setObjectName(u"imieLineEdit")

        self.horizontalLayout_21.addWidget(self.imieLineEdit)


        self.verticalLayout.addLayout(self.horizontalLayout_21)

        self.horizontalLayout_22 = QHBoxLayout()
        self.horizontalLayout_22.setObjectName(u"horizontalLayout_22")
        self.nazwiskoLabel = QLabel(self.centralwidget)
        self.nazwiskoLabel.setObjectName(u"nazwiskoLabel")

        self.horizontalLayout_22.addWidget(self.nazwiskoLabel)

        self.nazwiskoLineEdit = QLineEdit(self.centralwidget)
        self.nazwiskoLineEdit.setObjectName(u"nazwiskoLineEdit")

        self.horizontalLayout_22.addWidget(self.nazwiskoLineEdit)


        self.verticalLayout.addLayout(self.horizontalLayout_22)

        self.groupBox = QGroupBox(self.centralwidget)
        self.groupBox.setObjectName(u"groupBox")
        self.verticalLayout_3 = QVBoxLayout(self.groupBox)
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.niebieskieBtn = QRadioButton(self.groupBox)
        self.niebieskieBtn.setObjectName(u"niebieskieBtn")

        self.verticalLayout_3.addWidget(self.niebieskieBtn)

        self.zieloneBtn = QRadioButton(self.groupBox)
        self.zieloneBtn.setObjectName(u"zieloneBtn")

        self.verticalLayout_3.addWidget(self.zieloneBtn)

        self.piwneBtn = QRadioButton(self.groupBox)
        self.piwneBtn.setObjectName(u"piwneBtn")

        self.verticalLayout_3.addWidget(self.piwneBtn)


        self.verticalLayout.addWidget(self.groupBox)


        self.horizontalLayout.addLayout(self.verticalLayout)

        self.label = QLabel(self.centralwidget)
        self.label.setObjectName(u"label")

        self.horizontalLayout.addWidget(self.label)

        self.verticalLayout_2 = QVBoxLayout()
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")

        self.horizontalLayout.addLayout(self.verticalLayout_2)

        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 800, 30))
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"Wprowadzanie danych do paszportu. Wykona\u0142: 0000000", None))
        self.numerLabel.setText(QCoreApplication.translate("MainWindow", u"Numer", None))
        self.imieLabel.setText(QCoreApplication.translate("MainWindow", u"Imi\u0119", None))
        self.nazwiskoLabel.setText(QCoreApplication.translate("MainWindow", u"Nazwisko", None))
        self.groupBox.setTitle(QCoreApplication.translate("MainWindow", u"Kolor oczu", None))
        self.niebieskieBtn.setText(QCoreApplication.translate("MainWindow", u"niebieskie", None))
        self.zieloneBtn.setText(QCoreApplication.translate("MainWindow", u"zielone", None))
        self.piwneBtn.setText(QCoreApplication.translate("MainWindow", u"piwne", None))
        self.label.setText(QCoreApplication.translate("MainWindow", u"TextLabel", None))
    # retranslateUi

