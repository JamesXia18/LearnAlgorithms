#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>
//二叉树的遍历方法
//1.递归法
// (1) 根-左-右 前序遍历
// (2) 左-根-右 中序遍历
// (3) 左-右-根 后序遍历
//2.层序遍历

/// 二叉树节点
/// @tparam T 二叉树数据类型
template<class T>
struct Node {
    T data;
    Node* left;
    Node* right;
};

/// 二叉树的递归遍历
/// @tparam T 参数类型
/// @param L 节点指针
/// @return void
template<typename T>
auto func(Node<T>* L) {
    if (L==nullptr) {
        return;
    }
    std::cout<<L->data<<" ";
    func(L->left);
    std::cout<<L->data<<" ";
    func(L->right);
    std::cout<<L->data<<" ";
}

//递归法:前序遍历
template<typename T>
auto func_forward(Node<T>* L) {
    if (L==nullptr) {
        return;
    }
    std::cout<<L->data<<" ";

    func_forward(L->left);

    func_forward(L->right);

}

//递归:中序遍历
template<typename T>
auto func_middle(Node<T>* L) {
    if (L==nullptr) {
        return;
    }
    func_middle(L->left);
    std::cout<<L->data<<" ";
    func_middle(L->right);
}

//递归:后序遍历
template<typename T>
auto func_back(Node<T>* L) {
    if (L==nullptr) {
        return;
    }
    func_back(L->left);

    func_back(L->right);
    std::cout<<L->data<<" ";
}

//迭代:先序遍历 根-左-右
template<typename T>
auto forward(Node<T>* L) {
    //1.将根节压入栈
    //2.将节点弹出栈,并处理
    //3.将节点的右-左节点依次压入栈
    //4.执行2直到栈空
    if (L==nullptr) return;
    std::stack<Node<T>> s;
    s.push(*L);
    while (!s.empty()) {
        Node<T> tmp = s.top();
        s.pop();
        std::cout<<tmp.data<<" ";
        if (tmp.right!=nullptr)
            s.push(*(tmp.right));
        if (tmp.left!=nullptr)
            s.push(*(tmp.left));
    }
}

//迭代:中序遍历 左-根-右
template<typename T>
auto middle(Node<T>* L) {
    //1.将左边界全部压入栈
    //2.弹出节点元素，并判断
    //    (1) 有右节点
    //         压入右节点的全部左边界
    //    (2) 无右节点
    //         继续执行2，直到栈空
    if (L==nullptr) return;
    std::stack<Node<T>> s;
    s.push(*L);
    while (L->left!=nullptr) {
        s.push(*L->left);
        L = L->left;
    }
    while (!s.empty()) {
        Node<T> tmp = s.top();
        s.pop();
        std::cout<<tmp.data<<" ";
        if (tmp.right!=nullptr) {
            s.push(*tmp.right);
            tmp = *tmp.right;
            while (tmp.left!=nullptr) {
                s.push(*tmp.left);
                tmp = *tmp.left;
            }
        }
    }
}

//迭代:后序遍历 左-右-根
template<typename T>
auto back(Node<T>* L) {
    //1.将根节压入栈s1
    //2.将节点弹出栈,并进入栈s2
    //3.将节点的左-右节点依次压入栈
    //4.执行2直到栈s1空
    //5.将s2的数据依次岀栈
    if (L==nullptr) return;
    std::stack<Node<T>> s1,s2;
    s1.push(*L);
    while (!s1.empty()) {
        Node<T> tmp = s1.top();
        s1.pop();
        s2.push(tmp);
        if (tmp.left!=nullptr)
            s1.push(*tmp.left);
        if (tmp.right!=nullptr)
            s1.push(*tmp.right);
    }
    while (!s2.empty()) {
        Node<T> tmp = s2.top();
        std::cout<<tmp.data<<" ";
        s2.pop();
    }
}

//二叉树的层序遍历
template<typename T>
auto sequence(Node<T>* L) {
    //1.将根节点排入队列
    //2.取出节点
    //3.判断节点是否存在左右子节点
    //     (1) 左节点存在 ，左节点入队
    //     (2) 右节点存在 ，右节点入队
    //4.重复第2步，直到队空
    if (L==nullptr) return;
    std::queue<Node<T>> q;
    q.push(*L);
    while (!q.empty()) {
        Node<T> tmp = q.front();
        //TODO
        std::cout<<tmp.data<<" ";
        q.pop();
        if (tmp.left!=nullptr)
            q.push(*tmp.left);
        if (tmp.right!=nullptr)
            q.push(*tmp.right);
    }
}

//求解二叉树的宽度
//hash表记录自定义类型时，记录的是自定义类型的地址
template<typename T>
auto max_length(Node<T>* L) -> int {
    if (L == nullptr) return -1;
    std::unordered_map<Node<T>*, int> map; // hash表记录节点指针-层序
    int curLevel = 1; // 当前层,初始为第一层
    int max = 0; // 最大宽度
    int curLevelNodes = 0; // 当前层累计节点数
    std::queue<Node<T>*> q; // 层序遍历所需队列
    // 初始化，将根节点添加到队列和哈希表
    q.push(L);
    map[L] = curLevel;
    while (!q.empty()) {
        Node<T>* tmp = q.front();
        q.pop();
        int curNodeLevel = map[tmp];
        if (curNodeLevel == curLevel) {
            ++curLevelNodes;
        } else {
            max = std::max(max, curLevelNodes);
            ++curLevel;
            curLevelNodes = 1;
        }
        if (tmp->left != nullptr) {
            q.push(tmp->left);
            map[tmp->left] = curNodeLevel + 1;
        }
        if (tmp->right != nullptr) {
            q.push(tmp->right);
            map[tmp->right] = curNodeLevel + 1;
        }
    }
    max = std::max(max, curLevelNodes); // 别忘了最后一层
    return max;
}

int main(int argc,char* argv[]) {
    //创建二叉树
    //           1
    //       2      3
    //    4    5  6   7
    Node<int> _1;
    _1.data = 1;
    Node<int> _2;
    _2.data = 2;
    Node<int> _3;
    _3.data = 3;
    Node<int> _4;
    _4.data = 4;
    Node<int> _5;
    _5.data = 5;
    Node<int> _6;
    _6.data = 6;
    Node<int> _7;
    _7.data = 7;
    _1.left = &_2;_1.right = &_3;
    _2.left = &_4;_2.right = &_5;
    _3.left = &_6;_3.right = &_7;
    _4.left = nullptr;_4.right = nullptr;
    _5.left = nullptr;_5.right = nullptr;
    _6.left = nullptr;_6.right = nullptr;
    _7.left = nullptr;_7.right = nullptr;
    //
    std::cout<<"二叉树的递归遍历:";
    func<int>(&_1);
    std::cout<<"\n"<<"二叉树的前序遍历(递归):";
    func_forward(&_1);
    std::cout<<"\n"<<"二叉树的中序遍历(递归):";
    func_middle(&_1);
    std::cout<<"\n"<<"二叉树的后序遍历(递归):";
    func_back(&_1);
    std::cout<<"\n"<<"二叉树的先序遍历(迭代):";
    forward(&_1);
    std::cout<<"\n"<<"二叉树的中序遍历(迭代):";
    middle(&_1);
    std::cout<<"\n"<<"二叉树的后序遍历(迭代):";
    back(&_1);
    std::cout<<"\n"<<"二叉树的层序遍历:";
    sequence(&_1);
    std::cout<<"\n"<<"二叉树的宽度为:"<<max_length(&_1);
    return 0;
}
