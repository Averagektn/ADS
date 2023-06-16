#include <iostream>

using namespace std;

struct stack{
    int value, max;
    stack *next;
};

bool isEmpty(stack *head){
    return head == nullptr;
}

stack *push(stack *p, int val){
    auto *tmp = new stack;
    tmp->next = p;
    tmp->value = val;
    if (p == nullptr){
        tmp->max = val;
    } else {
        tmp->max = max(val, p->max);
    }
    return tmp;
}

void pop(stack **p){
    if (!isEmpty(*p)){
        *p = (*p)->next;
    }
}

int findMax(stack *p){
    return p->max;
}

int main() {
    string str;
    stack *head = nullptr;
    int q, v;

    cin >> q;

    for (int i = 0; i < q; i++){
        cin >> str;
        if (str == "push"){
            cin >> v;
            head = push(head, v);
        }
        if (str == "pop"){
            pop(&head);
        }
        if (str == "max"){
            cout << findMax(head) << endl;
        }
    }

    return 0;
}
