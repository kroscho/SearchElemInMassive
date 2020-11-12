#include <iostream>
#include <fstream>
#include <windows.h> //для работы с ОС
#include <ctime>

using namespace std;

int v, n, x;
unsigned long int* mas;

void Vvod()
{
    cout << "\nВыберите ввод данных: 1 - вручную, 2 - с файла, 3 - генерация случайных чисел.\n";
    cin >> v;

    switch (v)
    {
    case 1: {
        cout << "Введите количество элементов: ";
        cin >> n;
        mas = new unsigned long int[n];
        cout << "\nВведите искомое число: ";
        cin >> x;

        for (int i = 0; i < n; i++)
        {
            cout << "mas[" << i << "] = ";
            cin >> mas[i];
        }
        break;
    }
    case 2: {
        ifstream f("input.txt");

        f >> n;
        mas = new unsigned long int[n];
        f >> x;
        cout << n << " " << x << "\n";

        for (int i = 0; i < n; i++)
        {
            int k;
            f >> k;
            mas[i] = k;
            cout << k << " ";
        }
        f.close();
        break;
    }
    case 3: {
        srand(time(0));
        cout << "Введите количество элементов: ";
        cin >> n;
        mas = new unsigned long int[n];
        cout << "\nВведите искомое число: ";
        cin >> x;

        for (int i = 0; i < n; i++)
        {
            mas[i] = rand();
            //cout << mas[i] << " ";
        }
        break;
    }
    }
}


//функция для сортировки по возрастанию
int comp1(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

//линейный поиск
int linearSearch()
{
    for (int i = 0; i < n; i++)
    {
        if (mas[i] == x)
            return i;
    }
    return -1;
}

//бинарный поиск
int binarySearch()
{
    int l = 0, r = n, m;

    while (r >= l) //для того, чтобы если элемент не найден
    {
        m = (l + r) / 2; //середина
        if (mas[m] == x)  //если элемент найден, возвращаем индекс      
        {
            while (mas[m - 1] == x)
                m--;
            return m;            
        }
        else if (mas[m] < x)  //если элемент находится правее, сдвигаем левый край, иначе правый 
            l = m + 1;
        else
            r = m - 1;
    }

    return -1; //если элемент не найден, возвращаем -1
}

int main()
{
    //задаем кодировку для вывода символов на экран
    SetConsoleCP(1251);
    //задаем кодировку для ввода символов с клавиатуры в консоль
    SetConsoleOutputCP(1251);
    
    double timeStart, timeFinish;
    double timeSearch;
    int id;
    /*timeStart = clock();
    for (int i=0; i<100000000; i++)
        int p = 1;
    timeFinish = clock();
    cout << "time: " << (timeFinish - timeStart)/1000./300000002. << endl;*/

    bool out = true;

    Vvod();

    while (out)
    {
        cout << "\nВыберите алгоритм: 1 - линейный поиск, 2 - бинарный поиск\n";
        cin >> v;       

        if (v == 1)
        {           
            timeStart = clock();
            id = linearSearch();
            timeFinish = clock();
        }
        else
        {
            //timeStart = clock();
            qsort(mas, n, sizeof(int), comp1);
            timeStart = clock();
            for (int i=0; i<100000; i++)
                id = binarySearch();
            timeFinish = clock();
        }

        if (id == -1)
            cout << "Элемент не найден.";
        else
            cout << "Индекс искомого элемента: " << id;

        //время выполнения алгоритма
        timeSearch = (timeFinish - timeStart) / 1000.0;
        cout << "\nВремя выполнения: " << timeSearch << "c";

        cout << "\n\nПродолжить? 1 - да, 0 - нет:  ";
        cin >> out;
    }
    delete[]mas;

    cout << "\n";
    system("pause");
}