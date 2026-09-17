from math import sqrt


def searchPrimes(array: list[bool]):
    n = len(array)
    limit = int(sqrt(n)) + 1
    for i in range(2, limit):
        if array[i]:
            for j in range(i * i, n, i):
                array[j] = False


def main():
    arrayOfPrimes: list[bool] = [True] * 100
    searchPrimes(arrayOfPrimes)
    for index, prime in enumerate(arrayOfPrimes):
        if index >= 2 and prime:
            print(index, end=" ")

    return


if __name__ == "__main__":
    main()
