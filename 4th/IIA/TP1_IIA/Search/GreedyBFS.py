from queue import PriorityQueue
from Cell import Cell
from helpers.globalVariables import GOAL

def greedyBFS(init: list[list[int]], empty: tuple[int], heuristic) -> Cell:
    open_queue = PriorityQueue()
    explored: list[Cell] = []

    start_node = Cell(None, init, empty)
    start_node.f = heuristic(init)
    open_queue.put((start_node.f, start_node))

    while not open_queue.empty():
        _, cell = open_queue.get()

        if cell.state == GOAL:
            return cell

        explored.append(cell)
        branch = cell.getBranches()

        for child in branch:
            # Set heuristic value of child using parameter heuristic in state
            child.f = heuristic(child.state)

            if child not in explored:
                if not any(child == item for _, item in open_queue.queue):
                    # Only had one path to cell yet
                    open_queue.put((child.f, child))
                else:
                    # There's more than one path to the same cell
                    for _, existing_child in open_queue.queue:
                        if child == existing_child and child.f < existing_child.f:
                            # Keep the one with the greatest heuristic value
                            open_queue.queue.remove((existing_child.f, existing_child))
                            open_queue.put((child.f, child))
                            break

    return None
