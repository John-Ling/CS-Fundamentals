
# binary search tree in Python

class Tree_Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

def main():
    root = intialise_tree()
    search_tree(root, 87)

def inorder_traversal(root):
    if root is None:
        return
    inorder_traversal(root.left)
    print(root.value)
    inorder_traversal(root.right)

def search_tree(root, value):
    if root is None:
        print("Could not found value")
        return
    
    if (value < root.value):
        search_tree(root.left, value)
    elif (value > root.value):
        search_tree(root.right, value)
    else:
        print("Found value")
        return

def intialise_tree():
    root = Tree_Node(76)
    node1 = Tree_Node(50)
    node2 = Tree_Node(90)
    node3 = Tree_Node(39)
    node4 = Tree_Node(60)
    node5 = Tree_Node(87)
    node6 = Tree_Node(124)

    # connect nodes
    root.left = node1
    root.right = node2
    node1.left = node3
    node1.right = node4
    node2.left = node5
    node2.right = node6

    return root

if __name__ == "__main__":
    main()