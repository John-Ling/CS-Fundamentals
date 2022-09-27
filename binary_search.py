def main():
    list = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    index = binary_search(list, 9)
    if index == -1:
        print("Could not find value")
    else:
        print(f"Found value at index {index}")
        
def binary_search(list, value):
    lowestIndex = 0
    highestIndex = len(list) - 1
    while lowestIndex != highestIndex:
        mid = round((lowestIndex + highestIndex) / 2) # get middle index

        if value < list[mid]:
            highestIndex = mid - 1 
        elif value > list[mid]:
            lowestIndex = mid + 1
        elif value == list[mid]:
            return mid
        
    return -1

if __name__ == "__main__":
    main() 