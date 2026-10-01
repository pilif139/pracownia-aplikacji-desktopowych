# This Python file uses the following encoding: utf-8
import sys

from PySide6.QtWidgets import QApplication, QMainWindow
from PySide6.QtCore import QFile, QIODeviceBase

# Important:
# You need to run the following command to generate the ui_form.py file
#     pyside6-uic form.ui -o ui_form.py, or
#     pyside2-uic form.ui -o ui_form.py
from ui_form import Ui_MainWindow
from Album import Album

def loadAlbums(filename: str):
    file = QFile(filename)

    if not file.open(QIODeviceBase.OpenModeFlag.ReadOnly | QIODeviceBase.OpenModeFlag.Text):
        raise FileNotFoundError(f"Can't open {filename}: {file.errorString()}")

    lines = bytes(file.readAll().data()).decode("utf-8-sig")
    albumsData = [line.split("\n") for line in lines.split("\n\n")]
    albums: list[Album] = []

    for albumData in albumsData:
        album = Album(albumData[0], albumData[1], int(albumData[2]), int(albumData[3]), int(albumData[4]))
        albums.append(album)

    file.close()
    return albums

class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.albums = loadAlbums(":/data/Data.txt")
        self.set_current_album(self.albums[0])

        self.current_album_index = 0

        self.ui.prevButton.clicked.connect(self.on_prev_btn_clicked)
        self.ui.nextButton.clicked.connect(self.on_next_btn_clicked)
        self.ui.downloadButton.clicked.connect(self.on_download_btn_clicked)

    def set_current_album(self, album: Album):
        self.ui.albumTitleLabel.setText(album.name)
        self.ui.artistLabel.setText(album.artist)
        self.ui.songsCountLabel.setText(f"{str(album.songsNumber)} utworów")
        self.ui.downloadsLabel.setText(str(album.downloadNumber))
        self.ui.yearLabel.setText(str(album.year))


    def on_prev_btn_clicked(self):
        if self.current_album_index == 0:
            self.current_album_index = len(self.albums) - 1
        else:
            self.current_album_index -= 1

        self.set_current_album(self.albums[self.current_album_index])


    def on_next_btn_clicked(self):
        if self.current_album_index == len(self.albums) - 1:
            self.current_album_index = 0
        else:
            self.current_album_index += 1

        self.set_current_album(self.albums[self.current_album_index])


    def on_download_btn_clicked(self):
        currentAlbum = self.albums[self.current_album_index]
        currentAlbum.downloadNumber += 1
        self.ui.downloadsLabel.setText(str(currentAlbum.downloadNumber))




if __name__ == "__main__":
    app = QApplication(sys.argv)
    widget = MainWindow()
    widget.show()
    sys.exit(app.exec())
