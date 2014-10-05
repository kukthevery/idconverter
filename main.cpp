#include <iostream>
#include "idconverter.h"

using namespace std;

int main()
{
    IdConverter converter;
    string id = "A1A2A3A9Z9A1-A9A1-Z9";

    cout << "Enter id string: ";
    cin >> id;

    cout << "input:  " << id << endl;
    string id_out;
    int rc;
    rc = converter.Convert(id, id_out);
    switch(rc)
    {
    case 1:
        {
            cout << "Idenifier contains wrong symbols" << endl;
        }
        break;
    case 2:
        {
            cout << "Identifier too long" << endl;
        }
        break;
    case 3:
        {
            cout << "Z9-Z9 can't be incremented" << endl;
        }
        break;
    case 0:
    default:
        {
            cout << "output: " << id_out << endl;
        }
    }
    return 0;
}

