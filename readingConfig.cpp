#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    int mi=0, gama=0, alfa=0;
    ifstream config("config.txt");
    string line, dummy;
    int nLine=1;
    if (config.is_open())
    {
        while ( getline (config,line) )
        {
            if(nLine>3&&nLine<8)
            {
                istringstream iss(line);
                iss >> dummy;
                if(nLine==4)
                    iss >> mi;
                else if(nLine==5)
                    iss >> gama;
                else if(nLine==6)
                    iss >> alfa;
                else if(nLine==7)
                    iss >> cor;
                //cout << line << '\n';
                cout << "d1: " << dummy << endl <<  endl;
            }
            nLine++;
        }
        config.close();
    }
    else
    {
        cout << "O arquivo config.txt nao foi encontrado ou esta corrupto";
    }
    cout << "mi: " << mi << endl << "gama: " << gama << endl << "alfa: " << alfa << endl << endl;
}
