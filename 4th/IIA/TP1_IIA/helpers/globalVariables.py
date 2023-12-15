############################################################
#                                                          #
#   This file contains all global functions                #
#   and variables used throughout the code                 #
#                                                          #
############################################################
#                                                          #
#   Author: Izabela Garcia Tavares Pinheiro Pérez          #
#   Discipline: Introdução a Inteligência Artificial       #
#                                                          #
############################################################

#goal position of cells
GOAL = [[1, 2, 3],
        [4, 5, 6],
        [7, 8, 0]]

def heuristic1(state: list[list[int]]) -> int:
    #number of cells in wrong position
    count = 0
    for i, row in enumerate(state):
        for j, value in enumerate(row):
            if GOAL[i][j] != value:
                count += 1
    return count

def heuristic2(state: list[list[int]]) -> int:
    #sum of Manhattan distances between cells
    ind = 0
    for i, row in enumerate(state):
        for j, value in enumerate(row):
            index = value - 1
            if index < 0:
                index += 9
            rw = index // 3
            cl = index - rw * 3

            ind += abs(i - rw) + abs(j - cl)

    return ind

#standard heuristic is set to 1
HEURISTC = heuristic1