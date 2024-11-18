#include <iostream>
#include <vector>

//堆的是一种特殊的完全二叉树，区别是
//堆分为大根堆和小根堆，大根堆上所有元素的父亲节点均大于它两个孩子节点
//可以用一位数组去描述一个逻辑上的堆
//堆排序逻辑上可以原地排序，S(N) = O(1),这里为了，描述方便，S(N) = O(N)
//T(N) = O(NlogN)
class Heap {
public:
    std::vector<int> heap; //用动态数组描述二叉树

    /// @brief 根据int数组创建堆
    /// @param arr 数组指针
    /// @param N 数组大小
    auto init(int arr[],const int N) ->void {
        if (arr==nullptr || N<=0)
            return;
        heap.clear();
        heap_size = N;
        for (int i=0;i<N;++i) {
            heap.push_back(arr[i]);
            heapInsert(i);
        }
    }

    /// @brief 某个数现在在index位置，向上继续移动(或不动)
    /// @param index 元素位置
    auto heapInsert(int index) -> void {
        int father = (index-1)/2;
        while (heap[father] < heap[index]) {
            swap(father,index);
            index = father;
            father = (index-1)/2;
        }
    }

    /// @brief 某个数现在在index位置，向下继续移动(或不动)
    /// @param index 元素位置
    auto heapify(int index) -> void {
        int left = 2*index+1; //左孩子的下标
        while (left<=heap_size-1) { //如果存在左孩子
            if (left == heap_size-1) { //如果仅有左孩子
                if (heap[index] < heap[left]) {
                    swap(index,left);
                }
            }
            //找到两个孩子的最大值
            int largest = heap[left] > heap[left+1] ? left : left+1;
            //父亲比两个孩子都大，不需要下移
            if (heap[index] >= heap[largest])
                break;
            swap(index,largest);
            index = largest;
            left = 2*index+1;
        }
    }

    int operator[] (const int i) const {
        return heap[i];
    }

    int& operator[] (const int i) {
        return heap[i];
    }

    static auto heap_sort(int *arr, const int N) -> void {
        Heap heap;
        //创建一个大根堆
        heap.init(arr,N);
        for (int j=N-1;j>=0;--j) {
            arr[j] = heap[0]; //抛出根节点
            heap[0] = heap[heap.heap_size-1]; //交换最后一个叶子
            heap.heap_size -= 1; //堆大小减1
            heap.heapify(0); //根节点调整
        }
    }

    int heap_size = 0; //堆的大小

protected:
    /// @brief 交换a、b两个位置的元素
    auto swap(int a, int b) -> void {
        const int temp = heap[a];
        heap[a] = heap[b];
        heap[b] = temp;
    }
};


int main(int args,char* argv[]) {
    int arr[] = {12,3,41,42,20,10,-1,2,12,23,312};
    Heap::heap_sort(arr,sizeof(arr)/sizeof(int));
    for (auto item : arr) {
        std::cout<<item<<" ";
    }
    return 0;
}