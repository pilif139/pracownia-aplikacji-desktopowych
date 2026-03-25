import re
import sys

from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import (
    QApplication,
    QGridLayout,
    QLineEdit,
    QMainWindow,
    QPushButton,
    QVBoxLayout,
    QWidget,
)


class CalculatorMainWindow(QMainWindow):
    """Simple calculator window that can be used directly as app main window."""

    def __init__(self) -> None:
        super().__init__()
        self.setWindowTitle("Calculator")
        self.setMinimumSize(320, 420)

        self.display = QLineEdit("0")
        self.display.setReadOnly(True)
        self.display.setAlignment(Qt.AlignmentFlag.AlignRight)
        self.display.setMaxLength(32)
        self.display.setStyleSheet("font-size: 28px; padding: 8px;")

        grid = QGridLayout()
        buttons = [
            ("C", 0, 0),
            ("⌫", 0, 1),
            ("%", 0, 2),
            ("÷", 0, 3),
            ("7", 1, 0),
            ("8", 1, 1),
            ("9", 1, 2),
            ("×", 1, 3),
            ("4", 2, 0),
            ("5", 2, 1),
            ("6", 2, 2),
            ("-", 2, 3),
            ("1", 3, 0),
            ("2", 3, 1),
            ("3", 3, 2),
            ("+", 3, 3),
            ("±", 4, 0),
            ("0", 4, 1),
            (".", 4, 2),
            ("=", 4, 3),
        ]

        for text, row, col in buttons:
            button = QPushButton(text)
            button.setMinimumHeight(58)
            button.setStyleSheet("font-size: 20px;")
            button.clicked.connect(lambda _, value=text: self.on_button_clicked(value))
            grid.addWidget(button, row, col)

        root = QVBoxLayout()
        root.addWidget(self.display)
        root.addLayout(grid)

        container = QWidget()
        container.setLayout(root)
        self.setCentralWidget(container)

    def on_button_clicked(self, value: str) -> None:
        if value == "C":
            self.display.setText("0")
            return

        if value == "⌫":
            current = self.display.text()
            self.display.setText(current[:-1] if len(current) > 1 else "0")
            return

        if value == "±":
            current = self.display.text()
            if current.startswith("-"):
                self.display.setText(current[1:])
            elif current != "0":
                self.display.setText(f"-{current}")
            return

        if value == "=":
            self.evaluate_expression()
            return

        current = self.display.text()
        if current == "0" and value not in {".", "%"}:
            current = ""

        self.display.setText(current + value)

    def evaluate_expression(self) -> None:
        expression = self.display.text().replace("×", "*").replace("÷", "/")

        # Allow only numbers, decimal points, whitespace and math operators.
        if not re.fullmatch(r"[\d\s+\-*/%.()]+", expression):
            self.display.setText("Error")
            return

        try:
            result = eval(expression, {"__builtins__": {}}, {})
            if isinstance(result, float) and result.is_integer():
                result = int(result)
            self.display.setText(str(result))
        except Exception:
            self.display.setText("Error")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = CalculatorMainWindow()
    window.show()
    app.exec()
