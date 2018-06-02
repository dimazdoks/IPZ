//
// Created by dimazdoks on 03.06.18.
//

#include "tree.h"

node tree_init (_token information, string name, string padding) {
    node tree;
    tree.name = std::move(name);
    tree.padding = std::move(padding);
    tree.information = std::move(information);

    return tree;
}
void tree_addChild(node &father, _token information, string name, string padding) {
    node child = tree_init(information, name, padding);
    father.childs.emplace_back(child);
}


void tree_print(node father) {
    unsigned long i = 0, n = 0;

    cout << father.padding << father.name << endl;
    n = father.childs.size();
    for (i; i<n; i++) {
        tree_print(father.childs[i]);
    }
}