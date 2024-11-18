#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>

using namespace std;

auto print_arr(int arr[], int n) -> void {
    for (int i=0;i<n;++i)
        std::cout<<arr[i]<<" ";
    std::cout<<"\n";
}
//假设本次比较数的范围是[0,999]的3位数
//利用基数排序完成对数据的排序
//一共有10个桶，[0,9],即数据采用10进制

///
/// @param num 输入的正整数
/// @param k 第k位 EX:0个位，1十位，2百位
/// @return 第k位数
auto get_num(const int num,const int k) ->int {
    int result = 0;
    auto func = [](int i) -> int {
        int result = 1;
        for (int j=0;j<i;++j)
            result *= 10;
        return result;
    };
    for (int i=0;i<=k;++i) {
        result = num%(10*func(i)) - result;
    }
    return result/func(k);
}


auto radix_sort(int arr[],const int n,const int k) {
    auto buckets = vector<queue<int>>(10);
    for (int i = 0;i<=k;++i) { //遍历次数
        for (int j=0;j<n;++j) { //入桶
            int index = get_num(arr[j],i);
            buckets[index].push(arr[j]);
        }
        //出桶
        auto help = vector<int>();
        for (int j=0;j<10;++j) {
            int size = buckets[j].size();
            for (int m=0;m<size;++m) {
                help.push_back(buckets[j].front());
                buckets[j].pop();
            }
        }
        //拷贝
        for (int m=0;m<n;++m)
            arr[m] = help[m];
    }
}


int main(int argc,char* argv[]) {
    srand(time(nullptr));

    int arr[] = {16, 4, 10, 14, 7, 9, 3, 2, 8, 1,4,999};

    radix_sort(arr,sizeof(arr)/sizeof(int),2);
    print_arr(arr,sizeof(arr)/sizeof(int));
    return 0;
}
