import random
from graph import Graph

def create_signal_tree(integers):
	vertices = [integers[0]]
	edges = []

	for i in range(1, len(integers)):
		v1 = integers[i - 1]
		v2 = integers[i]

		if v2 not in vertices:
			vertices.append(v2)

		edges.append((v1, v2, min(v1, v2)))

	graph = Graph(vertices, edges, directed = False)
	print(graph.get_signal_tree())

integers = [1, 5, 2, 2, 7, 4, 1, 3]
create_signal_tree(integers)