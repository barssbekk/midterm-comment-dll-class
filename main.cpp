#include <iostream> // for cout and endl
using namespace std; // avoids writing std:: for simplicity

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
            temp->prev->next = temp->next; // link previous node to next node
        else
            head = temp->next; // if temp first node, update head to next node

        if (temp->next) // if temp is not the last node
            temp->next->prev = temp->prev; // link next node back to previous node
        else
            tail = temp->prev; // update tail

        delete temp; // frees memory
    }

    // deletes node by taking position
    void delete_pos(int pos) {
        if (!head) { // check if list is empty
            cout << "List is empty." << endl; // if so, prints this
            return; // exit
        }

        if (pos == 1) { // if first node
            pop_front(); // remove front
            return; // exit
        }

        Node* temp = head; // start from head

        for (int i = 1; i < pos; i++){ // repeats until reaching position
            if (!temp) { // checks if temp is empty
                cout << "Position doesn't exist." << endl; // prints it
                return; // exit
            }
            else
                temp = temp->next; // updates temp to next node
        }
        if (!temp) { // check if temp is last node
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next) { // checks if temp is last node
            pop_back(); // deletes the last node
            return;
        }

        Node* tempPrev = temp->prev; // store previous node
        tempPrev->next = temp->next; // previous skip temp
        temp->next->prev = tempPrev; // next skip temp
        delete temp; // delete node
    }

    void push_back(int v) { // add to the end
        Node* newNode = new Node(v); // create a new node
        if (!tail) // if list is empty
            head = tail = newNode; // first node
        else {
            tail->next = newNode; // old tail points forward
            newNode->prev = tail; // new node points bak
            tail = newNode; // update tail
        }
    }

    void push_front(int v) { // add to the front
        Node* newNode = new Node(v); // create a new node
        if (!head) // if list is empty
            head = tail = newNode; // makes newNode first node
        else {
            newNode->next = head; // new node points to old head
            head->prev = newNode; // old head points back
            head = newNode; // update head
        }
    }

    void pop_front() { // deletes first node

        if (!head) { // if empty
            cout << "List is empty." << endl; // print it
            return; // exit
        }

        Node * temp = head; // stores first node

        if (head->next) { // if more than one node
            head = head->next; // move head to the next
            head->prev = nullptr; // remove back
        }
        else
            head = tail = nullptr; // list becomes empty
        delete temp; // delete old head
    }

    void pop_back() { // remove last node
        if (!tail) { // if empty
            cout << "List is empty." << endl; // print it
            return; // exit
        }
        Node * temp = tail; // store last node

        if (tail->prev) { // if more than one
            tail = tail->prev; // move tail back
            tail->next = nullptr; // remove next
        }
        else
            head = tail = nullptr; // list becomes empty
        delete temp; // deletes old tail
    }

    ~DoublyLinkedList() { // destructor that runs everytime when the program is finished
        while (head) {  // while list is empty
            Node* temp = head; // stores current node
            head = head->next; // move forward
            delete temp; // delete node
        }
    }
    // print our nodes "forward"
    void print() {
        Node* current = head; // starts at head
        if (!current) { // if empty
            cout << "List is empty." << endl; // prints it
            return; // exit
        }
        while (current) { // loop through list
            cout << current->data << " "; // print its value
            current = current->next; // move to the next
        }
        cout << endl; // new line like '\n'
    }

    // print backword
    void print_reverse() {
        Node* current = tail; // start at tail
        if (!current) { // if empty
            cout << "List is empty." << endl; // prints it
            return; // exit
        }
        while (current) { // loop backward
            cout << current->data << " "; // prints its value
            current = current->prev; // move backword
        }
        cout << endl; // new line
    }

    void every_other_element() {
        Node* current = head;

        if (!current) {
            cout << "List is empty'\n";
            return;
        }

        while (current) {
            cout << current->data << " ";
        }
    }
};


int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    DoublyLinkedList myList{};
    myList.push_back(1);
    myList.push_back(3);
    myList.push_back(2);
    myList.push_back(5);
    myList.push_back(2);
    myList.every_other_element();
    return 0;
}
