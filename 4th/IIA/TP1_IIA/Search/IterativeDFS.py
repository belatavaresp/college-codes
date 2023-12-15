from Cell import Cell
from helpers.globalVariables import GOAL

def DFS(init: Cell, limit: int) -> Cell:
    open: list[Cell] = [init]

    while len(open) != 0:
        cell = open.pop()
        if cell.state == GOAL:
            return cell
        
        if cell.depth > limit:
            #ignore deeper cells
            continue

        if not cell.isCycle() and cell.depth < limit:
            branch = cell.getBranches()
            for child in branch:
                open.append(child)

    return None

def iterativeDFS(init: list[list[int]], empty: tuple[int]) -> Cell:
    cell = Cell(None, init, empty)
    i = 0
    found: Cell = None
    while found == None:
        found = DFS(cell, i)
        i = i + 1

    return found