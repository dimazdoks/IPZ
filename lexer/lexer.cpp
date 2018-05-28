//
// Created by dimazdoks on 08.04.18.
//

#include "lexer.h"

/* <--- FUNCTIONS ---> */
int lexer_isChar(char ch) {return ch >= 'A' && ch <= 'Z';}
int lexer_isDigit(char ch) {return ch >= '0' && ch <= '9';}
int lexer_isSeparators(char ch) {return (int) set_separators.count(ch);}
int lexer_isWs(char ch) {return (int)set_ws.count(ch);}

void lexer_addToken(size_t line, size_t column, size_t code,
                    string token, TokenType type, vector <_token> &vector_tokens) {
    _token newToken;

    newToken.line = line;
    newToken.column = column;
    newToken.token = token;
    newToken.code = code;
    newToken.type = type;

    vector_tokens.insert(vector_tokens.end(), newToken);
}

void lexer_isComment(istream &fin, size_t &column, size_t &line, vector <_token> &vector_tokens) {
    size_t column_buff = column;
    size_t line_buff = line;
    char ch;

    fin.get(ch);
    column ++;

    if (ch == '*') {
        fin.get(ch);
        column ++;
        while (!fin.eof()) {
            if (ch == '*') {
                fin.get(ch);
                column++;
                if (ch == ')') return;
            } else {
                if (ch == '\n') {
                    line++;
                    column = 1;
                } else
                    column++;
                fin.get(ch);
            }
        }
    }
    lexer_error(line_buff, column_buff, '(', vector_tokens);
}

string lexer_makeNewIdentifier(ifstream &fin, size_t line, size_t column, vector <_token> &vector_tokens) {
    string str;
    str = "#";
    char ch;
    size_t i = 0;
    for (i = 1; i <= 3; i++) {
        if (!fin.eof())
            fin.get(ch);
        else
            lexer_eof();

        if (lexer_isChar(ch))
            str += ch;
        else
            lexer_error(line + i, column, ch, vector_tokens);
    }
    line += 3;

    if (!fin.eof())
        fin.get(ch);
    else
        lexer_eof();

    if (ch == ':')
        str += ch;
    else
        lexer_error(line + 1, column, ch, vector_tokens);

    line++;

    for (i = 1; i <= 2; i++) {
        if (!fin.eof())
            fin.get(ch);
        else
            lexer_eof();

        if (lexer_isChar(ch) || lexer_isDigit(ch))
            str += ch;
        else
            lexer_error(line + i, column, ch, vector_tokens);
    }

    line += 2;


    if (!fin.eof())
        fin.get(ch);
    else
        lexer_eof();

    if (ch == '-')
        str += ch;
    else
        lexer_error(line + 1, column, ch, vector_tokens);

    line++;

    for (i = 1; i <= 2; i++) {
        fin.get(ch);

        if (fin.eof())
            lexer_eof();
        else if (lexer_isDigit(ch))
            str += ch;
        else
            lexer_error(line + i, column, ch, vector_tokens);
    }

    return str;
}

string lexer_makeStr(ifstream &fin, char &ch, int itIsChar, size_t line, size_t column, vector <_token> &vector_tokens) {
    string str;
    str += ch;

    while (true) {
        fin.get(ch);
        ch = (char) toupper(ch);

        if (fin.eof())
            return str;
        else if (lexer_isDigit(ch) || (lexer_isChar(ch) && itIsChar)) {
            str += ch;
        } else if (isspace(ch) || (lexer_isSeparators(ch)) || ch == '(') {
            return str;
        } else
            break;
    }

    lexer_error(line, column+str.length(), ch, vector_tokens);
    return "";
}

string lexer_isDoubleDot(ifstream &fin, char &ch) {
    string str;
    char f_ch = ch;
    str += ch;

    fin.get(ch);

    if (!fin.eof()) {
        if (ch == '.' && f_ch == '.') {
            str += '.';
            fin.get(ch);
        }
    }
    return str;
}

vector <_token> lexer_main(ifstream &fin) {
    vector <_token> vector_tokens;
    map <string, size_t> map_identifiers;
    map <string, size_t> map_constants;

    char ch;
    size_t column = 1, line = 1, constantsCode = 0, identifiersCode = 0, code = 0;
    string str;
    TokenType ttBuff;

    fin.get(ch);
    if (!fin.is_open())
        cout << "Файл не може відкритися!" << endl;
    else {
        while (!fin.eof()) {
            ch = (char) toupper(ch);
            str = "";
            if (ch == '#') {
                str = lexer_makeNewIdentifier(fin, line, column, vector_tokens);

                if (!map_identifiers.count(str))
                    {
                        code = 1001 + identifiersCode;
                        identifiersCode++;
                        map_identifiers.insert(pair <string, size_t >(str, code));
                    } else {
                    code = map_identifiers.at(str);
                    //cout << code << endl;
                }

                ttBuff = TT_Identifiers;

                fin.get(ch);
            } else if (lexer_isChar(ch)) {
                str = lexer_makeStr(fin, ch, 1, line, column, vector_tokens);
                if (map_words.count(str)) {
                    code = map_words.at(str);
                    ttBuff = TT_Keywords;
                } else {

                    if (!map_identifiers.count(str))
                    {
                        code = 1001 + identifiersCode;
                        identifiersCode++;
                        map_identifiers.insert(pair <string, size_t >(str, code));
                    } else {
                        code = map_identifiers.at(str);
                        //cout << code << endl;
                    }

                    ttBuff = TT_Identifiers;
                }
            } else if (lexer_isDigit(ch)) {
                str = lexer_makeStr(fin, ch, 0, line, column, vector_tokens);

                if (!map_constants.count(str))
                {
                    code = 501 + constantsCode;
                    constantsCode++;
                    map_constants.insert(pair <string, size_t >(str, code));
                } else {
                    code = map_constants.at(str);
                    //cout << code << endl;
                }
                ttBuff = TT_Constants;
            } else if (lexer_isSeparators(ch)) {
                str = lexer_isDoubleDot(fin, ch);
                if (str.length() == 2) {
                    ttBuff = TT_Multi_separators;
                    code = 301;
                } else {
                    ttBuff = TT_Single_separators;
                    code = (size_t)str[0];
                }
            } else if (ch == '(') {
                lexer_isComment(fin, column, line, vector_tokens);
                fin.get(ch);
                column++;
            } else if (lexer_isWs(ch)){
                column++;
                if (ch == '\n') {
                    line++;
                    column = 1;
                } else if (ch == '\t')
                    column += 3;

                fin.get(ch);
            } else {
                lexer_error(line, column, ch, vector_tokens);
            }
            if (str.length() != 0) {
                lexer_addToken(line, column, code, str, ttBuff, vector_tokens);
                column += str.length();
            }
        }
    }

    map_constants.clear();
    map_identifiers.clear();
    return vector_tokens;
}