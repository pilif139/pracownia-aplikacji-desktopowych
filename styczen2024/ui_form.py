# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'form.ui'
##
## Created by: Qt User Interface Compiler version 6.11.2
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
    QLineEdit, QMainWindow, QMenuBar, QPushButton,
    QRadioButton, QSizePolicy, QStatusBar, QVBoxLayout,
    QWidget)
import rc_resources

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(1000, 519)
        MainWindow.setMinimumSize(QSize(1000, 0))
        MainWindow.setAutoFillBackground(False)
        MainWindow.setStyleSheet(u"QMainWindow{\n"
"	background-color: CadetBlue;\n"
"}\n"
"QMessageBox{\n"
"	background-color: white;\n"
"	color: black;\n"
"}\n"
"QLineEdit, QPushButton{\n"
"background-color: Azure;\n"
"color: black;\n"
"}\n"
"QLabel, QPushButton, QRadioButton{\n"
"	color: black;\n"
"}\n"
"QGroupBox{\n"
"	color: black;\n"
"}\n"
"QPushButton{\n"
"	margin: 0 150;\n"
"}")
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.gridLayout = QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName(u"gridLayout")
        self.gridLayout_2 = QGridLayout()
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.gridLayout_2.setHorizontalSpacing(6)
        self.gridLayout_2.setContentsMargins(30, 30, 30, 30)
        self.groupBox = QGroupBox(self.centralwidget)
        self.groupBox.setObjectName(u"groupBox")
        self.verticalLayout = QVBoxLayout(self.groupBox)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.blueEyesBtn = QRadioButton(self.groupBox)
        self.blueEyesBtn.setObjectName(u"blueEyesBtn")
        self.blueEyesBtn.setChecked(True)

        self.verticalLayout.addWidget(self.blueEyesBtn)

        self.greenEyesBtn = QRadioButton(self.groupBox)
        self.greenEyesBtn.setObjectName(u"greenEyesBtn")

        self.verticalLayout.addWidget(self.greenEyesBtn)

        self.brownEyesBtn = QRadioButton(self.groupBox)
        self.brownEyesBtn.setObjectName(u"brownEyesBtn")

        self.verticalLayout.addWidget(self.brownEyesBtn)


        self.gridLayout_2.addWidget(self.groupBox, 3, 0, 1, 3)

        self.numberLabel = QLabel(self.centralwidget)
        self.numberLabel.setObjectName(u"numberLabel")
        self.numberLabel.setMinimumSize(QSize(150, 0))

        self.gridLayout_2.addWidget(self.numberLabel, 0, 0, 1, 2)

        self.numberEdit = QLineEdit(self.centralwidget)
        self.numberEdit.setObjectName(u"numberEdit")
        self.numberEdit.setStyleSheet(u"")

        self.gridLayout_2.addWidget(self.numberEdit, 0, 2, 1, 1)

        self.nameLabel = QLabel(self.centralwidget)
        self.nameLabel.setObjectName(u"nameLabel")

        self.gridLayout_2.addWidget(self.nameLabel, 1, 0, 1, 1)

        self.surnameLabel = QLabel(self.centralwidget)
        self.surnameLabel.setObjectName(u"surnameLabel")

        self.gridLayout_2.addWidget(self.surnameLabel, 2, 0, 1, 1)

        self.nameEdit = QLineEdit(self.centralwidget)
        self.nameEdit.setObjectName(u"nameEdit")

        self.gridLayout_2.addWidget(self.nameEdit, 1, 2, 1, 1)

        self.surnameEdit = QLineEdit(self.centralwidget)
        self.surnameEdit.setObjectName(u"surnameEdit")

        self.gridLayout_2.addWidget(self.surnameEdit, 2, 2, 1, 1)


        self.gridLayout.addLayout(self.gridLayout_2, 3, 5, 1, 1)

        self.gridLayout_3 = QGridLayout()
        self.gridLayout_3.setObjectName(u"gridLayout_3")
        self.fingerprintImage = QLabel(self.centralwidget)
        self.fingerprintImage.setObjectName(u"fingerprintImage")
        self.fingerprintImage.setPixmap(QPixmap(u":/materialy/000-odcisk.jpg"))
        self.fingerprintImage.setScaledContents(True)
        self.fingerprintImage.setMargin(50)

        self.gridLayout_3.addWidget(self.fingerprintImage, 0, 1, 1, 1)

        self.genderImage = QLabel(self.centralwidget)
        self.genderImage.setObjectName(u"genderImage")
        self.genderImage.setMaximumSize(QSize(16777215, 16777215))
        self.genderImage.setBaseSize(QSize(0, 180))
        self.genderImage.setPixmap(QPixmap(u":/materialy/000-zdjecie.jpg"))
        self.genderImage.setScaledContents(True)
        self.genderImage.setMargin(50)

        self.gridLayout_3.addWidget(self.genderImage, 0, 0, 1, 1)

        self.okBtn = QPushButton(self.centralwidget)
        self.okBtn.setObjectName(u"okBtn")
        self.okBtn.setMinimumSize(QSize(400, 50))
        self.okBtn.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_3.addWidget(self.okBtn, 1, 0, 1, 2)


        self.gridLayout.addLayout(self.gridLayout_3, 3, 6, 1, 3)

        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 1000, 21))
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"Wprowadzanie danych do paszportu. Wykona\u0142: 000000000", None))
        self.groupBox.setTitle(QCoreApplication.translate("MainWindow", u"Kolor oczu", None))
        self.blueEyesBtn.setText(QCoreApplication.translate("MainWindow", u"niebieskie", None))
        self.greenEyesBtn.setText(QCoreApplication.translate("MainWindow", u"zielone", None))
        self.brownEyesBtn.setText(QCoreApplication.translate("MainWindow", u"piwne", None))
        self.numberLabel.setText(QCoreApplication.translate("MainWindow", u"Numer", None))
        self.nameLabel.setText(QCoreApplication.translate("MainWindow", u"Imi\u0119", None))
        self.surnameLabel.setText(QCoreApplication.translate("MainWindow", u"Nazwisko", None))
        self.fingerprintImage.setText("")
        self.genderImage.setText("")
        self.okBtn.setText(QCoreApplication.translate("MainWindow", u"OK", None))
    # retranslateUi

