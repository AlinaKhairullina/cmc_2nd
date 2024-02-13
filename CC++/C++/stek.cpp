#include <iostream>
using namespace std;

class B1{
    public :
        int dlina = 0,
            max;
        int* elems;
        B1(int d, int* a = NULL)
        {
            max = d;
            elems = new int [d];
            if (a != NULL) {
                for (int i = 0; i < d; i++)
                {
                    elems[i] = a[i];
                }
                 dlina = d;}
    
        };
        void PR();
        ~B1(){
            delete [] elems;
            max = 0;
            dlina = 0;
        }
       
};

class B2{
    public :

    int max,
        dlina = 0;
    int* elems;
        B2(int d){
            elems = new int [d];
            max = d;

        };
        void PR();
        // ~B2(){
        //     delete [] elems;
        //     dlina = 0; max = 0;
        // }


};
void B1 :: PR(){
    cout << "Стек : ";
    for (int i = dlina - 1; i >= 0; i--)
    {
        cout << elems[i] << " ";

    }
    cout << "\n";

};
void B2 :: PR(){
    cout << "Очередь : ";
    for (int i = 0; i < dlina; i++)
    {
        cout << elems[i] << " ";

    }
    cout << "\n";
};
void F(B1 & b, int a){
    if (b.dlina < b.max){
        b.elems[b.dlina] = a;
        b.dlina++;
        return;
    }
    else if (b.dlina == b.max)
    {
        cout << "Стек переполнен\n";
        return;
    };
};

int G(B1 & b){
    if (b.dlina > 0){
        b.dlina--;
        return b.elems[b.dlina];
    }
    else {
        cout << "Стек пуст\n";
        return 0;
    }
};

void F(B2 & b, int x){
    if (b.dlina < b.max){
        b.elems[b.dlina] = x;
        b.dlina++;
    }
    else if (b.dlina == b.max){
        cout << "Очередь переполнена\n";
        return;
    }
}

int G(B2 & b){
    if (b.dlina > 0){
        b.dlina--;
        b.elems++;
        return b.elems[-1];
    }
    else{
        cout << "очередь пуста\n";
        return 0;
    }
}

int main(){

    int a[4] = {1,2,3,4}, n, k;
    B1 st1(4, a),  st2(2);
    B2 obj1(3);
    F(st1, 6); //сообщение о том, что стек переполнен
    F(st2, 7);
    n = G(st1); 
    F(st1, 5);
    F(obj1, 2);
    F(obj1, 7);
    k = G(obj1);
    F(obj1, 9);
    st1.PR();
    st2.PR();
    obj1.PR();
    cout << n << "," << k << endl;
    return 0;

}
