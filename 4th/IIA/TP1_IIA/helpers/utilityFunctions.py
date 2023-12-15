from Cell import Cell

def find(state: list[list[int]], value: int) -> tuple[int, int]:
    #searches (linear) all items in list trying to find value
    for i, row in enumerate(state):
        if value in row:
            return i, row.index(value)
        
def printResult(iterable) -> None:
    for row in iterable:
        for value in row:
            if value == 0:
                print('  ', end='')
            else:
                print(f'{value} ', end='')
        print('')

