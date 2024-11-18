#include <iostream>

auto print_arr(int* arr,const int n) {
    for (int i=0;i<n;++i)
        std::cout<<arr[i]<<" ";
    std::cout<<"\n";
}

template <typename T>
auto swap(T& a,T& b) {
    T temp = a;
    a = b;
    b = temp;
}

auto insertion_sort(int arr[],const int n) {
    for (int i=0;i<n;++i) {
        for(int j=i;j>0;--j) {
            if (arr[j]<arr[j-1]) {
                swap(arr[j],arr[j-1]);
            }
        }
    }
}

int main(int argc,char* argv[]) {
    int arr[] = {12,13,12,10,3,2,14,1};
    insertion_sort(arr,sizeof(arr)/sizeof(int));
    print_arr(arr,sizeof(arr)/sizeof(int));
    return 0;
}