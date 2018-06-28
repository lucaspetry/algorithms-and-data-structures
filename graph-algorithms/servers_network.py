import random
import time
from subprocess import call
import csv
from graph import Graph

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

times = []
random.seed(100)
v = 5000
e = 5000

while e <= 100000:
	graph = get_random_connected_graph(v, e)
	start = time.time()
	graph.get_minimum_spanning_tree()
	elapsed = ((time.time() - start) * 1000) // 1
	print("Graph with |V| = " + str(v) + " and |E| = " + str(e) + " :: Elapsed = " + str(elapsed) + " ms")
	times.append([e, elapsed])
	e += 5000

with open('graph_kruskal_data.csv', 'w') as csvfile:
	writer = csv.writer(csvfile, delimiter=',')
	writer.writerow(['edges', 'time'])

	for time in times:
		writer.writerow(time)

print("Plotting graph to plot.pdf")
call(["Rscript", "graph_kruskal_time_plot.R", "graph_kruskal_data.csv"])