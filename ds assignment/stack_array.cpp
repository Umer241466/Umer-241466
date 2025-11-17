#include <iostream>
using namespace std;
class Stack {
private:
    int* arr;
    int topIndex;
    int capacity;

public:
    Stack(int size = 5) {
        capacity = size;
        arr = new int[capacity];
        topIndex = -1;
    }
    bool empty() const {
        return topIndex == -1;
    }
    bool full() const {
        return topIndex == capacity - 1;
    }
    void push(int value) {
        if (full()) {
            cout << "OVer flow is happening " << value << endl;
            return;
        }
        arr[++topIndex] = value;
        cout << value << " pushed on stack"<<endl;
    }
    void pop() {
        if (empty()) {
            cout << " Underflow! "<<endl;
            return;
        }
        cout << arr[topIndex--] << " popped from stack"<<endl;
    }
    int top() const {
        if (empty()) {
            cout << "Stack is empt"<<endl;
            return -1;
        }
        return arr[topIndex];
    }
    void display() const {
        if (empty()) {
            cout << "Stack is empty"<<endl;
            return;
        }
        cout << "Stack: ";
        for (int i = topIndex; i >= 0; --i)
            cout << arr[i] << " ";
        cout << endl;
    }
    ~Stack() {
        delete[] arr;
    }
};
int main() {
    Stack s(5);
    s.push(10);
    s.push(20);
    s.push(30);
    s.display();
    cout << "Top of stack  " << s.top() << endl;
    s.pop();
    s.display();
    cout << "Top of stack after popping " << s.top() << endl;
    return 0;
}

