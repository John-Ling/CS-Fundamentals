from random import randint

LIST_SIZE = 9

def main():
    list = generate_numbers()
    print(f"Unsorted: {list}")
    bubble_sort(list)
    print(f"Sorted: {list}")

def bubble_sort(arr):
    upperLimit = len(arr)
    swaps = True

    while swaps:
        swaps = False;
        for i in range(1, upperLimit):
            if arr[i - 1] > arr[i]:
                tmp = arr[i - 1]
                arr[i - 1] = arr[i]
                arr[i] = tmp
                swaps = True
        upperLimit -= 1

def generate_numbers():
    list = []
    for i in range(LIST_SIZE):
        list.append(randint(0, 100))
    return list

if __name__ == "__main__":
    main()