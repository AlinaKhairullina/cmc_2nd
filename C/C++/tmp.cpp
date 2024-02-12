#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    char s[11] = "07.02.2004";
    char* c = s;
    int a = atoi(strtok(c, "."));
    int b = atoi(strtok(NULL, "."));
    cout << b << "\n";
    return 0;
}