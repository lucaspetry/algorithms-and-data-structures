class SetManager(object):

    _idxs = {}
    _ranks = {}
    _fathers = []
    _count = 0

    def __init__(self):
        self._idxs = {}
        self._ranks = {}
        self._fathers = []
        self._count = 0

    def get_count(self):
        return self._count

    def make_set(self, x):
        if x not in self._idxs:
            self._idxs[x] = len(self._idxs)
            self._ranks[x] = 0
            self._count += 1
            self._fathers.append(x)

    # Find set with path compression
    def find_set(self, x):
        father = self.get_father(x)

        if x != father:
            self.set_father(x, self.find_set(father))

        return self.get_father(x)

    def union(self, x, y):
        setX = self.find_set(x)
        setY = self.find_set(y)
        self.link(setX, setY)
        self._count = max(self._count - 1, 0)

    # Link two vertices with union by rank
    def link(self, x, y):
        if self._ranks[x] > self._ranks[y]:
            self.set_father(y, x)
        else:
            self.set_father(x, y)

            if self._ranks[x] == self._ranks[y]:
                self._ranks[y] += 1

    def get_father(self, x):
        return self._fathers[self._idxs[x]]

    def set_father(self, x, father):
        self._fathers[self._idxs[x]] = father

    def get_generated_tree(self):
        edges = []

        for x in self._idxs:
            idx = self._idxs[x]
            father = self._fathers[idx]
            
            if x != father:
                edges.append((x, father))

        return edges