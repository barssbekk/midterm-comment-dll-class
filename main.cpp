#include <iostream>
using namespace std;

// constants, so we don't have to write everytime, prevent accidental changes, and avoid magic numbers
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    // each element in the Linkedlist is NODE
    // private members and accessible inside the class
    struct Node {
        // public members of struct Node, since struct by default is a public
        int data; // stores the value of the node, int type
        Node* prev; // pointer to previous node
        Node* next; // pointer to the next node

        // Constructor with default parameters, if the user doesn't provide p and n,
        // then the constructor will assign them to "nullptr" which is default
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; // assigns user provided value to node member "data"
            prev = p; // assigns user provided previous pointer to node member "prev"
            next = n; // assigns user provided next pointer to node member "next"
        }
    };

    Node* head; // private member pointer to first node which is first element
    Node* tail; // private member pointer to last node which is last element

public:
    // Default constructor of the class
    // where head and tail point to null (empty list)
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    // insert after a given position where 0 is start
    void insert_after(int value, int position) { // takes two parameters, so user has to provide them
        if (position < 0) { // checks if position is invalid
            cout << "Position must be >= 0." << endl; // if so, prints error message
            return; // return or "exit" the function
        }

        Node* newNode = new Node(value); // creates a new node dynamically and stores its address in "newNode"
        if (!head) { // checks if the list is empty, it's the same as head == nullptr
            // new node becomes both head and tail, because the list is empty,
            // and we only have one node in the list
            head = tail = newNode;
            return; // exit the function
        }

        Node* temp = head; // create a pointer temp that starts at head
        for (int i = 0; i < position && temp; ++i) // loop to move temp up to the given position
            temp = temp->next; // move temp to next node using next pointer

        if (!temp) { // if temp points to nothing then position is out of the list
            cout << "Position exceeds list size. Node not inserted.\n"; // if condition true, prints error
            delete newNode; // frees memory to avoid memory leak
            return; // exit
        }

        newNode->next = temp->next; // new node points to the node after temp
        newNode->prev = temp; // new node points to back (previous) to temp
        if (temp->next) // if temp is not the last node
            temp->next->prev = newNode; // update the next  node to point back to new node
        else
            tail = newNode; // if inserting at end, update tail to new node
        temp->next = newNode; // updates temp to point to new node
    }

    // deletes the first node that contains the given value
    void delete_val(int value) {
        if (!head) return; // if list is empty, nothing to delete, exit

        Node* temp = head; // starts from head and stores address of first node

        while (temp && temp->data != value) // traverse list until value is found or end when it is reached
            temp = temp->next; // move forward by using next pointer

        if (!temp) return; // if value not found (points to nothing), exit function

        if (temp->prev) // if temp is not the first node
            temp->prev->next = temp->next; 
        else
            head = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1) {
            pop_front();
            return;
        }

        Node* temp = head;

        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next) {
            pop_back();
            return;
        }

        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning


    return 0;
}
