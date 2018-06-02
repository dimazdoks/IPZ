//
// Created by dimazdoks on 28.05.18.
//
#include "syntax.h"

void syntax_main(vector <_token> &vector_tokens, node &Tree) {
    int i=0;
    string padding;

    //cout<<padding<<"<signal-program>"<<endl;

    Tree = tree_init(token_null_data, "<signal-program>", padding);
    syntax_signal_program(vector_tokens, i, padding, Tree);
}

void syntax_signal_program(vector <_token> &vector_tokens, int &i, string padding, node &Tree) {
    padding += space;

    //cout<<padding<<"<program>"<<endl;
    tree_addChild(Tree, token_null_data, "<program>", padding);
    syntax_program(vector_tokens, i, padding, Tree.childs.back());
}

void syntax_program(vector <_token> &vector_tokens, int &i, string padding, node &Tree) {
    padding += space;

    if (vector_tokens[i].code != 401)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, "PROGRAM");
    else {
        //cout<<padding<<"PROGRAM"<<endl;
        tree_addChild(Tree, vector_tokens[i], "PROGRAM", padding);
        i++;
    }

    //cout<<padding<<"<procedure-identifier>"<<endl;
    tree_addChild(Tree, token_null_data, "<procedure-identifier>", padding);
    syntax_procedure_identifier(vector_tokens, i, padding, Tree.childs.back());


    if (vector_tokens[i].code != 59)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, ";");
    else {
        //cout<<padding<<";"<<endl;
        tree_addChild(Tree, vector_tokens[i], ";", padding);
        i++;
    }

    //cout<<padding<<"<block>"<<endl;
    tree_addChild(Tree, token_null_data, "<block>", padding);
    syntax_block(vector_tokens, i, padding, Tree.childs.back());

    if (vector_tokens[i].code != 46)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, ".");
    else {
        //cout<<padding<<"."<<endl;
        tree_addChild(Tree, vector_tokens[i], ".", padding);
        i++;
    }
}

void syntax_block(vector <_token> &vector_tokens, int &i, string padding, node &Tree) {
    padding += space;
    //cout<<padding<<"<declarations>"<<endl;
    tree_addChild(Tree, token_null_data, "<declarations>", padding);
    syntax_declarations(vector_tokens, i, padding, Tree.childs.back());

    if (vector_tokens[i].code != 409)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, "BEGIN");
    else {
        //cout<<padding<<"BEGIN"<<endl;
        tree_addChild(Tree, vector_tokens[i], "BEGIN", padding);
        i++;
    }

    if (vector_tokens[i].code != 410)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, "END");
    else {
        //cout<<padding<<"<statements-list>"<<endl;
        tree_addChild(Tree, token_null_data, "<statements-list>", padding);

        //cout<<padding<<"  <empty>"<<endl;
        tree_addChild(Tree, token_null_data, "<empty>", padding+space);

        //cout<<padding<<"END"<<endl;
        tree_addChild(Tree, vector_tokens[i], "END", padding);
        i++;
    }
}

void syntax_declarations(vector <_token> &vector_tokens, int &i, string padding, node &Tree) {
    padding += space;
    //cout<<padding<<"<variable-declarations>"<<endl;
    tree_addChild(Tree, token_null_data, "<variable-declarations>", padding);
    syntax_variable_declarations(vector_tokens, i, padding, Tree.childs.back());
}

void syntax_variable_declarations(vector <_token> &vector_tokens, int &i, string padding, node &Tree) {
    padding += space;

    if (vector_tokens[i].code != 402)
        if (vector_tokens[i].code != 409) {
            //cout<<padding<<"<declarations-list>"<<endl;
            tree_addChild(Tree, token_null_data, "<declarations-list>", padding);
            syntax_declarations_list(vector_tokens, i, padding, Tree.childs.back());
        } else {
            //cout<<padding<<"<empty>"<<endl;
            tree_addChild(Tree, token_null_data, "<empty>", padding);
        }
    else {
        //cout<<padding<<"VAR"<<endl;
        tree_addChild(Tree, vector_tokens[i], "VAR", padding);
        i++;

        if (vector_tokens[i].code != 409) {
            //cout<<padding<<"<declarations-list>"<<endl;
            tree_addChild(Tree, token_null_data, "<declarations-list>", padding);
            syntax_declarations_list(vector_tokens, i, padding, Tree.childs.back());
        } else {
            //cout<<padding<<"<empty>"<<endl;
            tree_addChild(Tree, token_null_data, "<empty>", padding);
        }
    }
}

void syntax_declarations_list(vector <_token> &vector_tokens, int &i, string padding, node &Tree) {
    padding += space;
    //cout<<padding<<"<declaration>"<<endl;
    tree_addChild(Tree, token_null_data, "<declaration>", padding);
    syntax_declaration(vector_tokens, i, padding, Tree.childs.back());

    if (vector_tokens[i].code != 409) {
        //cout<<padding<<"<declarations-list>"<<endl;
        tree_addChild(Tree, token_null_data, "<declarations-list>", padding);
        syntax_declarations_list(vector_tokens, i, padding, Tree.childs.back());
    } else {
        //cout<<padding<<"<empty>"<<endl;
        tree_addChild(Tree, token_null_data, "<empty>", padding);
    }
}

void syntax_declaration(vector <_token> &vector_tokens, int &i, string padding, node &Tree) {
    padding += space;

    //cout<<padding<<"<variable-identifier>"<<endl;
    tree_addChild(Tree, token_null_data, "<variable-identifier>", padding);
    syntax_variable_identifier(vector_tokens, i, padding, Tree.childs.back());

    //cout<<padding<<"<identifiers-list>"<<endl;
    tree_addChild(Tree, token_null_data, "<identifiers-list>", padding);
    if (vector_tokens[i].code != 58)
        syntax_identifiers_list(vector_tokens, i, padding, Tree.childs.back());
    else {
        //cout<<padding<<"<empty>"<<endl;
        tree_addChild(Tree, token_null_data, "<empty>", padding);
    }


    if (vector_tokens[i].code != 58)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, ":");
    else {
        //cout<<padding<<":"<<endl;
        tree_addChild(Tree, vector_tokens[i], ":", padding);
        i++;
    }

    //cout<<padding<<"<attribute>"<<endl;
    tree_addChild(Tree, token_null_data, "<attribute>", padding);
    syntax_attribute(vector_tokens, i, padding, Tree.childs.back());

    //cout<<padding<<"<attributes-list>"<<endl;
    tree_addChild(Tree, token_null_data, "<attributes-list>", padding);

    if (vector_tokens[i].code != 59)
        syntax_identifiers_list(vector_tokens, i, padding, Tree.childs.back());
    else {
        //cout<<padding<<"<empty>"<<endl;
        tree_addChild(Tree, token_null_data, "<empty>", padding);
    }

    if (vector_tokens[i].code != 59)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, ";");
    else {
        //cout<<padding<<";"<<endl;
        tree_addChild(Tree, vector_tokens[i], ";", padding);
        i++;
    }
}

void syntax_identifiers_list(vector <_token> &vector_tokens, int &i, string padding, node &Tree) {
    padding += space;

    if (vector_tokens[i].code != 44)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, ",");
    else {
        //cout<<padding<<","<<endl;
        tree_addChild(Tree, vector_tokens[i], ",", padding);
        i++;
    }

    //cout<<padding<<"<variable-identifier>"<<endl;
    tree_addChild(Tree, token_null_data, "<variable-identifier>", padding);
    syntax_variable_identifier(vector_tokens, i, padding, Tree.childs.back());


    if (vector_tokens[i].code != 59)
        syntax_identifiers_list(vector_tokens, i, padding, Tree.childs.back());
    else {
        //cout<<padding<<"<empty>"<<endl;
        tree_addChild(Tree, token_null_data, "<variable-identifier>", padding);
    }
}

void syntax_attributes_list(vector <_token> &vector_tokens, int &i, string padding, node &Tree) {
    padding += space;

    //cout<<padding<<"<attribute>"<<endl;
    tree_addChild(Tree, token_null_data, "<attribute>", padding);
    syntax_attribute(vector_tokens, i, padding, Tree.childs.back());

    if (vector_tokens[i].code != 59)
        syntax_attributes_list(vector_tokens, i, padding, Tree.childs.back());
    else {
        //cout<<padding<<"<empty>"<<endl;
        tree_addChild(Tree, token_null_data, "<attribute>", padding);
    }
}

void syntax_attribute(vector <_token> &vector_tokens, int &i, string padding, node &Tree) {
    padding += space;
    if (vector_tokens[i].code >= 403 && vector_tokens[i].code <= 408) {
        //cout<<padding<<vector_tokens[i].token<<endl;
        tree_addChild(Tree, vector_tokens[i], vector_tokens[i].token, padding);
        i++;
    }
    else if (vector_tokens[i].code == 91) {
        //cout<<padding<<"["<<endl;
        tree_addChild(Tree, vector_tokens[i], "[", padding);
        i++;

        //cout<<padding<<"<range>"<<endl;
        tree_addChild(Tree, token_null_data, "<range>", padding);
        syntax_range(vector_tokens, i, padding, Tree.childs.back());

        //cout<<padding<<"<range-list>"<<endl;
        tree_addChild(Tree, token_null_data, "<range-list>", padding);
        if (vector_tokens[i].code != 93)
            syntax_range_list(vector_tokens, i, padding, Tree.childs.back());
        else {
            //cout<<padding<<"<empty>"<<endl;
            tree_addChild(Tree, token_null_data, "<empty>", padding);
        }

        if (vector_tokens[i].code != 93)
            syntax_error(vector_tokens[i].line, vector_tokens[i].column, "]");
        else {
            //cout<<padding<<"]"<<endl;
            tree_addChild(Tree, token_null_data, "]", padding);
            i++;
        }
    } else {
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, "attribute");
    }
}

void syntax_range_list(vector <_token> &vector_tokens, int &i, string padding, node &Tree) {
    padding += space;

    if (vector_tokens[i].code != 44)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, ",");
    else {
        //cout<<padding<<","<<endl;
        tree_addChild(Tree, vector_tokens[i], ",", padding);
        i++;
    }

    //cout<<padding<<"<range>"<<endl;
    tree_addChild(Tree, token_null_data, "<range>", padding);
    syntax_range(vector_tokens, i, padding, Tree.childs.back());

    if (vector_tokens[i].code != 93)
        syntax_range_list(vector_tokens, i, padding, Tree.childs.back());
    else {
        //cout<<padding<<"<empty>"<<endl;
        tree_addChild(Tree, token_null_data, "<empty>", padding);
    }
}

void syntax_range(vector <_token> &vector_tokens, int &i, string padding, node &Tree) {
    padding += space;

    //cout<<padding<<"<unsigned-integer>"<<endl;
    tree_addChild(Tree, token_null_data, "<unsigned-integer>", padding);
    syntax_unsigned_integer(vector_tokens, i, padding, Tree.childs.back());

    if (vector_tokens[i].code != 301)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, "..");
    else {
        //cout<<padding<<".."<<endl;
        tree_addChild(Tree, vector_tokens[i], "..", padding);
        i++;
    }

    //cout<<padding<<"<unsigned-integer>"<<endl;
    tree_addChild(Tree, token_null_data, "<unsigned-integer>", padding);
    syntax_unsigned_integer(vector_tokens, i, padding, Tree.childs.back());
}

void syntax_variable_identifier(vector <_token> &vector_tokens, int &i, string padding, node &Tree) {
    padding += space;
    //cout<<padding<<"<identifier>"<<endl;
    tree_addChild(Tree, token_null_data, "<identifier>", padding);
    syntax_identifier(vector_tokens, i, padding, Tree.childs.back());
}


void syntax_procedure_identifier(vector <_token> &vector_tokens, int &i, string padding, node &Tree) {
    padding += space;
    //cout<<padding<<"<identifier>"<<endl;
    tree_addChild(Tree, token_null_data, "<identifier>", padding);
    syntax_identifier(vector_tokens, i, padding, Tree.childs.back());
}

void syntax_identifier(vector <_token> &vector_tokens, int &i, string padding, node &Tree) {
    padding += space;
    if (vector_tokens[i].code <= 1000)
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, "identifier");
    else {
        //cout<<padding<<vector_tokens[i].token<<endl;
        tree_addChild(Tree, vector_tokens[i], vector_tokens[i].token, padding);
        i++;
    }
}

void syntax_unsigned_integer(vector <_token> &vector_tokens, int &i, string padding, node &Tree) {
    padding += space;
//    cout<<vector_tokens[i].code<<endl;
//    cout<<vector_tokens[i].token<<endl;

    if (vector_tokens[i].code <= 1000 && vector_tokens[i].code >= 501) {
        //cout<<padding<<vector_tokens[i].token<<endl;
        tree_addChild(Tree, vector_tokens[i], vector_tokens[i].token, padding);
        i++;
    } else {
        syntax_error(vector_tokens[i].line, vector_tokens[i].column, "unsigned-integer");
    }
}