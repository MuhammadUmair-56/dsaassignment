#include <iostream>
#include <string>
using namespace std;

struct Lesson
{
    int id;
    string title;
    int duration;
    Lesson* prev;
    Lesson* next;
};

Lesson* head = NULL;
Lesson* tail = NULL;
Lesson* current = NULL;

Lesson* createNode(int id, string title, int duration)
{
    Lesson* node = new Lesson;
    node->id = id;
    node->title = title;
    node->duration = duration;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

int countLessons()
{
    int count = 0;
    Lesson* temp = head;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

bool idExists(int id)
{
    Lesson* temp = head;
    while (temp != NULL)
    {
        if (temp->id == id)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void insertAtBeginning(int id, string title, int duration)
{
    if (idExists(id))
    {
        cout << "Lesson ID already exists." << endl;
        return;
    }
    Lesson* node = createNode(id, title, duration);
    if (head == NULL)
    {
        head = node;
        tail = node;
        current = node;
    }
    else
    {
        node->next = head;
        head->prev = node;
        head = node;
    }
    cout << "Lesson inserted at the beginning." << endl;
}

void insertAtEnd(int id, string title, int duration)
{
    if (idExists(id))
    {
        cout << "Lesson ID already exists." << endl;
        return;
    }
    Lesson* node = createNode(id, title, duration);
    if (head == NULL)
    {
        head = node;
        tail = node;
        current = node;
    }
    else
    {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    cout << "Lesson inserted at the end." << endl;
}

void insertAtPosition(int pos, int id, string title, int duration)
{
    int total = countLessons();
    if (pos < 1 || pos > total + 1)
    {
        cout << "Invalid position." << endl;
        return;
    }
    if (idExists(id))
    {
        cout << "Lesson ID already exists." << endl;
        return;
    }
    if (pos == 1)
    {
        insertAtBeginning(id, title, duration);
        return;
    }
    if (pos == total + 1)
    {
        insertAtEnd(id, title, duration);
        return;
    }
    Lesson* temp = head;
    for (int i = 1; i < pos - 1; i++)
    {
        temp = temp->next;
    }
    Lesson* node = createNode(id, title, duration);
    node->next = temp->next;
    node->prev = temp;
    temp->next->prev = node;
    temp->next = node;
    cout << "Lesson inserted at position " << pos << "." << endl;
}

void removeNode(Lesson* temp)
{
    if (current == temp)
    {
        if (temp->next != NULL)
        {
            current = temp->next;
        }
        else
        {
            current = temp->prev;
        }
    }
    if (temp == head)
    {
        head = temp->next;
    }
    if (temp == tail)
    {
        tail = temp->prev;
    }
    if (temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }
    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }
    cout << "Lesson " << temp->title << " deleted." << endl;
    delete temp;
}

void deleteFirst()
{
    if (head == NULL)
    {
        cout << "List is empty." << endl;
        return;
    }
    removeNode(head);
}

void deleteLast()
{
    if (tail == NULL)
    {
        cout << "List is empty." << endl;
        return;
    }
    removeNode(tail);
}

void deleteAtPosition(int pos)
{
    if (head == NULL)
    {
        cout << "List is empty." << endl;
        return;
    }
    if (pos < 1 || pos > countLessons())
    {
        cout << "Invalid position." << endl;
        return;
    }
    Lesson* temp = head;
    for (int i = 1; i < pos; i++)
    {
        temp = temp->next;
    }
    removeNode(temp);
}

void searchLesson(int id)
{
    if (head == NULL)
    {
        cout << "List is empty." << endl;
        return;
    }
    Lesson* temp = head;
    int position = 1;
    while (temp != NULL)
    {
        if (temp->id == id)
        {
            cout << "Found at position " << position << ": ID " << temp->id
                 << ", Title: " << temp->title
                 << ", Duration: " << temp->duration << " min" << endl;
            return;
        }
        temp = temp->next;
        position++;
    }
    cout << "Lesson not found." << endl;
}

void displayForward()
{
    if (head == NULL)
    {
        cout << "List is empty." << endl;
        return;
    }
    Lesson* temp = head;
    while (temp != NULL)
    {
        cout << temp->id << " | " << temp->title << " | " << temp->duration << " min";
        if (temp == current)
        {
            cout << "  <-- current";
        }
        cout << endl;
        temp = temp->next;
    }
}

void displayBackward()
{
    if (tail == NULL)
    {
        cout << "List is empty." << endl;
        return;
    }
    Lesson* temp = tail;
    while (temp != NULL)
    {
        cout << temp->id << " | " << temp->title << " | " << temp->duration << " min";
        if (temp == current)
        {
            cout << "  <-- current";
        }
        cout << endl;
        temp = temp->prev;
    }
}

void goNext()
{
    if (current == NULL)
    {
        cout << "List is empty." << endl;
        return;
    }
    if (current->next == NULL)
    {
        cout << "Already at the last lesson." << endl;
        return;
    }
    current = current->next;
    cout << "Current lesson: " << current->title << endl;
}

void goPrevious()
{
    if (current == NULL)
    {
        cout << "List is empty." << endl;
        return;
    }
    if (current->prev == NULL)
    {
        cout << "Already at the first lesson." << endl;
        return;
    }
    current = current->prev;
    cout << "Current lesson: " << current->title << endl;
}

void clearList()
{
    while (head != NULL)
    {
        Lesson* temp = head;
        head = head->next;
        delete temp;
    }
    tail = NULL;
    current = NULL;
}

void showJustification()
{
    cout << "Application: Online Course Navigation System" << endl;
    cout << "Selected type: Doubly Linked List" << endl;
    cout << endl;
    cout << "Why doubly linked list is better:" << endl;
    cout << "1. A student can go to the next lesson and also back to the previous lesson." << endl;
    cout << "   Every node has next and prev pointers, so both directions are easy." << endl;
    cout << "2. In a singly linked list we cannot go back, and deleting the last" << endl;
    cout << "   lesson needs a traversal from the head to find the second last node." << endl;
    cout << "3. A circular linked list is not suitable because a course has a" << endl;
    cout << "   real first lesson and a real last lesson." << endl;
    cout << "4. The tail pointer makes insertion and deletion at the end simple." << endl;
}

void runTestCases()
{
    clearList();

    cout << "===== TEST CASE 1: EMPTY LIST =====" << endl;
    displayForward();
    deleteFirst();
    deleteLast();
    deleteAtPosition(1);
    searchLesson(5);
    goNext();
    goPrevious();

    cout << endl;
    cout << "===== TEST CASE 2: SINGLE NODE LIST =====" << endl;
    insertAtEnd(1, "Introduction", 10);
    displayForward();
    displayBackward();
    goNext();
    goPrevious();
    searchLesson(1);
    deleteFirst();
    displayForward();

    cout << endl;
    cout << "===== TEST CASE 3: INSERT, DELETE AND SEARCH =====" << endl;
    insertAtEnd(2, "Variables", 20);
    insertAtEnd(3, "Loops", 30);
    insertAtBeginning(1, "Introduction", 10);
    insertAtPosition(3, 4, "Functions", 25);
    insertAtPosition(10, 9, "Invalid", 5);
    insertAtEnd(3, "Duplicate", 5);
    displayForward();
    displayBackward();
    searchLesson(3);
    searchLesson(99);
    deleteFirst();
    deleteLast();
    deleteAtPosition(2);
    deleteAtPosition(10);
    displayForward();

    cout << endl;
    cout << "===== TEST CASE 4: NEXT AND PREVIOUS =====" << endl;
    clearList();
    insertAtEnd(1, "Introduction", 10);
    insertAtEnd(2, "Variables", 20);
    insertAtEnd(3, "Loops", 30);
    goNext();
    goNext();
    goNext();
    goPrevious();
    goPrevious();
    goPrevious();
    displayForward();

    clearList();
    cout << endl;
    cout << "Test cases finished. List is cleared." << endl;
}

void showMenu()
{
    cout << endl;
    cout << "===== ONLINE COURSE NAVIGATION SYSTEM =====" << endl;
    cout << " 1. Insert lesson at beginning" << endl;
    cout << " 2. Insert lesson at end" << endl;
    cout << " 3. Insert lesson at position" << endl;
    cout << " 4. Delete first lesson" << endl;
    cout << " 5. Delete last lesson" << endl;
    cout << " 6. Delete lesson at position" << endl;
    cout << " 7. Search lesson by ID" << endl;
    cout << " 8. Display lessons forward" << endl;
    cout << " 9. Display lessons backward" << endl;
    cout << "10. Go to next lesson" << endl;
    cout << "11. Go to previous lesson" << endl;
    cout << "12. Run test cases" << endl;
    cout << "13. Show why doubly linked list" << endl;
    cout << " 0. Exit" << endl;
    cout << "Enter your choice: ";
}

int main()
{
    int choice;
    int id;
    int duration;
    int pos;
    string title;

    do
    {
        showMenu();
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter lesson ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter lesson title: ";
            getline(cin, title);
            cout << "Enter duration in minutes: ";
            cin >> duration;
            insertAtBeginning(id, title, duration);
        }
        else if (choice == 2)
        {
            cout << "Enter lesson ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter lesson title: ";
            getline(cin, title);
            cout << "Enter duration in minutes: ";
            cin >> duration;
            insertAtEnd(id, title, duration);
        }
        else if (choice == 3)
        {
            cout << "Enter position: ";
            cin >> pos;
            cout << "Enter lesson ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter lesson title: ";
            getline(cin, title);
            cout << "Enter duration in minutes: ";
            cin >> duration;
            insertAtPosition(pos, id, title, duration);
        }
        else if (choice == 4)
        {
            deleteFirst();
        }
        else if (choice == 5)
        {
            deleteLast();
        }
        else if (choice == 6)
        {
            cout << "Enter position to delete: ";
            cin >> pos;
            deleteAtPosition(pos);
        }
        else if (choice == 7)
        {
            cout << "Enter lesson ID to search: ";
            cin >> id;
            searchLesson(id);
        }
        else if (choice == 8)
        {
            displayForward();
        }
        else if (choice == 9)
        {
            displayBackward();
        }
        else if (choice == 10)
        {
            goNext();
        }
        else if (choice == 11)
        {
            goPrevious();
        }
        else if (choice == 12)
        {
            runTestCases();
        }
        else if (choice == 13)
        {
            showJustification();
        }
        else if (choice == 0)
        {
            cout << "Exiting program." << endl;
        }
        else
        {
            cout << "Invalid choice." << endl;
        }
    }
    while (choice != 0);

    clearList();
    return 0;
}