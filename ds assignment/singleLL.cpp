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
    friend class List;
};
class List {
private:
    Node* list_head;

public:
    List() : list_head(nullptr) {}
    ~List() {
        while (!empty()) pop_front();
    }
    bool empty() const { return list_head == nullptr; }

    int size() const {
        int count = 0;
        for (Node* ptr = head(); ptr != nullptr; ptr = ptr->next())
            ++count;
        return count;
    }

    Node* head() const { return list_head; }

    int front() const {
        if (empty()) {
            cout << "List is empty"<<endl;
            return -1;
        }
        return head()->retrieve();
    }

    int end() const {
        if (empty()) {
            cout << "List is empty"<<endl;
            return -1;
        }
        Node* ptr = head();
        while (ptr->next() != nullptr)
            ptr = ptr->next();
        return ptr->retrieve();
    }

    int count(int n) const {
        int node_count = 0;
        for (Node* ptr = head(); ptr != nullptr; ptr = ptr->next())
            if (ptr->retrieve() == n)
                ++node_count;
        return node_count;
    }
    void push_front(int n) {
        Node* newnode = new Node(n, list_head);
        list_head = newnode;
    }

    void push_end(int n) {
        Node* newnode = new Node(n, nullptr);
        if (empty()) {
            list_head = newnode;
            return;
        }
        Node* ptr = head();
        while (ptr->next() != nullptr)
            ptr = ptr->next();
        ptr->set_next(newnode);
    }

    int pop_front() {
        if (empty()) {
            cout << "List is empty"<<endl;
            return -1;
        }
        int val = list_head->retrieve();
        Node* temp = list_head;
        list_head = list_head->next();
        delete temp;
        return val;
    }

    int pop_end() {
        if (empty()) {
            cout << "List is empty"<<endl;
            return -1;
        }
        if (list_head->next() == nullptr) {
            int val = list_head->retrieve();
            delete list_head;
            list_head = nullptr;
            return val;
        }

        Node* prev = nullptr;
        Node* curr = head();
        while (curr->next() != nullptr) {
            prev = curr;
            curr = curr->next();
        }

        int val = curr->retrieve();
        delete curr;
        prev->set_next(nullptr);
        return val;
    }

    int erase(int n) {
        if (empty()) return 0;

        int removed = 0;
        while (list_head && list_head->retrieve() == n) {
            Node* temp = list_head;
            list_head = list_head->next();
            delete temp;
            ++removed;
        }
        Node* curr = list_head;
        while (curr && curr->next()) {
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
        for (Node* ptr = head(); ptr != nullptr; ptr = ptr->next())
            cout << ptr->retrieve() << " -> ";
        cout << "Nullptr"<<endl;
    }
};
int main() {
    List list;

    cout << "ppush front:"<<endl;
    list.push_front(30);
    list.push_front(20);
    list.push_front(10);
    list.display();

    cout << "push end:\n";
    list.push_end(40);
    list.push_end(50);
    list.display();

    cout << "front: " << list.front() << endl;
    cout << "end: " << list.end() << endl;
    cout << "size: " << list.size() << endl;

    cout << "Counting 20 " << list.count(20) << endl;
    cout << "Pop front: " << list.pop_front() << endl;
    cout << "Pop end: " << list.pop_end() << endl;
    list.display();
    cout << "Erase 20 " << list.erase(20) << endl;
    list.display();
    return 0;

}
