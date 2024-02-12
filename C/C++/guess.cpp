#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    long ltime = time(NULL);
    srand(ltime);
    int random = rand() % 100 + 1; // Генерация случайного числа от 1 до 100
    std:: cout << random << std:: endl;
    int guess;
    int attempts = 0;

    std::cout << "Добро пожаловать в игру \"Угадай число\"!" << std::endl;

    do {
        std::cout << "Введите ваше предположенное число: ";
        std::cin >> guess;
        attempts++;

        if (guess < random)
            std::cout << "Загаданное число больше, введите число больше загаданного" << std::endl;
        else if (guess > random)
            std::cout << "Загаданное число меньше, введите число меньше загаданного" << std::endl;
        else 
            std::cout << "Поздравляю! Вы угадали число с " << attempts << " попытки!" << std::endl;
        

    } while (guess != random);

    return 0;
}