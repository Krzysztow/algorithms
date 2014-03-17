#!/usr/bin/python

import sys


def createReplacedString(string):
    '''takes a c-like string and returns its nearly-copy
    with spaces replaced with %20 '''

    #first iterate over the string and count spaces
    spacesCnt = 0
    for ch in string:
        if (' ' == ch):
            spacesCnt += 1

    #we have a string of idx+1 length (could use len() method too)
    #create longer array to store (length-spacesCnt) + 3*spacesCnt elements
    #these value stand for string length  w/o spaces, plus additional size for
    #inserted string
    resultLength = len(string) - spacesCnt + 3 * spacesCnt

    #create an array - I know I could do it on the go, but this how I would do it
    #in C++
    newString = [None for x in xrange(resultLength)]

    #iterate for the second time, inserting the sequence
    idx = 0
    newIdx = 0
    for ch in string:
        if (' ' == ch):
            newString[newIdx] = '%'
            newString[newIdx + 1] = '2'
            newString[newIdx + 2] = '0'
            newIdx += 3
        else:
            newString[newIdx] = string[idx]
            newIdx += 1
        idx += 1

    return newString

if (2 != len(sys.argv)):
    "Given {0} params".format(len(sys.argv))
    "Usage: {0} \<string\>".format(sys.argv[0])
    sys.exit(1)

input = sys.argv[1]

output = createReplacedString(input)
print "Result for {0} is {1}".format(input, "".join(output))
