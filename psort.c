// Реализация пирамидальной сортировки на C++
#include <stdio.h>


// Процедура для преобразования в двоичную кучу поддерева с корневым узлом i, что является
// индексом в arr[]. n - размер кучи
void swap(int  * a, int * b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
void heapify(int *arr, int n, int i)
{
    int largest = i;   
// Инициализируем наибольший элемент как корень
    int l = 2*i + 1; // левый = 2*i + 1
    int r = 2*i + 2; // правый = 2*i + 2

 // Если левый дочерний элемент больше корня
    if ((l < n) && (arr[l] > arr[largest]))
        largest = l;

   // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if ((r < n) && (arr[r] > arr[largest]))
        largest = r;

    // Если самый большой элемент не корень
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);

// Рекурсивно преобразуем в двоичную кучу затронутое поддерево
        heapify(arr, n, largest);
    }
}

// Основная функция, выполняющая пирамидальную сортировку
void heapSort(int arr[], int n)
{
  // Построение кучи (перегруппируем массив)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

   // Один за другим извлекаем элементы из кучи
    for (int i=n-1; i>=0; i--)
    {
        // Перемещаем текущий корень в конец
        swap(&arr[0], &arr[i]);

        // вызываем процедуру heapify на уменьшенной куче
        heapify(arr, i, 0);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    heapSort(a, n);
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}