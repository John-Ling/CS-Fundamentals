def main():
    arr = [2,5,3,8,7,4,9,1,6]
    insertion_sort(arr)
    print(arr)

def insertion_sort(arr):
    for i in range(1, len(arr)):
        val = arr[i]
        ptr = i - 1
        while arr[ptr] > val and ptr >= 0:
            arr[ptr + 1] = arr[ptr] # swap the original
            ptr -= 1
        arr[ptr + 1] = val 

if __name__ == "__main__":
    main()