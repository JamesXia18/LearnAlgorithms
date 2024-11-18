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

auto selection_sort(int* arr,const int n) {
    for (int i=0;i<n;++i) {
        int min = i;
        for (int j=i+1;j<n;++j) {
            if (arr[j]<arr[min]) {
                min = j;
            }
        }
        swap(arr[i],arr[min]);
    }
}

int main(int argc,char* argv[]) {
    int arr[] = {12,13,12,10,3,2,14,1};
    selection_sort(arr,sizeof(arr)/sizeof(int));
    print_arr(arr,sizeof(arr)/sizeof(int));
    return 0;
}