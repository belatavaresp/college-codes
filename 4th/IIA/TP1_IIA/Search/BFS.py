from queue import Queue
from Cell import Cell
from helpers.globalVariables import GOAL

def BFS(init: list[list[int]], empty: tuple[int]) -> Cell:
    open_queue = Queue()
    start_node = Cell(None, init, empty)
    open_queue.put(start_node)

    explored = set()

    while not open_queue.empty():
        cell = open_queue.get()

        if cell.state == GOAL:
            return cell

        explored.add(cell)
        branch = cell.getBranches()

        for child in branch:
            if child.state == GOAL:
                return child

            if child not in explored and child not in open_queue.queue:
                open_queue.put(child)

    return None
