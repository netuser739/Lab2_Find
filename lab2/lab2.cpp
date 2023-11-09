#include <iostream>

using namespace std;

void RandomArray(int* array, int size, int minValue, int maxValue) {
    for (int i = 0; i < size; i++) {
        array[i] = (double)rand() / RAND_MAX * (maxValue - minValue) + minValue;
    }
}

void LowToUpArray(int* array, int size, int minValue, int maxValue) {
    if (size >= (maxValue - minValue + 1)) {
        for (int i = 0; i < size; i++) {
            array[i] = minValue;
            if (minValue < maxValue)
                minValue++;
        }
    }
    else {
        int left = minValue;
        int right = maxValue - size + 1;
        for (int i = 0; i < size; i++) {
            array[i] = (double)rand() / RAND_MAX * (right - left) + left;
            left = array[i] + 1;
            right++;
        }
    }
}

int BLS(int* array, int size, int key) {
    int k = 0;
    int kInd = 0;

    for (int i = 0; i < size; i++) {
        k++;
        if (array[i] == key) {
            cout << k << " - kol-vo cravneniy;\n";
            return i;
        }
    }
    cout << k << " - kol-vo cravneniy;\n";
    return -1;
}

int SLS(int* array, int size, int key) {
    int k = 0;

    int last = array[size - 1];
    array[size - 1] = key;
    int i = 0;

    while (array[i] != key) {
        k++;
        i++;
    }
    array[size - 1] = last;

    if (i < size - 1 || array[size - 1] == key) {
        cout << k+1 << " - kol-vo cravneniy;\n";
        return i;
    }

    cout << k << " - kol-vo cravneniy";
    return -1;
}

int OAS(int* array, int size, int key) {
    int last = array[size - 1];
    array[size - 1] = INT_MAX;
    int i = 0;
    while (array[i] < key) {
        i++;
    }
    array[size - 1] = last;
    if (array[i] = key) {
        return i;
    }
    if (array[size - 1] = key) {
        return size - 1;
    }

    return -1;
}

int BS(int* array, int size, int key) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (array[mid] == key) {
            return mid;
        }
        else {
            if (array[mid] < key) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
    }
    return -1;
}

int main()
{
    const int size = 7;
    int arr[size] = { 1, 5, 6, 9, 23, 45, 87};
    cout << SLS(arr, size, 9);
}