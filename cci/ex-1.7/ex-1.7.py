#!/usr/bin/python
import sys


def crossNull(matrix):
    #assume the matrix is checked for empty one
    rowSize = len(matrix)
    colSize = len(matrix[0])
    #we have to iterate over all rows, so create an array
    nullRows = [1 for x in xrange(rowSize)]
    #we don't have to iterate over all cols, so it may be a set (not to duplicate)
    nullCols = set([])

    rowNo = 0
    colNo = 0
    for row in matrix:
        colNo = 0
        for cell in row:
            if (0 == cell):
                nullRows[rowNo] = 0
                nullCols.add(colNo)
                #no need to look in this row further
                break
            colNo += 1
        rowNo += 1

    #null entire row if nullRows is unset or null particular cols in that row
    rowNo = 0
    for row in matrix:
        colNo = 0
        if (0 == nullRows[rowNo]):
            #null entire row
            mRow = matrix[rowNo]
            for i in xrange(colSize):
                mRow[i] = 0
        else:
            #null only cells that correspond to cols
            mRow = matrix[rowNo]
            for colNo in nullCols:
                mRow[colNo] = 0
        rowNo += 1



def printMatrix(name, matrix):
    print name
    for row in matrix:
        print row

def main(argv):
    if (2 != len(argv)):
        print "Usage: {0} <file-path>".format(argv[0])
        sys.exit(1)

    matrix = []
    f = open(argv[1])
    for row in f:
        mRow = []
        cells= row.split(" ")
        for c in cells:
            mRow.append(int(c))
        matrix.append(mRow)

    printMatrix("Old: ", matrix)
    crossNull(matrix)
    printMatrix("New: ", matrix)


main(sys.argv)
