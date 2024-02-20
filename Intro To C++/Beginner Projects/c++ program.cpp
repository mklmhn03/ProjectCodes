//https://code.visualstudio.com/docs/cpp/config-mingw#_troubleshooting
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> msg {"Obey", "Me", "C++", "World","."};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
}