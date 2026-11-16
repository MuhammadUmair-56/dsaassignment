#include <iostream>
#include <string>
using namespace std;

class Block
{
public:
    int blockId;
    string transaction;
    string timestamp;
    int previousHash;
    int currentHash;
    Block* next;

    Block(int id, string trans, string time)
    {
        blockId = id;
        transaction = trans;
        timestamp = time;
        previousHash = 0;
        currentHash = 0;
        next = NULL;
    }
};

class BlockChain
{
private:
    Block* head;
    Block* newBlock;

    int calculateHash(Block* block)
    {
        int hash = block->blockId + block->previousHash;

        int length = block->transaction.length();
        for (int i = 0; i < length; i++)
        {
            hash = hash + block->transaction[i];
        }

        length = block->timestamp.length();
        for (int i = 0; i < length; i++)
        {
            hash = hash + block->timestamp[i];
        }

        return hash % 10007;
    }

    Block* findBlock(int id)
    {
        Block* temp = head;
        while (temp != NULL)
        {
            if (temp->blockId == id)
            {
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }

    void updateAllHashes()
    {
        int prevHash = 0;
        Block* temp = head;
        while (temp != NULL)
        {
            temp->previousHash = prevHash;
            temp->currentHash = calculateHash(temp);
            prevHash = temp->currentHash;
            temp = temp->next;
        }
    }

public:
    BlockChain()
    {
        head = NULL;
        newBlock = NULL;
    }

    void createBlock(int id, string trans, string time)
    {
        if (newBlock != NULL)
        {
            delete newBlock;
        }
        newBlock = new Block(id, trans, time);
        cout << "Block created. Use the add option to put it in the chain." << endl;
    }

    void addBlock()
    {
        if (newBlock == NULL)
        {
            cout << "No block created. Create a block first." << endl;
            return;
        }

        if (findBlock(newBlock->blockId) != NULL)
        {
            cout << "A block with this ID already exists." << endl;
            return;
        }

        if (head == NULL)
        {
            newBlock->previousHash = 0;
            newBlock->currentHash = calculateHash(newBlock);
            head = newBlock;
        }
        else
        {
            Block* last = head;
            while (last->next != NULL)
            {
                last = last->next;
            }
            newBlock->previousHash = last->currentHash;
            newBlock->currentHash = calculateHash(newBlock);
            last->next = newBlock;
        }

        newBlock = NULL;
        cout << "Block added to the chain." << endl;
    }

    void displayChain()
    {
        if (head == NULL)
        {
            cout << "Blockchain is empty." << endl;
            return;
        }

        Block* temp = head;
        while (temp != NULL)
        {
            cout << "Block ID: " << temp->blockId << endl;
            cout << "Transaction: " << temp->transaction << endl;
            cout << "Timestamp: " << temp->timestamp << endl;
            cout << "Previous Hash: " << temp->previousHash << endl;
            cout << "Current Hash: " << temp->currentHash << endl;
            cout << "-----------------------" << endl;
            temp = temp->next;
        }
    }

    void searchTransaction(string trans)
    {
        if (head == NULL)
        {
            cout << "Blockchain is empty." << endl;
            return;
        }

        Block* temp = head;
        while (temp != NULL)
        {
            if (temp->transaction == trans)
            {
                cout << "Transaction found in block " << temp->blockId << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Transaction not found." << endl;
    }

    void deleteBlock(int id)
    {
        if (head == NULL)
        {
            cout << "Blockchain is empty." << endl;
            return;
        }

        Block* current = head;
        Block* previous = NULL;

        while (current != NULL && current->blockId != id)
        {
            previous = current;
            current = current->next;
        }

        if (current == NULL)
        {
            cout << "Block not found." << endl;
            return;
        }

        if (previous == NULL)
        {
            head = current->next;
        }
        else
        {
            previous->next = current->next;
        }

        delete current;
        updateAllHashes();
        cout << "Block deleted." << endl;
    }

    void checkHash(int id)
    {
        Block* block = findBlock(id);

        if (block == NULL)
        {
            cout << "Block not found." << endl;
            return;
        }

        int newHash = calculateHash(block);
        cout << "Stored hash: " << block->currentHash << endl;
        cout << "Calculated hash: " << newHash << endl;

        if (newHash == block->currentHash)
        {
            cout << "Hash is correct." << endl;
        }
        else
        {
            cout << "Hash does not match." << endl;
        }
    }

    void detectModification()
    {
        if (head == NULL)
        {
            cout << "Blockchain is empty." << endl;
            return;
        }

        bool modified = false;
        int expectedPreviousHash = 0;
        Block* temp = head;

        while (temp != NULL)
        {
            if (temp->previousHash != expectedPreviousHash)
            {
                cout << "Block " << temp->blockId << ": link with previous block is broken." << endl;
                modified = true;
            }

            if (temp->currentHash != calculateHash(temp))
            {
                cout << "Block " << temp->blockId << ": data has been changed." << endl;
                modified = true;
            }

            expectedPreviousHash = temp->currentHash;
            temp = temp->next;
        }

        if (modified == false)
        {
            cout << "No modification found. Blockchain is safe." << endl;
        }
    }
};

int main()
{
    BlockChain chain;
    int choice;

    do
    {
        cout << endl;
        cout << "1. Create a block" << endl;
        cout << "2. Add a block" << endl;
        cout << "3. Display the chain" << endl;
        cout << "4. Search for a transaction" << endl;
        cout << "5. Delete a block" << endl;
        cout << "6. Calculate/verify a simple hash" << endl;
        cout << "7. Detect whether a block relationship has been modified" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int id;
            string trans;
            string time;
            cout << "Enter block ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter transaction: ";
            getline(cin, trans);
            cout << "Enter timestamp: ";
            getline(cin, time);
            chain.createBlock(id, trans, time);
        }
        else if (choice == 2)
        {
            chain.addBlock();
        }
        else if (choice == 3)
        {
            chain.displayChain();
        }
        else if (choice == 4)
        {
            string trans;
            cin.ignore();
            cout << "Enter transaction to search: ";
            getline(cin, trans);
            chain.searchTransaction(trans);
        }
        else if (choice == 5)
        {
            int id;
            cout << "Enter block ID to delete: ";
            cin >> id;
            chain.deleteBlock(id);
        }
        else if (choice == 6)
        {
            int id;
            cout << "Enter block ID: ";
            cin >> id;
            chain.checkHash(id);
        }
        else if (choice == 7)
        {
            chain.detectModification();
        }
        else if (choice != 0)
        {
            cout << "Invalid choice." << endl;
        }
    }
    while (choice != 0);

    return 0;
}