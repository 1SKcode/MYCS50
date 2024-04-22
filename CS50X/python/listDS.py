# ARRAYS - LISTS
# Называются LIST. Тут они динамические, походи на связные списки
print("------------------------------------------")

list1 = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
print("list 1: ", list1)

list2 = [x for x in range(2, 19, 2)]
print("list 2: ", list2, "\n")

list1.append(5)
print("Append 5 to the end of the list 1:")
print("list 1: ", list1, "\n")

list1.insert(1, 5)
print("Added 5 in 1 index:")
print("list 1: ", list1, "\n")

list1[len(list1):] = [100]
print("Connecting two lists:")
print("list 1: ", list1, "\n")

list1.insert(len(list1) // 2, 100)
print("Added 100 in the middle: ")
print("list 1: ", list1, "\n")

for i in range(0, len(list1), 1):
    print(f"{i} element: {list1[i]}.")
