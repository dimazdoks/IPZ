//
// Created by dimazdoks on 28.05.18.
//
#include "syntax.h"

void syntax_main(vector <_token> &vector_tokens) {
    int i=0;
    string padding = "";

    cout<<padding<<"<signal-program>"<<endl;
    syntax_signal_program(vector_tokens, i, padding);
    cout<<i<<endl;
}

void syntax_signal_program(vector <_token> &vector_tokens, int &i, string padding) {
    padding += space;

    cout<<padding<<"<program>"<<endl;
    syntax_program(vector_tokens, i, padding);
}

void syntax_program(vector <_token> &vector_tokens, int &i, string padding) {
    padding += "  ";

    if (vector_tokens[i].code != 401)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, "PROGRAM");
    else {
        cout<<padding<<"PROGRAM"<<endl;
        i++;
    }

    cout<<padding<<"<procedure-identifier>"<<endl;
    syntax_procedure_identifier(vector_tokens, i, padding);


    if (vector_tokens[i].code != 59)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, ";");
    else {
        cout<<padding<<";"<<endl;
        i++;
    }

    cout<<padding<<"<block>"<<endl;
    syntax_block(vector_tokens, i, padding);

    if (vector_tokens[i].code != 46)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, ".");
    else {
        cout<<padding<<"."<<endl;
        i++;
    }
}

void syntax_block(vector <_token> &vector_tokens, int &i, string padding) {
    padding += space;
    cout<<padding<<"<declarations>"<<endl;
    syntax_declarations(vector_tokens, i, padding);

    if (vector_tokens[i].code != 409)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, "BEGIN");
    else {
        cout<<padding<<"BEGIN"<<endl;
        i++;
    }

    if (vector_tokens[i].code != 410)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, "END");
    else {
        cout<<padding<<"<statements-list>"<<endl;
        cout<<padding<<"  <empty>"<<endl;
        cout<<padding<<"END"<<endl;
        i++;
    }
}

void syntax_declarations(vector <_token> &vector_tokens, int &i, string padding) {
    padding += space;
    cout<<padding<<"<variable-declarations>"<<endl;
    syntax_variable_declarations(vector_tokens, i, padding);
}

void syntax_variable_declarations(vector <_token> &vector_tokens, int &i, string padding) {
    padding += space;

    if (vector_tokens[i].code != 402)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, "VAR");
    else {
        cout<<padding<<"VAR"<<endl;
        i++;
    }

    if (vector_tokens[i].code != 409) {
        cout<<padding<<"<declarations-list>"<<endl;
        syntax_declarations_list(vector_tokens, i, padding);
    } else {
        cout<<padding<<"<empty>"<<endl;
    }
}

void syntax_declarations_list(vector <_token> &vector_tokens, int &i, string padding) {
    padding += space;
    cout<<padding<<"<declaration>"<<endl;
    syntax_declaration(vector_tokens, i, padding);

    if (vector_tokens[i].code != 409) {
        cout<<padding<<"<declarations-list>"<<endl;
        syntax_declarations_list(vector_tokens, i, padding);
    } else {
        cout<<padding<<"<empty>"<<endl;
    }
}

void syntax_declaration(vector <_token> &vector_tokens, int &i, string padding) {
    padding += space;

    cout<<padding<<"<variable-identifier>"<<endl;
    syntax_variable_identifier(vector_tokens, i, padding);

    cout<<padding<<"<identifiers-list>"<<endl;
    syntax_identifiers_list(vector_tokens, i, padding);


    if (vector_tokens[i].code != 58)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, ":");
    else {
        cout<<padding<<":"<<endl;
        i++;
    }

    cout<<padding<<"<attribute>"<<endl;
    syntax_attribute(vector_tokens, i, padding);

    cout<<padding<<"<attributes-list>"<<endl;
    syntax_attributes_list(vector_tokens, i, padding);

    if (vector_tokens[i].code != 59)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, ";");
    else {
        cout<<padding<<";"<<endl;
        i++;
    }
}

void syntax_identifiers_list(vector <_token> &vector_tokens, int &i, string padding) {
    padding += space;

    if (vector_tokens[i].code != 44)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, ",");
    else {
        cout<<padding<<","<<endl;
        i++;
    }

    cout<<padding<<"<variable-identifier>"<<endl;
    syntax_variable_identifier(vector_tokens, i, padding);


    if (vector_tokens[i].code != 58)
        syntax_identifiers_list(vector_tokens, i, padding);
    else {
        cout<<padding<<"<empty>"<<endl;
    }
}

void syntax_attributes_list(vector <_token> &vector_tokens, int &i, string padding) {
    padding += space;

    cout<<padding<<"<attribute>"<<endl;
    syntax_attribute(vector_tokens, i, padding);

    if (vector_tokens[i].code != 59)
        syntax_attributes_list(vector_tokens, i, padding);
    else {
        cout<<padding<<"<empty>"<<endl;
    }
}

void syntax_attribute(vector <_token> &vector_tokens, int &i, string padding) {
    padding += space;
    if (vector_tokens[i].code >= 403 && vector_tokens[i].code <= 408) {
        cout<<padding<<vector_tokens[i].token<<endl;
        i++;
    }
    else if (vector_tokens[i].code == 91) {
        cout<<padding<<"["<<endl;
        i++;

        cout<<padding<<"<range>"<<endl;
        syntax_range(vector_tokens, i, padding);

        cout<<padding<<"<range-list>"<<endl;
        syntax_range_list(vector_tokens, i, padding);

        if (vector_tokens[i].code != 93)
            syntax_error(vector_tokens[i].line, vector_tokens[i].column, "]");
        else {
            cout<<padding<<"]"<<endl;
            i++;
        }
    } else {
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, "attribute");
    }
}

void syntax_range_list(vector <_token> &vector_tokens, int &i, string padding) {
    padding += space;

    if (vector_tokens[i].code != 44)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, ",");
    else {
        cout<<padding<<","<<endl;
        i++;
    }

    cout<<padding<<"<range>"<<endl;
    syntax_range(vector_tokens, i, padding);

    if (vector_tokens[i].code != 93)
        syntax_range_list(vector_tokens, i, padding);
    else {
        cout<<padding<<"<empty>"<<endl;
    }
}

void syntax_range(vector <_token> &vector_tokens, int &i, string padding) {
    padding += space;

    cout<<padding<<"<unsigned-integer>"<<endl;
    syntax_unsigned_integer(vector_tokens, i, padding);

    if (vector_tokens[i].code != 301)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, "..");
    else {
        cout<<padding<<".."<<endl;
        i++;
    }

    cout<<padding<<"<unsigned-integer>"<<endl;
    syntax_unsigned_integer(vector_tokens, i, padding);
}

void syntax_variable_identifier(vector <_token> &vector_tokens, int &i, string padding) {
    padding += space;
    cout<<padding<<"<identifier>"<<endl;
    syntax_identifier(vector_tokens, i, padding);
}


void syntax_procedure_identifier(vector <_token> &vector_tokens, int &i, string padding) {
    padding += space;
    cout<<padding<<"<identifier>"<<endl;
    syntax_identifier(vector_tokens, i, padding);
}

void syntax_identifier(vector <_token> &vector_tokens, int &i, string padding) {
    padding += space;
    if (vector_tokens[i].code <= 1000)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, "identifier");
    else {
        cout<<padding<<vector_tokens[i].token<<endl;
        i++;
    }
}

void syntax_unsigned_integer(vector <_token> &vector_tokens, int &i, string padding) {
    padding += space;
    if (vector_tokens[i].code > 1000 && vector_tokens[i].code < 501)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, "unsigned-integer");
    else {
        cout<<padding<<vector_tokens[i].token<<endl;
        i++;
    }
}