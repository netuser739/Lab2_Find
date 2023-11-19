#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <windows.h>

using namespace std;

//������� ��������� ������
void deleteArr(int* arr) {
    delete arr;
}

//������� ��������� ������
int Better_Linear_Search(const int array[], int size, int target, int& comparisons) {
    comparisons = 0;
    for (int i = 0; i < size; ++i) {
        ++comparisons; // ���������� �������� ��� ������ ��������� ����� � ��������� �������
        if (array[i] == target) {
            return i; // ������� ������, ���� ������� ������
        }
    }
    return -1; // ���� ������� �� ������
}

int Sentinel_Linear_Search(const int array[], int size, int target, int& comparisons) {

    comparisons = 0;
    int lastElement = array[size - 1];
    // �������� ��������� ������� ������� �� ������� �������
    int *arrayWithSentinel = new int[size];
    copy(array, array + size, arrayWithSentinel);
    arrayWithSentinel[size - 1] = target;

    int i = 0;
    while (arrayWithSentinel[i] != target) {
        ++comparisons;
        ++i;
    }
    //��������������� ��������� ������� �������
    arrayWithSentinel[size - 1] = lastElement;

    if (i < size - 1 || array[size - 1] == target) {
        return i; // ������� ������, ���� ������� ������
    }
    else {
        return -1; // ������� -1, ���� ������� �� ������
    }

    deleteArr(arrayWithSentinel);
}

// ������� ��������� ������ � ������������� �������
int Ordered_Array_Search(const int array[], int size, int target, int& comparisons) {
    comparisons = 0;
    int i = 0;
    while (i < size && array[i] < target) {
        ++comparisons;
        ++i;
    }

    if (i < size && array[i] == target) {
        return i; // ������� ������, ���� ������� ������
    }
    else {
        return -1; // ������� -1, ���� ������� �� ������
    }
}
// ������� ��������� ������ � ������������� �������
int Binary_Search(const int array[], int size, int target, int& comparisons) {
    comparisons = 0;
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        ++comparisons;
        int mid = left + (right - left) / 2;

        if (array[mid] == target) {
            return mid;  // ������� ������, ���� ������� ������
        }
        else if (array[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1; // ������� -1, ���� ������� �� ������
}

//������� ��� ��������� ������� ������
template<typename Search>
pair<chrono::nanoseconds, int> measureSearchAndCountComparisons(Search searchFunction, const int array[], int size, int target) {
    auto startTime = chrono::high_resolution_clock::now(); // ���������� ����� ������ ���������� �������

    int comparisons; // ���������� ��� �������� ���������� �������� ���������

    int results = searchFunction(array, size, target, comparisons); // // ��������� ����� � �������� ���������� �������� ���������

    auto endTime = chrono::high_resolution_clock::now(); // ���������� ����� ��������� ���������� �������
    auto passedTime = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime); // ��������� ����� ���������� � �������������

    return{ passedTime, comparisons };//������� ���� ��������: ����� ���������� � ���������� �������� ���������
}

int main() {
    //������������� ���������� ��������� ����� � �������������� ���������� random
    random_device rd;// �������� ������� ��������� �����
    mt19937 gen(rd()); // �������� ��������� ����� � ������� ���� ��������� � ������� ��������
    uniform_int_distribution<int> distribution(1, 100);// �������� ��������� �� 1 �� 100

    const int maxSize = 200000;
    const int step = 10000;

    fstream ftime;
    ftime.open("test.txt");

    ftime << "BLS\tSLS\tOAS\tBS" << endl;

    //�������� �� ���������  �������� �������
    for (int size = step; size <= maxSize; size += step) {
        int *array = new int[size]; // ���������� ������ ��� �������� ���������


        //���������� ������� ���������� ������� � ���������� �� ����������
        for (int i = 0; i < size; ++i) {
            array[i] = distribution(gen);
        }
        sort(array, array + size);

        // �������� ��������� ������� ��� ������
        int target = array[size % 2];

        // �������� ����� ���������� � ������������ �������� ��������� ��� Better Linear Search
        auto linearSearchResult = measureSearchAndCountComparisons(Better_Linear_Search, array, size, target);
        cout << "Better Linear Search for size " << size << ": " << linearSearchResult.first.count() << " ns," <<
            linearSearchResult.second << " comparisons" << std::endl;

        ftime << linearSearchResult.first.count() << '\t';

        // �������� ����� ���������� � ������������ �������� ��������� ��� Sentinel Linear Search
        auto sentinalSearchResult = measureSearchAndCountComparisons(Sentinel_Linear_Search, array, size, target);
        cout << "Sentinel Linear Search for size " << size << ": "
            << sentinalSearchResult.first.count() << " ns, "
            << sentinalSearchResult.second << " comparisons" << endl;

        ftime << sentinalSearchResult.first.count() << '\t';

        // �������� ����� ���������� � ������������ �������� ��������� ��� Binary Search
        auto binarySearchResult = measureSearchAndCountComparisons(Binary_Search, array, size, target);
        cout << "Binary Search for size " << size << ": "
            << binarySearchResult.first.count() << " ns, " << binarySearchResult.second << " comparisons" << endl;

        ftime << binarySearchResult.first.count() << '\t';

        // �������� ����� ���������� � ������������ �������� ��������� ��� Ordered Array Search
        auto orderedSearchResult = measureSearchAndCountComparisons(Ordered_Array_Search, array, size, target);
        cout << "Ordered Array Search for size " << size << ": " << orderedSearchResult.first.count() << " ns," <<
            orderedSearchResult.second << " comparisons" << endl;

        ftime << orderedSearchResult.first.count() << '\t' << '\n';

        cout << endl;// �������� ������ ������ ��� ���������� �����������

        deleteArr(array);
    }

    ftime.close();

    return 0;
}

int main() {
    //������������� ���������� ��������� ����� � �������������� ���������� random
    random_device rd;// �������� ������� ��������� �����
    mt19937 gen(rd()); // �������� ��������� ����� � ������� ���� ��������� � ������� ��������
    uniform_int_distribution<int> distribution(1, 100);// �������� ��������� �� 1 �� 100

    const int maxSize = 200000;
    const int step = 10000;

    fstream ftime;
    ftime.open("test.txt");

    ftime << "BLS\tSLS\tOAS\tBS" << endl;

    //�������� �� ���������  �������� �������
    for (int size = step; size <= maxSize; size += step) {
        int* array = new int[size]; // ���������� ������ ��� �������� ���������


        //���������� ������� ���������� ������� � ���������� �� ����������
        for (int i = 0; i < size; ++i) {
            array[i] = distribution(gen);
        }
        sort(array, array + size);

        // �������� ������� ��� ������
        int target = array[size % 2];

        // �������� ����� ���������� � ������������ �������� ��������� ��� Better Linear Search
        auto linearSearchResult = measureSearchAndCountComparisons(Better_Linear_Search, array, size, target);
        cout << "Better Linear Search for size " << size << ": " << linearSearchResult.first.count() << " ns," <<
            linearSearchResult.second << " comparisons" << std::endl;

        ftime << linearSearchResult.first.count() << '\t';

        // �������� ����� ���������� � ������������ �������� ��������� ��� Sentinel Linear Search
        auto sentinalSearchResult = measureSearchAndCountComparisons(Sentinel_Linear_Search, array, size, target);
        cout << "Sentinel Linear Search for size " << size << ": "
            << sentinalSearchResult.first.count() << " ns, "
            << sentinalSearchResult.second << " comparisons" << endl;

        ftime << sentinalSearchResult.first.count() << '\t';

        // �������� ����� ���������� � ������������ �������� ��������� ��� Binary Search
        auto binarySearchResult = measureSearchAndCountComparisons(Binary_Search, array, size, target);
        cout << "Binary Search for size " << size << ": "
            << binarySearchResult.first.count() << " ns, " << binarySearchResult.second << " comparisons" << endl;

        ftime << binarySearchResult.first.count() << '\t';

        // �������� ����� ���������� � ������������ �������� ��������� ��� Ordered Array Search
        auto orderedSearchResult = measureSearchAndCountComparisons(Ordered_Array_Search, array, size, target);
        cout << "Ordered Array Search for size " << size << ": " << orderedSearchResult.first.count() << " ns," <<
            orderedSearchResult.second << " comparisons" << endl;

        ftime << orderedSearchResult.first.count() << '\t' << '\n';

        cout << endl;// �������� ������ ������ ��� ���������� �����������

        deleteArr(array);
    }

    ftime.close();

    return 0;
}