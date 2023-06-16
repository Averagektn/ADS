#include <iostream>
#include <set>

using namespace std;

struct stack{
    char value;
    int ind;
    stack *next;
};

stack *push(stack *p, char symbol, int index){
    auto *tmp = new stack;
    tmp->next = p;
    tmp->value = symbol;
    tmp->ind = index;
    return tmp;
}

char pop(stack **p){
    char tmp = (*p)->value;
    *p = (*p)->next;
    return tmp;
}

bool isEmpty(stack *head){
    return head == nullptr;
}

void check(string src, stack *ptr){
    set<char> pars_open = {'(', '[', '{'}, pars_close = {')', ']', '}'};
    char curr;

    for (int i = 0 ; i < src.length(); i++){
        if (pars_open.find(src[i]) != pars_open.end()){
            ptr = push(ptr, src[i], i);
        } else {
            if (pars_close.find(src[i]) != pars_close.end()) {
                if (isEmpty(ptr)) {
                    cout << i + 1;
                    return;
                }
                curr = pop(&ptr);
                if ((curr == '(' && src[i] != ')') || (curr == '[' && src[i] != ']') ||
                    (curr == '{' && src[i] != '}')) {
                    cout << i + 1;
                    return;
                }
            }
        }
    }
    if (isEmpty(ptr)){
        cout << "Success";
    } else {
        cout << ptr->ind + 1;
    }

}

int main() {
    string str;
    stack *head = nullptr;

    cin >> str;

    check(str, head);

    return 0;
}