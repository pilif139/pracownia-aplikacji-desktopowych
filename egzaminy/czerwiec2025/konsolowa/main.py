from random import randint


def draw_numbers():
    print("Ile wygenerować losowań?")
    n = int(input())
    drawnNumbers: list[list[int]] = []
    for i in range(n):
        drawnNumbers.append([])
        for j in range(6):
           while(True):
                randomNumber = randint(1, 49)
                if randomNumber not in drawnNumbers[i]:
                    drawnNumbers[i].append(randomNumber)
                    break

    return drawnNumbers


def get_numbers_count(drawnNumbers: list[list[int]]):
    counts = {}
    for i in drawnNumbers:
        for j in i:
            if j not in counts:
                counts[j] = 1
            else:
                counts[j] += 1
    return counts

# nazwa funkcji: show_results
# opis funkcji: Funkcja wyświetla wylosowane liczby oraz pokazuje ilość wystąpień kazdej z liczb we wszystkich turach
# parametry: drawnNumbers - tablica dwuwymiarowa zawierająca wylosowane liczby
# zwracany typ i opis: brak
# autor: Filip Kasperski
def show_results(drawnNumbers: list[list[int]]):
    print("Zestawy wylosowanych liczb:")
    for i, draw in enumerate(drawnNumbers):
        print(f"Losowanie {i}: ", end="")
        for j, number in enumerate(draw):
            endChar = ', '
            if j == 5:
                endChar = '\n'
            print(number, end=endChar)

    counts = get_numbers_count(drawnNumbers)
    for i in range(1, 50):
        print(f"Wystąpienia liczby {i}: {counts.get(i, 0)}")



def main():
    numbers = draw_numbers()
    show_results(numbers)


if __name__ == "__main__":
    main()
