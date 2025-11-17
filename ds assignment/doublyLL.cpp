#include <iostream>
using namespace std;
class Node {
private:
    int value;
    Node* next_node;
    Node* prev_node;

public:
    Node(int v = 0, Node* next = nullptr, Node* prev = nullptr)
        : value(v), next_node(next), prev_node(prev) {
    }
    int retrieve() const { return value; }
    Node* next() const { return next_node; }
    Node* previous() const { return prev_node; }
    void set_next(Node* n) { next_node = n; }
    void set_previous(Node* p) { prev_node = p; }

    friend class DoublyList;
};
class DoublyList {
private:
    Node* list_head;

public:
    DoublyList() : list_head(nullptr) {}
    ~DoublyList() {
        for (; !empty(); )
            pop_front();
    }
    bool empty() const { return list_head == nullptr; }

    Node* head() const { return list_head; }

    int size() const {
        int count = 0;
        for (Node* ptr = list_head; ptr != nullptr; ptr = ptr->next())
            ++count;
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

        int val = -1;
        for (Node* ptr = list_head; ptr != nullptr; ptr = ptr->next())
            val = ptr->retrieve();

        return val;
    }

    int count(int n) const {
        int c = 0;
        for (Node* ptr = list_head; ptr != nullptr; ptr = ptr->next())
            if (ptr->retrieve() == n)
                ++c;
        return c;
    }
    void push_front(int n) {
        Node* newnode = new Node(n, list_head, nullptr);
        if (list_head != nullptr)
            list_head->set_previous(newnode);
        list_head = newnode;
    }

    void push_end(int n) {
        Node* newnode = new Node(n, nullptr, nullptr);

        if (empty()) {
            list_head = newnode;
            return;
        }

        Node* last = nullptr;
        for (Node* ptr = list_head; ptr != nullptr; ptr = ptr->next())
            last = ptr;

        newnode->set_previous(last);
        last->set_next(newnode);
    }

    int pop_front() {
        if (empty()) {
            cout << "List is empty"<<endl;
            return -1;
        }

        int val = list_head->retrieve();
        Node* temp = list_head;
        list_head = list_head->next();

        if (list_head != nullptr)
            list_head->set_previous(nullptr);

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

        Node* ptr = list_head;
        for (; ptr->next() != nullptr; ptr = ptr->next());

        int val = ptr->retrieve();
        ptr->previous()->set_next(nullptr);
        delete ptr;
        return val;
    }

    int erase(int n) {
        if (empty()) return 0;

        int removed = 0;
        while (list_head != nullptr && list_head->retrieve() == n) {
            Node* temp = list_head;
            list_head = list_head->next();
            if (list_head != nullptr)
                list_head->set_previous(nullptr);
            delete temp;
            removed++;
        }

        if (empty()) return removed;
        for (Node* curr = list_head; curr != nullptr; curr = curr->next()) {
            if (curr->next() != nullptr && curr->next()->retrieve() == n) {
                Node* temp = curr->next();
                curr->set_next(temp->next());
                if (temp->next() != nullptr)
                    temp->next()->set_previous(curr);
                delete temp;
                removed++;
            }
        }

        return removed;
    }
    void display() const {
        cout << "List: ";
        for (Node* ptr = list_head; ptr != nullptr; ptr = ptr->next())
            cout << ptr->retrieve() << " <-> ";
        cout << "NULL\n";
    }
};
int main() {
    DoublyList list;

    cout << "Push front"<<endl;
    list.push_front(30);
    list.push_front(20);
    list.push_front(10);
    list.display();
    cout << "Push end"<<endl;
    list.push_end(40);
    list.display();

    cout << "Front " << list.front() << endl;
    cout << "End " << list.end() << endl;
    cout << "Size " << list.size() << endl;

    cout << "Counting 20: " << list.count(20) << endl;

    cout << "Pop front " << list.pop_front() << endl;
    cout << "Pop end " << list.pop_end() << endl;
    list.display();
    cout << "Erase 20 " << list.erase(20) << endl;
    list.display();
    return 0;
}

