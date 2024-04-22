print("-------WHILE--------")
i = 0;
while(i < 5):
    print(i)
    i += 1

print("--------FOR-------")

for i in range(5):
    print(i)

print("--------FORadd-------")
a = 5
for i in range(a, 10, 2):
    print(i)

# Замена Do While:


while True:
    try:
        a = input("Input: ")
        if a == "exit":
            break
        a = int(a)
        print(f"{a} * {2} = {a*2}.")
    except ValueError:
        print("It's not a num!")


