//
// Created by dimazdoks on 03.06.18.
//

#ifndef IPZ_TREE_H
#define IPZ_TREE_H

#include "../lexer/lexer.h"

struct node {
    vector <node> childs;
    _token information;
    string name;
    string padding;
};

node tree_init (_token information, string name, string padding);
void tree_addChild(node &father, _token information, string name, string padding);
void tree_print(node father);

#endif //IPZ_TREE_H
