def main():
    arr = [7,2,4,9,1,3,5,6,8]
    insertion_sort(arr)
    print(arr)

def insertion_sort(arr):
    for i in range(1, len(arr)):
        val = arr[i]
        ptr = i - 1
        while arr[ptr] > val and ptr >= 0:
            arr[ptr + 1] = arr[ptr]
            ptr -= 1
        arr[ptr + 1] = val

if __name__ == "__main__":
    main()