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

auto bubble_sort(int* arr,const int n) ->void {
    for (int i=0;i<n;++i) {
        for(int j=0;j<n-1-i;++j)
            if (arr[j+1]<arr[j])
                swap(arr[j+1],arr[j]);
    }
}

int main(int argc,char* argv[]) {
    int arr[] = {12,13,12,10,3,2,14,1};
    bubble_sort(arr,sizeof(arr)/sizeof(int));
    print_arr(arr,sizeof(arr)/sizeof(int));
    return 0;
}