#include <iostream>
using namespace std;
class Node {
private:
    int data;
    Node* next;
public:
    Node(int value) : data(value), next(nullptr) {}

    void setNext(Node* n) { next = n; }
    Node* getNext() const { return next; }
    int getData() const { return data; }
};

class Stack {
private:
    Node* topNode;
public:
    Stack() : topNode(nullptr) {}

    bool empty() const {
        return topNode == nullptr;
    }

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->setNext(topNode);
        topNode = newNode;
        cout << value << " pushed onto stack"<<endl;
    }

    void pop() {
        if (empty()) {
            cout << "Stack Underflow"<<endl;
            return;
        }
        Node* temp = topNode;
        cout << topNode->getData() << " is popped"<<endl;
        topNode = topNode->getNext();
        delete temp;
    }

    int top() const {
        if (empty()) {
            cout << "Stack is empty"<<endl;
            return -1;
        }
        return topNode->getData();
    }

    void display() const {
        if (empty()) {
            cout << "Stack is empty"<<Endl;
            return;
        }
        cout << "Stack  ";
        Node* temp = topNode;
        while (temp != nullptr) {
            cout << temp->getData() << "  ";
            temp = temp->getNext();
        }
        cout << endl;
    }

    ~Stack() {
        while (!empty()) {
            pop();
        }
    }
};
int main() {
    Stack s;
    s.push(10);
    s.push(20);
    s.push(30);
    s.display();
    cout << "Top element " << s.top() << endl;
    s.pop();
    s.display();
    cout << "Top elementafter popping " << s.top() << endl;
    return 0;
}

