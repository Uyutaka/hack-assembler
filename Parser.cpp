#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string_view>
#include "CommandType.h"

using namespace std;

class Parser
{
private:
    string line_;
    CommandType type_;
    string symbol_;
    string comp_;
    string dest_;
    string jump_;
    const char SEMICOLON = ';';
    const char EQUAL = '=';

    void SetCommandType()
    {
        string test = line_.substr(0, 1);
        switch (line_[0])
        {
        case '@':
            type_ = CommandType::A_COMMAND;
            break;
        case '(':
            type_ = CommandType::L_COMMAND;
            break;
        default:
            type_ = CommandType::C_COMMAND;
            break;
        }
    }

    // Extract Xxxx from @Xxxx or (Xxxx)
    void SetSymbol()
    {
        // EX @Xxxx -> Xxxx
        if (type_ == CommandType::A_COMMAND)
        {
            symbol_ = line_.substr(1, line_.size());
            return;
        }

        // EX (Xxxx) -> Xxxx
        if (type_ == CommandType::L_COMMAND)
        {
            cout << "test" << endl;
            symbol_ = line_.substr(1, line_.size() - 2);
            return;
        }
    }

    // EX dest=comp;jump -> dest
    void SetDest()
    {
        size_t found = line_.find(EQUAL);
        if (found != string::npos)
        {
            dest_ = line_.substr(0, found);
        }
        return;
    }

    // EX dest=comp;jump -> comp
    void SetComp()
    {
        size_t semicolonP = line_.find(SEMICOLON);
        size_t equalP = line_.find(EQUAL);
        comp_ = line_.substr(equalP + 1, semicolonP - equalP - 1);
        return;
    }

    // EX dest=comp;jump -> jump
    void SetJump()
    {
        size_t found = line_.find(SEMICOLON);
        if (found != string::npos)
        {
            jump_ = line_.substr(found + 1, string::npos);
        }
        return;
    }

public:
    Parser()
    {
        cout << "in parser class" << endl;
    }

    Parser(string const line)
    {
        line_ = line;
        SetCommandType();
        if (type_ == CommandType::A_COMMAND || type_ == CommandType::L_COMMAND)
        {
            SetSymbol();
        }
        if (type_ == CommandType::C_COMMAND)
        {
            SetDest();
            SetComp();
            SetJump();
        }
    }

    CommandType getCommand()
    {
        return type_;
    }
    string getSymbol()
    {
        return symbol_;
    }
    string getComp()
    {
        return comp_;
    }
    string getDest()
    {
        return dest_;
    }
    string getJmp()
    {
        return jump_;
    }
};