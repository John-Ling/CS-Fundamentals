from math import sqrt
import sys
# find all prime numbers both iteratively and recursively 

def main():
    sys.setrecursionlimit(1500)
    #iterative(start=1, end=1000)
    recursive(start=1, end=1000)
    
def is_prime(num):
    factors = 0
    for i in range(1, num + 1):
        if num % i == 0: 
            factors += 1
    if factors == 2:
        return True
    else:
        return False

def iterative(start, end):
    for i in range(start, end + 1):
        if is_prime(i):
            print(i)

def recursive(start, end):
    if is_prime(start): 
        print(start)
    if start == end:
        return 
    else:
        recursive(start + 1, end)

        
if __name__ == "__main__":
    main()