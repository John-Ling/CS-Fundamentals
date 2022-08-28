def main():
    arr = [5,9,2,3,4,8,7,1,6]
    bubble_sort(arr)
    print(arr)

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

if __name__ == "__main__":
    main()