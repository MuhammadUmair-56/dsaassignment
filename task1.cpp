#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    int key;
    string value;
    Node* previous;
    Node* next;

    Node(int k, string v)
    {
        key = k;
        value = v;
        previous = NULL;
        next = NULL;
    }
};

class LRUCache
{
private:
    Node* head;
    Node* tail;
    int capacity;
    int size;

    Node* findNode(int key)
    {
        Node* temp = head;
        while (temp != NULL)
        {
            if (temp->key == key)
            {
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }

    void removeNode(Node* node)
    {
        if (node->previous == NULL)
        {
            head = node->next;
        }
        else
        {
            node->previous->next = node->next;
        }

        if (node->next == NULL)
        {
            tail = node->previous;
        }
        else
        {
            node->next->previous = node->previous;
        }
    }

    void addToFront(Node* node)
    {
        node->previous = NULL;
        node->next = head;

        if (head == NULL)
        {
            tail = node;
        }
        else
        {
            head->previous = node;
        }
        head = node;
    }

    void moveNodeToFront(Node* node)
    {
        removeNode(node);
        addToFront(node);
    }

public:
    LRUCache(int cap)
    {
        head = NULL;
        tail = NULL;
        capacity = cap;
        size = 0;
    }

    void put(int key, string value)
    {
        Node* found = findNode(key);

        if (found != NULL)
        {
            found->value = value;
            moveNodeToFront(found);
            cout << "Key already exists. Value updated and moved to front." << endl;
            return;
        }

        if (size == capacity)
        {
            removeLeastRecentlyUsed();
        }

        Node* newNode = new Node(key, value);
        addToFront(newNode);
        size++;
        cout << "Item added to cache." << endl;
    }

    void get(int key)
    {
        Node* found = findNode(key);

        if (found == NULL)
        {
            cout << "Key not found in cache." << endl;
            return;
        }

        moveNodeToFront(found);
        cout << "Value: " << found->value << endl;
    }

    void moveToFront(int key)
    {
        Node* found = findNode(key);

        if (found == NULL)
        {
            cout << "Key not found in cache." << endl;
            return;
        }

        moveNodeToFront(found);
        cout << "Item with key " << key << " moved to front." << endl;
    }

    void removeLeastRecentlyUsed()
    {
        if (tail == NULL)
        {
            cout << "Cache is empty." << endl;
            return;
        }

        Node* oldNode = tail;
        cout << "Removed least recently used item with key " << oldNode->key << endl;
        removeNode(oldNode);
        delete oldNode;
        size--;
    }

    void display()
    {
        if (head == NULL)
        {
            cout << "Cache is empty." << endl;
            return;
        }

        Node* temp = head;
        while (temp != NULL)
        {
            cout << "Key: " << temp->key << "  Value: " << temp->value << endl;
            temp = temp->next;
        }
    }

    void displaySize()
    {
        cout << "Cache size: " << size << " out of " << capacity << endl;
    }
};

int main()
{
    int capacity;
    cout << "Enter cache capacity: ";
    cin >> capacity;

    LRUCache cache(capacity);
    int choice;

    do
    {
        cout << endl;
        cout << "1. Put (key, value)" << endl;
        cout << "2. Get (key)" << endl;
        cout << "3. Move an accessed item to the front" << endl;
        cout << "4. Remove least recently used item" << endl;
        cout << "5. Display cache" << endl;
        cout << "6. Display cache size" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int key;
            string value;
            cout << "Enter key: ";
            cin >> key;
            cin.ignore();
            cout << "Enter value: ";
            getline(cin, value);
            cache.put(key, value);
        }
        else if (choice == 2)
        {
            int key;
            cout << "Enter key: ";
            cin >> key;
            cache.get(key);
        }
        else if (choice == 3)
        {
            int key;
            cout << "Enter key: ";
            cin >> key;
            cache.moveToFront(key);
        }
        else if (choice == 4)
        {
            cache.removeLeastRecentlyUsed();
        }
        else if (choice == 5)
        {
            cache.display();
        }
        else if (choice == 6)
        {
            cache.displaySize();
        }
        else if (choice != 0)
        {
            cout << "Invalid choice." << endl;
        }
    }
    while (choice != 0);

    return 0;
}