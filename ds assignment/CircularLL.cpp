#include <iostream>
using namespace std;

class Node {
private:
    int value;
    Node* next_node;
public:
    Node(int v = 0, Node* n = nullptr)
        : value(v), next_node(n) {
    }
    int retrieve() const { return value; }
    Node* next() const { return next_node; }
    void set_next(Node* n) { next_node = n; }

    friend class CircularList;
};
class CircularList {
private:
    Node* list_head;

public:
    CircularList() : list_head(nullptr) {}

    ~CircularList() {
        while (!empty())
            pop_front();
    }
    bool empty() const { return list_head == nullptr; }

    Node* head() const { return list_head; }

    int size() const {
        if (empty()) return 0;

        int count = 0;
        Node* ptr = list_head;

        for (; ; ptr = ptr->next()) {
            ++count;
            if (ptr->next() == list_head)
                break;
        }
        return count;
    }

    int front() const {
        if (empty()) {
            cout << "List is empty"<<endl;
            return -1;
        }
        return list_head->retrieve();
    }

    int end() const {
        if (empty()) {
            cout << "List is empty"<<endl;
            return -1;
        }

        Node* last = nullptr;
        Node* ptr = list_head;

        for (; ; ptr = ptr->next()) {
            last = ptr;
            if (ptr->next() == list_head)
                break;
        }

        return last->retrieve();
    }

    int count(int n) const {
        if (empty()) return 0;

        int c = 0;
        Node* ptr = list_head;

        for (; ; ptr = ptr->next()) {
            if (ptr->retrieve() == n)
                ++c;

            if (ptr->next() == list_head)
                break;
        }
        return c;
    }
    void push_front(int n) {
        Node* newnode = new Node(n);

        if (empty()) {
            newnode->set_next(newnode);
            list_head = newnode;
            return;
        }

        Node* last = nullptr;
        Node* ptr = list_head;

        for (; ; ptr = ptr->next()) {
            last = ptr;
            if (ptr->next() == list_head)
                break;
        }
        newnode->set_next(list_head);
        last->set_next(newnode);
        list_head = newnode;
    }

    void push_end(int n) {
        Node* newnode = new Node(n);

        if (empty()) {
            newnode->set_next(newnode);
            list_head = newnode;
            return;
        }

        Node* last = nullptr;
        Node* ptr = list_head;

        for (; ; ptr = ptr->next()) {
            last = ptr;
            if (ptr->next() == list_head)
                break;
        }

        last->set_next(newnode);
        newnode->set_next(list_head);
    }

    int pop_front() {
        if (empty()) {
            cout << "List is empty"<<endl;
            return -1;
        }

        int val = list_head->retrieve();

        if (list_head->next() == list_head) { 
            delete list_head;
            list_head = nullptr;
            return val;
        }

        Node* last = nullptr;
        Node* ptr = list_head;

        for (; ; ptr = ptr->next()) {
            last = ptr;
            if (ptr->next() == list_head)
                break;
        }

        Node* temp = list_head;
        list_head = list_head->next();
        last->set_next(list_head);
        delete temp;

        return val;
    }

    int pop_end() {
        if (empty()) {
            cout << "List is empty"<<endl;
            return -1;
        }

        if (list_head->next() == list_head) { 
            int val = list_head->retrieve();
            delete list_head;
            list_head = nullptr;
            return val;
        }

        Node* prev = nullptr;
        Node* curr = list_head;

        for (; curr->next() != list_head; curr = curr->next())
            prev = curr;

        int val = curr->retrieve();
        prev->set_next(list_head);
        delete curr;
        return val;
    }

    int erase(int n) {
        if (empty()) return 0;
        int removed = 0;
        while (!empty() && list_head->retrieve() == n) {
            pop_front();
            ++removed;
        }

        if (empty()) return removed;

        Node* curr = list_head;

        for (; curr->next() != list_head; ) {
            if (curr->next()->retrieve() == n) {
                Node* temp = curr->next();
                curr->set_next(temp->next());
                delete temp;
                ++removed;
            }
            else {
                curr = curr->next();
            }
        }

        return removed;
    }
    void display() const {
        if (empty()) {
            cout << "List is empty"<<endl;
            return;
        }

        cout << "Circular List: ";

        Node* ptr = list_head;
        for (; ; ptr = ptr->next()) {
            cout << ptr->retrieve() << " -> ";
            if (ptr->next() == list_head)
                break;
        }

        cout << "(head)\n";
    }
};

int main() {
    CircularList cl;

    cout << "Push front "<< endl;
    cl.push_front(30);
    cl.push_front(20);
    cl.push_front(10);
    cl.display();

    cout << "Push end" << endl;
    cl.push_end(40);
    cl.push_end(50);
    cl.display();

    cout << "Front: " << cl.front() << endl;
    cout << "End: " << cl.end() << endl;
    cout << "Size: " << cl.size() << endl;

    cout << "Counting 20 " << cl.count(20) << endl;

    cout << "Pop front " << cl.pop_front() << endl;
    cout << "Pop end " << cl.pop_end() << endl;
    cl.display();

    cout << "Erase 20 " << cl.erase(20) << endl;
    cl.display();
    return 0;

}
