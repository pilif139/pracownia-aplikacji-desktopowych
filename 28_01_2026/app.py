import sys

from PyQt6.QtCore import QSize, Qt
from PyQt6.QtGui import QAction
from PyQt6.QtWidgets import (
    QApplication,
    QDialog,
    QLabel,
    QLineEdit,
    QMainWindow,
    QMenu,
    QPushButton,
    QVBoxLayout,
    QWidget,
)

from calculator_window import CalculatorMainWindow
from customdialog import CustomDialog


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setMouseTracking(True)
        self.label = QLabel(self)
        self.label.setMouseTracking(True)
        self.input = QLineEdit(self)
        self.input.textChanged.connect(self.label.setText)

        self.button_is_checked = True

        self.setWindowTitle("Hello World!")
        self.button = QPushButton("Wcisnij mnie!")
        self.button.setCheckable(True)
        self.button.clicked.connect(self.the_button_was_clicked)
        self.button.clicked.connect(self.the_button_was_toggled)
        self.button.setChecked(self.button_is_checked)

        self.dialogButton = QPushButton("Otworz dialog")
        self.dialogButton.clicked.connect(self.open_dialog)

        self.setFixedSize(QSize(400, 300))
        self.setMinimumSize(QSize(100, 100))
        self.setMaximumSize(QSize(800, 600))

        layout = QVBoxLayout(self)
        layout.addWidget(self.label)
        layout.addWidget(self.input)
        layout.addWidget(self.button)
        layout.addWidget(self.dialogButton)

        container = QWidget()
        container.setLayout(layout)

        self.setCentralWidget(container)

    def open_dialog(self):
        dialog = CustomDialog(self)
        dialog.exec()

    def the_button_was_clicked(self):
        self.button.setText("You clicked me!")
        self.button.setEnabled(False)

    def the_button_was_toggled(self, checked):
        self.button_is_checked = checked
        if checked:
            print("Button is checked")
        else:
            print("Button is unchecked")

    def mouseMoveEvent(self, a0):
        self.label.setText("mouseMoveEvent")

    def mousePressEvent(self, a0):
        if a0 is None:
            return
        if a0.button() == Qt.MouseButton.LeftButton:
            # handle the left-button press in here
            self.label.setText("mousePressEvent LEFT")
        elif a0.button() == Qt.MouseButton.MiddleButton:
            # handle the middle-button press in here.
            self.label.setText("mousePressEvent MIDDLE")
        elif a0.button() == Qt.MouseButton.RightButton:
            # handle the right-button press in here.
            self.label.setText("mousePressEvent RIGHT")

    def mouseReleaseEvent(self, a0):
        if a0 is None:
            return
        if a0.button() == Qt.MouseButton.LeftButton:
            self.label.setText("mouseReleaseEvent LEFT")

        elif a0.button() == Qt.MouseButton.MiddleButton:
            self.label.setText("mouseReleaseEvent MIDDLE")

        elif a0.button() == Qt.MouseButton.RightButton:
            self.label.setText("mouseReleaseEvent RIGHT")

    def mouseDoubleClickEvent(self, a0):
        if a0 is None:
            return
        if a0.button() == Qt.MouseButton.LeftButton:
            self.label.setText("mouseDoubleClickEvent LEFT")

        elif a0.button() == Qt.MouseButton.MiddleButton:
            self.label.setText("mouseDoubleClickEvent MIDDLE")

        elif a0.button() == Qt.MouseButton.RightButton:
            self.label.setText("mouseDoubleClickEvent RIGHT")

    def contextMenuEvent(self, event) -> None:
        if event is None:
            return
        context = QMenu(self)
        context.addAction(QAction("Action 1", self))
        context.addAction(QAction("Action 2", self))
        context.exec(event.globalPos())


app = QApplication(sys.argv)

window = CalculatorMainWindow()
window.show()

app.exec()
