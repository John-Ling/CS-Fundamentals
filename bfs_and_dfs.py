def main():
    GRAPH = {
		'A': [(1, 'E1'), (1, 'E2'), (1, 'E3'), (1, 'E4')],
		'E1': [(1, 'A'), (1, 'D1'), (1, 'D2')],
		'E2': [(1, 'A'), (1, 'D2'), (1, 'D3')],
		'E3': [(1, 'A'), (1, 'D3'), (1, 'D4')],
		'E4': [(1, 'A'), (1, 'D4'), (1, 'D1'), (1, 'E5')],
		'E5': [(1, 'E4'), (1, 'E6')],
		'E6': [(1, 'E5'), (1, 'D4')],
		'D1': [(1, 'E4'), (1, 'E1')],
		'D2': [(1,'E1'), (1, 'E2')],
		'D3': [(1, 'E2'), (1, 'E3')],
		'D4': [(1, 'E3'), (1, 'E4')]
	}
    print(bfs_traversal(GRAPH))

    GRAPH = {'A': [(1, 'E1')],
		  	'E1': [(1, 'A'), (1, 'E2'), (1, 'D1')],
			'D1': [(1, 'E1')],
			'E2': [(1, 'E1'), (1, 'E3')],
			'E3': [(1, 'E2'), (1, 'D2'), (1, 'E4')],
			'E4': [(1, 'E3')],
			'D2': [(1, 'E3')]
	}
    print(bfs_traversal(GRAPH))

def bfs_traversal(graph):
    frontier = []
    unvisited = list(graph.keys())
    previous = {}
    currentNode = 'A'

    previous[currentNode] = None
    while len(unvisited) != 0:
        # get adjacent nodes
        for i in range(len(graph[currentNode])):
            node = graph[currentNode][i][1]
    
            if node in unvisited and  node not in frontier:
                previous[node] = currentNode
                frontier.append(node)
        
        print(currentNode)
        unvisited.remove(currentNode)

        # get front of queue
        if frontier != []:
            currentNode = frontier.pop(0)
    
    return previous


if __name__ == "__main__":
    main()