#include <iostream>
#include "lexer/lexer.h"

using namespace std;



int main() {
    unsigned int start_time;
    start_time = static_cast<unsigned int>(clock());

    vector <_token> vector_tokens;

    ifstream fin("../input.txt");
    vector_tokens = lexer_main(fin);

    lexer_qPrintTokens(vector_tokens);
    fin.close();

    unsigned int end_time;
    end_time = static_cast<unsigned int>(clock());

    cout << (float) (end_time - start_time) / CLOCKS_PER_SEC * 1000 << endl;
    return 0;
}