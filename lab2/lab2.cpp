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
    for (int i = 0; i < size; i++) {
        if (array[i] == key) return i;
    }
    return -1;
}

int SLS(int* array, int size, int key) {

    int last = array[size - 1];
    array[size - 1] = key;
    int i = 0;
    while (array[i] != key) {
        i++;
    }
    array[size - 1] = last;

    if (i < size - 1 || array[size - 1] == key) {
        return i;
    }
    return -1;
}

int OAS(int* array, int size, int key) {
    int i = 0;
    while (i != size) {
        if (array[i] == key) {
            return i;
        }
        i++;
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
    cout << BLS(arr, size, 56);
}