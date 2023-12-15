from Cell import Cell

def hillClimbing(init: list[list[int]], empty: tuple[int], heuristic) -> Cell:
    curr: Cell = Cell(None, init, empty)
    next: Cell
    limit = 3
    stag = 0
    while True:
        branch = curr.getBranches()
        #finding the neighbor cell with the smallest heuristic value
        next = min(branch, key=lambda n: heuristic(n.state))
        if heuristic(next.state) > heuristic(curr.state) or stag >= limit:
            return curr #found minimum (every neighbor has greater heuristic)
        if heuristic(next.state) == heuristic(curr.state):
            stag += 1 #heuristic didn't change (stagnated)
        else:
            stag = 0 #heuristic changed (not stagnated anymore)
        curr = next