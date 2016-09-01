#include <iostream>
#include <gedamial.h>

using namespace std;
using namespace ged::Data;

int main()
{
    GMap<string,int> voti(10);
    const string read[10] {"pippo","paolo","maria","erika","eleonora","roberto", "matteo", "luca", "francesco", "elisa"};
    for (int i=0;i<10;i++)
        voti.Add(read[i],i);
    for (int i=0;i<10;i++)
    cout << voti.Find(read[i])<< endl;
    return 0;
}
