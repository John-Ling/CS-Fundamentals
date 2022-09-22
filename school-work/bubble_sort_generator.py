from random import randint

numberOfQuestions = 0

def main():
    generate_questions("bubble_sort_questions.txt")
    while True:
        print("Welcome to the bubble sort generaor")
        print("""
        1: Attempt question
        2: Create question
        3: Quit
        """)
        selection = str(input("Enter your choice: "))
        if selection == "1":
            attempt_question()
        elif selection == "2":
            test()
        elif selection == "3":
            break

def generate_questions(question_file):
    with open(question_file, 'r') as file:
        for line in file:
            print(line.strip())
            produce_answer(line)

def produce_answer(line):
    global numberOfQuestions
    line = line.strip().split(',')
    ascending = True
    if line[0] == 'desc': # order code decides whether answer should be ascending or descending
        ascending = False
    line.pop(0) # remove order code
    swaps = False
    limit = len(line)
    with open("bubble_sort_solutions.txt", 'a') as file:
        while swaps or limit != 0:
            for i in range(limit - 1):
                value1 = int(line[i])   
                value2 = int(line[i + 1])
                if value1 > value2 and ascending:
                    temp = line[i + 1]
                    line[i + 1] = line[i]
                    line[i] = temp 
                    swaps = True
                elif value1 < value2 and not ascending:
                    temp = line[i]
                    line[i] = line[i + 1]
                    line[i + 1] = temp
                    swaps = True
            limit -= 1
            swaps = False
        line = str(line)
        file.write(line)
        file.write('\n')
        numberOfQuestions += 1

def test():
    with open("bubble_sort_questions.txt", 'r') as file:
        numbers = file.readline()
        print(numbers.strip())
        numbers = file.readline()
        print(numbers)

def attempt_question():
    global numberOfQuestions
    questionNumber = randint(1, numberOfQuestions)
    print(questionNumber)
    count = 0
    numbers = ""
    with open("bubble_sort_questions.txt", 'r') as file:
        questionFound = False
        while not questionFound:
            print(count)
            if count == questionNumber:
                break
            else:
                numbers = file.readline()
                count += 1
    numbers = numbers.strip()
    numbers = numbers.split(',')

    # check order code
    orderCode = numbers[0]
    numbers.pop(0)
    print(numbers)

if __name__ == "__main__":
    main()