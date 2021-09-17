class Value:
    """
    "Value" objects represent the string, array, and code-array constants that are pushed onto the stack.  
    
    In our interpreter,
        -  For simplicity, the integers and boolean values are pushed onto the opstack as integers and booleans, respectively. 
        -  Similarly, name constants (e.g. '/x') are pushed to the opstack as strings. 
        -  The string, array, and codearray constants are represented as StrConstant, ArrayConstant, and FunctionBody objects, 
           which are subclasses of the `Value`. 
        -  StrConstant, ArrayConstant, and FunctionBody implement the following methods in the `Value` interface:
            * apply : Evaluates the value. `apply` is only applicable to FunctionBody objects (applies the function, evaluates all the tokens in the function's code-array, i.e., FunctionBody )  
            * Conversts the value to  a human-readable version (i.e., string) for printing.
    """

    def __init__(self, value):
        self.value = value

    def apply(self, psstack):
        """
        Each subclass of Value implements its own `apply` method.
        Note that only `FunctionBody`s can be "applied"; attempting to apply a StrConstant or ArrayConstant will give an error. 
        """
        raise NotImplementedError

    def __str__(self):
        """
        Returns a parsable and human-readable version of this value (i.e. the string to be displayed in the interpreter).
        """
        raise NotImplementedError

    def __repr__(self):
        """
        Returns how this value is printed in our Python representation.
        """
        return "{}({})".format(type(self).__name__, self.value)

##---------------------------------------------------------

class StrConstant(Value):
    """A plain string constant delimited in paranthesis. Attempting to apply a `string constant` will give an error.
      The `value` attribute is the Python string that this value represents.

      You may add additional methods to this class as needed and use them in your operator implementations. 
    """
    def __init__(self, value):
        Value.__init__(self, value)
        self.value = value

    def apply(self, psstacks):
        raise TypeError("Ouch! Cannot apply `string constant` {} ".format(self.value))

    def __str__(self):
        return str(self.value)

# ------------------------------------------------------------

class ArrayConstant(Value):
    """An array constant delimited in square brackets. Attempting to apply an `array constant` will give an error.
      The `value` attribute is the Python list that this value represents.
    """
    def __init__(self, value):
        Value.__init__(self, value)
        self.value = value

    def apply(self, psstacks):
        raise TypeError("Ouch! Cannot apply `string constant` {} ".format(self.value))

    def __str__(self):
        return str(self.value)

# ------------------------------------------------------------

class FunctionBody(Value):
    """The constant-array that represents the body of a (user-defined) function. 
    
    The `body` attribute is a nested list of tokens.
    The tokens, which are themselves are codearrays, are included as sublists in `body`.  
    
    The `apply` method will evaluate each token in the `body` by calling token's `eval` method. 
    Tokens will be evaluated in in the current referencing environment (psstacks).  
    """
    def __init__(self, body):
        Value.__init__(self, body)
        self.body = body

    def apply(self, psstacks):
        # TO-DO in part2
        pass

    def __str__(self):
        # definition = LambdaExpr(self.parameters, self.body)
        return '<function {}>'.format(self.body)




