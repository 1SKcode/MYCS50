while True:
    try:
        h = int(input("Height: "))
        if h >= 1 and h <= 8:
            break
    except ValueError:
        print("It's not a num")

for i in range(0, h, 1):
    spaces = i + 1

    while spaces < h:
        print(" ", end="")
        spaces += 1

    hashesLeft = i + 1
    while hashesLeft > 0:
        print("#", end="")
        hashesLeft -= 1

    print("  ", end="")

    hashesRight = i + 1
    while hashesRight > 0:
        print("#", end="")
        hashesRight -= 1

    print()
