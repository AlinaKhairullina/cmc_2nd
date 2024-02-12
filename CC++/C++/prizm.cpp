#include <iostream>

using namespace std;

class Prizma{
    double v, 
        height,
        len,
        square_base;
    int grans;
    public:
        Prizma(double vv = 1, double h = 1, double l = 1, double s = 1 ) :
        v(vv), height(h), len(l), square_base(s) {};
        double getHeight() const { 
            return height; 
        }
        int getGrans() const {
             return grans;
        }
        double getSquare_base() const {
            return square_base;
        }
        double getLen() const{
            return len;
        }
        double getV() const{ 
            return height * square_base; 
        }
        void setHeight(const long h) { 
            height = h; 
        }
        void SetLen(const long l) {
            len = l;
        }
        void SetGrans(const int g) {
            grans = g;
        }
        void GetSquare_base(const long s) {
            square_base = s;
        }

};

int main(){
    Prizma P;
    int request, exit = 1, tmp;
    do {
    cout << "Сделайте выбор:\n0 - выход;  1 - показать высоту призмы;\n2 - показать колличество боковых граней;"
             << "3 - показать площадь основания;\n4 - показать длинну сторон призмы;  5 - показать объём призмы;\n"
             << "6 - установить высоту призмы;  7 - установить длинну сторон призмы; \n8 - установить количество граней;  9 - задать площадь основания\n>> "; 
    cin >> request;
        switch (request)
        {
            case 0 : exit = 0;
                    break;
            case 1 : cout <<  "Высота : " << P.getHeight() << "\n"; break;
            case 2 : cout << "Колличество боковых граней : " << P.getHeight() << "\n";break;
            case 3 : cout << "площадь основания : " << P.getSquare_base() << "\n"; break; 
            case 4 : cout << "длиннa сторон призмы : " << P.getLen() << "\n"; break;
            case 5 : cout << "объём призмы : " << P.getV() << "\n"; break;
            case 6 : 
                cin >> tmp; 
                P.setHeight(tmp);
                cout << "Установлена высота призмы :" << tmp << "\n";
                break;
            case 7 : 
                cin >> tmp; 
                P.SetLen(tmp);
                cout << "Установлена длиннa сторон призмы :" << tmp << "\n";
                break;
            case 8 : 
                cin >> tmp; 
                P.SetGrans(tmp);
                cout << "Установлено количество граней :" << tmp << "\n";
                break;
            case 9 : 
                cin >> tmp;
                P.GetSquare_base(tmp); 
                cout << "Установлена площадь основания:" << tmp << "\n";
                break;
            default:
                cout << "Неверный запрос\n";
                break;
        }
    }
    while (exit);
    

    return 0;
}