# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'form.ui'
##
## Created by: Qt User Interface Compiler version 6.10.2
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
from PySide6.QtWidgets import (QApplication, QDialog, QGroupBox, QHBoxLayout,
    QLabel, QLineEdit, QPushButton, QRadioButton,
    QSizePolicy, QTextEdit, QVBoxLayout, QWidget)

class Ui_window(object):
    def setupUi(self, window):
        if not window.objectName():
            window.setObjectName(u"window")
        window.resize(800, 600)
        self.verticalLayout_2 = QVBoxLayout(window)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.verticalLayout_3 = QVBoxLayout()
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.horizontalLayout_4 = QHBoxLayout()
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.label = QLabel(window)
        self.label.setObjectName(u"label")

        self.horizontalLayout_4.addWidget(self.label)

        self.nazwaProduktu = QLineEdit(window)
        self.nazwaProduktu.setObjectName(u"nazwaProduktu")

        self.horizontalLayout_4.addWidget(self.nazwaProduktu)


        self.verticalLayout_3.addLayout(self.horizontalLayout_4)

        self.groupBox = QGroupBox(window)
        self.groupBox.setObjectName(u"groupBox")
        self.verticalLayoutWidget_3 = QWidget(self.groupBox)
        self.verticalLayoutWidget_3.setObjectName(u"verticalLayoutWidget_3")
        self.verticalLayoutWidget_3.setGeometry(QRect(9, 39, 331, 101))
        self.verticalLayout_4 = QVBoxLayout(self.verticalLayoutWidget_3)
        self.verticalLayout_4.setObjectName(u"verticalLayout_4")
        self.verticalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.spozywcze = QRadioButton(self.verticalLayoutWidget_3)
        self.spozywcze.setObjectName(u"spozywcze")
        self.spozywcze.setChecked(True)

        self.verticalLayout_4.addWidget(self.spozywcze)

        self.elektronika = QRadioButton(self.verticalLayoutWidget_3)
        self.elektronika.setObjectName(u"elektronika")
        self.elektronika.setChecked(False)

        self.verticalLayout_4.addWidget(self.elektronika)

        self.kosmetyki = QRadioButton(self.verticalLayoutWidget_3)
        self.kosmetyki.setObjectName(u"kosmetyki")

        self.verticalLayout_4.addWidget(self.kosmetyki)


        self.verticalLayout_3.addWidget(self.groupBox)

        self.addBtn = QPushButton(window)
        self.addBtn.setObjectName(u"addBtn")

        self.verticalLayout_3.addWidget(self.addBtn)


        self.horizontalLayout.addLayout(self.verticalLayout_3)

        self.verticalLayout = QVBoxLayout()
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.listaProduktow = QTextEdit(window)
        self.listaProduktow.setObjectName(u"listaProduktow")
        self.listaProduktow.setReadOnly(True)

        self.verticalLayout.addWidget(self.listaProduktow)

        self.liczbaProduktow = QLabel(window)
        self.liczbaProduktow.setObjectName(u"liczbaProduktow")
        font = QFont()
        font.setPointSize(14)
        font.setBold(True)
        self.liczbaProduktow.setFont(font)

        self.verticalLayout.addWidget(self.liczbaProduktow)


        self.horizontalLayout.addLayout(self.verticalLayout)


        self.verticalLayout_2.addLayout(self.horizontalLayout)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.clearListBtn = QPushButton(window)
        self.clearListBtn.setObjectName(u"clearListBtn")

        self.horizontalLayout_2.addWidget(self.clearListBtn)


        self.verticalLayout_2.addLayout(self.horizontalLayout_2)


        self.retranslateUi(window)

        QMetaObject.connectSlotsByName(window)
    # setupUi

    def retranslateUi(self, window):
        window.setWindowTitle(QCoreApplication.translate("window", u"window", None))
        self.label.setText(QCoreApplication.translate("window", u"Nazwa produktu", None))
        self.nazwaProduktu.setText(QCoreApplication.translate("window", u"Chleb", None))
        self.groupBox.setTitle(QCoreApplication.translate("window", u"Kategoria", None))
        self.spozywcze.setText(QCoreApplication.translate("window", u"Spo\u017cywcze", None))
        self.elektronika.setText(QCoreApplication.translate("window", u"Elektronika", None))
        self.kosmetyki.setText(QCoreApplication.translate("window", u"Kosmetyki", None))
        self.addBtn.setText(QCoreApplication.translate("window", u"Dodaj", None))
        self.liczbaProduktow.setText(QCoreApplication.translate("window", u"Liczba produkt\u00f3w: 0", None))
        self.clearListBtn.setText(QCoreApplication.translate("window", u"Wyczy\u015b\u0107 list\u0119", None))
    # retranslateUi

