/*
 * MS549 - Week 5 - Assignment: Binary Search Tree
 * Mark Montenieri
 * 
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <chrono>
#include <iomanip>
#include<vector>
#include <wtypes.h>
#include <winuser.h>


using namespace std;

// Node structure
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class
class BST
{
private:
    Node* root;
    
    Node* insert(Node* node, int value)
    {
        if (node == nullptr)
            return new Node(value);
        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        return node;
    }

    bool search(Node* node, int value) const {
        if (node == nullptr)
            return false;
        if (node->data == value)
            return true;
        if (value < node->data)
            return search(node->left, value);
        return search(node->right, value);
    }

    Node* findMin(Node* node) {
        while (node && node->left != nullptr)
            node = node->left;
        return node;
    }

    Node* remove(Node* node, int value)
    {
        if (node == nullptr) return node;

        // Traverse the tree to find the node
        if (value < node->data)
            node->left = remove(node->left, value);
        else if (value > node->data)
            node->right = remove(node->right, value);
        else {
            // Node found
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }

    Node* findMax(Node* node) const {
        if (node == nullptr) {
            return nullptr; // Tree is empty
        }
        while (node->right != nullptr) {
            node = node->right; // Move to the rightmost node
        }
        return node;
    }

    void inOrder(Node* node) const {       
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->data << " ";
            inOrder(node->right);
        }
    }
public:
    BST() : root(nullptr) {}

    // Insert a value into the BST
    void insert(int value) {
        root = insert(root, value);
    }

    // Search for a value in the BST
    bool search(int value) const {
        return search(root, value);
    }

    // Remove a value from the BST
    void remove(int value) {
        root = remove(root, value);
    }

    // Find the maximum value
    int findMax() const {
        Node* maxNode = findMax(root);
        if (maxNode == nullptr) {
            throw runtime_error("The tree is empty.");
        }
        return maxNode->data;
    }

    // Perform in-order traversal
    void inOrder() const {
        inOrder(root);
        cout << '\n';
    }

    /*
     *
     *
     * Working with the Dat file data
     *
     *
     * 
     */

    
    template<class T>// Template def

    struct DatNode // DatNode structure
    {
        T data; // Template data
        DatNode* next; // Previous node
        DatNode* prev; // Next node
    };

    /* Declare head/tail, of type <int> */
    DatNode<int>* head;
    DatNode<int>* tail;
    
    
    void DisplayList()
    {	 
        DatNode<int>* current;// Create a local node var			

        if (head->next == nullptr)//Only a single node in list
        {
            current = head;// Make current = head
            cout << current->data << " ";
        }
        else// Multiple nodes in list
        {
            current = head;
            while (current != nullptr)// While current val isn't nullptr
            {
                cout << current->data << " ";
                current = current->next;// Assign to next in list				
            }
        }	 
    }

    void InsertDataAtEnd(int value)// Insert at end
    {	 
        DatNode<int>* node = new DatNode<int>;// Init a new node of type int
        node->data = value;// Assign value to the newly created node

        if (head->data == NULL)// Is there a list yet?
        {
            /* Create first node of a new list */
            head = node;// Assign node to head
            tail = node;// Assign node to tail

            head->next = nullptr;// Next item in list is nullptr
            head->prev = nullptr;// Previous item in list is nullptr
            tail->next = nullptr;// Next item in list is nullptr
            tail->prev = nullptr;// Previous item in list is nullptr
        }
        else
        {
            if (head->next == nullptr)// Only a single item in list?
            {
                head->next = node;// Head next is our new node
            }

            DatNode<int>* oldTail = tail;
            oldTail->next = node; //Assign the new node to the old one's next
            tail->next = node;// Previous tail's next is now this node
            tail = node;// Make this node the new tail
            tail->next = nullptr;// This new node becomes the end of list	
            tail->prev = oldTail;// Set new tail's prev val to that of the old tail		  
        }	 
    }
    
    bool ImportFileContents(string fileName)// Read the file, if valid
    {
        ifstream in(fileName.c_str());// Open the File	 
        if (!in)// Is valid?
        {
            cerr << "Cannot open the File : " << fileName << '\n';
            return false;
        }
        string str;// String var	
        while (getline(in, str))// Read each line until the end
        {
            if (str.size() > 0)// Line has data?
            {
                int value = stoi(str);// Convert to int
                InsertDataAtEnd(value);// Insert to Linked list
            }		 
        }
        in.close();//Close The File
        return true;// Success!
    }

    
    void MenuChooseFile()
    {
        /* Init nodes (allocate memory) */
        head = new DatNode<int>;
        tail = new DatNode<int>;

        /* Init data values to NULL */
        head->data = NULL;
        tail->data = NULL;
        
        //Node<int>* insertList = NULL;// Insertion sort list
        int num = 0;// File choice
        string fileName;// File name to open
        cout << "Choose which file to run." << '\n';
        cout << "1 = num10.dat" << '\n';
        cout << "2 = num100.dat" << '\n';
        cout << "3 = num1000.dat" << '\n';
        cout << "4 = num10000.dat" << '\n';
        cout << "5 = num100000.dat" << '\n';
        cout << "6 = num1000000.dat" << '\n';
        cout << "Your choice: ";
        cin >> num;	

        switch (num)// User choice selects one of these files
        {
        case 1:
            {
                fileName = "Datasets\\num10.dat";
                break;
            }
        case 2:
            {
                fileName = "Datasets\\num100.dat";
                break;
            }
        case 3:
            {
                fileName = "Datasets\\num1000.dat";
                break;
            }
        case 4:
            {
                fileName = "Datasets\\num10000.dat";
                break;
            }
        case 5:
            {
                fileName = "Datasets\\num100000.dat";
                break;
            }
        case 6:
            {
                fileName = "Datasets\\num1000000.dat";
                break;
            }
        default:
            fileName = "Datasets\\num10.dat";
            break;
        }
	 
        bool result = ImportFileContents(fileName);// Attempt to open file
        if (result)
        {             
            //DisplayList();
            // 1. Start timer
            auto start = chrono::high_resolution_clock::now();// Start high-res timer
            while (head != nullptr)
            {
                Node* node = new Node(head->data);
                insert(node->data);
                head = head->next;
            }

            // 2. End timer
            auto finish = chrono::high_resolution_clock::now();// Stop high-res timer
            auto microseconds = chrono::duration_cast<chrono::microseconds>(finish - start);// Get duration
            auto milliseconds = chrono::duration_cast<chrono::milliseconds>(finish - start);// Get duration
            auto seconds = chrono::duration_cast<chrono::seconds>(finish - start);// Get duration

            // 3. Display time results
            /*Display in micro-milli-seconds */		 
            if (microseconds.count() < 1000)
            {
                cout << '\n' << '\n' << "Sort runtime: " << microseconds.count() << " Microseconds" << '\n';
            }            
            else
            {
                
                cout << '\n' << '\n' << "Sort runtime: " << milliseconds.count() << " Milliseconds" << '\n';
            }
            
            //cout << "\n\nIn-order Traversal: \n\n";
            //inOrder();// Debug
            mainmenu();
        }
    }

    void mainmenu()
    {
      
        int choice, value;

        do {
            cout << "\nBinary Search Tree Operations:\n";
            cout << "1. Insert\n";
            cout << "2. Search\n";
            cout << "3. Remove\n";
            cout << "4. In-order Traversal\n";
            cout << "5. Find Maximum Value\n";
            cout << "6. Multiple Insert Menu\n";        
            cout << "7. Exit\n";        
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                //insert(value);
                insert(value);
                break;
            case 2:
                cout << "Enter value to search: ";
                cin >> value;
                if (search(value))
                    cout << value << " is in the tree \n";
                else
                    cout << value << " was not found in the tree \n";
                break;
            case 3:
                cout << "Enter value to remove: ";
                cin >> value;
                remove(value);
                cout << value << " has been removed.\n";
                break;
            case 4:
                cout << "In-order Traversal: ";
                inOrder();
                break;
            case 5:
                try {
                    cout << "The highest value in the tree is: " << findMax() << '\n';
                } catch (const runtime_error& e) {
                    cout << e.what() << '\n';
                }
                break;
            case 6:
                cout << "Opening Dat menu...\n";
                MenuChooseFile();
                break;
            case 7:
                cout << "Exiting...\n";
                break;        
            default:
                cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 7);

    }
    
};// End of BST class1




int main() {
   
    BST bst;
    bst.mainmenu();
    // int choice, value;
    //
    // do {
    //     cout << "\nBinary Search Tree Operations:\n";
    //     cout << "1. Insert\n";
    //     cout << "2. Search\n";
    //     cout << "3. Remove\n";
    //     cout << "4. In-order Traversal\n";
    //     cout << "5. Find Maximum Value\n";
    //     cout << "6. Exit\n";        
    //     cout << "Enter your choice: ";
    //     cin >> choice;
    //
    //     switch (choice) {
    //     case 1:
    //         cout << "Enter value to insert: ";
    //         cin >> value;
    //     //insert(value);
    //         bst.insert(value);
    //         break;
    //     case 2:
    //         cout << "Enter value to search: ";
    //         cin >> value;
    //         if (bst.search(value))
    //             cout << value << " is in the tree \n";
    //         else
    //             cout << value << " was not found in the tree \n";
    //         break;
    //     case 3:
    //         cout << "Enter value to remove: ";
    //         cin >> value;
    //         bst.remove(value);
    //         cout << value << " has been removed.\n";
    //         break;
    //     case 4:
    //         cout << "In-order Traversal: ";
    //         bst.inOrder();
    //         break;
    //     case 5:
    //         try {
    //             cout << "The highest value in the tree is: " << bst.findMax() << '\n';
    //         } catch (const runtime_error& e) {
    //             cout << e.what() << '\n';
    //         }
    //         break;
    //     case 6:
    //         cout << "Exiting...\n";
    //         break;
    //     case 7:
    //         cout << "Opening Dat menu...\n";
    //         bst.MenuChooseFile();
    //         break;
    //     
    //     default:
    //         cout << "Invalid choice! Please try again.\n";
    //     }
    // } while (choice != 7);

    return 0;
}
