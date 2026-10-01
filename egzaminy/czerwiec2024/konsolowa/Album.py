class Album:
    def __init__(self, artist: str, name: str, songsNumber: int, year: int, downloadNumber: int) -> None:
        self.artist = artist
        self.name = name
        self.songsNumber = songsNumber
        self.year = year
        self.downloadNumber = downloadNumber


    def __str__(self):
        return f"{self.artist}\n{self.name}\n{self.songsNumber}\n{self.year}\n{self.downloadNumber}"
