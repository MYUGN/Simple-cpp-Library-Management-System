//Inventory System
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

class InventoryItem {
    public:
        int id;
        string name;
        double price;
        int stock;
        InventoryItem* next;

        InventoryItem(int id, string name, double price, int stock) {
            this->id = id;
            this->name = name;
            this->price = price;
            this->stock = stock;
            this->next = nullptr;
        }
};

void saveToFileInventory(InventoryItem* head) {
    string filePath = "./Inventory/inventoryfiles.txt";
    ofstream file(filePath);

    if (!file.is_open()) {
        cout << "Error: Could not open inventoryfiles.txt for writing." << endl;
        return;
    }
    InventoryItem* temp = head;
    while (temp != nullptr){
        file << temp->id << "|" << temp->name << "|" << temp->price << "|" << temp->stock << endl;
        temp = temp->next;
    }
    file.close();
    cout << "Data saved to inventoryfiles.txt successfully!" << endl;
}

//loads inventory items from inventoryfiles.txt
    void loadFromFileInventory(InventoryItem*& head) {
    string filePath = "./Inventory/inventoryfiles.txt";
    ifstream file(filePath);
    
    if (!file.is_open()) {
        cout << "No previous data found. Starting fresh." << endl;
        return;
    }

    string line;
    while(getline(file, line)) {
        if (line.empty()) continue;  //Skip empty lines
        
        //Parse the line: id|name|price|stock
        int id, stock;
        string name;
        double price;

        int pos1 = line.find('|');
        int pos2 = line.find('|', pos1 + 1);
        int pos3 = line.find('|', pos2 + 1);

        id = stoi(line.substr(0, pos1));
        name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        price = stod(line.substr(pos2 + 1, pos3 - pos2 - 1));
        stock = stoi(line.substr(pos3 + 1));
        
        // ADD THIS SECTION - Actually add the item to the list!
        InventoryItem* newItem = new InventoryItem(id, name, price, stock);
        if (head == nullptr) {
            head = newItem;
        } else {
            InventoryItem* temp = head;
            while (temp->next != nullptr) temp = temp->next;
            temp->next = newItem;
        }
    }
    file.close();
    if (head != nullptr) {
        cout << "Data loaded from inventoryfiles.txt successfully!" << endl;
    }
}


void deleteAllInventoryItems(InventoryItem*& head) {
    while (head != nullptr){
        InventoryItem* temp = head;
        head = head->next;
        delete temp;
    }
}

bool productExists(InventoryItem* head, int id) {
    InventoryItem* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) return true;
        temp = temp->next;
    }
    return false;
}

void addProduct(InventoryItem*& head, int id, string name, double price, int stock) {
    
    if (productExists(head, id)) {
        cout << "Product with ID " << id << " already exists." << endl;
        return;
    }
    InventoryItem* newItem = new InventoryItem(id, name, price, stock);
    if (head == nullptr) head = newItem;
    else {
        InventoryItem* temp = head;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = newItem;
    }
    cout << "Product added to inventory!" << endl;
}

void removeProduct(InventoryItem*& head, int id) {
    if (head == nullptr) {
        cout << "Inventory empty." << endl;
        return;
    }
    if (head->id == id) {
        InventoryItem* temp = head;
        head = head->next;
        delete temp;
        cout << "Product removed!" << endl;
        return;
    }
    InventoryItem* temp = head;
    while (temp->next != nullptr && temp->next->id != id) temp = temp->next;
    if (temp->next == nullptr) {
        cout << "Product not found." << endl;
    }
    else {
        InventoryItem* node = temp->next;
        temp->next = temp->next->next;
        delete node;
        cout << "Product removed!" << endl;
    }
}

void updateStock(InventoryItem*& head, int id, int newStock) {
    InventoryItem* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            temp->stock = newStock;
            cout << "Stock updated for ID " << id << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Product not found." << endl;
}

void displayProducts(InventoryItem* head) {
    if (head == nullptr) {
        cout << "Inventory empty." << endl;
        return;
    }
    InventoryItem* temp = head;
    while (temp != nullptr) {
        cout << "ID: " << temp->id << " | Name: " << temp->name
            << " | Price: " << temp->price << " | Stock: " << temp->stock << endl;
        temp = temp->next;
    }
}

