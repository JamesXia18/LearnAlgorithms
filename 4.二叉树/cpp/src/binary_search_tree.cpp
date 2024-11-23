#include <iostream>
#include <stack>
#include <functional>
//判断一个二叉树是否为二叉搜索树
//1.非空左子树的所有键值小于其根结点的键值。
//2.非空右子树的所有键值大于其根结点的键值。
//3.左、 右子树都是二叉搜索树

/// 二叉树节点
/// @tparam T 二叉树数据类型
template<class T>
struct Node {
    T data;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(T data) : data(data) { }
};

//假设T为正整数
template<>
struct Node<int> {
    int data = INT32_MIN;
    Node* left = nullptr;
    Node* right = nullptr;
};

class CheckBST {
public:

    //法一：改造二叉树的中序遍历（递归法）
    template<typename T>
    static auto func1(Node<T>* L,T& preValue) ->bool {
        if (L==nullptr) return true;
        //左子树是二叉搜索树
        bool isLeftBST = func1<T>(L->left,preValue);
        if (!isLeftBST) return false;
        if (L->data<=preValue) return false;
        else preValue = L->data;
        //右子树是二叉搜索树
        return func1(L->right,preValue);
    }

    //法二：改造二叉树的中序遍历（迭代法）
    template<typename T>
    static auto func2(Node<T>* L,T& preValue) ->bool {
        if (L==nullptr) return true;
        std::stack<Node<T>> s;
        s.push(*L);
        while (L->left!=nullptr) {
            s.push(*L->left);
            L = L->left;
        }
        while (!s.empty()) {
            Node<T> tmp = s.top();
            s.pop();
            if (tmp.data<=preValue) {
                return false;
            }else {
                preValue = tmp.data;
            }
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

    //法三：利用数形DP的常规解法（动态规划）
    template<typename T>
    static auto func3(Node<T>* L) ->bool {
        MSG<int>MSG = process<int>(L);
        return MSG.isBST;
    }

    template<typename T>
    struct MSG{
        //TODO 如果T不再是int,请实现该模板
    };

    template<>
    struct MSG<int> {
        bool isBST = false; //是否该侧为DST
        int max = INT32_MIN;
        int min = INT32_MAX;
        MSG() = default;
        MSG(bool data,int min,int max):isBST(data),max(max),min(min) { }
    };

    template<typename T>
    static auto process(Node<T>* L) ->MSG<T> {
        //TODO 如果T不再是int,请实现该模板
    }

    template<>
    static auto process(Node<int>* L) ->MSG<int> {
        if (L==nullptr) return MSG<int>(true,INT32_MAX,INT32_MIN);
        MSG<int> leftMsg,rightMsg;
        leftMsg = process(L->left);
        rightMsg = process(L->right);
        int min = std::min(std::min(L->data,leftMsg.min),rightMsg.min);
        int max = std::max(std::max(L->data,leftMsg.max),rightMsg.max);
        bool isBST = true;
        if (!leftMsg.isBST || leftMsg.max>=L->data) isBST = false;
        if (!rightMsg.isBST || rightMsg.min<L->data) isBST = false;
        return MSG<int>(isBST,min,max);
    }

};

template<typename T>
auto print(Node<T>& L,std::function<bool(Node<T>*)> func) {
    bool isBST = func(&L);
    if (isBST) {std::cout<<"The tree is a binary search tree.\n";return;}
    std::cout<<"The tree is not a binary search tree!\n";
}


int main(int argc,char* argv[]) {
    //生成一个搜索二叉树
    Node<int> a,b,c,d,e,f,g,h,i,j,k;
    a.data = 6; a.left = &b; a.right = &c;
    b.data = 3; b.left = &d; b.right = &e;
    c.data = 9; c.left = &f; c.right = &g;
    d.data = 1;              d.right = &h;
    e.data = 4;              e.right = &i;
    f.data = 7;              f.right = &j;
    g.data = 10;             g.right = &k;
    h.data = 2;
    i.data = 5;
    j.data = 8;
    k.data = 11;
    //法一
    std::cout<<"法一判断:\n";
    int preValue = INT32_MIN;
    std::function<bool(Node<int>* L)> func = std::bind(&CheckBST::func1<int>,
    std::placeholders::_1,std::ref(preValue));//
    print(a,func);
    //法二
    std::cout<<"法二判断:\n";
    preValue = INT32_MIN;
    func = std::bind(&CheckBST::func2<int>,
    std::placeholders::_1,std::ref(preValue));
    print(a,func);
    //法三
    std::cout<<"法三判断:\n";
    func = std::bind(&CheckBST::func3<int>,
    std::placeholders::_1);
    print(a,func);
    return 0;
}