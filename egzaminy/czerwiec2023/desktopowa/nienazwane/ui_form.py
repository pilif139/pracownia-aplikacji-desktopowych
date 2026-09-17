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
from PySide6.QtWidgets import (QApplication, QGridLayout, QGroupBox, QLabel,
    QLayout, QLineEdit, QMainWindow, QMenuBar,
    QPushButton, QRadioButton, QSizePolicy, QStatusBar,
    QVBoxLayout, QWidget)
import rc_resources

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(748, 387)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.gridLayout = QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName(u"gridLayout")
        self.sprawdzCeneBtn = QPushButton(self.centralwidget)
        self.sprawdzCeneBtn.setObjectName(u"sprawdzCeneBtn")

        self.gridLayout.addWidget(self.sprawdzCeneBtn, 1, 0, 1, 2)

        self.przesylkaImage = QLabel(self.centralwidget)
        self.przesylkaImage.setObjectName(u"przesylkaImage")
        self.przesylkaImage.setPixmap(QPixmap(u":/materialy/list.png"))
        self.przesylkaImage.setScaledContents(True)
        self.przesylkaImage.setAlignment(Qt.AlignmentFlag.AlignCenter)

        self.gridLayout.addWidget(self.przesylkaImage, 2, 0, 1, 1)

        self.cena = QLabel(self.centralwidget)
        self.cena.setObjectName(u"cena")
        font = QFont()
        font.setPointSize(20)
        font.setBold(True)
        self.cena.setFont(font)
        self.cena.setScaledContents(False)
        self.cena.setAlignment(Qt.AlignmentFlag.AlignHCenter|Qt.AlignmentFlag.AlignTop)

        self.gridLayout.addWidget(self.cena, 2, 1, 1, 1)

        self.groupBox = QGroupBox(self.centralwidget)
        self.groupBox.setObjectName(u"groupBox")
        self.verticalLayout = QVBoxLayout(self.groupBox)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.pocztowkaBtn = QRadioButton(self.groupBox)
        self.pocztowkaBtn.setObjectName(u"pocztowkaBtn")
        self.pocztowkaBtn.setChecked(True)

        self.verticalLayout.addWidget(self.pocztowkaBtn)

        self.listBtn = QRadioButton(self.groupBox)
        self.listBtn.setObjectName(u"listBtn")

        self.verticalLayout.addWidget(self.listBtn)

        self.paczkaBtn = QRadioButton(self.groupBox)
        self.paczkaBtn.setObjectName(u"paczkaBtn")

        self.verticalLayout.addWidget(self.paczkaBtn)


        self.gridLayout.addWidget(self.groupBox, 0, 0, 1, 2)

        self.zatwierdzBtn = QPushButton(self.centralwidget)
        self.zatwierdzBtn.setObjectName(u"zatwierdzBtn")

        self.gridLayout.addWidget(self.zatwierdzBtn, 3, 0, 1, 4)

        self.groupBox_2 = QGroupBox(self.centralwidget)
        self.groupBox_2.setObjectName(u"groupBox_2")
        self.verticalLayout_2 = QVBoxLayout(self.groupBox_2)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.verticalLayout_2.setSizeConstraint(QLayout.SizeConstraint.SetDefaultConstraint)
        self.ulicaLabel = QLabel(self.groupBox_2)
        self.ulicaLabel.setObjectName(u"ulicaLabel")
        self.ulicaLabel.setMaximumSize(QSize(16777215, 20))

        self.verticalLayout_2.addWidget(self.ulicaLabel)

        self.ulicaNrEdit = QLineEdit(self.groupBox_2)
        self.ulicaNrEdit.setObjectName(u"ulicaNrEdit")

        self.verticalLayout_2.addWidget(self.ulicaNrEdit)

        self.kodPocztowyLabel = QLabel(self.groupBox_2)
        self.kodPocztowyLabel.setObjectName(u"kodPocztowyLabel")
        self.kodPocztowyLabel.setMaximumSize(QSize(16777215, 20))

        self.verticalLayout_2.addWidget(self.kodPocztowyLabel)

        self.kodPocztowyEdit = QLineEdit(self.groupBox_2)
        self.kodPocztowyEdit.setObjectName(u"kodPocztowyEdit")

        self.verticalLayout_2.addWidget(self.kodPocztowyEdit)

        self.miastoLabel = QLabel(self.groupBox_2)
        self.miastoLabel.setObjectName(u"miastoLabel")
        self.miastoLabel.setMaximumSize(QSize(16777215, 20))

        self.verticalLayout_2.addWidget(self.miastoLabel)

        self.miastoEdit = QLineEdit(self.groupBox_2)
        self.miastoEdit.setObjectName(u"miastoEdit")

        self.verticalLayout_2.addWidget(self.miastoEdit)


        self.gridLayout.addWidget(self.groupBox_2, 0, 2, 3, 2)

        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 748, 39))
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"Nadaj przesy\u0142k\u0119. PESEL: 0000000", None))
        self.sprawdzCeneBtn.setText(QCoreApplication.translate("MainWindow", u"Sprawd\u017a cen\u0119", None))
        self.przesylkaImage.setText("")
        self.cena.setText(QCoreApplication.translate("MainWindow", u"Cena:", None))
        self.groupBox.setTitle(QCoreApplication.translate("MainWindow", u"Rodzaj Przesy\u0142ki", None))
        self.pocztowkaBtn.setText(QCoreApplication.translate("MainWindow", u"Poczt\u00f3wka", None))
        self.listBtn.setText(QCoreApplication.translate("MainWindow", u"List", None))
        self.paczkaBtn.setText(QCoreApplication.translate("MainWindow", u"Paczka", None))
        self.zatwierdzBtn.setText(QCoreApplication.translate("MainWindow", u"Zatwierd\u017a", None))
        self.groupBox_2.setTitle(QCoreApplication.translate("MainWindow", u"Dane adresowe", None))
        self.ulicaLabel.setText(QCoreApplication.translate("MainWindow", u"Ulica z numerem", None))
        self.kodPocztowyLabel.setText(QCoreApplication.translate("MainWindow", u"Kod pocztowy", None))
        self.miastoLabel.setText(QCoreApplication.translate("MainWindow", u"Miasto", None))
    # retranslateUi

