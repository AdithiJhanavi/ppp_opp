#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Abstract LibraryItem class (Abstraction)
class LibraryItem {
protected:
    string title;
    string author;

public:
    LibraryItem(string t, string a) : title(t), author(a) {}
    virtual void displayDetails() = 0; // pure virtual function
    virtual ~LibraryItem() {}
};

// Book class (Inheritance)
class Book : public LibraryItem {
private:
    int pages;

public:
    Book(string t, string a, int p) : LibraryItem(t, a), pages(p) {}

    void displayDetails() override {
        cout << "Book - " << title << " by " << author << " [Pages: " << pages << "]" << endl;
    }
};

// Magazine class (Inheritance)
class Magazine : public LibraryItem {
private:
    int issueNumber;

public:
    Magazine(string t, string a, int i) : LibraryItem(t, a), issueNumber(i) {}

    void displayDetails() override {
        cout << "Magazine - " << title << " by " << author << " [Issue: " << issueNumber << "]" << endl;
    }
};

// Library class (Encapsulation)
class Library {
private:
    vector<LibraryItem*> collection;
    int issuedCount = 0;

public:
    void addItem(LibraryItem* item) {
        collection.push_back(item);
        cout << "Item added to library." << endl;
    }

    void viewItems() {
        if (collection.empty()) {
            cout << "Library is empty." << endl;
            return;
        }

        cout << "\nLibrary Collection:" << endl;
        for (auto item : collection) {
            item->displayDetails();
        }
    }

    void issueItem() {
        if (collection.empty()) {
            cout << "No items to issue." << endl;
            return;
        }

        cout << "Select item number to issue:" << endl;
        for (size_t i = 0; i < collection.size(); ++i) {
            cout << i + 1 << ". ";
            collection[i]->displayDetails();
        }

        int choice;
        cin >> choice;

        if (choice >= 1 && choice <= (int)collection.size()) {
            cout << "Issued: ";
            collection[choice - 1]->displayDetails();
            issuedCount++;
        } else {
            cout << "Invalid choice." << endl;
        }
    }

    void totalIssued() {
        cout << "Total items issued: " << issuedCount << endl;
    }

    ~Library() {
        for (auto item : collection) {
            delete item;
        }
    }
};

int main() {
    Library lib;
    int choice;

    while (true) {
        cout << "\n===== Library Management System =====" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Add Magazine" << endl;
        cout << "3. View Library Collection" << endl;
        cout << "4. Issue an Item" << endl;
        cout << "5. View Total Issued Items" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string title, author;
            int pages;
            cout << "Enter Book Title: ";
            cin >> ws;
            getline(cin, title);
            cout << "Enter Author: ";
            getline(cin, author);
            cout << "Enter Number of Pages: ";
            cin >> pages;
            lib.addItem(new Book(title, author, pages));
        }
        else if (choice == 2) {
            string title, author;
            int issue;
            cout << "Enter Magazine Title: ";
            cin >> ws;
            getline(cin, title);
            cout << "Enter Author: ";
            getline(cin, author);
            cout << "Enter Issue Number: ";
            cin >> issue;
            lib.addItem(new Magazine(title, author, issue));
        }
        else if (choice == 3) {
            lib.viewItems();
        }
        else if (choice == 4) {
            lib.issueItem();
        }
        else if (choice == 5) {
            lib.totalIssued();
        }
        else if (choice == 6) {
            cout << "Thank you! Visit again." << endl;
            break;
        }
        else {
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
