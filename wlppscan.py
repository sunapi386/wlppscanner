import string


#    setT( ST_START,      ".",            ST_DOT        );
#    setT( ST_DOT,        "w",            ST_DOTW       );
#    setT( ST_DOTW,       "o",            ST_DOTWO      );
#    setT( ST_DOTWO,      "r",            ST_DOTWOR     );
#    setT( ST_DOTWOR,     "d",            ST_DOTWORD    );
Q = '"'
com = ","
pre = "ST_"
keywords = ["DELETE","ELSE","IF","INT","PRINTLN","NULL","NEW","WAIN","WHILE"]
src = "ST_START,"
dst = "ST_DOT,"
via = '".",'
kw = ["wain", "int", "if", "else", "while", "println", "return", "NULL", "new", "delete"]
sy = ["(", ")", "{", "}", "[", "]", "==", "!=",
        "<", ">", "<=", ">=", "+", "-", "*", "/",
        "%", ",", ";", "&"]
na = ["LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACK", "RBRACK", "EQ", "NE",
        "LT", "GT", "LE", "GE", "PLUS", "MINUS", "STAR", "SLASH",
        "PCT", "COMMA", "SEMI", "AMP"]
er = "NULLadefhilnprstuw"
letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"


def printline (src,via,dst):
    print( "setT( {0:15}{1:16}{2:15});".format(pre+src+com,Q+via+Q+com,pre+dst) )

def printline_noquote (src,dst,via):
    print( "setT( {0:15}{1:16}{2:15});".format(pre+src+com,via+com,pre+dst) )


def returnTransitions (word):
    cur = ""
    for i in range( 0, word.__len__()-1):
        cur += word[i]
        src = cur.upper()
        dst = "sans_" + word[i+1] + " digits"
        via = "ID"
        printline_noquote (src, via, dst)
#    printline_noquote (word.upper(),"ID", "letters digits")

#returnTransitions ("return")

def superReturnTransitions (somelist):
    for i in range (0, somelist.__len__()):
        returnTransitions (somelist[i])

#superReturnTransitions (kw)
#setT( ST_W,          sans_a digits,  ST_ID          );
#setT( ST_WA,         sans_i digits,  ST_ID          );
#setT( ST_WAI,        sans_n digits,  ST_ID          );
#setT( ST_I,          sans_n digits,  ST_ID          );
#setT( ST_IN,         sans_t digits,  ST_ID          );
#setT( ST_I,          sans_f digits,  ST_ID          );
#setT( ST_E,          sans_l digits,  ST_ID          );
#setT( ST_EL,         sans_s digits,  ST_ID          );
#setT( ST_ELS,        sans_e digits,  ST_ID          );
#setT( ST_W,          sans_h digits,  ST_ID          );
#setT( ST_WH,         sans_i digits,  ST_ID          );
#setT( ST_WHI,        sans_l digits,  ST_ID          );
#setT( ST_WHIL,       sans_e digits,  ST_ID          );
#setT( ST_P,          sans_r digits,  ST_ID          );
#setT( ST_PR,         sans_i digits,  ST_ID          );
#setT( ST_PRI,        sans_n digits,  ST_ID          );
#setT( ST_PRIN,       sans_t digits,  ST_ID          );
#setT( ST_PRINT,      sans_l digits,  ST_ID          );
#setT( ST_PRINTL,     sans_n digits,  ST_ID          );
#setT( ST_R,          sans_e digits,  ST_ID          );
#setT( ST_RE,         sans_t digits,  ST_ID          );
#setT( ST_RET,        sans_u digits,  ST_ID          );
#setT( ST_RETU,       sans_r digits,  ST_ID          );
#setT( ST_RETUR,      sans_n digits,  ST_ID          );
#setT( ST_N,          sans_U digits,  ST_ID          );
#setT( ST_Nu,         sans_L digits,  ST_ID          );
#setT( ST_NuL,        sans_L digits,  ST_ID          );
#setT( ST_N,          sans_e digits,  ST_ID          );
#setT( ST_Ne,         sans_w digits,  ST_ID          );
#setT( ST_D,          sans_e digits,  ST_ID          );
#setT( ST_DE,         sans_l digits,  ST_ID          );
#setT( ST_DEL,        sans_e digits,  ST_ID          );
#setT( ST_DELE,       sans_t digits,  ST_ID          );
#setT( ST_DELET,      sans_e digits,  ST_ID          );

def filterL (string):
    for i in range (0, string.__len__()):
        line = letters
        print("#define sans_" + string[i] + '      "'+ line.translate( None, string[i]) + '"')

#filterL (er)


def printList (klist):
    toprint = ""
    for i in range (0, klist.__len__()):
        toprint += klist[i]
    print (toprint)

#printList (kw)
#printList (sy)

def createNode (src, word):
    via = ""
    dst = ""
    frm = ""
    for i in range (0, word.__len__()):
        if (i == 0):
            frm = src
        else:
            frm = dst
        dst += word[i]
        via = word[i]
        printline (frm, dst, via)

#setT( ST_DE,         letters digits, ST_ID          );
def circularRef (src, word):
    via = "letters digits"
    dst = "ID"
    frm = ""
    for i in range (0, word.__len__()):
        if (i==0):
            frm = src
        else:
            frm = word[0:i]
        print( "setT( {0:15}{1:16}{2:15});".format(pre+frm+com,via+com,pre+dst) )
#circularRef ("START", "START")

def generateCirc (klist):
    for i in range (0, klist.__len__()):
        circularRef ("START", klist[i])
#generateCirc (keywords)

def generateKeywords (klist):
    for i in range (0, klist.__len__()):
        createNode ("START", klist[i])

def genSymbols (names, symbols):
    for i in range (0, symbols.__len__()):
        printline ("START", names[i], symbols[i])

def promptTupleInput (size):
    t = []
    for i in range (0, size):
        inp = input( "{0} Input: ".format(i)).strip()
        t.append(inp)
    print (t)




#promptTupleInput(10)
#setT( ST_START,      start_lett,     ST_ID         );




#printline ("START", "LPAREN", "(")
#createNode ("START","RETURN")

#generateKeywords ("RETURN")
#createNode ("START", "RETURN")
#setT( ST_START,      "W",            ST_W           );
#setT( ST_START,      "H",            ST_WH          );
#setT( ST_START,      "I",            ST_WHI         );
#setT( ST_START,      "L",            ST_WHIL        );
#setT( ST_START,      "E",            ST_WHILE       );
#setT( ST_START,      "W",            ST_W           );
#setT( ST_START,      "A",            ST_WA          );
#setT( ST_START,      "I",            ST_WAI         );
#setT( ST_START,      "N",            ST_WAIN        );
#setT( ST_START,      "I",            ST_I           );
#setT( ST_START,      "N",            ST_IN          );
#setT( ST_START,      "T",            ST_INT         );
#setT( ST_START,      "I",            ST_I           );
#setT( ST_START,      "F",            ST_IF          );
#setT( ST_START,      "E",            ST_E           );
#setT( ST_START,      "L",            ST_EL          );
#setT( ST_START,      "S",            ST_ELS         );
#setT( ST_START,      "E",            ST_ELSE        );
#setT( ST_START,      "P",            ST_P           );
#setT( ST_START,      "R",            ST_PR          );
#setT( ST_START,      "I",            ST_PRI         );
#setT( ST_START,      "N",            ST_PRIN        );
#setT( ST_START,      "T",            ST_PRINT       );
#setT( ST_START,      "L",            ST_PRINTL      );
#setT( ST_START,      "N",            ST_PRINTLN     );
#setT( ST_START,      "N",            ST_N           );
#setT( ST_START,      "U",            ST_NU          );
#setT( ST_START,      "L",            ST_NUL         );
#setT( ST_START,      "L",            ST_NULL        );
#setT( ST_START,      "N",            ST_N           );
#setT( ST_START,      "E",            ST_NE          );
#setT( ST_START,      "W",            ST_NEW         );
#setT( ST_START,      "D",            ST_D           );
#setT( ST_START,      "E",            ST_DE          );
#setT( ST_START,      "L",            ST_DEL         );
#setT( ST_START,      "E",            ST_DELE        );
#setT( ST_START,      "T",            ST_DELET       );
#setT( ST_START,      "E",            ST_DELETE      );

#genSymbols (na, sy)
#setT( ST_START,      "(",            ST_LPAREN      );
#setT( ST_START,      ")",            ST_RPAREN      );
#setT( ST_START,      "{",            ST_LBRACE      );
#setT( ST_START,      "}",            ST_RBRACE      );
#setT( ST_START,      "[",            ST_LBRACK      );
#setT( ST_START,      "]",            ST_RBRACK      );
#setT( ST_START,      "==",           ST_EQ          );
#setT( ST_START,      "!=",           ST_NE          );
#setT( ST_START,      "<",            ST_LT          );
#setT( ST_START,      ">",            ST_GT          );
#setT( ST_START,      "<=",           ST_LE          );
#setT( ST_START,      ">=",           ST_GE          );
#setT( ST_START,      "+",            ST_PLUS        );
#setT( ST_START,      "-",            ST_MINUS       );
#setT( ST_START,      "*",            ST_STAR        );
#setT( ST_START,      "/",            ST_SLASH       );
#setT( ST_START,      "%",            ST_PCT         );
#setT( ST_START,      ",",            ST_COMMA       );
#setT( ST_START,      ";",            ST_SEMI        );
#setT( ST_START,      "&",            ST_AMP         );

