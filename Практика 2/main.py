from copy import deepcopy
from dataclasses import dataclass
from ADTGraph import ADTGraph


def find_bridges(graph: ADTGraph):
    edges = deepcopy(graph.edges)
    original_components = graph.generate_components()
    print(f'OC: {original_components}')
    graph.reset()

    bridges: list[tuple[str, str]] = []

    for start, end in edges.keys():
        test_graph = deepcopy(graph)
        test_graph.del_e(start.mark, end.mark)

        test_components = test_graph.generate_components()
        if test_components > original_components:
            print(f'TC: {test_components}')
            bridges.append((start.mark, end.mark))
            # test_graph.draw()

    color_map = ['red' if edge in bridges else 'black' for edge in graph.g.edges]
    print(bridges)
    print(color_map)
    graph.draw(colors=color_map, title="Graph with colored bridges")


def main():
    graph = ADTGraph()

    graph.add_v('1')
    graph.add_v('2')
    graph.add_v('3')
    graph.add_v('4')
    graph.add_v('5')
    graph.add_v('6')
    graph.add_v('7')

    graph.add_e('1', '2')
    graph.add_e('2', '3')
    graph.add_e('3', '4')
    graph.add_e('4', '5')
    graph.add_e('5', '6')
    graph.add_e('6', '7')

    graph.draw(title="Graph")
    find_bridges(graph)


if __name__ == '__main__':
    main()
