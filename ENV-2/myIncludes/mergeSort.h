#ifndef MY_MERGE_H
#define MY_MERGE_H

#include <vector>
#include "MyComplex.h"

void mergeParts(std::vector<MyComplex>& arr, int l, int m, int r);
void mergeSortRec(std::vector<MyComplex>& arr, int l, int r);

#endif	
