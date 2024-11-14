#include <iostream>


int merge(int* arr,int L,int mid,int R) {
    int* help = new int[R-L+1];
    int i = 0;
    int p1 = L,p2 = mid+1;
    int sum = 0;
    while (p1<=mid && p2<=R) {
        if (arr[p1]<arr[p2]) {
            //左边小于右边
            //小和 = (p2->R).length*arr[p1]
            sum += arr[p1]*(R-p2+1);
            help[i++] = arr[p1++];
        } else {
            //左边不动，右边copy
            help[i++] = arr[p2++];
        }
    }

    while ( p1 <= mid ) {
        help[i++] = arr[p1++];
    }

    while ( p2 <= R )
    {
        help[i++] = arr[p2++];
    }
    delete[] help;
    help = nullptr;
    return sum;
}


int process(int* arr,int L,int R) {
    if (L==R) return 0;
    int mid = L + (R-L)/2;
    return process(arr,L,mid)+process(arr,mid+1,R)+merge(arr,L,mid,R);
}


int main(void) {
    
    int arr[] = {1,3,4,2,5};
    int small_sum = process(arr,0,sizeof(arr)/sizeof(int)-1);
    std::cout<<"The small sum of the arr is "<<small_sum<<std::endl;

    return 0;
}