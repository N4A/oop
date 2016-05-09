#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    string in_file;
    string out_file;


    switch (argc) {
    case 2:
        in_file = argv[1];
        out_file = "a.cpp";
        break;
    case 3:
        in_file = argv[1];
        out_file = argv[2];
        break;
    default:
        cout << "argument error, you should enter './pre in_file [out_file]'";
        break;
    }

    cout << in_file << "/" << out_file << endl;

    return 0;
}
