#pragma once

#include <iostream>

using namespace std;

template<class Item>
struct Node {
    Item item;
    Node* next;
    Node(Item item, Node* next) :item(item), next(next) {}
};

template<class Item>
class SingleLinkedList {

    Node<Item>* head, * tail;
    int length;

public:
    SingleLinkedList() :head(nullptr), tail(nullptr), length(0) {}

    //~SingleLinkedList() {
    //    Node<Item>* curr = head;
    //    while (curr != nullptr) {
    //        Node<Item>* next = curr->next;
    //        delete curr;
    //        curr = next;
    //    }
    //}

    Node<Item>* getHead() {
    return head;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    void addLast(Item item) {
        if (isEmpty())
            tail = head = new Node<Item>(item, nullptr);
        else
            tail = tail->next = new Node<Item>(item, nullptr);

        ++length;
    }

    void addFirst(Item item) {
        if (isEmpty())
            tail = head = new Node<Item>(item, nullptr);
        else
            head = new Node<Item>(item, head);

        ++length;
    }

    bool removeFirst() {

        if (isEmpty())
            return false;

        Node<Item>* temp = head;
        head = head->next;
        delete temp;
        --length;
        return true;
    }

   Item *removeFirstWithReturnItem() {

        if (isEmpty())
            return nullptr;
        Item *item=&head->item;
        head = head->next;
        --length;
        return item;
    }

    void print() {
        Node<Item>* curr = head;

        while (curr != nullptr)
        {
            cout << curr->item << endl;
            cout << "--------------------\n";
            curr = curr->next;
        }

    }

    template<class Variable>
    Item* find(Variable variable) {
        if (isEmpty())
            return nullptr;
        Node<Item>* curr = head;

        while (curr != nullptr)
        {
            if (curr->item == variable)
                return &curr->item;
            curr = curr->next;
        }
        return nullptr;
    }

    template<class Variable>
    bool remove(Variable variable) {
        if (isEmpty()) {
            return false;
        }

        if (head->item == variable)
            return removeFirst();

        Node<Item>* prev = head;
        Node<Item>* curr = head->next;

        while (curr != nullptr) {
            if (curr->item == variable) {
                prev->next = curr->next;

                if (curr == tail)
                    tail = prev;
                delete curr;
                length--;
                return true;
            }

            prev = curr;
            curr = curr->next;
        }

        return false;
    }

    int size() {
        return length;
    }
};

template<class Item>
class Queue {

    SingleLinkedList<Item> singleLinkedList;

public:

    void enqueue(Item item) {
        singleLinkedList.addLast(item);
    }

    Item* dequeue() {
        return singleLinkedList.removeFirstWithReturnItem();
    }

    void push(Item item) {
        singleLinkedList.addFirst(item);
    }

    bool isEmpty() {
        return singleLinkedList.isEmpty();
    }

    int size() {
        return singleLinkedList.size();
    }
};

template<class Item>
class Stack {

    SingleLinkedList<Item> singleLinkedList;

public:

    void push(Item item) {
        singleLinkedList.addFirst(item);
    }

    Item* pop() {
        return singleLinkedList.removeFirstWithReturnItem();
    }

    bool isEmpty() {
        return singleLinkedList.isEmpty();
    }

    int size() {
        return singleLinkedList.size();
    }

    void toQueue(Queue<Item> &q){
    while(!isEmpty())
        q.enqueue(pop());
    }

};

template<class Item>
struct DoubleNode {
    Item item;
    DoubleNode* next;
    DoubleNode* previous;

    DoubleNode(Item item, DoubleNode* next, DoubleNode* previous) :
        item(item), next(next), previous(previous) {
    }
};

template<class Item>
class DoubleLinkedList {
private:

    DoubleNode<Item>* head;
    DoubleNode<Item>* tail;
    int length;

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr), length(0) {}

    ~DoubleLinkedList() {
        DoubleNode<Item>* curr = head;
        while (curr != nullptr) {
            DoubleNode<Item>* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    bool isEmpty() {
        return head == nullptr;
    }

    int size() {
        return length;
    }

    DoubleNode<Item>* getHead(){
          return head;
    }

    bool isBigger(int i1,int i2){

    DoubleNode<Item> *curr=head;
    while(curr!=nullptr)
    {
    if(curr->item==i1)
        return false;
    if(curr->item==i2)
        return true;
    curr=curr->next;
    }

    return false;
    }

    void addFirst(Item item) {
        if (isEmpty())
            head = tail = new DoubleNode<Item>(item, nullptr, nullptr);
        else
            head = head->previous = new DoubleNode<Item>(item, head, nullptr);

        length++;
    }

    void addLast(Item item) {
        if (isEmpty())
            head = tail = new DoubleNode<Item>(item, nullptr, nullptr);
        else
            tail = tail->next = new DoubleNode<Item>(item, nullptr, tail);

        length++;
    }

    void add(int index, Item item) {
        if (index < 0 || index > length) {
            throw out_of_range("Index out of bounds");
        }

        if (index == 0) {
            addFirst(item);
            return;
        }

        if (index == length) {
            addLast(item);
            return;
        }

        DoubleNode<Item>* curr = head;
        for (int i = 0; i < index - 1; i++) {
            curr = curr->next;
        }

        DoubleNode<Item>* newNode = new DoubleNode<Item>(item, curr->next, curr);
        curr->next->previous = newNode;
        curr->next = newNode;
        length++;
    }

    Item* operator[](int index) {
        if (index < 0 || index >= length) {
            throw out_of_range("Index out of bounds");
        }

        DoubleNode<Item>* curr = head;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }

        return &curr->item;
    }

    template<class Variable>
    bool remove(Variable variable) {
        if (isEmpty()) {
            return false;
        }

        if (head->item == variable) { // Error Here binary '==': 'Item' does not define this operator or a conversion to a type acceptable to the predefined operator
            DoubleNode<Item>* temp = head;
            head = head->next;

            if (head != nullptr)
                head->previous = nullptr;
            else
                tail = nullptr;

            delete temp;
            length--;
            return true;
        }

        DoubleNode<Item>* curr = head;

        while (curr != nullptr) {
            if (curr->item == variable) { //Error Here binary '==': 'Item' does not define this operator or a conversion to a type acceptable to the predefined operator
                curr->previous->next = curr->next;

                if (curr->next != nullptr)
                    curr->next->previous = curr->previous;
                else
                    tail = curr->previous;

                delete curr;
                length--;
                return true;
            }
            curr = curr->next;
        }

        return false;
    }

    void print() {
        DoubleNode<Item>* curr = head;
        while (curr != nullptr) {
            cout << curr->item << '\n';
            cout << "---------------------\n";
            curr = curr->next;
        }
        cout << endl;
    }

    template<class Variable>
    Item* find(Variable variable) {
        if (isEmpty())
            return nullptr;
        DoubleNode<Item>* curr = head;
        while (curr != nullptr)
        {
            if (curr->item == variable)
                return &curr->item;
            curr = curr->next;
        }
        return nullptr;
    }
};

template<class Key, class Item>
struct HashNode {
    Key key;
    Item item;

    HashNode(Key key, Item item) :key(key), item(item) {}

    bool operator==(Key key) {
        return this->key == key;
    }

};

template<class Key, class Item>
class OpenHash {

    int capacity, length;
    SingleLinkedList<HashNode<Key, Item>>* array;

    int hashCode(int key) {
        return key % capacity;
    }

    int hashCode(string key) {
        int count = 0;

        for (char c : key)
            count += c;

        return count % capacity;
    }


public:
    OpenHash(int capacity = 20) :capacity(capacity), length(0) { array = new SingleLinkedList<HashNode<Key, Item>>[capacity]; }
  /*  ~OpenHash() { delete[] array; }*/

    void insert(Key key, Item item) {
        int index = hashCode(key);
        array[index].addLast(HashNode<Key, Item>(key, item));
        length++;
    }

    void print() {
        for (int i = 0;i < size;i++)
            if (!array[i].isEmpty())
                array[i].print();
    }


    Item* operator[](Key key) {
        int index = hashCode(key);
        HashNode<Key, Item>* node = array[index].find(key);
        if (node == nullptr)
            return nullptr;
        return &node->item;
    }


    bool remove(Key key) {
        int index = hashCode(key);
        bool result = array[index].remove(key);
        if (result)
            length--;
        return result;
    }

    Node <HashNode<Key,Item>>* getHead(int index){
        if (&array[index] == nullptr)
            return nullptr;
         return array[index].getHead();
    }

    int size() {
        return length;
    }

    bool isEmpty() {
        return length == 0;
    }

    int getCapicty()
    {
        return capacity;
    }


};


//Making Closed Hashing DataStructure


template <typename Key, typename Item>
struct ClosedNode :public HashNode<Key, Item>
{

    enum enNodeType { EMPTY = 0, DELETED, FULL };

    enNodeType nodeType;

    ClosedNode(Key key, Item item) : HashNode<Key, Item>(key, item), nodeType(FULL) {}
    ClosedNode() : HashNode<Key, Item>(Key(), Item()), nodeType(EMPTY) {}
};



template <typename Key, typename Item>
class ClosedHash
{
    int length, capacity;
    ClosedNode<Key, Item>* array;

    int hashCode(int key) {
        return key % capacity;
    }

    int hashCode(string key) {
        int count = 0;

        for (char c : key)
            count += c;

        return count % capacity;
    }

    void resize(int newCapacity) {
        ClosedNode<Key, Item>* newArray = new ClosedNode<Key, Item>[newCapacity];

        for (int i = 0; i < capacity;i++) {
            if (array[i].nodeType == ClosedNode<Key, Item>::FULL) {
                int newIndex = hashCode(array[i].key);

                while (newArray[newIndex].nodeType == ClosedNode<Key, Item>::FULL)
                    newIndex = (newIndex + 1) % newCapacity;


                newArray[newIndex] = array[i];
            }
        }

        delete[] array;
        array = newArray;
        capacity = newCapacity;
    }


public:

    int size()
    {
        return length;
    }

    bool isFull() {
        return (length / capacity) == 1;
    }

    ClosedHash(int capacity = 20) :capacity(capacity)
    {
        array = new ClosedNode<Key, Item>[capacity];
    }

    //~ClosedHash()
    //{
    //    delete[]array;
    //}

    void insert(Key key, Item item)
    {
        if (isFull())
            resize(2 * capacity);

        int index = hashCode(key);
        int originalIndex = index;

        do {
            if (array[index].nodeType != ClosedNode<Key, Item>::FULL) {
                array[index] = ClosedNode<Key, Item>(key, item);
                length++;
                return;
            }

            index = (index + 1) % capacity;
        } while (index != originalIndex);
    }


    Item* operator[](Key key) {

        int index = hashCode(key);
        int originalIndex = index;

        do {
            if (array[index].nodeType == ClosedNode<Key, Item>::EMPTY) {
                return nullptr;
            }

            if (array[index].nodeType == ClosedNode<Key, Item>::FULL && array[index].key == key) {
                return &array[index].item;
            }

            index = (index + 1) % capacity;
        } while (index != originalIndex);

        return nullptr;
    }



    Item *getNode(int index){
        if (array[index].nodeType == ClosedNode <Key, Item>::EMPTY)
            return nullptr;
         return &array[index].item;
    }

    bool remove(Key key) {

        int index = hashCode(key);
        int originalIndex = index;

        do {
            if (array[index].nodeType == ClosedNode<Key, Item>::EMPTY) {
                return false;
            }

            if (array[index].nodeType == ClosedNode<Key, Item>::FULL && array[index].key == key) {
                array[index].nodeType = ClosedNode<Key, Item>::DELETED;
                length--;
                return true;
            }

            index = (index + 1) % capacity;
        } while (index != originalIndex);

        return false;
    }

};


