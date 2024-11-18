#include <iostream>

//此算法为插入排序的改进
//T(n) = O(n^1.3)

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



auto shell_sort(int* arr,const int n) {
   int gap = n/2;//初始间隔为n/2
   while (gap>=1) {
        //外循环控制gap
        //每隔gap个数进行一次插入排序
        for(int i=gap;i<n;++i) {
            int count = i/gap;//向前遍历次数
            int offset = i%gap;//确定组号
            for (int j=count;j>0;--j) {
                if (arr[j*gap+offset]<arr[(j-1)*gap+offset])
                    swap(arr[j*gap+offset],arr[(j-1)*gap+offset]);
            }
        }
       gap /= 2; //间隔变成原来一半
   }
}

int main(int argc,char* argv[]) {
    int arr[] = {12,13,12,10,3,2,14,1,9,19,6};
    shell_sort(arr,sizeof(arr)/sizeof(int));
    print_arr(arr,sizeof(arr)/sizeof(int));
}