# This Python file uses the following encoding: utf-8
import sys

from PySide6.QtWidgets import QApplication, QMainWindow, QMessageBox, QPushButton
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

        self.ui.okBtn.clicked.connect(self.on_btn_click)
        self.ui.numberEdit.editingFinished.connect(self.on_focus_lost)


    def on_focus_lost(self):
        number = self.ui.numberEdit.text()
        fingerprint_image_name = f":/materialy/{number}-odcisk.jpg"
        gender_image_name = f":/materialy/{number}-zdjecie.jpg"

        gender_image = QPixmap(gender_image_name)
        if not gender_image.isNull():
            self.ui.genderImage.setPixmap(gender_image)
        else:
            self.ui.genderImage.setPixmap(QPixmap())

        fingerprint_image = QPixmap(fingerprint_image_name)
        if not fingerprint_image.isNull():
            self.ui.fingerprintImage.setPixmap(fingerprint_image)
        else:
            self.ui.fingerprintImage.setPixmap(QPixmap())


    def on_btn_click(self):
        number = self.ui.numberEdit.text().strip()
        name = self.ui.nameEdit.text().strip()
        surname = self.ui.surnameEdit.text().strip()

        blue_eye = self.ui.blueEyesBtn.isChecked()
        green_eye = self.ui.greenEyesBtn.isChecked()
        eye_color = ""
        if blue_eye:
            eye_color = "niebieskie"
        elif green_eye:
            eye_color = "zielone"
        else:
            eye_color = "piwne"

        if not surname or not name or not number:
            QMessageBox.information(self.ui.centralwidget, "", "Wprowadź dane", QMessageBox.StandardButton.Ok)
        else:
            QMessageBox.information(self.ui.centralwidget, "", f"{name} {surname} kolor oczu {eye_color}", QMessageBox.StandardButton.Ok)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    widget = MainWindow()
    widget.show()
    sys.exit(app.exec())
