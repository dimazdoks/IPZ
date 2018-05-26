//
// Created by dimazdoks on 08.04.18.
//

#ifndef IPZ_OUT_H
#define IPZ_OUT_H

#include "../lexer/lexer.h"
using namespace std;

typedef struct _token _token;

void lexer_printToken(size_t column, size_t line, string str, size_t code);
void lexer_qPrintTokens(vector <_token> &vector_tokens);


#endif //IPZ_OUT_H
