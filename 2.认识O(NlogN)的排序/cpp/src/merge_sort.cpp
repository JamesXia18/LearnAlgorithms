#include <iostream>

void merge(int* arr,int L,int mid,int R) {
    int i =0;
    int* help = new int[R-L+1]; //The ptr beed to be free!
    int p1 = L;
    int p2 = mid+1;
    //归并
    while (p1<=mid && p2<=R) {
        help[i++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
    }
    while (p1<=mid) {
        help[i++] = arr[p1++];
    }
    while (p2<=R) {
        help[i++] = arr[p2++];
    }
    for(i = 0;i<(R-L+1);++i) {
        arr[L+i] = help[i];
    }
    delete[] help; //Free help!
    help = nullptr;//Care about the problem of Dangling
}

void process(int*arr,int L,int R) {
    if (L==R) return;
    int mid = L + (R-L)/2;
    process(arr,L,mid);
    process(arr,mid+1,R);
    merge(arr,L,mid,R);
}


int main(void) {
    int arr[] = {12,5,14,2,11,20,5};
    process(arr,0,sizeof(arr)/sizeof(int)-1);
    for (auto i : arr) 
        std::cout<<i<<" ";
    return 0;
}