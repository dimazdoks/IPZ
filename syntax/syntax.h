//
// Created by dimazdoks on 28.05.18.
//

#ifndef IPZ_SYNTAX_H
#define IPZ_SYNTAX_H

#include "../lexer/lexer.h"
const string space = "   ";

void syntax_main(vector <_token> &vector_tokens);
void syntax_signal_program(vector <_token> &vector_tokens, int &i, string padding) ;
void syntax_program(vector <_token> &vector_tokens, int &i, string padding);
void syntax_block(vector <_token> &vector_tokens, int &i, string padding);
void syntax_declarations(vector <_token> &vector_tokens, int &i, string padding);
void syntax_variable_declarations(vector <_token> &vector_tokens, int &i, string padding);
void syntax_declarations_list(vector <_token> &vector_tokens, int &i, string padding);
void syntax_declaration(vector <_token> &vector_tokens, int &i, string padding);
void syntax_identifiers_list(vector <_token> &vector_tokens, int &i, string padding);
void syntax_attributes_list(vector <_token> &vector_tokens, int &i, string padding);
void syntax_attribute(vector <_token> &vector_tokens, int &i, string padding);
void syntax_range_list(vector <_token> &vector_tokens, int &i, string padding);
void syntax_range(vector <_token> &vector_tokens, int &i, string padding);
void syntax_variable_identifier(vector <_token> &vector_tokens, int &i, string padding);
void syntax_procedure_identifier(vector <_token> &vector_tokens, int &i, string padding);
void syntax_identifier(vector <_token> &vector_tokens, int &i, string padding);
void syntax_unsigned_integer(vector <_token> &vector_tokens, int &i, string padding);

#endif //IPZ_SYNTAX_H
