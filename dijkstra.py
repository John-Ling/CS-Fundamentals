SOURCE_NODE = 'A'

def main():
	GRAPH = {'A': [(6, 'B'), (1, 'D')],
			 'B': [(5, 'C'), (2, 'D'), (2, 'E')],
			 'C': [(5, 'B'), (5, 'E')],
			 'D': [(1, 'A'), (2, 'B'), (1, 'E')],
			 'E': [(2, 'B'), (1, 'D'), (5, 'C')]}
	graphData = generate_shortest_paths(GRAPH, SOURCE_NODE)
	data = get_shortest_path('C', graphData)
	print(f"Shortest path: {data[0]}")
	print(f"Shortest path distance: {data[1]}")
	

def generate_shortest_paths(GRAPH, source): 
	# generate the shortest paths between source vertex and every other node in the graph

	# key steps in dijkstra's algorithm
	# 1. Update the shortest distances between adjacent nodes
	# 2. Choose the next vertex based on the shortest distance

	distances = {}  # the distance table for all nodes from the source node
	shortestPaths = {} 
	previousNodes = {}
	unexploredNodes = list(GRAPH.keys()) # all nodes start as unvisited

	# set the shortest distance as infinity for all vertices 
	for node in unexploredNodes:
		distances[node] = float('inf')
		shortestPaths[node] = []
	distances[source] = 0 # we know the shortest distance from source to itself is 0
	del shortestPaths[source] # we already know the shortest path to source because its itself
	currentNode = source

	while len(unexploredNodes) != 0: # explore every node
		smallestDistance = float('inf')
		nextNode = ''
		for i in range(len(GRAPH[currentNode])): # check adjacent nodes to the current node
			node = GRAPH[currentNode][i][1] # the adjacent node connected to the current node
			distance = GRAPH[currentNode][i][0] + distances[currentNode]; # distance is distance of the current node + the distance to the adjacent node

			if distance < distances[node]: # update the shortest distance for the adjacent node
				distances[node] = distance 
				previousNodes[node] = currentNode

			if (distance < smallestDistance or len(unexploredNodes) == 1) and node in unexploredNodes: # pick the shortest / lowest cost non-explored node as the next node
				# however if there is only one explored node left then it will be the next node regardless of whether it fufils the above criteria
				smallestDistance = distance
				nextNode = node

		unexploredNodes.remove(currentNode) # remove the current node as we will no longer visit it
		currentNode = nextNode # go to next node
	
	return (distances, previousNodes)

def get_shortest_path(destination, graphData):
	# given a destination and graph data created by dijkstra's algorithm, generate a list of nodes to travel and the total distance / cost to reach destination from the source node
	shortestDistances = graphData[0]
	previousNodes = graphData[1]

	if any(node not in shortestDistances for node in (SOURCE_NODE, destination)):
		print(f"Node does not exist")
		return;
	
	distance = shortestDistances[destination]
	path = [destination]

	node = destination
	while node != SOURCE_NODE:
		path.insert(0, previousNodes[node])
		node = previousNodes[node]
	return (path, distance)

if __name__ == "__main__":
	main()