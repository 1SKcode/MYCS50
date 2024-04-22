from cs50 import get_string


def main():
    text = get_string("Text: ")
    gradeCalculation(text)


def gradeCalculation(t):
    length = len(t)
    c_letters = letters_calc(t)
    c_words = words_calc(t)
    c_sentences = sentences_calc(t)

    avgOfLetters = c_letters / c_words * 100
    avgOfSentences = c_sentences / c_words * 100
    index = round(0.0588 * avgOfLetters - 0.296 * avgOfSentences - 15.8)

    if index > 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


def letters_calc(t):
    count = 0
    for char in t:
        if char.isalpha():
            count += 1
    return count


def words_calc(t):
    count = t.count(" ") + 1
    return count


def sentences_calc(t):
    count = t.count("!") + t.count(".") + t.count("?")
    return count


if __name__ == "__main__":
    main()
