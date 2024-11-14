#include <cstdlib>
#include <ctime>
#include <iostream>

//快速排序在不引入随机数时,T(n) = O(N^2)

//基础函数swap
void swap(int* a,int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/// @brief 选取最右侧的数做划分
/// @param arr 
/// @param L 
/// @param R 
int partition(int* arr,int L,int R) {
    int index = L; //最小区域的右边界
    for (int i=L;i<=R-1;++i) {
        if (arr[i]<=arr[R]) {
            //将index位置与i位置交换
            swap(arr+index,arr+i);
            ++index; //最小区域右移
        } 
    }
    swap(arr+R,arr+index);
    return index;
}

void quick_sort(int* arr,int L,int R) {
    if (L<R){
        //T(N) = O(NlogN)
        int r = rand()%(R-L)+L;
        swap(arr+r,arr+R);
        int i = partition(arr,L,R);
        quick_sort(arr,L,i-1);
        quick_sort(arr,i+1,R);
    }
}


int main(void) {
    srand(time(nullptr));

    int arr[] = {2,3,12,1,4,5,2,3,7,0,1,1,2};

    quick_sort(arr,0,sizeof(arr)/sizeof(int)-1);

    for (auto item : arr) 
        std::cout<<item<<" ";
    return 0;
}