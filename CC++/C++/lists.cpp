/*
    Создать структуру, которая будет хранить информации о знаке зодиака, с именем Znak. 
Структура Znak должна содержать следующие поля:
name — фамилия, имя и отчество;
zodiac — знак зодиака;
bday — день рождения (массив из трёх чисел);

    ввод с клавиатуры данных в массив book, который состоит из восьми элементов типа Znak;

    вывод на экран информации о людях, определенного знака зодиака, значение которого введено с клавиатуры, если таких нет, выдать на дисплей соответствующее сообщение;

*/
#define N 1
#include <iostream>
#include <string.h>

using namespace std;

struct Znak{
    char name[2][15];
    char zodiac[9];
    int bday[3];
    Znak(){};
    Znak(char* n, char* f, int d, int m, int g)
    {
        strcpy(name[0], n);
        strcpy(name[1], f);
        bday[0] = d;
        bday[1] = m;
        bday[2] = g;
        const char* znaks[12] = {"Овен", "Телец", "Близнецы", "Рак" , "Лев", "Дева",
                          "Весы", "Скорпион", "Стрелец", "Козерог", "Водолей", "Рыбы"};
        if (((bday[0] <= 20) && (bday[1] == 4)) || 
        ((bday[0] >= 21) && (bday[1] == 3 )))
            {strcpy(zodiac, znaks[0]); return;}
        if (((bday[0] <= 20) && (bday[1] == 5)) || 
        ((bday[0] >= 21) && (bday[1] == 4 )))
            {strcpy(zodiac, znaks[1]); return;}
        if (((bday[0] <= 21) && (bday[1] == 6)) || 
        ((bday[0] >= 21) && (bday[1] == 5 )))
            {strcpy(zodiac, znaks[2]); return;}
        if (((bday[0] <= 22) && (bday[1] == 7)) || 
        ((bday[0] >= 22) && (bday[1] == 6 )))
            {strcpy(zodiac, znaks[3]); return;}
        if (((bday[0] <= 23) && (bday[1] == 8)) || 
        ((bday[0] >= 23) && (bday[1] == 7 )))
            {strcpy(zodiac, znaks[4]); return;}
        if (((bday[0] <= 23) && (bday[1] == 9)) || 
        ((bday[0] >= 24) && (bday[1] == 8 )))
            {strcpy(zodiac, znaks[5]); return;}
        if (((bday[0] <= 23) && (bday[1] == 10)) || 
        ((bday[0] >= 24) && (bday[1] == 9 )))
            {strcpy(zodiac, znaks[6]); return; }
        if (((bday[0] <= 22) && (bday[1] == 11)) || 
        ((bday[0] >= 24) && (bday[1] == 10 )))
            {strcpy(zodiac, znaks[7]); return;}
        if (((bday[0] <= 21) && (bday[1] == 12)) || 
        ((bday[0] >= 23) && (bday[1] == 11 )))
            {strcpy(zodiac, znaks[8]); return;}
        if (((bday[0] <= 20) && (bday[1] == 1)) || 
        ((bday[0] >= 22) && (bday[1] == 12)))
            {strcpy(zodiac, znaks[9]); return;}
        if (((bday[0] <= 20) && (bday[1] == 2)) || 
        ((bday[0] >= 21) && (bday[1] == 1 )))
            {strcpy(zodiac, znaks[10]); return;}
        if (((bday[0] <= 20) && (bday[1] == 3)) || 
        ((bday[0] >= 21) && (bday[1] == 2 )))
            {strcpy(zodiac, znaks[11]); return;}
    };

};

int main()
{
    Znak book[N];
    char name[15], fam[15];
    char data[11];
    int bday[3];
    for (int i = 0; i < N; i++){
        cout << "Введите имя и фамилию через пробел: ";
        cin >> name;
        cin >> fam;
        cout << "Введите дату рождения (в формате дд.мм.гггг): ";
        cin >> data;
        bday[0] = atoi(strtok(data, "."));
        bday[1] = atoi(strtok(NULL, "."));
        bday[2] = atoi(strtok(NULL, "."));
        cout << bday[0] << " " << bday[1] << " " << bday[2] << "\n";
        book[i] = Znak(name, fam, bday[0], bday[1], bday[2]);
    }

    char zodiac[9];
    cout << "Введите желаемый знак зодиака ";
    cin >> zodiac;
    for (int i = 0; i < N; i++)
    {
        cout << book[i].bday[0] << " " << book[i].bday[1] << " " << book[i].bday[2] << "\n";
        // if ((strcmp(book[i].zodiac, zodiac)) == 0){
        //     cout << book[i].name[0] <<  " " <<  book[i].name[1] <<  "\n";
        // if (book[i].bday[0] > 9 ) cout <<  book[i].bday[0] <<  ".";
        // else cout <<  "0" <<  book[i].bday[0] <<  ".";
        //     if (book[i].bday[1] > 9 ) cout <<  book[i].bday[1] <<  ".";
        //     else cout <<  "0" <<  book[i].bday[1] <<  ".";
        //     cout <<  book[i].bday[1] <<  "\n";
        // }
    }
}