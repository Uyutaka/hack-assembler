#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string_view>
#include <string_view>
#include "Parser.cpp"
#include "Code.cpp"
#include "CommandType.h"

using namespace std;

int main(int argc, char **argv)
{
    ifstream myfile("samples/PongL.asm");
    string myline;

    vector<string> line;

    if (myfile.is_open())
    {

        while (myfile)
        {
            getline(myfile, myline);

            // Remove space
            myline.erase(std::remove(myline.begin(), myline.end(), ' '), myline.end());
            if (!myline.starts_with("//") && !myline.starts_with('\r'))
            {
                // Remove \r
                myline.erase(std::remove(myline.begin(), myline.end(), '\r'), myline.end());
                if (!myline.empty())
                {
                    line.push_back(myline);
                }
            }
        }
    }
    else
    {
        cout << "Couldn't open file\n";
    }

    for (auto val : line)
    {
        Parser p{val};
        // cout << val << endl;
        Code c{p.getCommand(), p.getSymbol(), p.getDest(), p.getComp(), p.getJmp()};
        cout << c.getBinary() << endl;
    }

    return 0;
}
