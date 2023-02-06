def main():
    graph = {'A': [(6, 'B'), (1, 'D')],
        'B': [(5, 'C'), (2, 'D'), (2, 'E')],
        'C': [(5, 'B'), (5, 'E')],
        'D': [(1, 'A'), (2, 'B'), (1, 'E')],
        'E': [(2, 'B'), (1, 'D'), (5, 'C')]}
    
    shortest_path(graph, 'A')

def shortest_path(graph, source): 
    # generate the shortest paths between source vertex and every other node in the graph

    # key steps in dijkstra's algorithm
    # 1. Update the shortest distances between adjacent nodes
    # 2. Choose the next vertex based on the shortest distance

    distances = {}  # the distance table for all nodes from the source node
    shortestPaths = {} 
    previousNodes = {}
    unexploredNodes = list(graph.keys()) # all nodes start as unvisited

    # set the shortest distance as infinity for all vertices 
    for node in unexploredNodes:
        distances[node] = float('inf')
        shortestPaths[node] = []
    distances[source] = 0 # we know the shortest distance from source to itself is 0
    unexploredNodes.remove(source) # we've explored the source node since we start there to remove it
    del shortestPaths[source] # we already know the shortest path to source because its itself

    print(distances)
    print(unexploredNodes)
    currentNode = source
    distanceFromSource = 0
    distance = 0
    while len(unexploredNodes) != 0: # explore every node
        # get estimates for distances between adjacent nodes

        smallestDistance = float('inf')
        nextNode = ''
        for i in range(len(graph[currentNode])): # check adjacent nodes to the current node
            node = graph[currentNode][i][1]
            distance = graph[currentNode][i][0] + distanceFromSource;
            if distance < distances[node] and node in unexploredNodes:
                distances[node] = distance # update the shortest distance for the node
                if distance < smallestDistance: # the next node is the node with the lowest shortest distance from source
                    smallestDistance = distance
                    nextNode = graph[currentNode][i][1]
        
        distanceFromSource = distance
        previousNodes[nextNode] = currentNode
        unexploredNodes.remove(currentNode) # remove the current node as we will no longer visit it
        currentNode = nextNode # go to next node
    
    print(distances)
    print(previousNodes)
    

if __name__ == "__main__":
    main()