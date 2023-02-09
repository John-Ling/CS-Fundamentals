SOURCE_NODE = 'A'

def main():
	GRAPH = {'A': [(5, 'B'), (6, 'C')],
		    'B': [(5, 'A'), (4, 'D'), (6, 'E')],
		    'C': [(6, 'A'), (7, 'E'), (6, 'F')],
		    'D': [(4, 'B'), (3, 'E'), (12, 'G')],
		    'E': [(6, 'B'), (7, 'C'), (3, 'D'), (6, 'G'), (5, 'F')],
	        'F': [(6, 'C'), (5, 'E'), (8, 'G')],
	        'G': [(12, 'D'), (6, 'E'), (8, 'F')]}
	graphData = generate_shortest_paths(GRAPH, SOURCE_NODE)
	data = get_shortest_path('G', graphData)
	print(f"Shortest path: {data[0]}")
	print(f"Shortest path distance: {data[1]}")

def generate_shortest_paths(GRAPH, source): 
	# generate the shortest paths between source vertex and every other node in the graph

	# key steps in dijkstra's algorithm
	# 1. Update the shortest distances between adjacent nodes
	# 2. Choose the next vertex based on the shortest distance

	distances = {}  # the distance table for all nodes from the source node 
	previousNodes = {}
	unexploredNodes = list(GRAPH.keys()) # all nodes start as unvisited

	# set the shortest distance as infinity for all vertices 
	for node in unexploredNodes:
		distances[node] = float('inf')
	currentNode = source
	distances[source] = 0 # we know the shortest distance from source to itself is 0

	while len(unexploredNodes) != 0: # explore every node
		for i in range(len(GRAPH[currentNode])): # check adjacent nodes to the current node
			node = GRAPH[currentNode][i][1] # the adjacent node connected to the current node
			distance = GRAPH[currentNode][i][0] + distances[currentNode]; # distance is distance of the current node + the distance to the adjacent node

			if distance < distances[node]: # update the shortest distance for the adjacent node
				distances[node] = distance 
				previousNodes[node] = currentNode

		unexploredNodes.remove(currentNode) # remove the current node as we will no longer visit it
		nextNode = ''
		lowestDistance = float('inf')
		for node in unexploredNodes: # select shortest unexplored node
			if distances[node] < lowestDistance:
				nextNode = node
				lowestDistance = distances[node]
		currentNode = nextNode
	
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