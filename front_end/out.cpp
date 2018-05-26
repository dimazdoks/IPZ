//
// Created by dimazdoks on 08.04.18.
//
#include"out.h"

void lexer_printToken(size_t column, size_t line, string str, size_t code) {
    cout << setw(5) << line << ' ' << setw(5) << column << ' ' << setw(5) << code << ' ' << setw(12) << str << endl;
}

void lexer_qPrintTokens(vector <_token> &vector_tokens) {
    _token newToken;
    size_t i = 0;
    for (i; i < vector_tokens.size(); i++) {
        newToken = vector_tokens[i];
        lexer_printToken(newToken.column, newToken.line, newToken.token, newToken.code);
    }
}
