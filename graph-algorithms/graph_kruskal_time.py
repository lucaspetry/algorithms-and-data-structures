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

    # Make sure the graph is connected
    for i in range(1, len(shuffledVertices)):
        v1 = shuffledVertices[i - 1]
        v2 = shuffledVertices[i]

        if vertices.index(v2) < vertices.index(v1):
            v1, v2 = v2, v1

        edges.append((v1, v2, 0))

    # Generate random edges
    while len(edges) < edgeCount:
        r1 = random.randint(0, len(vertices) - 1)
        r2 = random.randint(0, len(vertices) - 1)

        if r2 < r1:
            r1, r2 = r2, r1

        edges.append((vertices[r1], vertices[r2], 0))

    # Assign random weights to the edges
    for i in range(0, len(edges)):
        edges[i] = (edges[i][0], edges[i][1], random.randint(1, 10))

    return Graph(vertices, edges, directed = False)


########################################################################
############                   |V| = 1000                   ############
########################################################################
times = []
random.seed(100)
v = 1000
e = 1000

while e <= 100000:
    graph = get_random_connected_graph(v, e)
    start = time.time()
    graph.get_spanning_tree(min = True)
    elapsed = ((time.time() - start) * 1000) // 1
    print("Graph with |V| = " + str(v) + " and |E| = " + str(e) + " :: Elapsed = " + str(elapsed) + " ms")
    times.append([e, elapsed])
    e += 3000

with open('graph_kruskal_data_1000.csv', 'w') as csvfile:
    writer = csv.writer(csvfile, delimiter=',')
    writer.writerow(['edges', 'time'])

    for t in times:
        writer.writerow(t)

print("Plotting graph to graph_kruskal_data_1000.csv.pdf")
call(["Rscript", "graph_kruskal_time_plot.R", "graph_kruskal_data_1000.csv"])


########################################################################
############                   |V| = 5000                   ############
########################################################################
times = []
random.seed(100)
v = 5000
e = 5000

while e <= 200000:
    graph = get_random_connected_graph(v, e)
    start = time.time()
    graph.get_spanning_tree(min = True)
    elapsed = ((time.time() - start) * 1000) // 1
    print("Graph with |V| = " + str(v) + " and |E| = " + str(e) + " :: Elapsed = " + str(elapsed) + " ms")
    times.append([e, elapsed])
    e += 5000

with open('graph_kruskal_data_5000.csv', 'w') as csvfile:
    writer = csv.writer(csvfile, delimiter=',')
    writer.writerow(['edges', 'time'])

    for t in times:
        writer.writerow(t)

print("Plotting graph to graph_kruskal_data_5000.csv.pdf")
call(["Rscript", "graph_kruskal_time_plot.R", "graph_kruskal_data_5000.csv"])


########################################################################
############                   |V| = 10000                  ############
########################################################################
times = []
random.seed(100)
v = 10000
e = 10000

while e <= 400000:
    graph = get_random_connected_graph(v, e)
    start = time.time()
    graph.get_spanning_tree(min = True)
    elapsed = ((time.time() - start) * 1000) // 1
    print("Graph with |V| = " + str(v) + " and |E| = " + str(e) + " :: Elapsed = " + str(elapsed) + " ms")
    times.append([e, elapsed])
    e += 10000

with open('graph_kruskal_data_10000.csv', 'w') as csvfile:
    writer = csv.writer(csvfile, delimiter=',')
    writer.writerow(['edges', 'time'])

    for t in times:
        writer.writerow(t)

print("Plotting graph to graph_kruskal_data_10000.csv.pdf")
call(["Rscript", "graph_kruskal_time_plot.R", "graph_kruskal_data_10000.csv"])