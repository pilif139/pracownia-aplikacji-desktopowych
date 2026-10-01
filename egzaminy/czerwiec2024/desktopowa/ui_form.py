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
from PySide6.QtWidgets import (QApplication, QHBoxLayout, QLabel, QMainWindow,
    QMenuBar, QPushButton, QSizePolicy, QStatusBar,
    QVBoxLayout, QWidget)
import rc_resources

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(957, 435)
        MainWindow.setWindowTitle(u"MojeD\u017awi\u0119ki. Wykona\u0142: 00000000")
        MainWindow.setStyleSheet(u"background-color: #2E8B57")
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.widget = QWidget(self.centralwidget)
        self.widget.setObjectName(u"widget")
        self.widget.setGeometry(QRect(0, -10, 961, 311))
        self.horizontalLayout_2 = QHBoxLayout(self.widget)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.horizontalLayout_2.setContentsMargins(30, 0, 30, 0)
        self.prevButton = QPushButton(self.widget)
        self.prevButton.setObjectName(u"prevButton")
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.prevButton.sizePolicy().hasHeightForWidth())
        self.prevButton.setSizePolicy(sizePolicy)
        self.prevButton.setMaximumSize(QSize(80, 70))
        self.prevButton.setBaseSize(QSize(80, 70))
        self.prevButton.setAutoFillBackground(False)
        self.prevButton.setStyleSheet(u"")
        icon = QIcon()
        icon.addFile(u":/images/obraz3.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.prevButton.setIcon(icon)
        self.prevButton.setIconSize(QSize(70, 70))

        self.horizontalLayout_2.addWidget(self.prevButton)

        self.label = QLabel(self.widget)
        self.label.setObjectName(u"label")
        self.label.setMaximumSize(QSize(200, 200))
        self.label.setPixmap(QPixmap(u":/images/obraz.png"))
        self.label.setScaledContents(True)

        self.horizontalLayout_2.addWidget(self.label)

        self.verticalLayout = QVBoxLayout()
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.artistLabel = QLabel(self.widget)
        self.artistLabel.setObjectName(u"artistLabel")
        font = QFont()
        font.setPointSize(50)
        font.setItalic(False)
        font.setKerning(False)
        self.artistLabel.setFont(font)
        self.artistLabel.setStyleSheet(u"color: white;")

        self.verticalLayout.addWidget(self.artistLabel)

        self.albumTitleLabel = QLabel(self.widget)
        self.albumTitleLabel.setObjectName(u"albumTitleLabel")
        font1 = QFont()
        font1.setPointSize(30)
        font1.setItalic(True)
        font1.setKerning(True)
        self.albumTitleLabel.setFont(font1)
        self.albumTitleLabel.setStyleSheet(u"color: white;\n"
"")

        self.verticalLayout.addWidget(self.albumTitleLabel)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.songsCountLabel = QLabel(self.widget)
        self.songsCountLabel.setObjectName(u"songsCountLabel")
        font2 = QFont()
        font2.setPointSize(20)
        self.songsCountLabel.setFont(font2)
        self.songsCountLabel.setStyleSheet(u"color: #61D918;")

        self.horizontalLayout.addWidget(self.songsCountLabel)

        self.yearLabel = QLabel(self.widget)
        self.yearLabel.setObjectName(u"yearLabel")
        self.yearLabel.setFont(font2)
        self.yearLabel.setStyleSheet(u"color: #61D918;")

        self.horizontalLayout.addWidget(self.yearLabel)


        self.verticalLayout.addLayout(self.horizontalLayout)


        self.horizontalLayout_2.addLayout(self.verticalLayout)

        self.nextButton = QPushButton(self.widget)
        self.nextButton.setObjectName(u"nextButton")
        sizePolicy.setHeightForWidth(self.nextButton.sizePolicy().hasHeightForWidth())
        self.nextButton.setSizePolicy(sizePolicy)
        self.nextButton.setMaximumSize(QSize(80, 70))
        self.nextButton.setBaseSize(QSize(80, 70))
        self.nextButton.setAutoFillBackground(False)
        self.nextButton.setStyleSheet(u"")
        icon1 = QIcon()
        icon1.addFile(u":/images/obraz2.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.nextButton.setIcon(icon1)
        self.nextButton.setIconSize(QSize(70, 70))

        self.horizontalLayout_2.addWidget(self.nextButton)

        self.widget1 = QWidget(self.centralwidget)
        self.widget1.setObjectName(u"widget1")
        self.widget1.setGeometry(QRect(200, 300, 281, 61))
        self.horizontalLayout_3 = QHBoxLayout(self.widget1)
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.horizontalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.downloadsLabel = QLabel(self.widget1)
        self.downloadsLabel.setObjectName(u"downloadsLabel")
        self.downloadsLabel.setFont(font2)
        self.downloadsLabel.setStyleSheet(u"color: #61D918;\n"
"")

        self.horizontalLayout_3.addWidget(self.downloadsLabel)

        self.downloadButton = QPushButton(self.widget1)
        self.downloadButton.setObjectName(u"downloadButton")
        font3 = QFont()
        font3.setPointSize(20)
        font3.setBold(True)
        self.downloadButton.setFont(font3)
        self.downloadButton.setAutoFillBackground(False)
        self.downloadButton.setStyleSheet(u"background-color: #61D918;\n"
"color: black;\n"
"")

        self.horizontalLayout_3.addWidget(self.downloadButton)

        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 957, 38))
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        self.prevButton.setText("")
        self.label.setText("")
        self.artistLabel.setText(QCoreApplication.translate("MainWindow", u"TextLabel", None))
        self.albumTitleLabel.setText(QCoreApplication.translate("MainWindow", u"TextLabel", None))
        self.songsCountLabel.setText(QCoreApplication.translate("MainWindow", u"TextLabel", None))
        self.yearLabel.setText(QCoreApplication.translate("MainWindow", u"TextLabel", None))
        self.nextButton.setText("")
        self.downloadsLabel.setText(QCoreApplication.translate("MainWindow", u"TextLabel", None))
        self.downloadButton.setText(QCoreApplication.translate("MainWindow", u"Pobierz", None))
        pass
    # retranslateUi

