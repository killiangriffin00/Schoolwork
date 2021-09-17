# CptS 355 - Fall 2020 - Assignment 3
# Please include your name and the names of the students with whom you discussed any of the problems in this homework

debugging = False


def debug(*s):
    if debugging:
        print(*s)


## problem 1-a) organizebyFlavor - 15%
def organizebyFlavor(feedingL):
    d = {}
    for i in feedingL:
        for j in feedingL[i]:
            if not (j in d):
                d.update({j: {i: feedingL[i][j]}})
            else:
                d[j].update({i: feedingL[i][j]})
    return d


from functools import reduce

## problem 1-b) popularFlavor - 15%
def popularFlavor(feedingL):
    newLog = organizebyFlavor(feedingL)
    tupleList = list(map((lambda d : (d, reduce((lambda x,y : x + newLog[d][y]), newLog[d], 0))), newLog))

    return max(tupleList, key=lambda d : d[1])

## problem 2) unzip - 15%
def unzip(L):
    return (list(map((lambda x: x[0]), L)), list(map((lambda x: x[1]), L)), list(map((lambda x: x[2]), L)))


## problem 3 - findCycle - 15%
def helper(graph, current, l, start):
    if current in l:
          l = l + [current]
          return l[l.index(current):]
    if graph[current] == None:
         return None
    l = l + [current]
    return helper(graph, graph[current], l, start)


def findCycle(graph, start):
    return helper(graph, start, [], start)

## problem 4 - getNextNode - 10%
def getNextNode(graph,start):
     current = start
     while current != None:
         yield current
         current = graph[current]

## problem 5 - DecodeIter - 25%
class DecodeIter ():
    def __init__(self, itable, istring):
        self.table = itable
        self.string = istring

    def __next__(self):
        if self.string == "":
            raise StopIteration
        word = ""
        while str(self.string)[0] != ' ':

            if not(str(self.string)[0] in self.table):
                word = word + str(self.string)[0]
            else:
                word = word + self.table[str(self.string)[0]]
            if str(self.string)[1:] == "":
                break
            else:
                self.string = str(self.string)[1:]
        self.string = str(self.string)[1:]
        return word

    def __iter__(self):
        return self

