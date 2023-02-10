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
			cost = GRAPH[currentNode][i][0] + costs[currentNode]; 

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

def get_shortest_path(destination, graphData):
	# given a destination and graph data created by dijkstra's algorithm, generate a list of nodes to travel and the total distance / cost to reach destination from the source node
	lowestCosts = graphData[0]
	previousNodes = graphData[1]

	if any(node not in lowestCosts for node in (SOURCE_NODE, destination)):
		print(f"Node does not exist")
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