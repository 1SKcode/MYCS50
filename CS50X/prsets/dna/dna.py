import csv
import sys


def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)
    # Чтение файла базы данных в переменную
    db_path = sys.argv[1]
    with open(db_path, "r") as csvfile:
        csv_reader = csv.DictReader(csvfile)
        dict_list = list(csv_reader)

    # Чтение файла с последовательностью ДНК в переменную
    seq_path = sys.argv[2]
    with open(seq_path, "r") as file:
        sequence = file.read()

    # Поиск самого длинного соответствия каждого STR в последовательности ДНК
    max_counts = [0] * (len(csv_reader.fieldnames) - 1)

    for i in range(1, len(csv_reader.fieldnames)):
        STR = csv_reader.fieldnames[i]

        # Используем функцию longest_match для нахождения самой длинной последовательности
        longest_run = longest_match(sequence, STR)

        # Обновление max_counts
        max_counts[i - 1] = longest_run

    # Проверка соответствия профилей в базе данных
    for profile in dict_list:
        matches = 0
        for i in range(1, len(csv_reader.fieldnames)):
            if int(max_counts[i - 1]) == int(profile[csv_reader.fieldnames[i]]):
                matches += 1
            if matches == (len(csv_reader.fieldnames) - 1):
                print(profile["name"])
                sys.exit(0)

    print("No match")


def longest_match(sequence, subsequence):
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    for i in range(sequence_length):
        count = 0
        while True:
            start = i + count * subsequence_length
            end = start + subsequence_length

            if sequence[start:end] == subsequence:
                count += 1
            else:
                break

        longest_run = max(longest_run, count)

    return longest_run


if __name__ == "__main__":
    main()
