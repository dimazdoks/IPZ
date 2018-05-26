//
// Created by dimazdoks on 08.04.18.
//
#include "error.h"

void lexer_error(size_t line, size_t column, char ch, vector <_token> &vector_tokens) {
    lexer_qPrintTokens(vector_tokens);
    cout << "Lexer: Error (line " << line << ", column "
         << column << "): Illegal symbol ‘" << ch << "’" << endl;
    exit(1);
}

void lexer_eof() {
    cout << "Lexer: Error (end of file!)" << endl;
    exit(2);
}