# This Python file uses the following encoding: utf-8
import sys

from PySide6.QtWidgets import QApplication, QMainWindow, QMessageBox
from PySide6.QtGui import QPixmap

# Important:
# You need to run the following command to generate the ui_form.py file
#     pyside6-uic form.ui -o ui_form.py, or
#     pyside2-uic form.ui -o ui_form.py
from ui_form import Ui_MainWindow

class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.ui.sprawdzCeneBtn.clicked.connect(self.sprawdz_cene)
        self.ui.zatwierdzBtn.clicked.connect(self.weryfikuj_dane)


    def sprawdz_cene(self):
        if self.ui.paczkaBtn.isChecked():
            self.ui.przesylkaImage.setPixmap(QPixmap(u":/materialy/paczka.png"))
            self.ui.cena.setText("Cena: 10 zł")
        elif self.ui.listBtn.isChecked():
            self.ui.przesylkaImage.setPixmap(QPixmap(u":/materialy/list.png"))
            self.ui.cena.setText("Cena: 1,5 zł")
        else:
            self.ui.przesylkaImage.setPixmap(QPixmap(u":/materialy/pocztowka.png"))
            self.ui.cena.setText("Cena: 1 zł")
            
            
    def weryfikuj_dane(self):
        kod_pocztowy = self.ui.kodPocztowyEdit.text()
        if kod_pocztowy.isnumeric() and len(kod_pocztowy) is 5:
            QMessageBox.information(self.ui.centralwidget, "Wprowadzono dane", "Dane przesyłki zostały wprowadzone")
        elif len(kod_pocztowy) is not 5:
            QMessageBox.warning(self.ui.centralwidget, "Błąd", "Nieprawidłowa liczba cyfr w kodzie pocztowym")
        elif not kod_pocztowy.isnumeric():
            QMessageBox.warning(self.ui.centralwidget, "Błąd", "Kod pocztowy powinien się składać z samych cyfr")
        else:
            print("błąd")



if __name__ == "__main__":
    app = QApplication(sys.argv)
    widget = MainWindow()
    widget.show()
    sys.exit(app.exec())
