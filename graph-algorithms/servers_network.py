from graph import Graph

########################################################################
############                    EXAMPLE 1                   ############
########################################################################
vertices1 = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J']
edges1 = [
    ('A', 'B', 15),
    ('A', 'E', 11),
    ('B', 'C', 16),
    ('C', 'D', 10),
    ('E', 'F', 9),
    ('E', 'I', 8),
    ('D', 'G', 3),
    ('C', 'H', 14),
    ('F', 'G', 6),
    ('F', 'J', 7),
    ('G', 'J', 4),
    ('G', 'H', 15)
]

graph1 = Graph(vertices1, edges1, directed = False)
print('Example 1 - Edges corresponding to the minimum spanning tree:')
print(graph1.get_spanning_tree(min = True))

########################################################################
############                    EXAMPLE 2                   ############
########################################################################
vertices2 = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L']
edges2 = [
    ('A', 'B', 10),
    ('A', 'F', 8),
    ('B', 'G', 2),
    ('C', 'H', 4),
    ('C', 'K', 7),
    ('D', 'E', 7),
    ('D', 'F', 23),
    ('D', 'L', 15),
    ('E', 'L', 16),
    ('F', 'G', 2),
    ('F', 'I', 4),
    ('F', 'J', 3),
    ('G', 'J', 4),
    ('H', 'J', 4),
    ('I', 'J', 5),
    ('J', 'K', 5),
    ('K', 'L', 19)
]

graph2 = Graph(vertices2, edges2, directed = False)
print('Example 2 - Edges corresponding to the minimum spanning tree:')
print(graph2.get_spanning_tree(min = True))