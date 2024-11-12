#include <iostream>

int get_max(int* arr,int L, int R) {
    if (L==R)
        return arr[L];
    int mid = L + ((R-L)>>2);
    int leftMax = get_max(arr,L,mid);
    int rightMax = get_max(arr,mid+1,R);
    return leftMax>rightMax ? leftMax : rightMax;
}


int main(void) {
    int arr[] = {12,13,14,15,16,20};
    int max= get_max(arr,0,sizeof(arr)/sizeof(int)-1);
    std::cout<<max;
}