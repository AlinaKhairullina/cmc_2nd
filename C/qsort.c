#include <stdio.h>

void qsort(int *mas, int size) {
    //Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;

    //Центральный элемент массива
    int mid = mas[size / 2];

    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while(mas[i] < mid) {
            i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while(mas[j] > mid) {
            j--;
        }

        //Меняем элементы местами
        if (i <= j) {
            int tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);


    //Рекурсивные вызовы, если осталось, что сортировать
    if(j > 0) {
        //"Левый кусок"
        qsort(mas, j + 1);
    }
    if (i < size) {
        //"Првый кусок"
        qsort(&mas[i], size - i);
    }
}
int main(int argc, char ** argv)
{
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    qsort(a, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}