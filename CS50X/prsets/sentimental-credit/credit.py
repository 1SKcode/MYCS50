from cs50 import get_int


def main():
    num = get_int("Number: ")
    if is_valid(num):
        card_type = identify_card(num)
        print(card_type)
    else:
        print("INVALID")


def is_valid(num):
    return get_sum(num) % 10 == 0


def identify_card(num):
    num_str = str(num)
    length = len(num_str)

    # AMEX
    if length == 15 and (num_str.startswith("34") or num_str.startswith("37")):
        return "AMEX"
    # MASTERCARD
    elif length == 16 and 51 <= int(num_str[0:2]) <= 55:
        return "MASTERCARD"
    # VISA
    elif (length == 13 or length == 16) and num_str.startswith("4"):
        return "VISA"
    else:
        return "INVALID"


def get_sum(num):
    summation = 0
    i = 1
    digit = 0
    digit1 = 0
    while num // i > 0:
        digit = 2 * ((num % (i * 100)) // (i * 10))
        digit1 = (num % (i * 10)) // i
        summation += digit1
        i *= 100
        if digit // 10 == 1:
            num1 = digit % 10 + digit // 10
            summation += num1
        else:
            summation += digit
    return summation


if __name__ == "__main__":
    main()
