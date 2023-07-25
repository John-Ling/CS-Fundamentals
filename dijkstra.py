import heapq

SOURCE_NODE = 'A'

def main():
	# GRAPH = {'A': [(5, 'B'), (6, 'C')],
	# 	    'B': [(5, 'A'), (4, 'D'), (6, 'E')],
	# 	    'C': [(6, 'A'), (7, 'E'), (6, 'F')],
	# 	    'D': [(4, 'B'), (3, 'E'), (12, 'G')],
	# 	    'E': [(6, 'B'), (7, 'C'), (3, 'D'), (6, 'G'), (5, 'F')],
	#       'F': [(6, 'C'), (5, 'E'), (8, 'G')],
	#       'G': [(12, 'D'), (6, 'E'), (8, 'F')]}
	# GRAPH = {'A': [(2, 'B'), (6, 'C')],
	# 		'B': [(6, 'A'), (8, 'D')],
	# 		'C': [(2, 'A'), (5, 'D')],
	# 		'D': [(5, 'B'), (8, 'C'), (15, 'E'), (10, 'F')],
	# 		'E': [(15, 'D'), (6, 'F'), (6, 'G')],
	# 		'F': [(10, 'D'), (6, 'E'), (2, 'G')],
	# 		'G': [(6, 'E'), (2, 'F')]}
	GRAPH = {'A': [(5, 'B'), (7, 'E'), (9, 'G')],
			'B': [(5, 'A'), (6, 'C'), (7, 'E')],
			'C': [(6, 'B'), (7, 'F'), (6, 'E')],
			'D': [(9, 'F'), (6, 'I')],
			'E': [(7, 'A'), (7, 'B'), (6, 'C'), (11, 'F')],
			'F': [(6, 'C'), (11, 'E'), (11, 'G'), (float('inf'), 'H'), (9, 'D'), (10, 'I')],
			'G': [(9, 'A'), (11, 'F')],
			'H': [(float('inf'), 'F'), (7, 'I')],
			'I': [(6, 'D'), (10, 'F'), (7, 'H')]
			}
	# GRAPH = {'A': [(100, 'B')],
	#   		'B': [(100, 'C'), (600, 'D')],
	# 		'C': [(100, 'A'), (200, 'D')],
	# 		'D': [(float('inf'), 'A')]
	#   		}
			
	graphData = generate_shortest_paths(GRAPH, SOURCE_NODE)
	data = get_shortest_path('I', graphData)
	print(f"Shortest path: {data[0]}")
	print(f"Shortest path distance: {data[1]}")

	graphData = priority_queue_implementation(GRAPH, SOURCE_NODE)
	data = get_shortest_path('I', graphData)
	print(f"Shortest path: {data[0]}")
	print(f"Shortest path distance: {data[1]}")

def generate_shortest_paths(GRAPH, source): 
	costs = {}  # the cost table for all nodes from the source node 
	previousNodes = {}
	unexploredNodes = list(GRAPH.keys())

	# set the cost as infinity for all vertices (we don't know the initial costs yet)
	for node in unexploredNodes:
		costs[node] = float('inf')
	currentNode = source
	costs[source] = 0 # we know the shortest distance from source to itself is 0

	while len(unexploredNodes) != 0: 
		for i in range(len(GRAPH[currentNode])):
			node = GRAPH[currentNode][i][1] 
			cost = GRAPH[currentNode][i][0] + costs[currentNode]

			if cost < costs[node]: # update the cost for the adjacent node
				costs[node] = cost
				previousNodes[node] = currentNode

		unexploredNodes.remove(currentNode) # remove the current node as we will no longer visit it
		lowestCost = float('inf')
		for node in unexploredNodes: # update current node and select lowest cost unexplored node
			if costs[node] < lowestCost:
				currentNode = node 
				lowestCost = costs[node]
	
	return (costs, previousNodes)

def priority_queue_implementation(GRAPH, source):
	costs = {}
	previousNodes = {}
	unexploredNodes = list(GRAPH.keys())
	queue = [] # priority queue

	for node in unexploredNodes:
		costs[node] = float('inf')
	currentNode = source
	costs[source] = 0
	unexploredNodes.remove(source) # we have already visted the source node as we start there

	while len(unexploredNodes) != 0:
		for i in range(len(GRAPH[currentNode])):
			node = GRAPH[currentNode][i][1] 
			cost = GRAPH[currentNode][i][0] + costs[currentNode];

			if cost < costs[node]: # update distances
				costs[node] = cost
				previousNodes[node] = currentNode
			heapq.heappush(queue, (cost, node)) # enqueue node 

		# take the top the queue (lowest cost)
		frontQueueItem = heapq.heappop(queue)
		lowestCostNode = frontQueueItem[1]

		while lowestCostNode not in unexploredNodes: # find the top the queue that is unexplored
			frontQueueItem = heapq.heappop(queue)
			lowestCostNode = frontQueueItem[1]

		currentNode = lowestCostNode
		unexploredNodes.remove(lowestCostNode)

	return (costs, previousNodes)

def get_shortest_path(destination, graphData):
	# given a destination and graph data created by dijkstra's algorithm, generate a list of nodes to travel and the total distance / cost to reach destination from the source node
	lowestCosts = graphData[0]
	previousNodes = graphData[1]

	if any(node not in lowestCosts for node in (SOURCE_NODE, destination)):
		print("Node does not exist")
		return;
	
	cost = lowestCosts[destination]
	path = [destination]

	node = destination
	while node != SOURCE_NODE:
		path.insert(0, previousNodes[node])
		node = previousNodes[node]
	return (path, cost)

if __name__ == "__main__":
	main()