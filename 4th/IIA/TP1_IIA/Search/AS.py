from Cell import Cell
from queue import PriorityQueue
from helpers.globalVariables import GOAL
import heapq

def AStar(initial_state, empty_cell, heuristic_func):
    visited = set()
    priority_queue = PriorityQueue()
    start_node = Cell(None, initial_state, empty_cell)
    start_node.f = heuristic_func(initial_state)
    priority_queue.put((start_node.f, start_node))

    while not priority_queue.empty():
        _, current_node = priority_queue.get()

        if current_node.state == GOAL:
            return current_node

        if current_node in visited:
            continue

        visited.add(current_node)

        for child_node in current_node.getBranches():
            if child_node not in visited:
                child_node.f = child_node.depth + heuristic_func(child_node.state)
                priority_queue.put((child_node.f, child_node))

    return None