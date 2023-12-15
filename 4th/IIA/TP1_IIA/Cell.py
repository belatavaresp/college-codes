############################################################
#                                                          #
#   This class contains all information                    #
#   about a position in the puzzle's board and             #
#   all branches(moves) possible from the current state    #
#                                                          #
############################################################
#                                                          #
#   Author: Izabela Garcia Tavares Pinheiro Pérez          #
#   Discipline: Introdução a Inteligência Artificial       #
#                                                          #
############################################################

from typing_extensions import Self

#posible shifts for the empty cell
rows = [1, 0, -1, 0]
colums = [0, -1, 0, 1]

def swapCells(list: list[list[int]], cell1: tuple[int, int], cell2: tuple[int, int]) -> list[list[int]]:
    #swaps two cell position in a list of cells
    list[cell1[0]][cell1[1]], list[cell2[0]][cell2[1]] = list[cell2[0]][cell2[1]], list[cell1[0]][cell1[1]]
    return list

def validMove(x: int, y: int) -> bool:
    #checks if cell position is valid in world boundaries
    return x >= 0 and x < 3 and y >=0 and y < 3

class Cell:
    def __init__(self, parent: Self, state: list[list[int]], empty: tuple[int, int], depth: int = 0):
        #cell constructor
        self.state = state #current board state
        self.parent = parent #parent cell (last state of board)
        self.empty = empty #position of the empty cell in current board
        self.branches: list[Self] = [] #posible board state branches after moving current cell
        self.depth = depth #depth of current board state
        self.f = depth #function f(n), when used
    
    def __setBranches(self) -> list[Self]:
        #calculate all valid branches of current state
        newbranch = []
        for i in range(4):
            #checking all shifts in empty cell position
            newEmpty = (self.empty[0] + rows[i], self.empty[1] + colums[i])
            
            if validMove(*newEmpty) and (not self.parent or newEmpty != self.parent.empty):
                #valid position of empty cell in new board config, and not in a cycle (back to grandparent)
                newState = [list(ls) for ls in self.state]
                newState = swapCells(newState, self.empty, newEmpty) #update position of empty cell

                newbranch.append(Cell(self, newState, newEmpty, self.depth + 1))
        self.branches = newbranch #update branches

    def getBranches(self) -> list[Self]:
        #returns the branch of current cell
        if not self.branches:
            self.__setBranches() #create branches if not existent
        
        return self.branches
    
    def isCycle(self) -> bool:
        #checks if there is a cycle inside branches (used in IDS)
        cell = self.parent
        while cell != None:
            #backtracks all positions in previous branch trying to find itself
            if cell == self:
                return True
            cell = cell.parent
        return False
    
    def __eq__(self, other):
        if not self and not other:
            return True  # Both null
        elif (self and not other) or (not self and other):
            return False  # Only one null
        return self.state == other.state

    def __hash__(self):
        # Implement a hash function based on the state of the cell
        return hash(tuple(tuple(row) for row in self.state))
    
    def __lt__(self, cell: Self) -> bool:
        #compares two cells by f(n), then depth
        if self.f == cell.f:
            return self.depth < cell.depth
        return self.f < cell.f
    