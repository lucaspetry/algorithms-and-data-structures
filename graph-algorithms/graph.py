
class Graph(object):

    _vertices = []
    _edges = []
    _directed = True

    def __init__(self, vertices, edges = [], directed = True):
        self._directed = directed
        self._vertices = vertices
        self._edges = [[0 for j in range(0, len(vertices))] for i in range(0, len(vertices))]

        for edge in edges:
            idx1 = self._vertices.index(edge[0])
            idx2 = self._vertices.index(edge[1])

            self._edges[idx1][idx2] = 1 if len(edge) < 3 else edge[2]

            if not self._directed:
                self._edges[idx2][idx1] = 1 if len(edge) < 3 else edge[2]

    # Connect vertex v1 to v2
    def connect(self, v1, v2, weight = 1):
        idx1 = self._vertices.index(v1)
        idx2 = self._vertices.index(v2)

        self._edges[idx1][idx2] = weight

        if not self._directed:
            self._edges[idx2][idx1] = weight

    # Check whether there is a connection from v1 to v2
    def is_connected(self, v1, v2):
        idx1 = self._vertices.index(v1)
        idx2 = self._vertices.index(v2)

        return True if self._edges[idx1][idx2] == 1 else False

    # Get all source vertices, i.e., vertices with no incoming edges
    def get_source_vertices(self):
        source = [True for i in range(0, len(self._vertices))]

        for row in range(0, len(self._edges)):
            for col in range(0, len(self._edges[row])):
                if self._edges[row][col] == 1:
                    source[col] = False

        return [v for v, s in zip(self._vertices, source) if s]

    # Topological sorting implemented with depth-first search
    def get_topological_ordering(self):
        if not self._directed:
            raise Exception('Topological ordering not applicable to undirected graphs!')

        sorting = []
        sources = self.get_source_vertices()

        for v in sources:
            visited = self.dfs_visit(v, sorting)
            visited.extend(sorting)
            sorting = visited

        return sorting

    # Depth-first search
    def dfs_visit(self, v, visited):
        nowVisited = []
        idxV = self._vertices.index(v)

        for col in range(0, len(self._vertices)):
            v2 = self._vertices[col]
            allVisited = set().union(nowVisited, visited, v)
            if self._edges[idxV][col] == 1 and v2 not in allVisited:
                newVisited = self.dfs_visit(v2, allVisited)
                newVisited.extend(nowVisited)
                nowVisited = newVisited

        newVisited = [v]
        newVisited.extend(nowVisited)
        return newVisited
    
    # Minimum spanning tree of the graph via 
    def get_minimum_spanning_tree(self):
        return None # TO-DO