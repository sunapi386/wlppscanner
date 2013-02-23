#include <string>
#include <iostream>
using namespace std;

int main () {
    string s = "abc";
    if (s.length()-2 >= 0)
        cout << s.substr (s.length()-2) << endl;
}
