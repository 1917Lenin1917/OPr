import networkx as nx
import matplotlib.pyplot as plt


class Node:
    def __init__(self, mark: str = '', idx: int = 0):
        self.mark = mark
        self.idx = idx
        self.visited = False
        self.component = 0

    def __repr__(self):
        return f'{self.mark}: {self.component=}'


class Edge:
    def __init__(self, start: Node, end: Node, weight=0):
        self.start = start
        self.end = end
        self.weight = weight


class ADTGraph:
    MAX_VERTEX_COUNT = 20

    def __init__(self):
        self.g = nx.DiGraph()

        self.nodes: dict[str, Node] = {}
        self.edges: dict[tuple[Node, Node], Edge] = {}

        self.A: list[list[int]] = [[0 for _ in range(self.MAX_VERTEX_COUNT)] for _ in range(self.MAX_VERTEX_COUNT)]
        self.idx = 0

    def __get_node_by_index(self, idx: int):
        for key, value in self.nodes.items():
            if value.idx == idx:
                return key
        return None

    # ADD_V(<имя>) - добавить УЗЕЛ
    def add_v(self, name: str):
        n = Node(name, self.idx)
        self.nodes[name] = n
        self.idx += 1

        self.g.add_node(name)

    # ADD_Е(v, w) - добавить ДУГУ
    def add_e(self, start: str, end: str):
        n_start = self.nodes[start]
        n_end   = self.nodes[end]

        edge = Edge(n_start, n_end)
        self.edges[(n_start, n_end)] = edge
        self.A[n_start.idx][n_end.idx] = 1

        self.g.add_edge(start, end)

    # FIRST(v) - возвращает индекс первой вершины, смежной с вершиной v.
    # Если вершина v не имеет смежных вершин, то возвращается "нулевая" вершина ?.
    def first(self, v: str):
        n = self.nodes[v]
        for index, value in enumerate(self.A[n.idx]):
            if value == 1:
                return self.__get_node_by_index(index)
        return None

    # NEXT(v, i)- возвращает индекс вершины, смежной с вершиной v, следующий за индексом i.
    # Если i — это индекс последней вершины, смежной с вершиной v, то возвращается ?.
    def next(self, v: str, i: int):
        n = self.nodes[v]
        for v_idx in range(i + 1, self.idx + 1):

            if self.A[n.idx][v_idx] == 1:
                return self.__get_node_by_index(v_idx)
        return None

    # VERTEX(v, i) - возвращает вершину с индексом i из множества вершин, смежных с v.
    def vertex(self, v: str, i: int):
        n = self.nodes[v]
        for index, value in enumerate(self.A[n.idx]):
            if value == 1 and i == 1:
                return self.__get_node_by_index(index)
            i -= value
        return None

    # DEL_Е(v, w) – удалить ДУГУ
    def del_e(self, v: str, w: str):
        n1 = self.nodes[v]
        n2 = self.nodes[w]

        self.A[n1.idx][n2.idx] = 0
        self.A[n2.idx][n1.idx] = 0

        del self.edges[(n1, n2)]
        self.g.remove_edge(n1.mark, n2.mark)

    def dfs1(self, v: str, order: list[str]):
        # count = 0
        # components[v] = comp_num
        # while n := self.next(v, count):
        #     if n not in components:
        #         self.dfs(n, comp_num, components)
        #     count += 1

        n = self.nodes[v]
        n.visited = True

        count = 0
        while u := self.next(v, count):
            un = self.nodes[u]
            if not un.visited:
                self.dfs1(u, order)
            count += 1
        order.append(v)

    def dfs2(self, v: str, cnt_count: int):
        n = self.nodes[v]
        n.component = cnt_count
        count = 0
        while u := self.next(v, count):
            un = self.nodes[u]
            if un.component == 0:
                self.dfs2(u, cnt_count)
            count += 1

    def generate_components(self) -> int:
        order = []
        for key in self.nodes:
            n = self.nodes[key]
            if not n.visited:
                self.dfs1(key, order)

        order = order[::-1]
        component_count = 1
        for key in order:
            n = self.nodes[key]
            if n.component == 0:
                self.dfs2(key, component_count)
                component_count += 1
        return len(set([n.component for n in self.nodes.values()]))

    def reset(self):
        for key, value in self.nodes.items():
            value.visited = False
            value.component = 0

    def draw(self, *, colors=None, title=None):

        #pos = nx.planar_layout(self.g)
        # pos = nx.kamada_kawai_layout(self.g)
        pos = nx.circular_layout(self.g)
        nx.draw_networkx_edges(self.g, pos, arrows=False, edge_color=colors)
        nx.draw_networkx_nodes(self.g, pos)
        nx.draw_networkx_labels(self.g, pos)
        plt.title(title)
        plt.show()
        plt.savefig(f'graph-{hash(self.g) + hash(tuple(colors) if colors else None) + hash(title)}.png')
        print(f'file graph-{hash(self.g) + hash(tuple(colors) if colors else None) + hash(title)}.png saved!')
