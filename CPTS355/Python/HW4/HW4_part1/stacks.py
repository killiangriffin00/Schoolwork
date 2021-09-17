from psElements import Value, StrConstant, ArrayConstant, FunctionBody
class Stacks:
    def __init__(self):
        #stack variables
        self.opstack = []  #assuming top of the stack is the end of the list
        self.dictstack = []  #assuming top of the stack is the end of the list
        
        #The builtin operators supported by our interpreter
        self.builtin_operators = {
             #TO-DO in part1
        }
    #-------  Operand Stack Operators --------------
    """
        Helper function. Pops the top value from opstack and returns it.
    """
    def opPop(self):
        val = self.opstack[0]
        del self.opstack[0]
        return val

    """
       Helper function. Pushes the given value to the opstack.
    """
    def opPush(self,value):
        self.opstack = [value] + self.opstack
        
    #------- Dict Stack Operators --------------
    
    """
       Helper function. Pops the top dictionary from dictstack and returns it.
    """   
    def dictPop(self):
        val = self.dictstack[0]
        del self.dictstack[0]
        return val


    """
       Helper function. Pushes the given dictionary onto the dictstack. 
    """   
    def dictPush(self,d):
        self.dictstack = [d] + self.dictstack

    """
       Helper function. Adds name:value pair to the top dictionary in the dictstack.
       (Note: If the dictstack is empty, first adds an empty dictionary to the dictstack then adds the name:value to that. 
    """   
    def define(self,name, value):
        if not self.dictstack:
            self.dictPush({})
        self.dictstack[0][name] = value

    """
       Helper function. Searches the dictstack for a variable or function and returns its value. 
       (Starts searching at the top of the opstack; if name is not found returns None and prints an error message.
        Make sure to add '/' to the beginning of the name.)
    """
    def lookup(self,name):
        i = 0
        while i < len(self.dictstack):
            for x in self.dictstack[i]:
                if x == "/" + name:
                    return self.dictstack[i]["/" + name]
            i += 1
        print("Name not found on top of dictstack.")
        return None
    
    #------- Arithmetic Operators --------------
    
    """
       Pops 2 values from opstack; checks if they are numerical (int); adds them; then pushes the result back to opstack. 
    """   
    def add(self):
        if len(self.opstack) > 1:
            op1 = self.opPop()
            op2 = self.opPop()
            if isinstance(op1,int) and isinstance(op2,int):
                self.opPush(op1 + op2)
            else:
                print("Error: add - one of the operands is not a number value")
                self.opPush(op2)
                self.opPush(op1)             
        else:
            print("Error: add expects 2 operands")
 
    """
       Pop 2 values from opstack; checks if they are numerical (int); subtracts them; and pushes the result back to opstack. 
    """   
    def sub(self):
        val1 = self.opPop()
        val2 = self.opPop()
        if isinstance(val1, int) and isinstance(val2, int):
            self.opPush(val2 - val1)

    """
        Pops 2 values from opstack; checks if they are numerical (int); multiplies them; and pushes the result back to opstack. 
    """    
    def mul(self):
        val1 = self.opPop()
        val2 = self.opPop()
        if isinstance(val1, int) and isinstance(val2, int):
            self.opPush(val2 * val1)

    #---------- Comparison Operators  -----------------
    """
       Pops the top two values from the opstack; pushes "True" is they are equal, otherwise pushes "False"
    """ 
    def eq(self):
        if self.opPop() == self.opPop():
            self.opPush(True)
        else:
            self.opPush(False)

    """
       Pops the top two values from the opstack; pushes "True" if the bottom value is less than the top value, otherwise pushes "False"
    """ 
    def lt(self):
        if self.opPop() > self.opPop():
            self.opPush(True)
        else:
            self.opPush(False)

    """
       Pops the top two values from the opstack; pushes "True" if the bottom value is greater than the top value, otherwise pushes "False"
    """ 
    def gt(self):
        if self.opPop() < self.opPop():
            self.opPush(True)
        else:
            self.opPush(False)

    # ------- String and Array Operators --------------
    """ 
       Pops a string or array value from the operand opstack and calculates the length of it. Pushes the length back onto the opstack.
       The `length` method should support both ArrayConstant and StrConstant values.
    """
    def length(self):
        val = self.opPop()
        if isinstance(val,StrConstant):
            self.opPush(len(val.value) - 2)
        elif isinstance(val,ArrayConstant):
            self.opPush(len(val.value))
        else:
            self.opPush(val)

    """ 
        Pops a StrConstant or an ArrayConstant and an index from the operand opstack.  
        If the argument is a StrConstant, pushes the ascii value of the the character in the string at the index onto the opstack;
        If the argument is an ArrayConstant, pushes the value at the `index` of array onto the opstack;
    """
    def get(self):
        index = self.opPop()
        val = self.opPop()
        if isinstance(val,StrConstant) and isinstance(index,int):
            self.opPush(ord(val.value[index + 1]))
        elif isinstance(val,ArrayConstant) and isinstance(index,int):
            self.opPush(val.value[index])
        else:
            self.opPush(index)
            self.opPush(val)


    """
    Pops a StrConstant or ArrayConstant value, an (zero-based) `index`, and an `item` from the opstack
    If the argument is a StrConstant, replaces the character at `index` of the StrConstant's string with the character having the ASCII value of `item`.
    If the argument is an ArrayConstant, replaces the element at `index` of the ArrayConstant's list with the value `item`.
    """
    def put(self):
        item = self.opPop()
        index = self.opPop()
        val = self.opPop()
        if isinstance(val,StrConstant) and isinstance(index,int) and isinstance(item,int):
            val.value = val.value[:index + 1] + chr(item) + val.value[index + 2:]
        elif isinstance(val,ArrayConstant) and isinstance(index,int) and isinstance(item,int):
            val.value[index] = item
        else:
            self.opPush(val)
            self.opPush(index)
            self.opPush(item)
            
    #------- Stack Manipulation and Print Operators --------------

    """
       This function implements the Postscript "pop operator". Calls self.opPop() to pop the top value from the opstack and discards the value. 
    """
    def pop (self):
        return self.opPop()

    """
       Prints the opstack. The end of the list is the top of the stack. 
    """
    def stack(self):
        print(self.opstack)

    """
       Copies the top element in opstack.
    """
    def dup(self):
        self.opPush(self.opstack[0])

    """
       Pops an integer count from opstack, copies count number of values in the opstack. 
    """
    def copy(self):
        val = self.opPop()
        s = self.opstack[:val]
        while val - 1 >= 0:
            self.opPush(s[val - 1])
            val = val - 1



    """
        Counts the number of elements in the opstack and pushes the count onto the top of the opstack.
    """
    def count(self):
        self.opPush(len(self.opstack))

    """
       Clears the opstack.
    """
    def clear(self):
        self.opstack.clear()
        
    """
       swaps the top two elements in opstack
    """
    def exch(self):
        temp1 = self.pop()
        temp2 = self.pop()
        self.opPush(temp1)
        self.opPush(temp2)

    """
       Pops an integer from the opstack (size argument) and pushes an  empty dictionary onto the opstack.
    """
    def psDict(self):
        self.opPop()
        self.opPush({})

    """
       Pops the dictionary at the top of the opstack; pushes it to the dictstack.
    """
    def begin(self):
        self.dictPush(self.opPop())

    """
       Removes the top dictionary from dictstack.
    """
    def end(self):
        del self.dictstack[0]
        
    """
       Pops a name and a value from opstack, adds the name:value pair to the top dictionary by calling define.  
    """
    def psDef(self):
        value = self.opPop()
        name = self.opPop()
        self.define(name, value)


    # ------- if/ifelse Operators --------------
    """
       Implements if operator. 
       Pops the `ifbody` and the `condition` from opstack. 
       If the condition is True, evaluates the `ifbody`.  
    """
    def psIf(self):
        pass
        # TO-DO in part2

    """
       Implements ifelse operator. 
       Pops the `elsebody`, `ifbody`, and the condition from opstack. 
       If the condition is True, evaluate `ifbody`, otherwise evaluate `elsebody`. 
    """
    def psIfelse(self):
        pass
        # TO-DO in part2


    #------- Loop Operators --------------
    """
       Implements for operator.   
       Pops the `loopbody`, `end`index, `increment`, `start` index arguments from opstack; 
       loop counter starts at `start` , incremented by `increment` value, and ends at `end`. 
       for each value of loop counter, push the counter value on opstack, and  evaluate the `loopbody`. 
    """   
    def psFor(self):
        pass
        # TO-DO in part2

    #--- used in the setup of unittests 
    def clearBoth(self):
        self.opstack[:] = []
        self.dictstack[:] = []
