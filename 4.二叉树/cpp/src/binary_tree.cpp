#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>
//�������ı�������
//1.�ݹ鷨
// (1) ��-��-�� ǰ�����
// (2) ��-��-�� �������
// (3) ��-��-�� �������
//2.�������

/// �������ڵ�
/// @tparam T ��������������
template<class T>
struct Node {
    T data;
    Node* left;
    Node* right;
};

/// �������ĵݹ����
/// @tparam T ��������
/// @param L �ڵ�ָ��
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

//�ݹ鷨:ǰ�����
template<typename T>
auto func_forward(Node<T>* L) {
    if (L==nullptr) {
        return;
    }
    std::cout<<L->data<<" ";

    func_forward(L->left);

    func_forward(L->right);

}

//�ݹ�:�������
template<typename T>
auto func_middle(Node<T>* L) {
    if (L==nullptr) {
        return;
    }
    func_middle(L->left);
    std::cout<<L->data<<" ";
    func_middle(L->right);
}

//�ݹ�:�������
template<typename T>
auto func_back(Node<T>* L) {
    if (L==nullptr) {
        return;
    }
    func_back(L->left);

    func_back(L->right);
    std::cout<<L->data<<" ";
}

//����:������� ��-��-��
template<typename T>
auto forward(Node<T>* L) {
    //1.������ѹ��ջ
    //2.���ڵ㵯��ջ,������
    //3.���ڵ����-��ڵ�����ѹ��ջ
    //4.ִ��2ֱ��ջ��
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

//����:������� ��-��-��
template<typename T>
auto middle(Node<T>* L) {
    //1.����߽�ȫ��ѹ��ջ
    //2.�����ڵ�Ԫ�أ����ж�
    //    (1) ���ҽڵ�
    //         ѹ���ҽڵ��ȫ����߽�
    //    (2) ���ҽڵ�
    //         ����ִ��2��ֱ��ջ��
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

//����:������� ��-��-��
template<typename T>
auto back(Node<T>* L) {
    //1.������ѹ��ջs1
    //2.���ڵ㵯��ջ,������ջs2
    //3.���ڵ����-�ҽڵ�����ѹ��ջ
    //4.ִ��2ֱ��ջs1��
    //5.��s2���������Ό�ջ
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

//�������Ĳ������
template<typename T>
auto sequence(Node<T>* L) {
    //1.�����ڵ��������
    //2.ȡ���ڵ�
    //3.�жϽڵ��Ƿ���������ӽڵ�
    //     (1) ��ڵ���� ����ڵ����
    //     (2) �ҽڵ���� ���ҽڵ����
    //4.�ظ���2����ֱ���ӿ�
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

//���������Ŀ��
//hash���¼�Զ�������ʱ����¼�����Զ������͵ĵ�ַ
template<typename T>
auto max_length(Node<T>* L) -> int {
    if (L == nullptr) return -1;
    std::unordered_map<Node<T>*, int> map; // hash���¼�ڵ�ָ��-����
    int curLevel = 1; // ��ǰ��,��ʼΪ��һ��
    int max = 0; // �����
    int curLevelNodes = 0; // ��ǰ���ۼƽڵ���
    std::queue<Node<T>*> q; // ��������������
    // ��ʼ���������ڵ���ӵ����к͹�ϣ��
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
    max = std::max(max, curLevelNodes); // ���������һ��
    return max;
}

int main(int argc,char* argv[]) {
    //����������
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
    std::cout<<"�������ĵݹ����:";
    func<int>(&_1);
    std::cout<<"\n"<<"��������ǰ�����(�ݹ�):";
    func_forward(&_1);
    std::cout<<"\n"<<"���������������(�ݹ�):";
    func_middle(&_1);
    std::cout<<"\n"<<"�������ĺ������(�ݹ�):";
    func_back(&_1);
    std::cout<<"\n"<<"���������������(����):";
    forward(&_1);
    std::cout<<"\n"<<"���������������(����):";
    middle(&_1);
    std::cout<<"\n"<<"�������ĺ������(����):";
    back(&_1);
    std::cout<<"\n"<<"�������Ĳ������:";
    sequence(&_1);
    std::cout<<"\n"<<"�������Ŀ��Ϊ:"<<max_length(&_1);
    return 0;
}
