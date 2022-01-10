from pyeda.inter import *
even = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30}
prime = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}

def getEdges():  # Makes a dictionary, with all nodes as keys and a set of nodes the key points to as values
    R = {}
    nums = set()
    i = 0
    while i < 32:
        nums.add(i)
        i += 1

    for inode in nums:
        R[inode] = set()
        for jnode in nums:
            if (inode + 3) % 32 == jnode % 32 or (inode + 8) % 32 == jnode % 32:
                R[inode].add(jnode)
    return R

def getEven(R):  # Makes a dictionary, with even values as keys and a set of nodes the key points to as values
    enodes = {}
    for key in R:
        if key in even:
            enodes[key] = R[key]
    return enodes

def getPrime(R):  # Makes a dictionary, with prime values as keys and a set of nodes the key points to as values
    pnodes = {}
    for key in R:
        if key in prime:
            pnodes[key] = R[key]
    return pnodes

def getBDD5(R, var):  # Formats a string for a 5 variable encoding representation of a set of numbers, then uses
    expression = ''   # that string to make a Binary Decision Diagram, or BDD
    first = 1
    for node in R:
        if first:              # Or encompasses entire set of 5 variable encoded numbers
            expression += 'Or('
            first = 0
        else:
            expression += ', '
        expression += 'And('   # Each 5 variable encoded number is a set of variables all "anded" together, with each
        i = 0                  # variable corresponding to a digit in the binary representation of the number

        keyBin = bin(node)[2:]     # Number is converted to binary
        while len(keyBin) < 5:     # -
            keyBin = '0' + keyBin  # -

        while i < 5:                                          # Each of the five variables is assigned a digit
            if keyBin[i] == '1':                              # If the digit is 1...
                expression += var[0] + str(i)                 # keep the variable as is
            else:                                             # If not...
                expression += 'Not(' + var[0] + str(i) + ')'  # negate the variable
            if i != 4:
                expression += ', '
            i += 1

        expression += ')'
    expression += ')'
    e = expr(expression)  # String is changed to an expression
    return expr2bdd(e)    # then to a BDD

def getBDD10(R):     # Formats a string for a 10 variable encoding representation of a set of edges, then uses
    expression = ''  # that string to make a Binary Decision Diagram, or BDD
    first = 1
    for node in R:
        if first:    # Or encompasses entire set of 10 variable encoded edges
            expression += 'Or('
            first = 0
        else:
            expression += ', '
        for edge in R[node]:
            expression += 'And('  # Each 10 variable encoded number is a set of variables all "anded" together, with
            i = 0                 # each of the first 5 variables representing the node itself, and the other 5
                                  # variables representing the node it is pointing to
            keyBin = bin(node)[2:]     # Both numbers are converted to binary
            valBin = bin(edge)[2:]     # -
            while len(keyBin) < 5:     # -
                keyBin = '0' + keyBin  # -
            while len(valBin) < 5:     # -
                valBin = '0' + valBin  # -

            while i < 5:                                  # The first 5 variables are assigned digits
                if keyBin[i] == '1':                      # If the digit is 1...
                    expression += 'x' + str(i)            # keep the variable as is
                else:                                     # If not...
                    expression += 'Not(x' + str(i) + ')'  # Negate the variable
                expression += ', '
                i += 1

            i = 0
            while i < 5:                                  # Same process is undertaken for the next 5 variables, except
                if valBin[i] == '1':                      # with the value of the node the edge points to
                    expression += 'y' + str(i)            # -
                else:                                     # -
                    expression += 'Not(y' + str(i) + ')'  # -
                if i != 4:
                    expression += ', '
                i += 1
            expression += ')'
            if edge != list(R[node])[-1]:
                expression += ','
    expression += ')'
    BDD = expr(expression)  # String is changed to an expression
    return expr2bdd(BDD)    # then to a BDD

def comp(R1, R2):      # Makes a BDD such that the starting 5 variables of the first are now "anded" with the
    z0 = bddvar('z0')  # ending 5 variables of the second
    z1 = bddvar('z1')
    z2 = bddvar('z2')
    z3 = bddvar('z3')
    z4 = bddvar('z4')
    x0 = bddvar('x0')
    x1 = bddvar('x1')
    x2 = bddvar('x2')
    x3 = bddvar('x3')
    x4 = bddvar('x4')
    y0 = bddvar('y0')
    y1 = bddvar('y1')
    y2 = bddvar('y2')
    y3 = bddvar('y3')
    y4 = bddvar('y4')

    R1s = R1.compose({y0: z0, y1: z1, y2: z2, y3: z3, y4: z4})  # Assignes the same variable to the ending 5 varibles
    R2s = R2.compose({x0: z0, x1: z1, x2: z2, x3: z3, x4: z4})  # of R1 and the starting 5 of R2
    RR2 = R1s & R2s                                             # "Ands" the two BDDs together
    RRs = RR2.smoothing({z0, z1, z2, z3, z4})                   # Removes the Z varibles
    return expr2bdd(RRs)

def transitiveClosure(R): # Makes a BDD such that nodes point to all reachable nodes. If done with a BDD comp(R, R),
    i = 0                 # this will return a BDD with nodes pointing to all nodes reachable within even steps
    RR2s = R
    c = R
    while i < 2:          # Loop executed twice, because for our purposes, nodes loop to themselves after 2 executions
        c = comp(c, R)
        RR2s = RR2s | c
        i += 1
    return RR2s

def statementA(prime, even, RR2s):  # Composes statement A
    y0 = bddvar('y0')
    y1 = bddvar('y1')
    y2 = bddvar('y2')
    y3 = bddvar('y3')
    y4 = bddvar('y4')

    F = (even & RR2s).smoothing({y0, y1, y2, y3, y4})  # We "and" together even and the set of nodes reachable in even
    return (prime & F.__invert__()).__invert__()       # steps. Then, we remove the y variables from the BDD. Since any
                                                       # number 0 - 31 has an even number in the list of edges reachable
                                                       # in even steps, the first statement is always true, making the
                                                       # the set of primes trivial
def testCase(PE, prime, even):  # Binds the varibles in the BDD to the prime number and the even number,
    x0 = bddvar('x0')           # then returns truth value
    x1 = bddvar('x1')
    x2 = bddvar('x2')
    x3 = bddvar('x3')
    x4 = bddvar('x4')
    y0 = bddvar('y0')
    y1 = bddvar('y1')
    y2 = bddvar('y2')
    y3 = bddvar('y3')
    y4 = bddvar('y4')

    keyBin = bin(prime)[2:]    # Both numbers are converted to binary
    valBin = bin(even)[2:]     # -
    while len(keyBin) < 5:     # -
        keyBin = '0' + keyBin  # -
    while len(valBin) < 5:     # -
        valBin = '0' + valBin  # -
    i = 0
    while i < 5:                           # Each variable is restricted to a value based on the digit it represents
        if keyBin[i] == '1':               # If the digit is 1...
            if i == 0:                     # assign the correct variable 1
                PE = PE.restrict({x0: 1})  # -
            if i == 1:                     # -
                PE = PE.restrict({x1: 1})  # -
            if i == 2:                     # -
                PE = PE.restrict({x2: 1})  # -
            if i == 3:                     # -
                PE = PE.restrict({x3: 1})  # -
            if i == 4:                     # -
                PE = PE.restrict({x4: 1})  # -
        else:                              # If not...
            if i == 0:                     # assign the correct variable 0
                PE = PE.restrict({x0: 0})  # -
            if i == 1:                     # -
                PE = PE.restrict({x1: 0})  # -
            if i == 2:                     # -
                PE = PE.restrict({x2: 0})  # -
            if i == 3:                     # -
                PE = PE.restrict({x3: 0})  # -
            if i == 4:                     # -
                PE = PE.restrict({x4: 0})  # -
        i += 1
    i = 0

    while i < 5:                           # Same process is undertaken with the even variable
        if valBin[i] == '1':
            if i == 0:
                PE = PE.restrict({y0: 1})
            if i == 1:
                PE = PE.restrict({y1: 1})
            if i == 2:
                PE = PE.restrict({y2: 1})
            if i == 3:
                PE = PE.restrict({y3: 1})
            if i == 4:
                PE = PE.restrict({y4: 1})
        else:
            if i == 0:
                PE = PE.restrict({y0: 0})
            if i == 1:
                PE = PE.restrict({y1: 0})
            if i == 2:
                PE = PE.restrict({y2: 0})
            if i == 3:
                PE = PE.restrict({y3: 0})
            if i == 4:
                PE = PE.restrict({y4: 0})
        i += 1
    return PE

if __name__ == '__main__':
    #Step 3.0: Set up node structure
    R = getEdges()
    pnodes = getPrime(R)
    enodes = getEven(R)
    print('Edge node structure: ' + str(R))
    print('Even node structure: ' + str(enodes))
    print('Prime node structure: ' + str(pnodes))

    #Step 3.1: Get BDDs for RR, PRIME, EVEN
    PRIME = getBDD5(pnodes, 'x')
    EVEN = getBDD5(enodes, 'y')
    RR = getBDD10(R)

    #Step 3.2: Get BDD for RR2, which is every node reached in two steps
    RR2 = comp(RR, RR)

    #Step 3.3: Get BDD for RR2s, which is every node reachable in even steps
    RR2s = transitiveClosure(RR2)

    #Step 3.4: Get PE, which is an expression such that x varibles make a prime number, y varibles make an even
    #          number, and x reaches y in even steps
    PE = RR2s & PRIME & EVEN

    #Step 3.5: Get validity of statement A, being for every node u in prime, there is a node v in even such that
    #          u reaches v in even steps
    val = statementA(PRIME, EVEN, RR2s)
    print('Statement A: ' + str(bool(val)))

    #Bonus: Test a valid set of numbers on PE

    # 1. If the prime number is 5, then it can reach 8 and 13 in one step.
    # 2. Go to 8. 8 can reach 16 in one step.
    # 3. Go to 16. 5 reaches 16 in 2 steps, which is even.
    t = testCase(PE, 5, 16)
    print('Test case 1 : ' + str(bool(t)))

    # Test should not work on this case, because the second number is not even
    t = testCase(PE, 5, 11)
    print('Test case 2 : ' + str(bool(t)))







