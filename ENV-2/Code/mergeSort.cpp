#include "../myIncludes/mergeSort.h"
#include <cmath>

void mergeParts(std::vector<MyComplex>& arr, int l, int m, int r) {
    int size1 = m - l + 1;
    int size2 = r - m;

    std::vector<MyComplex> arr1 (size1);
   

    for (int i = 0; i < size1; ++i)
        arr1[i] = arr[l + i];

    std::vector<MyComplex> arr2 (size2);
    for (int j = 0; j < size2; ++j)
        arr2[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < size1 && j < size2) {
        double absLeft = arr1[i].modules();
        double absRight = arr2[j].modules();

        if (absLeft < absRight ||
           (absLeft == absRight && arr1[i].getReal() <= arr2[j].getReal())) {
            arr[k++] = arr1[i++];
        } else {
            arr[k++] = arr2[j++];
        }
    }

    while (i < size1)
        arr[k++] = arr1[i++];

    while (j < size2)
        arr[k++] = arr2[j++];
}

void mergeSortRec(std::vector<MyComplex>& arr, int l, int r) {
    if (r <= l) return;

        int m = (l + r) / 2;
        mergeSortRec(arr, l, m);
        mergeSortRec(arr, m + 1, r);
        mergeParts(arr, l, m, r);
    
}

