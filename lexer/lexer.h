//
// Created by dimazdoks on 08.04.18.
//

#ifndef IPZ_LEXER_H
#define IPZ_LEXER_H

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#include <iterator>
#include <functional>
#include <algorithm>
#include "../front_end/out.h"
#include "../front_end/error.h"

using namespace std;

/* <--- STRUCTURES ---> */
typedef enum _TokenType {
    TT_Single_separators,
    TT_Multi_separators,
    TT_Keywords,
    TT_Constants,
    TT_Identifiers
}TokenType;

struct _token {
    size_t line;
    size_t  column;
    size_t code;
    string token;
    TokenType type;
};

const set <char> set_separators( {';', ':', ',', '[', ']', '.'} );
const set <char> set_ws( {(char(32)), char(13), char(10), char(9), char(11), char(12)} );

const map <string, size_t> map_words = { {"PROGRAM", 401},  {"VAR", 402}, {"SIGNAL", 403},
                                   {"COMPLEX", 404}, {"INTEGER", 405},   {"FLOAT", 406},
                                   {"BLOCKFLOAT", 407}, {"EXT", 408},   {"BEGIN", 409}, {"END", 410}};


/* <--- FUNCTIONS ---> */

int lexer_isChar(char ch);
int lexer_isDigit(char ch);
int lexer_isSeparators(char ch);
int lexer_isWs(char ch);

void lexer_addToken(size_t line, size_t column, size_t code,
                    string token, TokenType type, vector <_token> &vector_tokens);

void lexer_isComment(istream &fin, size_t &column, size_t &line, vector <_token> &vector_tokens);
string lexer_makeStr(ifstream &fin, char &ch, int itIsChar, size_t line, size_t column, vector <_token> &vector_tokens);

string lexer_isDoubleDot(ifstream &fin, char &ch);
vector <_token> lexer_main(ifstream &fin);

#endif //IPZ_LEXER_H
