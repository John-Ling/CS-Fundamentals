
# binary search tree in Python

class Tree_Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

def main():
    root = intialise_tree()
    inorder_traversal(root)

def inorder_traversal(root):
    if root is None:
        return
    inorder_traversal(root.left)
    print(root.value)
    inorder_traversal(root.right)

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