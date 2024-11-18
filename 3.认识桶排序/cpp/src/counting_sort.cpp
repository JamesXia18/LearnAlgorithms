#include <iostream>

auto print_arr(int arr[], int n) -> void {
    for (int i=0;i<n;++i)
        std::cout<<arr[i]<<" ";
    std::cout<<"\n";
}

auto max(const int arr[],const int n) -> int {
    int max = arr[0];
    for (int i=0;i<n;++i)
        max = arr[i]>max ? arr[i] : max;
    return max;
}

/// 计数排序
/// @param arr 数组arr
/// @param n 范围[0,n)
/// @param k 数组元素[0,k]整数
auto counting_sort(int arr[],const int n,const int k) -> void  {
    int* help = new int[k+1]{0};
    int* arr_help = new int[n]{0};
    //求频率表
    for (int i=0;i<n;++i) {
        ++help[arr[i]];
    }
    //求前缀和
    for (int i=1;i<k+1;++i)
        help[i] += help[i-1];
    //根据前缀和求出排序后的数组
    //前缀和确定了元素的位置
    //从后往前遍历，确保元素的稳定性
    for (int j=n-1;j>=0;--j) {
        int a = arr[j];
        //int index = help[a]-1;
        //arr_help[index] = a;
        arr_help[help[a]-1] = a;
        --help[a];
    }
    //拷贝
    for (int i=0;i<n;++i) {
        arr[i] = arr_help[i];
    }
    delete[] help;
    delete[] arr_help;
}

int main(int argc,char* argv[]) {
    int arr[] = {16, 4, 10, 14, 7, 9, 3, 2, 8, 1,4,};
    int k = max(arr,sizeof(arr)/sizeof(int));
    counting_sort(arr,sizeof(arr)/sizeof(int),k);
    print_arr(arr,sizeof(arr)/sizeof(int));
    return 0;
}
