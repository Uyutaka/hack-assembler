#include "CommandType.h"
#include <string>
#include <iostream>
#include <bitset>
#include <map>

using namespace std;

class Code
{
private:
    bitset<16> binary_;
    string comp_;
    string dest_;
    string jmp_;
    string symbol_;

    void convertCCommand()
    {
        binary_ = bitset<16>("111" + convertComp() + convertDest() + convertJmp());
    }

    string convertComp()
    {
        map<string, string> comps;

        // a = 0
        string prefix = "0";
        comps["0"] = prefix + "101010";
        comps["1"] = prefix + "111111";
        comps["-1"] = prefix + "111010";
        comps["D"] = prefix + "001100";
        comps["A"] = prefix + "110000";
        comps["!D"] = prefix + "001101";
        comps["!A"] = prefix + "110001";
        comps["-D"] = prefix + "001111";
        comps["-A"] = prefix + "110011";
        comps["D+1"] = prefix + "011111";
        comps["A+1"] = prefix + "110111";
        comps["D-1"] = prefix + "001110";
        comps["A-1"] = prefix + "110010";
        comps["D+A"] = prefix + "000010";
        comps["D-A"] = prefix + "010011";
        comps["A-D"] = prefix + "000111";
        comps["D&A"] = prefix + "000000";
        comps["D|A"] = prefix + "010101";

        // a = 1
        prefix = "1";
        comps["M"] = prefix + "110000";
        comps["!M"] = prefix + "110001";
        comps["-M"] = prefix + "110011";
        comps["M+1"] = prefix + "110111";
        comps["M-1"] = prefix + "110010";
        comps["D+M"] = prefix + "000010";
        comps["D-M"] = prefix + "010011";
        comps["M-D"] = prefix + "000111";
        comps["D&M"] = prefix + "000000";
        comps["D|M"] = prefix + "010101";

        if (comps.find(comp_) != comps.end())
        {
            return comps[comp_];
        }
        return "";
    }

    string convertJmp()
    {
        map<string, string> jmps;
        jmps[""] = "000";
        jmps["JGT"] = "001";
        jmps["JEQ"] = "010";
        jmps["JGE"] = "011";
        jmps["JLT"] = "100";
        jmps["JNE"] = "101";
        jmps["JLE"] = "110";
        jmps["JMP"] = "111";

        if (jmps.find(jmp_) != jmps.end())
        {
            return jmps[jmp_];
        }
        return "";
    }

    string convertDest()
    {
        map<string, string> dests;
        dests[""] = "000";
        dests["M"] = "001";
        dests["D"] = "010";
        dests["MD"] = "011";
        dests["A"] = "100";
        dests["AM"] = "101";
        dests["AD"] = "110";
        dests["AMD"] = "111";

        if (dests.find(dest_) != dests.end())
        {
            return dests[dest_];
        }
        return "";
    }

public:
    Code(CommandType type, string symbol, string dest, string comp, string jmp)
    {
        if (type == CommandType::C_COMMAND)
        {
            comp_ = comp;
            dest_ = dest;
            jmp_ = jmp;
            convertCCommand();
        }
        if (type == CommandType::A_COMMAND)
        {
            try
            {
                int decimal;
                decimal = stoi(symbol);
                binary_ = bitset<16>(decimal);
            }
            catch (const invalid_argument &e)
            {
                cout << e.what() << "\n";
            }
            catch (const out_of_range &e)
            {
                cout << e.what() << "\n";
            }
        }
    }

    bitset<16> getBinary()
    {
        return binary_;
    }
};