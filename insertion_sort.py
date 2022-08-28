def main():
    arr = [2,5,3,8,7,4,9,1,6]
    insertion_sort(arr)
    print(arr)

def insertion_sort(arr):
    for i in range(1, len(arr)):
        val = arr[i] # save the inital state of the current index as it will be overwritte when swapping
        ptr = i - 1 # left adjacent index of i
        while arr[ptr] > val and ptr >= 0:
            arr[ptr + 1] = arr[ptr] # swap the current index i (i = ptr + 1) with the left adjacent index
            ptr -= 1
            # repeat this until front of list is reached (repeat until ptr >= 0)
            # or the left adjacent value is smaller than the moving value ( repeat until arr[ptr] > val)
        arr[ptr + 1] = val 

if __name__ == "__main__":
    main()