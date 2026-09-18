//POS System class implementation
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

class CartItem {
public:
    int id;
    string name;
    double price;
    int quantity;
    CartItem* next;

    CartItem( int id, string name, double price, int quantity) {
        
        this->id = id;
        this->name = name;
        this->price = price;
        this->quantity = quantity;
        this->next = nullptr;
    }
};

//Saves all cart items to cartfiles.txt
void saveToFileCart(CartItem* head) {
    string filePath = "./Cart Item/cartfiles.txt";
    ofstream file(filePath);
    
    if (!file.is_open()) {
        cout << "Error: Could not open cartfiles.txt for writing." << endl;
        return;
    }
    
    CartItem* temp = head;
    while (temp != nullptr) {
        //Write cart item data in format: id|name|price|quantity
        file  << temp->id << "|" << temp->name << "|" << temp->price << "|" << temp->quantity << endl;
        temp = temp->next;
    }
    
    file.close();
    cout << "Data saved to cartfiles.txt successfully!" << endl;
}

//Loads cart items from cartfiles.txt1
void loadFromFileCart(CartItem*& head) {
    string filePath = "./Cart Item/cartfiles.txt";
    ifstream file(filePath);
    
    if (!file.is_open()) {
        cout << "No previous data found. Starting fresh." << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;  //Skip empty lines
        
        //Parse the line: id|name|price|quantity
        int id;
        string name;
        double price;
        int quantity;

        size_t pos = 0;
        string token;
        int fieldCount = 0;

        while ((pos = line.find('|')) != string::npos) {
            token = line.substr(0, pos);
            switch (fieldCount) {
                case 0: id = stoi(token); break;
                case 1: name = token; break;
                case 2: price = stod(token); break;
            }
            line.erase(0, pos + 1);
            fieldCount++;
        }
        quantity = stoi(line); //Last field after last '|'

        CartItem* newItem = new CartItem(id, name, price, quantity);
        if (head == nullptr) {
            head = newItem;
        } else {
            CartItem* temp = head;
            while (temp->next != nullptr) temp = temp->next;
            temp->next = newItem;
        }
    }
    file.close();
    if (head != nullptr) {
        cout << "Data loaded from cartfiles.txt successfully!" << endl;
    }
}

//Check if product already exists in cart, if yes update quantity, else add new item
bool cartItemExists(CartItem* head, int id) {
    CartItem* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) return true;
        temp = temp->next;
    }
    return false;
}

//Free all memory used by cart items
void deleteAllCartItems(CartItem*& head) {  
    while (head != nullptr){
        CartItem* temp = head;
        head = head->next;
        delete temp;
    }
}

void addToCart(CartItem*& head, int id, string name, double price, int quantity) {
    // Update quantity if item already exists
    if (cartItemExists(head, id)) {
        CartItem* temp = head;
        while (temp != nullptr) {
            if (temp->id == id) {
                temp->quantity += quantity;
                cout << "Product quantity updated in cart!" << endl;
                return;
            }
            temp = temp->next;
        }
    }
    CartItem* newItem = new CartItem(id, name, price, quantity);    
    if (head == nullptr) head = newItem;
    else {
        CartItem* temp = head;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = newItem;
    }
    cout << "Product added to cart!" << endl;
}

void computeTotal(CartItem* head) {
    if (head == nullptr) {
        cout << "Cart is empty." << endl;
        return;
    }
    double total = 0.0;
    CartItem* temp = head;
    while (temp != nullptr) {
        total += temp->price * temp->quantity;
        temp = temp->next;
    }
    cout << "Total Cart Value: P" << total << endl;
}

void displayCart(CartItem* head) {
    if (head == nullptr) {
        cout << "Cart is empty." << endl;
        return;
    }
    CartItem* temp = head;
    while (temp != nullptr) {
        cout << "ID: " << temp->id << " | Name: " << temp->name
            << " | Price: " << temp->price << " | Qty: " << temp->quantity << endl;
        temp = temp->next;
    }
}
