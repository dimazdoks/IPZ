#include <iostream>
#include "syntax/syntax.h"

using namespace std;



int main() {
    vector <_token> vector_tokens;
    ifstream fin("../input.txt");
    node Tree;


    vector_tokens = lexer_main(fin);
    lexer_qPrintTokens(vector_tokens);
    syntax_main(vector_tokens, Tree);

    tree_print(Tree);

    fin.close();
    return 0;
}