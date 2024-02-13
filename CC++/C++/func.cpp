#include <iostream>
using namespace std;

class A 
{
    public:
        operator int(){ return 0;};
        operator double(){ return 0;};
};

void fk(int a, int b) {
    cout << "111" << "\n";
};

void fk(double a, double b) {
    cout << "222" << "\n";
};

int main() {
    A ob; 
    short x = 1;
    fk(ob, 7); //11
    fk(ob, 3.4);//22
    fk(x, 7);//11
    fk(2.4f, 7.0); //22
    fk(4, 7);//11
    fk(3.3, 7.0);//22
    return 0;
}
