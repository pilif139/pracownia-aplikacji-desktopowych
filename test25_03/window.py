# This Python file uses the following encoding: utf-8
import sys

from PySide6.QtWidgets import QApplication, QDialog, QMessageBox

# Important:
# You need to run the following command to generate the ui_form.py file
#     pyside6-uic form.ui -o ui_form.py, or
#     pyside2-uic form.ui -o ui_form.py
from ui_form import Ui_window

class window(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.ui = Ui_window()
        self.ui.setupUi(self)
        self.adjustSize()
        self.setFixedSize(self.sizeHint())
        self.licznik = 0

        self.ui.clearListBtn.clicked.connect(self.wyczysc_liste)
        self.ui.addBtn.clicked.connect(self.dodaj_produkt)


    def dodaj_produkt(self):
        nazwa = self.ui.nazwaProduktu.text().strip()

        if not nazwa:
            QMessageBox.warning(self, "Błąd", "Proszę podać nazwę produktu.")
            return

        kategoria = self.get_kategoria()

        wpis = f"{nazwa} ({kategoria})"

        self.ui.listaProduktow.append(wpis)
        self.licznik+=1
        self.ui.liczbaProduktow.setText(f"Liczba produktów: {self.licznik}")

        self.ui.nazwaProduktu.clear()
        self.ui.nazwaProduktu.setFocus()

    def wyczysc_liste(self):
        self.ui.listaProduktow.clear()
        self.licznik = 0
        self.ui.liczbaProduktow.setText("Liczba produktów: 0")

    def get_kategoria(self):
        if self.ui.spozywcze.isChecked():
            return "Spożywcze"
        if self.ui.elektronika.isChecked():
            return "Elektronika"
        if self.ui.kosmetyki.isChecked():
            return "Kosmetyki"


if __name__ == "__main__":
    app = QApplication(sys.argv)
    widget = window()
    widget.show()
    sys.exit(app.exec())
