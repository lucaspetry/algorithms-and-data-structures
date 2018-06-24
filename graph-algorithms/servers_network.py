from graph import Graph
import random

def get_random_connected_graph(vertexCount, edgeCount):
	if edgeCount < vertexCount - 1:
		raise Exception('There must be at least |V| - 1 edges in a connected graph!')

	vertices = ['v' + str(i) for i in range(1, vertexCount + 1)]
	edges = []

	shuffledVertices = vertices.copy()
	random.shuffle(shuffledVertices)

	for i in range(1, len(shuffledVertices)):
		v1 = shuffledVertices[i - 1]
		v2 = shuffledVertices[i]

		if vertices.index(v2) < vertices.index(v1):
			v1, v2 = v2, v1

		edges.append((v1, v2, 0))

	while len(edges) < edgeCount:
		r1 = random.randint(0, len(vertices) - 1)
		r2 = random.randint(0, len(vertices) - 1)

		if r2 < r1:
			r1, r2 = r2, r1

		if (vertices[r1], vertices[r2], 0) in edges:
			continue
		else:
			edges.append((vertices[r1], vertices[r2], 0))

	for i in range(0, len(edges)):
		edges[i] = (edges[i][0], edges[i][1], random.randint(1, 10))

	return Graph(vertices, edges, directed = False)


vertices = ['A', 'B', 'C', 'D', 'E']
edges = [
	('A', 'B', 2),
	('A', 'C', 4),
	('D', 'E', 2),
	('C', 'E', 3),
	('C', 'B', 5),
	('A', 'E', 1),
	('B', 'D', 3)
]

graph = Graph(vertices, edges, directed = False)
print(graph.get_minimum_spanning_tree())

graph2 = get_random_connected_graph(100, 300)
print(graph2.get_minimum_spanning_tree())