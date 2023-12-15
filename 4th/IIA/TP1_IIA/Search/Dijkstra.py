from Cell import Cell
from helpers.globalVariables import GOAL
from queue import PriorityQueue

def Dijkstra(init: list[list[int]], empty: tuple[int]) -> Cell:
    visited = set()
    priority_queue = PriorityQueue()
    start_node = Cell(None, init, empty)
    priority_queue.put((0, start_node))

    while not priority_queue.empty():
        _, current_node = priority_queue.get()

        if current_node.state == GOAL:
            return current_node

        if current_node in visited:
            continue

        visited.add(current_node)

        for child_node in current_node.getBranches():
            if child_node not in visited:
                priority_queue.put((child_node.depth, child_node))

    return None