# binary search tree in Python
# binary search trees smaller values go to the left
# bigger values go to the right

class Tree_Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

def main():
    root = intialise_tree()
    inorder_traversal(root)
    search_tree(root, 50)
    root = insert(root, 943)
    root = delete(root, 90)

def inorder_traversal(root):
    if root is None:
        return
    inorder_traversal(root.left)
    print(root.value)
    inorder_traversal(root.right)

def search_tree(root, value):
    if root is None or root.value == value:
        if root is None:
            print("Not Found")
        else:
            print("Found")
        return root
    
    if (value < root.value):
        return search_tree(root.left, value)
    elif (value > root.value):
        return search_tree(root.right, value)

def insert(root, value):
    if root is None:
        return Tree_Node(value)
    
    if value < root.value:
        root.left = insert(root.left, value)
    elif value > root.value:
        root.right = insert(root.right, value)
    return root

def delete(root, value):
    # there are three cases when deleting nodes
    # 1. Trying to delete a leaf node (a node with no children)
    # 2. Trying to delete a node with 1 child
    # 3. Trying to delete a node with 2 children

    if root is None:
        return root
    
    if value < root.value:
        root.left = delete(root.left, value) # make function calls that will eventually update the left or right node
    elif value > root.value:
        root.right = delete(root.right, value)
    else:
        if root.left is None and root.right is None: # no children / leaf node
            root = None
            return root
        if root.left is None: # 1 child in right 
            tmp = root.right # pointer that stores the right node of the node we want to delete
            root = None # free node
            return tmp
        if root.right is None: # 1 child in left
            tmp = root.left # point that stores the left node of the node we want to delete
            root = None
            return tmp
        
        # third case (two children)
        minElement = find_min_node(root.right) # find the 
        root.value = minElement.value
        root.right = delete(root.right, minElement.value) # remove the duplicate
    return root


def find_min_node(root): # usually we will be using the rightmost node of the root node found in delete()
    current = root
    while current.left is not None: # because in a 
        current = current.left
    return current
  

def intialise_tree():
    root = None
    root = insert(root, 76)
    root = insert(root, 50)
    root = insert(root, 90)
    insert(root, 39)
    insert(root, 60)
    insert(root, 87)
    insert(root, 124)
    return root

if __name__ == "__main__":
    main()