import string

lowerabcs = string.ascii_lowercase
upperabcs = string.ascii_uppercase
keywords = ["while", "wain", "int", "if", "else", "println", "NULL", "new", "delete"]

def createNode (currentNode, defaultNode, exception):
    ## UPPERCASES and lowercases: if is an exception
    ## go to exception node
    for i in range (0, 26):
        if (upperabcs[i] == exception):
            print (currentNode, upperabcs[i], currentNode+exception)
        else:
            print (currentNode, upperabcs[i], defaultNode)

    for i in range (0, 26):
        if (lowerabcs[i] == exception):
            print (currentNode, lowerabcs[i], currentNode+exception)
        else:
            print (currentNode, lowerabcs[i], defaultNode)
    ## any numbers seen is still a string            
    for i in range (0, 10):
        print (currentNode, i, defaultNode)
    return

def createStates (state):
    created = 0
    displ = ""
    for i in range (0, state.__len__()):
        displ = displ + state[i]
        print (displ)
        created += 1
    return created

def keyword (word):
    state = word[0]
    for i in range (1, word.__len__()):
        createNode (state, "ID", word[i])
        state += word[i]
    createNode (state, "ID", "ID")
    return

def alphabet ():
    length = 0
    for i in range (0, 26):
        print (upperabcs[i])
        length += 1
    for i in range (0, 26):
        print (lowerabcs[i])
        length += 1
    for i in range (0, 10):
        print (i)
        length += 1
    symbols = "(){}=!<>+-*/%,;[]&"
    for i in range (0, symbols.__len__()):
        print (symbols[i])
        length += 1
    return length

def generateStates (listofStrings):
    for i in range (0, listofStrings.__len__()):
        createStates (listofStrings[i])
    return

def generateTransitions (listofStrings):
    for i in range (0, listofStrings.__len__()):
        keyword (listofStrings[i])
    return

def generateFinishStates (listofStrings):
    for i in range (0, listofStrings.__len__()):
        print (listofStrings[i])
    return

generateStates (keywords)
#generateFinishStates (keywords)
#generateTransitions (["ID"])
#generateTransitions (keywords)
