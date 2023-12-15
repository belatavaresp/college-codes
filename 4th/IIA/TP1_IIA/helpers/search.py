from typing import Callable
from Cell import Cell
from helpers.globalVariables import HEURISTC, GOAL
from Search.IterativeDFS import iterativeDFS
from Search.Dijkstra import Dijkstra
from Search.GreedyBFS import greedyBFS
from Search.HillClimbing import hillClimbing
from Search.AS import AStar
from Search.BFS import BFS

def exec(init: list[list[int]], empty: tuple[int], algorithm: Callable) -> tuple[int, list[list[list[int]]]]:
    found: Cell = algorithm(init, empty)
    reslt: list[list[list[int]]] = []

    if found.state != GOAL:
        return 0, reslt
    
    depth = found.depth
    while found:
        reslt.append(found.state)
        found = found.parent
    return depth, list(reversed(reslt))

def execHeuristic(init: list[list[int]], empty: tuple[int], algorithm: Callable) -> tuple[int, list[list[list[int]]]]:
    found: Cell = algorithm(init, empty, HEURISTC)
    reslt: list[list[list[int]]] = []

    if found.state != GOAL:
        return 0, reslt
    
    depth = found.depth
    while found:
        reslt.append(found.state)
        found = found.parent
    return depth, list(reversed(reslt))

def search(algorithm: str, state, empty) -> Cell:
    reslt = None
    if algorithm == 'B':
        reslt = exec(state, empty, BFS)
    elif algorithm == 'I':
        reslt = exec(state, empty, iterativeDFS)
    elif algorithm == 'U':
        reslt = exec(state, empty, Dijkstra)
    elif algorithm == 'A':
        reslt = execHeuristic(state, empty, AStar)
    elif algorithm == 'G':
        reslt = execHeuristic(state, empty, greedyBFS)
    elif algorithm == 'H':
        reslt = execHeuristic(state, empty, hillClimbing)

    return reslt