from random import randint

def main():
    VALUES = [7, 45, 72, 12, 59, 43, 67, 83, 21, 13]
    linkedList = Linked_List(VALUES)

    # example use of a linked list
    linkedList.insert(50, 0)
    linkedList.search(43)
    linkedList.delete(linkedList.maxIndex)
    linkedList.display()

class Linked_List:
    def __init__(self, values):
        self.startIndex = 0
        self.maxIndex = len(values) - 1
        self.head = self._initialise_linked_list(values)

    def _initialise_linked_list(self, values):
        head = Node(values[0])
        previousNode = head
        nodeCount = len(values)
        for i in range(1, nodeCount):
            node = Node(values[i])
            previousNode.pointer = node
            previousNode = node
        return head
    
    def display(self):
        temp = self.head
        while temp is not None:
            print(temp.value)
            temp = temp.pointer
    
    def insert(self, value, position):
        temp = self.head
        node = Node(value)
        if position == self.startIndex:
            node.pointer = self.head
            self.head = node
        elif position == self.maxIndex:
            while temp.pointer is not None:
                temp = temp.pointer
            temp.pointer = node
            node.pointer = None
        elif position > self.startIndex and position < self.maxIndex:
            for i in range(position - 1):
                if temp.pointer is not None:
                    temp = temp.pointer
            node.pointer = temp.pointer
            temp.pointer = node
        else:
            print("Position out of range")
            return
        self.maxIndex += 1

    
    def delete(self, position):
        temp = self.head;
        if position == self.startIndex:
            self.head = self.head.pointer
        elif position == self.maxIndex:
            while temp.pointer.pointer is not None: # reach penultimate node
                temp = temp.pointer
            temp.pointer = None
        elif position > 0 and position < self.maxIndex:
            temp = self.head
            for i in range(position - 2):
                temp = temp.pointer
            temp.pointer = temp.pointer.pointer
        else:
            print("Position out of range")
            return
        self.maxIndex -= 1
    
    def search(self, value):
        temp = self.head
        while temp.pointer is not None:
            if temp.value == value:
                print(f"Found value {value}")
                return
            temp = temp.pointer
        print(f"Could not find value {value}")

class Node:
    def __init__(self, value):
        self.value = value
        self.pointer = None

if __name__ == "__main__":
    main()