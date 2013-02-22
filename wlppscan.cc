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
    LPARENS,            // (
    RPARENS,            // )
    LBRACE,             // {
    RBRACE,             // }
    LBRACK,             // [
    RBRACK,             // ]
    AMP,                // &
    NULL,               // "NULL"
    RETURN,             // "return"
    IF,                 // "if"
    ELSE,               // "else"
    WHILE,              // "while"
    PRINTLN,            // "println"
    WAIN,               // "wain"
    NEW,                // "new"
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
    ST_START
    ST_INVALID
    ST_W
    ST_WH
    ST_WHI
    ST_WHIL
    ST_WHILE
    ST_WA
    ST_WAI
    ST_WAIN
    ST_I
    ST_IN
    ST_INT
    ST_IF
    ST_E
    ST_EL
    ST_ELS
    ST_ELSE
    ST_P
    ST_PR
    ST_PRI
    ST_PRIN
    ST_PRINT
    ST_PRINTL
    ST_PRINTLN
    ST_N
    ST_NU
    ST_NUL
    ST_NULL
    ST_N
    ST_NE
    ST_NEW
    ST_D
    ST_DE
    ST_DEL
    ST_DELE
    ST_DELET
    ST_DELETE
    ST_ID
    ST_ZERO
    ST_NUM
    ST_LPARENS
    ST_RPARENS
    ST_LBRACE
    ST_RBRACE
    ST_BECOMES
    ST_EQ
    ST_NE
    ST_BANG
    ST_LT
    ST_GT
    ST_LE
    ST_GE
    ST_PLUS
    ST_MINUS
    ST_STAR
    ST_SLASH
    ST_PCT
    ST_COMMA
    ST_SEMI
    ST_LBRACK
    ST_RBRACK
    ST_AMP
    ST_SPACE
    ST_TAB             
    ST_NEWLINE
    ST_COMMENT
};

// The *kind* of token (see previous enum declaration)
// represented by each state; states that don't represent
// a token have stateKinds == NUL.

Kind stateKinds[] = {
    INVALID			//    ST_START
    INVALID			//    ST_INVALID
    INVALID			//    ST_W
    INVALID			//    ST_WH
    INVALID			//    ST_WHI
    INVALID			//    ST_WHIL
    WHILE			//    ST_WHILE
    INVALID			//    ST_WA
    INVALID			//    ST_WAI
    WAIN			//    ST_WAIN
    INVALID			//    ST_I
    INVALID			//    ST_IN
    INT				//    ST_INT
    IF				//    ST_IF
    INVALID			//    ST_E
    INVALID			//    ST_EL
    INVALID			//    ST_ELS
    ELSE			//    ST_ELSE
    INVALID			//    ST_P
    INVALID			//    ST_PR
    INVALID			//    ST_PRI
    INVALID			//    ST_PRIN
    INVALID			//    ST_PRINT
    INVALID			//    ST_PRINTL
    PRINTLN			//    ST_PRINTLN
    INVALID			//    ST_N
    INVALID			//    ST_NU
    INVALID			//    ST_NUL
    NULL			//    ST_NULL
    INVALID			//    ST_N
    INVALID			//    ST_NE
    NEW				//    ST_NEW
    INVALID			//    ST_D
    INVALID			//    ST_DE
    INVALID			//    ST_DEL
    INVALID			//    ST_DELE
    INVALID			//    ST_DELET
    DELETE			//    ST_DELETE
    ID				//    ST_ID
    ZERO			//    ST_ZERO
    NUM				//    ST_NUM
    LPARENS			//    ST_LPARENS
    RPARENS			//    ST_RPARENS
    LBRACE			//    ST_LBRACE
    RBRACE			//    ST_RBRACE
    BECOMES			//    ST_BECOMES
    EQ				//    ST_EQ
    NE				//    ST_NE
    BANG			//    ST_BANG
    LT				//    ST_LT
    GT				//    ST_GT
    LE				//    ST_LE
    GE				//    ST_GE
    PLUS			//    ST_PLUS
    MINUS			//    ST_MINUS
    STAR			//    ST_STAR
    SLASH			//    ST_SLASH
    PCT				//    ST_PCT
    COMMA			//    ST_COMMA
    SEMI			//    ST_SEMI
    LBRACK			//    ST_LBRACK
    RBRACK			//    ST_RBRACK
    AMP				//    ST_AMP
    SPACE			//    ST_SPACE
    TAB				//    ST_TAB             
    NEWLINE			//    ST_NEWLINE
    COMMENT			//    ST_COMMENT
};

State delta[ST_SPACE+1][256];

#define space       " "
#define tab         "\t"
#define newline     "\n\r"
#define letters     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define start_lett  "ABCDEFGHIJKLMOPQRSTUVWXYZabcfghjklmoqrstuvxyz"
#define digits      "0123456789"
#define oneToNine   "123456789"

void setT(State from, string chars, State to) {
    for(int i = 0; i < chars.length(); i++ ) delta[from][chars[i]] = to;
}

void initT(){
    int i, j;

    // The default transition is ST_INVALID (i.e., no transition
    // defined for this char).
    for ( i=0; i<=ST_WHITESPACE; i++ ) {
        for ( j=0; j<256; j++ ) {
            delta[i][j] = ST_INVALID;
        }
    }
    // Non-null transitions of the finite state machine.
    // NB: in the third line below, letters digits are macros
    // that are replaced by string literals, which the compiler
    // will concatenate into a single string literal.
    setT( ST_START,      space,          ST_SPACE      );
    setT( ST_SPACE,      space,          ST_SPACE      );
    setT( ST_START,      start_lett,     ST_ID         );
    setT( ST_ID,         letters digits, ST_ID         );
    setT( ST_START,      oneToNine,      ST_INT        );
    setT( ST_INT,        digits,         ST_INT        );
    setT( ST_MINUS,      digits,      	 ST_INT        );
    setT( ST_DOLLAR,     digits,         ST_REGISTER   );
    setT( ST_REGISTER,   digits,         ST_REGISTER   );
    setT( ST_ZERO,       digits,      	 ST_INT        );
    setT( ST_ZEROX,      hexDigits,      ST_HEXINT     );
    setT( ST_HEXINT,     hexDigits,      ST_HEXINT     );
    setT( ST_ID,         ":",            ST_LABEL      );
    setT( ST_START,      ";",            ST_COMMENT    );
    setT( ST_START,      ".",            ST_DOT        );
    

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
        while(true) {
            State nextState = ST_NUL;
            if(i < input.length())
                nextState = delta[state][(unsigned char) input[i]];
            if(nextState == ST_NUL) {
                // no more transitions possible
                if(stateKinds[state] == NUL) {
                    throw("ERROR in lexing after reading " + input.substr(0, i));
                }
                if(stateKinds[state] != WHITESPACE) {
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
    if(kind == INT) {
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
    } else if(kind == HEXINT) {
        long long l;
        sscanf( lexeme.c_str(), "%llx", &l );
	unsigned long long ul = l;
        if(ul > 0xffffffffLL)
            throw("ERROR: constant out of range: "+lexeme);
        return l;
    } else if(kind == REGISTER) {
        long long l;
        sscanf( lexeme.c_str()+1, "%lld", &l );
	unsigned long long ul = l;
        if(ul > 31)
            throw("ERROR: constant out of range: "+lexeme);
        return l;
    }
    throw("ERROR: attempt to convert non-integer token "+lexeme+" to Int");
}

// kindString maps each kind to a string for use in error messages.

string kS[] = {
    "ID",           // ID
    "INT",          // INT
    "HEXINT",       // HEXINT
    "REGISTER",     // REGISTER
    "COMMA",        // COMMA
    "LPAREN",       // LPAREN
    "RPAREN",       // RPAREN
    "LABEL",        // LABEL
    "DOTWORD",      // DOTWORD
    "WHITESPACE",   // WHITESPACE
    "NUL"           // NUL
};

string kindString( Kind k ){
    if ( k < ID || k > NUL ) return "INVALID";
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

        // Tokenize each line, storing the results in tokLines.
        vector<vector<Token> > tokLines;

        for(int line = 0; line < srcLines.size(); line++) {
            tokLines.push_back(scan(srcLines[line]));
        }

        // Now we process the tokens.
        // Sample usage: print the tokens of each line.
        for(int line=0; line < tokLines.size(); line++ ) {
            for(int j=0; j < tokLines[line].size(); j++ ) {
                Token token = tokLines[line][j];
                cerr << "  Token: " << kindString(token.kind) 
                    << " {" << token.lexeme << "}";
                if(token.kind == INT || token.kind == HEXINT ||
                        token.kind == REGISTER) {
                    cerr << token.toInt();
                }
                cerr << endl;
            }
        }
    } catch(string msg) {
        cerr << msg << endl;
    }

    return 0;
}
