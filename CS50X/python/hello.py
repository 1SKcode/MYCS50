s = input("Your name? ")

print(f"Hi, " + s + "!\nLets start!")

a = 0
# a++ - такого тут нет!! Нужно использовать a += 1
a += 1
print(a)

b = int(input("Введите число: "))
if b > a:
    print(f"{b} > {a}")
elif b < a:
    print(f"{b} < {a}")
else:
    print(f"{b} = {a}")

strSogUzn = input("Согласны? Узнали??  --> ").lower()

if strSogUzn == "cогласны":
    print("Вы согласны!")
elif strSogUzn == "узнали":
    print("Вы узнали!")
else:
    print("Вы согласны узнали!!!")

strSogUzn = input("А теперь? Узнали??  --> ").lower()
if strSogUzn in ["с", "согл", "согласен"]:
    print("Вы согласны!")
else: print("Вы НЕ согласны?!")
