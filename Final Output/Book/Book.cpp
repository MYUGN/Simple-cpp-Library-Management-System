//library management system using file managing and oop

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Book {
public:
    int id;
    string name;
    string author;
    string status;
    Book* next;

    Book(int id, string name, string author, string status) {
        this->id = id;
        this->name = name;
        this->author = author;
        this->status = status;
        this->next = nullptr;
    }
};

//Saves all books to bookfiles.txt
void saveToFileBook(Book* head) {
    string filePath = "./Book/bookfiles.txt";
    ofstream file(filePath);
    
    if (!file.is_open()) {
        cout << "Error: Could not open bookfiles.txt for writing." << endl;
        return;
    }
    
    Book* temp = head;
    while (temp != nullptr) {
        //Write book data in format: id|name|author|status
        file  << temp->id << "|" << temp->name << "|" << temp->author << "|" << temp->status << endl;
        temp = temp->next;
    }
    
    file.close();
    cout << "Data saved to bookfiles.txt successfully!" << endl;
}

//Loads books from bookfiles.txt
void loadFromFileBook(Book*& head) {
    string filePath = "./Book/bookfiles.txt";
    ifstream file(filePath);
    
    if (!file.is_open()) {
        cout << "No previous data found. Starting fresh." << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;  //Skip empty lines
        
        //Parse the line: id|name|author|status
        int id;
        string name, author, status;
        
        int pos1 = line.find('|');
        int pos2 = line.find('|', pos1 + 1);
        int pos3 = line.find('|', pos2 + 1);
        
        id = stoi(line.substr(0, pos1));
        name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        author = line.substr(pos2 + 1, pos3 - pos2 - 1);
        status = line.substr(pos3 + 1);
        
        // Add the book to the linked list
        Book* newBook = new Book(id, name, author, status);
        
        if (head == nullptr) {
            head = newBook;
        } else {
            Book* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newBook;
        }
    }
    file.close();
    if (head != nullptr) {
        cout << "Data loaded from bookfiles.txt successfully!" << endl;
    } 
}

//Check if book exists para di ma ulet
bool bookExists(Book* head, int id) {
    Book* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

//Free all memory to 
void deleteAllBooks(Book*& head) {
    while (head != nullptr) {
        Book* temp = head;
        head = head->next;
        delete temp;
    }
}

void removeBook(Book*& head, int id) {
    if (head == nullptr) {
        cout << "No Book records available. Nothing to remove." << endl;
        return;
    }

    if (head->id == id) {
        Book* temp = head;
        head = head->next;
        delete temp;
        cout << "Book record removed successfully!" << endl;
        return;
    }

    Book* temp = head;
    while (temp->next != nullptr && temp->next->id != id) {
        temp = temp->next;
    }

    if (temp->next == nullptr) {
        cout << "Book with ID " << id << " not found." << endl;
    } else {
        Book* nodeToDelete = temp->next;
        temp->next = temp->next->next;
        delete nodeToDelete;
        cout << "Book record removed successfully!" << endl;
    }
}

void addBook(Book*& head, int id, string name, string author, string status) {
    //Check if book already exists
    if (bookExists(head, id)) {
        cout << "Book with ID " << id << " already exists. Cannot add duplicate." << endl;
        return;
    }
    
    Book* newBook = new Book(id, name, author, status);
    if (head == nullptr) {
        head = newBook;
    } else {
        Book* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newBook;
    }
    cout << "Book added successfully!" << endl;
}

void searchBook(Book* head, int id) {
    if (head == nullptr) {
        cout << "No Book records available." << endl;
        return;
    }
    Book* temp = head;
    bool found = false;
    while (temp != nullptr) {
        if (temp->id == id) {
            cout << "ID: " << temp->id << ", Name: " << temp->name << ", Author: " << temp->author << ", Status: " << temp->status << endl; 
            found = true;
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "Book with ID " << id << " not found." << endl;
    }
}

void displayBook(Book* head) {
    if (head == nullptr) {
        cout << "No Book records available." << endl;
        return;
    }

    Book* temp = head;
    cout << "\n--- All Books ---" << endl;
    while (temp != nullptr) {
        cout << "ID: " << temp->id << ", Name: " << temp->name
             << ", Author: " << temp->author << ", Status: " << temp->status << endl;
        temp = temp->next;
    }
}
