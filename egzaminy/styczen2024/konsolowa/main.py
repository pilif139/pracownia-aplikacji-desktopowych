def getGender(peselNumber: str):
    isEven = int(peselNumber[9]) % 2
    if isEven:
        return 'K'
    else:
        return 'M'
    
    
PESEL_WEIGTHS = [1, 3, 7, 9, 1, 3, 7, 9, 1, 3]
    
def getControlSum(peselNumber: str):
    sum = 0;
    for (index, num) in enumerate(PESEL_WEIGTHS):
        sum += num * int(peselNumber[index])
        
    modulo = sum % 10
    r = 0
    if modulo != 0:
        r = 10 - modulo
    
    return r == int(peselNumber[10])

         
def main():
    peselInput = input("Podaj numer PESEL:")
    plec = getGender(peselInput)
    if plec == 'K':
        print("Kobieta")
    else:
        print("Męzczyzna")
        
    controlSum = getControlSum(peselInput)
    if controlSum:
        print("Suma kontrolna zgodna")
    else:
        print("Suma kontrolna niezgodna")
    
    
if __name__ == "__main__":
    main()