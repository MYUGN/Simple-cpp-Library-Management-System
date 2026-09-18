#include "Book/Book.cpp"
#include "Inventory/Inventory.cpp" 
#include "Cart Item/CartItem.cpp" 
#include <iostream>
#include <limits>
using namespace std;

void runLibrarySystem() {
        Book *head = nullptr;
    int choice, id;
    string name, author, status;

    //Load existing data when program starts
    loadFromFileBook(head);

    while (true){
        cout << "\n--- Library Management System ---\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Search Book by ID\n";
        cout << "4. Display All Books\n";
        cout << "5. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Book ID: ";
                cin >> id;
                cout << "Enter title: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Status of Book: ";
                getline(cin, status);
                addBook(head, id, name, author, status);
                break;
            case 2:
                cout << "Enter Book ID to remove: ";
                cin >> id;
                removeBook(head, id);
                break;
            case 3:
                cout << "Enter Book ID to search: ";
                cin >> id;
                searchBook(head, id);
                break;
            case 4:
                displayBook(head);
                break;
            case 5:
                saveToFileBook(head);
                deleteAllBooks(head); 
                cout << "Exiting the program. Goodbye!" << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;    
        }

    }
}

void runInventorySystem() {
InventoryItem* head = nullptr;
    int choice, id, stock;
    string name;
    double price;
    loadFromFileInventory(head);  

    while (true) {
        cout << "\n--- Store Inventory System ---\n";
        cout << "1. Add Product\n";
        cout << "2. Remove Product\n";
        cout << "3. Update Stock\n";
        cout << "4. Display Products\n";
        cout << "5. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Name: ";
            getline(cin, name);

            cout << "Price: ";
            cin >> price;

            cout << "Stock: ";
            cin >> stock;

            addProduct(head, id, name, price, stock);
            break;
        case 2:
            cout << "ID to remove: "; cin >> id;
            removeProduct(head, id);
            break;
        case 3:
            cout << "ID to update: "; cin >> id;
            cout << "New Stock: "; cin >> stock;
            updateStock(head, id, stock);
            break;
        case 4:
            displayProducts(head);
            break;
        case 5:
            saveToFileInventory(head);
            deleteAllInventoryItems(head);
            cout << "Exiting the program. Goodbye!" << endl;
            return;
        default: cout << "Invalid choice." << endl;
        }
    }
}

void runPOSSystem() {
    CartItem *head = nullptr;
    int choice, id, quantity;
    string name, author, status;
    double price;

    loadFromFileCart(head);  // Load existing cart items from file

    while (true){
        cout << "\n--- Point of Sale (POS) System ---\n";
        cout << "1. Add Product\n";
        cout << "2. Compute Total\n";
        cout << "3. Display Cart\n";
        cout << "4. Save and Exit\n";
        cout << "Enter your Choice: "; 
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Name: ";
            getline(cin, name);

            cout << "Price: ";
            cin >> price;

            cout << "Quantity: ";
            cin >> quantity;

            addToCart(head, id, name, price, quantity);
            break;
        case 2:
            computeTotal(head);
            break;
        case 3:
            displayCart(head);
            break;
        case 4:
            saveToFileCart(head);
            cout << "Exiting the program. Goodbye!" << endl;
            return;
        default: cout << "Invalid choice." << endl;
        }
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n====== GENERAL MENU ======\n";
        cout << "1. Library Management System\n";
        cout << "2. Store Inventory System\n";
        cout << "3. Point of Sale (POS) System\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            runLibrarySystem();
            break;
        case 2:
            runInventorySystem();
            break;
        case 3:
            runPOSSystem();
            break;
        case 4:
            cout << "Exiting the program. Goodbye!" << endl;
            return 0;
        default: cout << "Invalid choice." << endl;
        }
    }
}