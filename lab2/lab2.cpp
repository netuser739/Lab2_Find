#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <windows.h>

using namespace std;

//функция удалления массва
void deleteArr(int* arr) {
    delete arr;
}

//функция линейного поиска
int Better_Linear_Search(const int array[], int size, int target, int& comparisons) {
    comparisons = 0;
    for (int i = 0; i < size; ++i) {
        ++comparisons; // увеличение счетчика при каждом сравнении ключа с элементом массива
        if (array[i] == target) {
            return i; // вернуть индекс, если элемент найден
        }
    }
    return -1; // если элемент не найден
}

int Sentinel_Linear_Search(const int array[], int size, int target, int& comparisons) {

    comparisons = 0;
    int lastElement = array[size - 1];
    // заменяем последний элемент массива на искомый элемент
    int *arrayWithSentinel = new int[size];
    copy(array, array + size, arrayWithSentinel);
    arrayWithSentinel[size - 1] = target;

    int i = 0;
    while (arrayWithSentinel[i] != target) {
        ++comparisons;
        ++i;
    }
    //восстанавливаем последний элемент массива
    arrayWithSentinel[size - 1] = lastElement;

    if (i < size - 1 || array[size - 1] == target) {
        return i; // Вернуть индекс, если элемент найден
    }
    else {
        return -1; // Вернуть -1, если элемент не найден
    }

    deleteArr(arrayWithSentinel);
}

// Функция линейного поиска в упорядоченном массиве
int Ordered_Array_Search(const int array[], int size, int target, int& comparisons) {
    comparisons = 0;
    int i = 0;
    while (i < size && array[i] < target) {
        ++comparisons;
        ++i;
    }

    if (i < size && array[i] == target) {
        return i; // Вернуть индекс, если элемент найден
    }
    else {
        return -1; // Вернуть -1, если элемент не найден
    }
}
// Функция бинарного поиска в упорядоченном массиве
int Binary_Search(const int array[], int size, int target, int& comparisons) {
    comparisons = 0;
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        ++comparisons;
        int mid = left + (right - left) / 2;

        if (array[mid] == target) {
            return mid;  // Вернуть индекс, если элемент найден
        }
        else if (array[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1; // Вернуть -1, если элемент не найден
}

//функция для измерения времени поиска
template<typename Search>
pair<chrono::nanoseconds, int> measureSearchAndCountComparisons(Search searchFunction, const int array[], int size, int target) {
    auto startTime = chrono::high_resolution_clock::now(); // Запоминаем время начала выполнения функции

    int comparisons; // Переменная для хранения количества операций сравнения

    int results = searchFunction(array, size, target, comparisons); // // Выполняем поиск и получаем количество операций сравнения

    auto endTime = chrono::high_resolution_clock::now(); // Запоминаем время окончания выполнения функции
    auto passedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime); // Вычисляем время выполнения в миллисекундах

    return{ passedTime, comparisons };//вернуть пару значений: время выполнения и количество операций сравнения
}

int main() {
    //инициализация генератора случайных чисел с использованием библиотеки random
    random_device rd;// создание объекта случайных чисел
    mt19937 gen(rd()); // создание случайных чисел с хорошим стат свойством и длинным периодом
    uniform_int_distribution<int> distribution(1, 100);// создание диапазона от 1 до 100

    const int maxSize = 200000;
    const int step = 10000;

    fstream ftime;
    ftime.open("test.txt");

    ftime << "BLS\tSLS\tOAS\tBS" << endl;

    //итерация по различным  размерам массива
    for (int size = step; size <= maxSize; size += step) {
        int *array = new int[size]; // используем массив для хранения элементов


        //Заполнения массива случайными числами и сортировка по неубыванию
        for (int i = 0; i < size; ++i) {
            array[i] = distribution(gen);
        }
        sort(array, array + size);

        // Выбираем случайный элемент для поиска
        int target = array[size % 2];

        // Измеряем время выполнения и подсчитываем операции сравнения для Better Linear Search
        auto linearSearchResult = measureSearchAndCountComparisons(Better_Linear_Search, array, size, target);
        cout << "Better Linear Search for size " << size << ": " << linearSearchResult.first.count() << " ns," <<
            linearSearchResult.second << " comparisons" << std::endl;

        ftime << linearSearchResult.first.count() << '\t';

        // Измеряем время выполнения и подсчитываем операции сравнения для Sentinel Linear Search
        auto sentinalSearchResult = measureSearchAndCountComparisons(Sentinel_Linear_Search, array, size, target);
        cout << "Sentinel Linear Search for size " << size << ": "
            << sentinalSearchResult.first.count() << " ns, "
            << sentinalSearchResult.second << " comparisons" << endl;

        ftime << sentinalSearchResult.first.count() << '\t';

        // Измеряем время выполнения и подсчитываем операции сравнения для Binary Search
        auto binarySearchResult = measureSearchAndCountComparisons(Binary_Search, array, size, target);
        cout << "Binary Search for size " << size << ": "
            << binarySearchResult.first.count() << " ns, " << binarySearchResult.second << " comparisons" << endl;

        ftime << binarySearchResult.first.count() << '\t';

        // Измеряем время выполнения и подсчитываем операции сравнения для Ordered Array Search
        auto orderedSearchResult = measureSearchAndCountComparisons(Ordered_Array_Search, array, size, target);
        cout << "Ordered Array Search for size " << size << ": " << orderedSearchResult.first.count() << " ns," <<
            orderedSearchResult.second << " comparisons" << endl;

        ftime << orderedSearchResult.first.count() << '\t' << '\n';

        cout << endl;// Печатаем пустую строку для разделения результатов

        deleteArr(array);
    }

    ftime.close();

    return 0;
}

int main() {
    //инициализация генератора случайных чисел с использованием библиотеки random
    random_device rd;// создание объекта случайных чисел
    mt19937 gen(rd()); // создание случайных чисел с хорошим стат свойством и длинным периодом
    uniform_int_distribution<int> distribution(1, 100);// создание диапазона от 1 до 100

    const int maxSize = 200000;
    const int step = 10000;

    fstream ftime;
    ftime.open("test.txt");

    ftime << "BLS\tSLS\tOAS\tBS" << endl;

    //итерация по различным  размерам массива
    for (int size = step; size <= maxSize; size += step) {
        int* array = new int[size]; // используем массив для хранения элементов


        //Заполнения массива случайными числами и сортировка по неубыванию
        for (int i = 0; i < size; ++i) {
            array[i] = distribution(gen);
        }
        sort(array, array + size);

        // Выбираем элемент для поиска
        int target = array[size % 2];

        // Измеряем время выполнения и подсчитываем операции сравнения для Better Linear Search
        auto linearSearchResult = measureSearchAndCountComparisons(Better_Linear_Search, array, size, target);
        cout << "Better Linear Search for size " << size << ": " << linearSearchResult.first.count() << " ns," <<
            linearSearchResult.second << " comparisons" << std::endl;

        ftime << linearSearchResult.first.count() << '\t';

        // Измеряем время выполнения и подсчитываем операции сравнения для Sentinel Linear Search
        auto sentinalSearchResult = measureSearchAndCountComparisons(Sentinel_Linear_Search, array, size, target);
        cout << "Sentinel Linear Search for size " << size << ": "
            << sentinalSearchResult.first.count() << " ns, "
            << sentinalSearchResult.second << " comparisons" << endl;

        ftime << sentinalSearchResult.first.count() << '\t';

        // Измеряем время выполнения и подсчитываем операции сравнения для Binary Search
        auto binarySearchResult = measureSearchAndCountComparisons(Binary_Search, array, size, target);
        cout << "Binary Search for size " << size << ": "
            << binarySearchResult.first.count() << " ns, " << binarySearchResult.second << " comparisons" << endl;

        ftime << binarySearchResult.first.count() << '\t';

        // Измеряем время выполнения и подсчитываем операции сравнения для Ordered Array Search
        auto orderedSearchResult = measureSearchAndCountComparisons(Ordered_Array_Search, array, size, target);
        cout << "Ordered Array Search for size " << size << ": " << orderedSearchResult.first.count() << " ns," <<
            orderedSearchResult.second << " comparisons" << endl;

        ftime << orderedSearchResult.first.count() << '\t' << '\n';

        cout << endl;// Печатаем пустую строку для разделения результатов

        deleteArr(array);
    }

    ftime.close();

    return 0;
}