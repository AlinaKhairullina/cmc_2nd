#include <iostream>

using namespace std;

class rational{
    public:
        int ch,
            zn;
        rational(int x, int y = 1){
            if (y < 0) y *= -1;
            if (y == 0) {
                cout << "Знаменатель не может быть равен нулю\n";
                y = 1;
            }
            int i = 2;
            while (i <= min(abs(x), y))
            {
                if ((x % i == 0) && (y % i == 0)){
                    x /= i;
                    y /= i;
                }
                i++;
            }
            ch = x;
            if (x != 0) zn = y;
            else zn = 1;
        }

};

rational operator +(const rational & a, const rational & b){
    int res1, res2, x, y;
    if (a.zn != b.zn)
    {
        res2 = a.zn * b.zn;
        x = a.ch * b.zn;
        y = b.ch * a.zn;
        res1 = x + y;
    }
    else{
        res2 = a.zn;
        res1 = a.ch + b.ch;
    }
    return rational(res1, res2);
}

int main(){
    rational a(3, 9), b(-21, 49);
    rational c = a + b;
    cout << c.ch << " " << c.zn << endl;
    return 0;
}