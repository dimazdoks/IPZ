//
// Created by dimazdoks on 08.04.18.
//

#ifndef IPZ_ERROR_H
#define IPZ_ERROR_H

#include "../lexer/lexer.h"
using namespace std;

typedef struct _token _token;

void lexer_error(size_t line, size_t column, char ch, vector <_token> &vector_tokens);
void lexer_eof();

#endif //IPZ_ERROR_H
