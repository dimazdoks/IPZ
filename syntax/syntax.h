//
// Created by dimazdoks on 28.05.18.
//

#ifndef IPZ_SYNTAX_H
#define IPZ_SYNTAX_H

#include "../tree/tree.h"
const string space = "   ";
const _token token_null_data = _token();

void syntax_main(vector <_token> &vector_tokens, node &Tree);
void syntax_signal_program(vector <_token> &vector_tokens, int &i, string padding, node &Tree) ;
void syntax_program(vector <_token> &vector_tokens, int &i, string padding, node &Tree);
void syntax_block(vector <_token> &vector_tokens, int &i, string padding, node &Tree);
void syntax_declarations(vector <_token> &vector_tokens, int &i, string padding, node &Tree);
void syntax_variable_declarations(vector <_token> &vector_tokens, int &i, string padding, node &Tree);
void syntax_declarations_list(vector <_token> &vector_tokens, int &i, string padding, node &Tree);
void syntax_declaration(vector <_token> &vector_tokens, int &i, string padding, node &Tree);
void syntax_identifiers_list(vector <_token> &vector_tokens, int &i, string padding, node &Tree);
void syntax_attributes_list(vector <_token> &vector_tokens, int &i, string padding, node &Tree);
void syntax_attribute(vector <_token> &vector_tokens, int &i, string padding, node &Tree);
void syntax_range_list(vector <_token> &vector_tokens, int &i, string padding, node &Tree);
void syntax_range(vector <_token> &vector_tokens, int &i, string padding, node &Tree);
void syntax_variable_identifier(vector <_token> &vector_tokens, int &i, string padding, node &Tree);
void syntax_procedure_identifier(vector <_token> &vector_tokens, int &i, string padding, node &Tree);
void syntax_identifier(vector <_token> &vector_tokens, int &i, string padding, node &Tree);
void syntax_unsigned_integer(vector <_token> &vector_tokens, int &i, string padding, node &Tree);

#endif //IPZ_SYNTAX_H
