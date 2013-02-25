// Modified
#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
using namespace std;

//======================================================================
//========= Declarations for the scan() function =======================
//======================================================================

// Each token has one of the following kinds.

enum Kind {
    ID,                 // (A-Z,a-z)(0-9,A-Z,a-z)* but not equal a key
    NUM,                // A decimal integer type
    ZERO,               // special state for 0
    LPAREN,             // (
    RPAREN,             // )
    LBRACE,             // {
    RBRACE,             // }
    LBRACK,             // [
    RBRACK,             // ]
    AMP,                // &
    NuLL,               // "NULL"
    RETURN,             // "return"
    IF,                 // "if"
    ELSE,               // "else"
    WHILE,              // "while"
    PRINTLN,            // "println"
    WAIN,               // "wain"
    NeW,                // "new"
    DELETE,             // "delete"
    BECOMES,            // "="
    INT,                // "int"
    EQ,                 // "=="
    NE,                 // "!="
    LT,                 // "<"
    GT,                 // ">"
    LE,                 // "<="
    GE,                 // ">="
    PLUS,               // "+"
    MINUS,              // "-"
    STAR,               // "*"
    SLASH,              // "/"
    PCT,                // "%"
    COMMA,              // ","
    SEMI,               // ";"
    SPACE,              // ASCII 32
    TAB,                // ASCII 9
    NEWLINE,            // ASCII 10
    COMMENT,            // "//" followed by characters up to and including  NEWLINE
    INVALID             // Bad/invalid token
};

// kindString(k) returns string a representation of kind k
// that is useful for error and debugging messages.
string kindString(Kind k);

// Each token is described by its kind and its lexeme.

struct Token {
    Kind      kind;
    string    lexeme;
    /* toInt() returns an integer representation of the token. For tokens
     * of kind INT (decimal integer constant),
     * returns the integer constant.
     */
    int       toInt();
};

// scan() separates an input line into a vector of Tokens.
vector<Token> scan(string input);

// =====================================================================
// The implementation of scan() and associated type definitions.
// If you just want to use the scanner, skip to the next ==== separator.

// States for the finite-state automaton that comprises the scanner.

enum State {
    ST_INVALID,
    ST_START,
    ST_R,
    ST_RE,
    ST_RET,
    ST_RETU,
    ST_RETUR,
    ST_RETURN,
    ST_W,
    ST_WH,
    ST_WHI,
    ST_WHIL,
    ST_WHILE,
    ST_WA,
    ST_WAI,
    ST_WAIN,
    ST_I,
    ST_IN,
    ST_INT,
    ST_IF,
    ST_E,
    ST_EL,
    ST_ELS,
    ST_ELSE,
    ST_P,
    ST_PR,
    ST_PRI,
    ST_PRIN,
    ST_PRINT,
    ST_PRINTL,
    ST_PRINTLN,
    ST_N,
    ST_Nu,
    ST_NuL,
    ST_NuLL,
    ST_Ne,
    ST_NeW,
    ST_D,
    ST_DE,
    ST_DEL,
    ST_DELE,
    ST_DELET,
    ST_DELETE,
    ST_ID,
    ST_ZERO,
    ST_NUM,
    ST_LPAREN,
    ST_RPAREN,
    ST_LBRACE,
    ST_RBRACE,
    ST_BECOMES,
    ST_EQ,
    ST_NE,
    ST_BANG,
    ST_LT,
    ST_GT,
    ST_LE,
    ST_GE,
    ST_PLUS,
    ST_MINUS,
    ST_STAR,
    ST_SLASH,
    ST_PCT,
    ST_COMMA,
    ST_SEMI,
    ST_LBRACK,
    ST_RBRACK,
    ST_AMP,
    ST_COMMENT,
    ST_TAB,
    ST_NEWLINE,
    ST_SPACE
};

// The *kind* of token (see previous enum declaration)
// represented by each state; states that don't represent
// a token have stateKinds == INVALID.

Kind stateKinds[] = {
    INVALID,			//    ST_INVALID
    INVALID,			//    ST_START
    ID,     			//    ST_R
    ID,     			//    ST_RE
    ID,     			//    ST_RET
    ID,     			//    ST_RETU
    ID,     			//    ST_RETUR
    RETURN,             //    ST_RETURN
    ID,     			//    ST_W
    ID,     			//    ST_WH
    ID,     			//    ST_WHI
    ID,     			//    ST_WHIL
    WHILE,				//    ST_WHILE
    ID,     			//    ST_WA
    ID,     			//    ST_WAI
    WAIN,				//    ST_WAIN
    ID,     			//    ST_I
    ID,     			//    ST_IN
    INT,				//    ST_INT
    IF,					//    ST_IF
    ID,     			//    ST_E
    ID,     			//    ST_EL
    ID,     			//    ST_ELS
    ELSE,				//    ST_ELSE
    ID,     			//    ST_P
    ID,     			//    ST_PR
    ID,     			//    ST_PRI
    ID,     			//    ST_PRIN
    ID,     			//    ST_PRINT
    ID,     			//    ST_PRINTL
    PRINTLN,			//    ST_PRINTLN
    ID,     			//    ST_N
    ID,     			//    ST_NU
    ID,     			//    ST_NUL
    NuLL,				//    ST_NULL
    ID,     			//    ST_NE
    NeW,				//    ST_NEW
    ID,     			//    ST_D
    ID,     			//    ST_DE
    ID,     			//    ST_DEL
    ID,     			//    ST_DELE
    ID,     			//    ST_DELET
    DELETE,				//    ST_DELETE
    ID,					//    ST_ID
    ZERO,				//    ST_ZERO
    NUM,				//    ST_NUM
    LPAREN,	    		//    ST_LPARENS
    RPAREN, 			//    ST_RPARENS
    LBRACE,				//    ST_LBRACE
    RBRACE,				//    ST_RBRACE
    BECOMES,			//    ST_BECOMES
    EQ,					//    ST_EQ
    NE,					//    ST_NE
    INVALID,			//    ST_BANG
    LT,					//    ST_LT
    GT,					//    ST_GT
    LE,					//    ST_LE
    GE,					//    ST_GE
    PLUS,				//    ST_PLUS
    MINUS,				//    ST_MINUS
    STAR,				//    ST_STAR
    SLASH,				//    ST_SLASH
    PCT,				//    ST_PCT
    COMMA,				//    ST_COMMA
    SEMI,				//    ST_SEMI
    LBRACK,				//    ST_LBRACK
    RBRACK,				//    ST_RBRACK
    AMP,				//    ST_AMP
    COMMENT,			//    ST_COMMENT
    TAB,				//    ST_TAB
    NEWLINE,			//    ST_NEWLINE
    SPACE				//    ST_SPACE
};

State delta[ST_SPACE+1][256];

#define whitespace  " \t\n\r"
#define letters     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define firstStart  "ABCDEFGHIJKLMOPQRSTUVWXYZabcfghjklmoqstuvxyz"
#define digits      "0123456789"
#define oneToNine   "123456789"
#define symbols     "(){}[]==!=<><=>=+-*/%,;&"
#define sans_N      "ABCDEFGHIJKLMOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define sans_U      "ABCDEFGHIJKLMNOPQRSTVWXYZabcdefghijklmnopqrstuvwxyz"
#define sans_L      "ABCDEFGHIJKMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define sans_L      "ABCDEFGHIJKMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define sans_a      "ABCDEFGHIJKLMNOPQRSTUVWXYZbcdefghijklmnopqrstuvwxyz"
#define sans_d      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcefghijklmnopqrstuvwxyz"
#define sans_e      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdfghijklmnopqrstuvwxyz"
#define sans_f      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdeghijklmnopqrstuvwxyz"
#define sans_h      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefgijklmnopqrstuvwxyz"
#define sans_i      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghjklmnopqrstuvwxyz"
#define sans_l      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz"
#define sans_n      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmopqrstuvwxyz"
#define sans_p      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnoqrstuvwxyz"
#define sans_r      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqstuvwxyz"
#define sans_s      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrtuvwxyz"
#define sans_t      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrsuvwxyz"
#define sans_u      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstvwxyz"
#define sans_w      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvxyz"
#define sans_ah     "ABCDEFGHIJKLMNOPQRSTUVWXYZbcdefgijklmnopqrstuvwxyz"
#define sans_nf     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdeghijklmopqrstuvwxyz"
#define sans_Ue     "ABCDEFGHIJKLMNOPQRSTVWXYZabcdfghijklmnopqrstuvwxyz"

void setT(State from, string chars, State to) {
    for(unsigned i = 0; i < chars.length(); i++ ) delta[from][chars[i]] = to;
}

void initT(){
    int i, j;

    // The default transition is ST_INVALID (i.e., no transition
    // defined for this char).
    for ( i=0; i<=ST_SPACE; i++ ) {
        for ( j=0; j<256; j++ ) {
            delta[i][j] = ST_INVALID;
        }
    }
    // Non-null transitions of the finite state machine.
    // NB: in the third line below, letters digits are macros
    // that are replaced by string literals, which the compiler
    // will concatenate into a single string literal.
    setT( ST_START,      whitespace,     ST_SPACE       );
    setT( ST_SPACE,      whitespace,     ST_SPACE       );
    setT( ST_START,      firstStart,     ST_ID          );
    setT( ST_ID,         letters digits, ST_ID          );
    setT( ST_START,      oneToNine,      ST_NUM         );
    setT( ST_NUM,        digits,         ST_NUM         );
    setT( ST_START,      "0",            ST_ZERO        );
    setT( ST_ZERO,       letters digits, ST_INVALID     );

// keywords
    setT( ST_START,      "r",            ST_R           );
    setT( ST_R,          "e",            ST_RE          );
    setT( ST_RE,         "t",            ST_RET         );
    setT( ST_RET,        "u",            ST_RETU        );
    setT( ST_RETU,       "r",            ST_RETUR       );
    setT( ST_RETUR,      "n",            ST_RETURN      );
    setT( ST_RETURN,     letters digits, ST_ID          );
    setT( ST_START,      "d",            ST_D           );
    setT( ST_D,          "e",            ST_DE          );
    setT( ST_DE,         "l",            ST_DEL         );
    setT( ST_DEL,        "e",            ST_DELE        );
    setT( ST_DELE,       "t",            ST_DELET       );
    setT( ST_DELET,      "e",            ST_DELETE      );
    setT( ST_DELETE,     letters digits, ST_ID          );
    setT( ST_START,      "e",            ST_E           );
    setT( ST_E,          "l",            ST_EL          );
    setT( ST_EL,         "s",            ST_ELS         );
    setT( ST_ELS,        "e",            ST_ELSE        );
    setT( ST_ELSE,       letters digits, ST_ID          );
    setT( ST_START,      "i",            ST_I           );
    setT( ST_I,          "f",            ST_IF          );
    setT( ST_IF,         letters digits, ST_ID          );
    setT( ST_I,          "n",            ST_IN          );
    setT( ST_IN,         "t",            ST_INT         );
    setT( ST_INT,        letters digits, ST_ID          );
    setT( ST_START,      "p",            ST_P           );
    setT( ST_P,          "r",            ST_PR          );
    setT( ST_PR,         "i",            ST_PRI         );
    setT( ST_PRI,        "n",            ST_PRIN        );
    setT( ST_PRIN,       "t",            ST_PRINT       );
    setT( ST_PRINT,      "l",            ST_PRINTL      );
    setT( ST_PRINTL,     "n",            ST_PRINTLN     );
    setT( ST_PRINTLN,    letters digits, ST_ID          );
    setT( ST_START,      "N",            ST_N           );
    setT( ST_N,          "U",            ST_Nu          );
    setT( ST_Nu,         "L",            ST_NuL         );
    setT( ST_NuL,        "L",            ST_NuLL        );
    setT( ST_NuLL,       letters digits, ST_ID          );
    setT( ST_START,      "n",            ST_N           );
    setT( ST_N,          "e",            ST_Ne          );
    setT( ST_Ne,         "w",            ST_NeW         );
    setT( ST_NeW,        letters digits, ST_ID          );
    setT( ST_START,      "w",            ST_W           );
    setT( ST_W,          "a",            ST_WA          );
    setT( ST_WA,         "i",            ST_WAI         );
    setT( ST_WAI,        "n",            ST_WAIN        );
    setT( ST_WAIN,       letters digits, ST_ID          );
    setT( ST_W,          "h",            ST_WH          );
    setT( ST_WH,         "i",            ST_WHI         );
    setT( ST_WHI,        "l",            ST_WHIL        );
    setT( ST_WHIL,       "e",            ST_WHILE       );
    setT( ST_WHILE,      letters digits, ST_ID          );

// reloop partial words to ID
    setT( ST_W,          sans_ah digits, ST_ID          );
    setT( ST_WA,         sans_i digits,  ST_ID          );
    setT( ST_WAI,        sans_n digits,  ST_ID          );
    setT( ST_I,          sans_nf digits, ST_ID          );
    setT( ST_IN,         sans_t digits,  ST_ID          );
    setT( ST_WH,         sans_i digits,  ST_ID          );
    setT( ST_WHI,        sans_l digits,  ST_ID          );
    setT( ST_WHIL,       sans_e digits,  ST_ID          );
    setT( ST_E,          sans_l digits,  ST_ID          );
    setT( ST_EL,         sans_s digits,  ST_ID          );
    setT( ST_ELS,        sans_e digits,  ST_ID          );
    setT( ST_P,          sans_r digits,  ST_ID          );
    setT( ST_PR,         sans_i digits,  ST_ID          );
    setT( ST_PRI,        sans_n digits,  ST_ID          );
    setT( ST_PRIN,       sans_t digits,  ST_ID          );
    setT( ST_PRINT,      sans_l digits,  ST_ID          );
    setT( ST_PRINTL,     sans_n digits,  ST_ID          );
    setT( ST_R,          sans_e digits,  ST_ID          );
    setT( ST_RE,         sans_t digits,  ST_ID          );
    setT( ST_RET,        sans_u digits,  ST_ID          );
    setT( ST_RETU,       sans_r digits,  ST_ID          );
    setT( ST_RETUR,      sans_n digits,  ST_ID          );
    
    setT( ST_N,          sans_Ue digits,ST_ID          );
    setT( ST_Nu,         sans_L digits,  ST_ID          );
    setT( ST_NuL,        sans_L digits,  ST_ID          );
    setT( ST_Ne,         sans_w digits,  ST_ID          );
    setT( ST_D,          sans_e digits,  ST_ID          );
    setT( ST_DE,         sans_l digits,  ST_ID          );
    setT( ST_DEL,        sans_e digits,  ST_ID          );
    setT( ST_DELE,       sans_t digits,  ST_ID          );
    setT( ST_DELET,      sans_e digits,  ST_ID          );

// symbols
    setT( ST_START,      "(",            ST_LPAREN      );
    setT( ST_START,      ")",            ST_RPAREN      );
    setT( ST_START,      "{",            ST_LBRACE      );
    setT( ST_START,      "}",            ST_RBRACE      );
    setT( ST_START,      "[",            ST_LBRACK      );
    setT( ST_START,      "]",            ST_RBRACK      );
    setT( ST_START,      "=",            ST_BECOMES     );
    setT( ST_BECOMES,    "=",            ST_EQ          );
    setT( ST_START,      "!",            ST_BANG        );
    setT( ST_BANG,       "=",            ST_NE          );
    setT( ST_START,      "<",            ST_LT          );
    setT( ST_START,      ">",            ST_GT          );
    setT( ST_LT,         "=",            ST_LE          );
    setT( ST_GT,         "=",            ST_GE          );
    setT( ST_START,      "+",            ST_PLUS        );
    setT( ST_START,      "-",            ST_MINUS       );
    setT( ST_START,      "*",            ST_STAR        );
    setT( ST_START,      "/",            ST_SLASH       );
    setT( ST_SLASH,      "/",            ST_COMMENT     );
    setT( ST_START,      "%",            ST_PCT         );
    setT( ST_START,      ",",            ST_COMMA       );
    setT( ST_START,      ";",            ST_SEMI        );
    setT( ST_START,      "&",            ST_AMP         );


    for ( j=0; j<256; j++ ) delta[ST_COMMENT][j] = ST_COMMENT;
}

static int initT_done = 0;

vector<Token> scan(string input){
    // Initialize the transition table when called for the first time.
    if(!initT_done) {
        initT();
        initT_done = 1;
    }

    vector<Token> ret;

    int i = 0;
    int startIndex = 0;
    State state = ST_START;

    if(input.length() > 0) {
        bool zeroPrev = false;
        while(true) {

            State nextState = ST_INVALID;
            if(i < input.length())
                nextState = delta[state][(unsigned char) input[i]];

////            cout << "state " << kindString(stateKinds[state]) << endl;
////            cout << "nextState " << kindString(stateKinds[nextState]) << endl;
//            cout << "currentItem: " << kindString(stateKinds[state]) << endl;
//            if (zeroPrev ) {
//                cout << "zeroPrev" << endl;
////                cout << "ERROR read this after 0: " << input.substr(0, i) << endl;
////                break;
//            }
//            if(state == ST_ZERO) {
//                zeroPrev = true;
//            } else {
//                zeroPrev = false;
//            }

            if(nextState == ST_INVALID) {
                cout << "TEST: invalid next state " << input.substr(0, i) << endl;
                if(stateKinds[state] == ID) {
                    throw("ERROR in lexing after reading " + input.substr(0, i));
                }
                // no more transitions possible
                if(stateKinds[state] == INVALID) {
                    throw("ERROR in lexing after reading " + input.substr(0, i));
                }
                if(stateKinds[state] != SPACE) {
                    Token token;
                    token.kind = stateKinds[state];
                    token.lexeme = input.substr(startIndex, i-startIndex);
                    ret.push_back(token);
                }
                startIndex = i;
                state = ST_START;
                if(i >= input.length()) break;
            } else {
                state = nextState;
                i++;
            }
        }
    }

    return ret;
}

int Token::toInt() {
    if(kind == NUM) {
        long long l;
        sscanf( lexeme.c_str(), "%lld", &l );
	if (lexeme.substr(0,1) == "-") {
            if(l < -2147483648LL)
                throw("ERROR: constant out of range: "+lexeme);
	} else {
	    unsigned long long ul = l;
            if(ul > 4294967295LL)
                throw("ERROR: constant out of range: "+lexeme);
	}
        return l;
    }
    throw("ERROR: attempt to convert non-integer token "+lexeme+" to Int");
}

// kindString maps each kind to a string for use in error messages.

string kS[] = {
    "ID",
    "NUM",
    "NUM",
    "LPAREN",
    "RPAREN",
    "LBRACE",
    "RBRACE",
    "LBRACK",
    "RBRACK",
    "AMP",
    "NULL",
    "RETURN",
    "IF",
    "ELSE",
    "WHILE",
    "PRINTLN",
    "WAIN",
    "NEW",
    "DELETE",
    "BECOMES",
    "INT",
    "EQ",
    "NE",
    "LT",
    "GT",
    "LE",
    "GE",
    "PLUS",
    "MINUS",
    "STAR",
    "SLASH",
    "PCT",
    "COMMA",
    "SEMI",
    "SPACE",
    "TAB",
    "NEWLINE",
    "COMMENT",
    "INVALID"
};

string kindString( Kind k ){
    if ( k < ID || k > INVALID ) return "INVALID";
    return kS[k];
}

//======================================================================
//======= A sample program demonstrating the use of the scanner. =======
//======================================================================

int main() {

    try {
        vector<string> srcLines;

        // Read the entire input file, storing each line as a
        // single string in the array srcLines.
        while(true) {
            string line;
            getline(cin, line);
            if(cin.fail()) break;
            srcLines.push_back(line);
        }

        // Tokenize each line, clestoring the results in tokLines.
        vector<vector<Token> > tokLines;

        for(int line = 0; line < srcLines.size(); line++) {
            tokLines.push_back(scan(srcLines[line]));
        }

        // Now we process the tokens.
        // Sample usage: print the tokens of each line.
        for(int line=0; line < tokLines.size(); line++ ) {
            for(int j=0; j < tokLines[line].size(); j++ ) {
                Token token = tokLines[line][j];
                if(token.kind == COMMENT) {
//                    cout << token.toInt();
//                    line += 1;
                    continue;
                }
                cout << kindString(token.kind) << " "
                    << token.lexeme;
                cout << endl;
            }
        }
    } catch(string msg) {
        cerr << msg << endl;
    }

    return 0;
}

