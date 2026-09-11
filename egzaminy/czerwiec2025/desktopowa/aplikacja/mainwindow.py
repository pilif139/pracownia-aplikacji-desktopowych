# This Python file uses the following encoding: utf-8
import sys
from PySide6.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget, QLabel, QSlider, QHBoxLayout, QPushButton
from PySide6.QtCore import Qt


class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Wzornik kolorów RGB. Wykonał: 00000000")

        root = QVBoxLayout()

        self.bigColorBox = QWidget()

        self.bigColorBox.setMinimumWidth(600)
        self.bigColorBox.setMinimumHeight(300)
        self.bigColorBox.setStyleSheet("background-color: white;")

        labelText = QLabel()
        labelText.setText("Dobierz kolor suwakami i zapisz przyciskiem:")

        root.addWidget(self.bigColorBox)
        root.addWidget(labelText)

        self.redSlider = QSlider(Qt.Horizontal)
        self.greenSlider = QSlider(Qt.Horizontal)
        self.blueSlider = QSlider(Qt.Horizontal)
        self.redValueLabel = QLabel()
        self.greenValueLabel = QLabel()
        self.blueValueLabel = QLabel()
        sliders = [(self.redSlider, "R", self.redValueLabel), (self.greenSlider, "G", self.greenValueLabel), (self.blueSlider, "B", self.blueValueLabel)]
        for slider, label, valueLabel in sliders:
            sliderLayout = QHBoxLayout()
            sliderLabel = QLabel()
            sliderLabel.setText(label)
            slider.setRange(0, 255)
            slider.setValue(255)
            slider.valueChanged.connect(self.update_big_box_color)

            valueLabel.setText("255")

            sliderLayout.addWidget(sliderLabel)
            sliderLayout.addWidget(slider)
            sliderLayout.addWidget(valueLabel)
            root.addLayout(sliderLayout)


        getValuesBtn = QPushButton()
        getValuesBtn.setText("Pobierz")
        getValuesBtn.setStyleSheet("background-color: Peru; color: black; border: 2px solid black;")
        getValuesBtn.setMinimumSize(200, 50)
        getValuesBtn.clicked.connect(self.update_small_box_color)
        root.addWidget(getValuesBtn, alignment=Qt.AlignmentFlag.AlignCenter)

        self.smallColorBox = QLabel()
        self.smallColorBox.setMinimumWidth(200)
        self.smallColorBox.setMinimumHeight(50)
        self.smallColorBox.setStyleSheet("background-color: white; color: black;")
        self.smallColorBox.setText("255, 255, 255")
        root.addWidget(self.smallColorBox, alignment=Qt.AlignmentFlag.AlignCenter)

        container = QWidget()
        container.setLayout(root)
        container.setStyleSheet("background-color: Cornsilk; color: black;")
        self.setCentralWidget(container)


    def update_small_box_color(self):
        r = self.redSlider.value()
        g = self.greenSlider.value()
        b = self.blueSlider.value()

        self.smallColorBox.setText(f"{r}, {g}, {b}")
        self.smallColorBox.setStyleSheet(f"background-color: rgb({r}, {g}, {b})")


    def update_big_box_color(self):
        r = self.redSlider.value()
        g = self.greenSlider.value()
        b = self.blueSlider.value()

        self.redValueLabel.setText(str(r))
        self.greenValueLabel.setText(str(g))
        self.blueValueLabel.setText(str(b))

        self.bigColorBox.setStyleSheet(f"background-color: rgb({r}, {g}, {b})")




if __name__ == "__main__":
    app = QApplication([])
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
