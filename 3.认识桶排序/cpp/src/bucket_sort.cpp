#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

auto print_arr(int* arr,const int n) {
    for (int i=0;i<n;++i)
        cout<<arr[i]<<" ";
    cout<<endl;
}

auto max(const int arr[],const int n) -> int {
    int max = arr[0];
    for (int i=0;i<n;++i)
        max = arr[i]>max ? arr[i] : max;
    return max;
}

//桶的个数
constexpr int BUCKET_NUM = 5;

//注意返回的是桶的逻辑序号，即第几个桶
auto find_bucket(const int k,const int num) ->int {
    // k/BUCKET_NUM确定了每个桶的范围
    int step = k/BUCKET_NUM+1;
    return num/step+1;
}


/// 0~k范围内桶排序
/// @param arr 数组arr
/// @param n 数组范围[0,n)
/// @param k [0,k]
auto bucket_sort(int* arr,const int n,const int k) ->void {
    auto buckets = vector<vector<int>>(BUCKET_NUM);
    //每个桶容纳的范围由k决定
    for (int i=0;i<n;++i) {
        int index = find_bucket(k,arr[i]);
        buckets[index-1].push_back(arr[i]);
    }
    //对每个桶进行排序
    for (auto& bucket : buckets) {
        std::sort(bucket.begin(),bucket.end(),[](int& a,int& b)->bool{return a<b;});
    }
    //归并每一个桶
    auto help = vector<int>();
    for (const auto& bucket: buckets) {
        for (auto i : bucket) {
            help.push_back(i);
        }
    }
    //拷贝
    for (int i=0;i<n;++i)
        arr[i] = help[i];
}

int main(int argc,char* argv[]) {
    int arr[] = {16, 4, 10, 14, 7, 9, 3, 2, 8, 1,4,20};
    int k = max(arr,sizeof(arr)/sizeof(int));
    bucket_sort(arr,sizeof(arr)/sizeof(int),k);
    print_arr(arr,sizeof(arr)/sizeof(int));
    return 0;
}