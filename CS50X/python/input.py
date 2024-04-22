def mine():
    printBlock(getPosInt())
    ieeemaaieeioo()

def printBlock(n):
    for i in range(n):
        print("#")
        
def getPosInt():
    while True:
        try:
            n = int(input("Ведите положительное число: "))
            if n > 0:
                return n
        except ValueError:
            print("Это не число!")

def ieeemaaieeioo():
    x = getPosInt()
    y = getPosInt()
    for i in range(x):
        for j in range(y):
            print("#", end="")
        print()

mine()
