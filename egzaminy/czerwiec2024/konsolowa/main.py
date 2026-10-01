from Album import Album


def loadAlbums(filename: str):
    file = open(filename, mode="r", encoding="utf-8-sig")

    lines = file.read()
    albumsData = [line.split("\n") for line in lines.split("\n\n")]
    albums: list[Album] = []

    for albumData in albumsData:
        album = Album(albumData[0], albumData[1], int(albumData[2]), int(albumData[3]), int(albumData[4]))
        albums.append(album)

    file.close()
    return albums


def printAlbums(albums: list[Album]):
    for album in albums:
        print(album)
        print()


def main():
    albums = loadAlbums("../pliki2/Data.txt")
    printAlbums(albums)

if __name__ == "__main__":
    main()
