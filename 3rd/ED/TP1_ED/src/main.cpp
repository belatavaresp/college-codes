#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include "tree.h"
#include "regex.h"

using namespace std;

int main(int argc, char const *argv[])
{
    fstream file;
    file.open("exemplos.txt"); // test file (can be changed to test cases)
    string s;                  // auxiliary string
    while (!file.eof())
    {
        string text = ""; // expression
        file >> s;
        cout << endl;
        while (s != "POSFIXA" && s != "INFIXA" && s != "RESOLVE")
        {
            if (s == "#")
            {
                while (s != "LER" || !file.eof())
                {
                    file >> s;
                }
            }
            else if (s == "LER")
            {
                text.clear();
                file >> s;
            }
            else
            {
                text = text + " " + s;
                file >> s;
            }
        }

        if (isValidExpression(text))
        {
            if (s == "POSFIXA")
            {
                // removes all spaces from expression
                text.erase(remove_if(text.begin(), text.end(), ::isspace), text.end());

                cout << "EXPRESSAO OK: " << text << endl;
                cout << "POSFIXA: " << infixToPostfix(text) << endl;
                Tree treeI(text);
                double result = treeI.solve();
                cout << "RESOLVE: " << fixed << setprecision(6) << result << endl;
            }
            else if (s == "INFIXA")
            {
                cout << "EXPRESSAO OK: " << text << endl;
                cout << "INFIXA: " << postfixToInfix(text) << endl;
                Tree treeP(text);
                double result = treeP.solve();
                cout << "RESOLVE: " << fixed << setprecision(6) << result << endl;
            }
            else if (s == "RESOLVE")
            {
                while (s != "LER" && !file.eof())
                {
                    file >> s;
                }
            }
        }
        else
        {
            if (text.empty())
            {
                cout << "ERRO: " << text << " NAO EXISTE" << endl;
            }
            else
            {
                cout << "ERRO: " << text << " NAO VALIDA" << endl;
            }
        }
    }
}
