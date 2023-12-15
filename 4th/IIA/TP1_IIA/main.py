import sys
from helpers.utilityFunctions import printResult, find, printResult
from helpers.search import search

algorithm = sys.argv[1]

state = [list(map(int, sys.argv[i*3+2:i*3+5])) for i in range(3)]
empty = find(state, 0)
Print = len(sys.argv) > 11 and sys.argv[11] == 'PRINT'

result: tuple[int, list[list[list[int]]]]
result = search(algorithm, state, empty)
print(result[0])
if Print:
    for state in result[1]:
        printResult(state)
        print('')