/*
Problem Statement : 
        A book consists of chapters ,chapters consists of sections
                        &
        sections consist of subsection .
        construct a tree and print the nodes . Find the time and space requirements of your method..
explain :
        chapter --> section --> subsection
        make tree and display nodes..
        time required to method..
*/


#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

struct node {
    string label;
    int count;
    struct node* child[10];
};

class BookTree {
private:
    node* root;

public:
    BookTree() { root = nullptr; }

    void create() {
        int chapters, i, j;
        
        root = new node();
        cout << "Enter Name of Book: ";
        cin.ignore();
        getline(cin, root->label);
        cout << "Enter No. of Chapters in Book: ";
        cin >> chapters;
        root->count = chapters;

        for (i = 0; i < chapters; i++) {
            root->child[i] = new node();
            cout << "Enter Chapter " << i + 1 << " Name: ";
            cin.ignore();
            getline(cin, root->child[i]->label);

            cout << "Enter No. of Sections in Chapter \"" << root->child[i]->label << "\": ";
            cin >> root->child[i]->count;

            for (j = 0; j < root->child[i]->count; j++) {
                root->child[i]->child[j] = new node();
                cout << "Enter Section " << j + 1 << " Name: ";
                cin.ignore();
                getline(cin, root->child[i]->child[j]->label);
            }
        }
    }

    void display(node* r1) {
        if (r1 == nullptr) {
            cout << "Book Tree is empty.\n";
            return;
        }

        cout << "\n\n______ Book Hierarchy ______\n";
        cout << "Book Title: " << r1->label << endl;
        
        for (int i = 0; i < r1->count; i++) {
            cout << "\nChapter " << i + 1 << ": " << r1->child[i]->label;
            cout << "\n  Sections:";

            for (int j = 0; j < r1->child[i]->count; j++) {
                cout << "\n    - " << r1->child[i]->child[j]->label;
            }
            cout << endl;
        }
    }

    void show() {
        display(root);
    }
};

int main() {
    int choice;
    BookTree bookTree;

    while (true) {
	cout << "\n___________*_*_____________";
        cout << "|_____ Book Tree Creation __|" << endl;
        cout << "| 1. Create Book Structure  |" << endl;
        cout << "| 2. Display Book Tree      |" << endl;
        cout << "| 3. Quit                   |" << endl;
        cout << "-----------------------------" << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bookTree.create();
                break;
            case 2:
                bookTree.show();
                break;
            case 3:
                cout << "Exiting program.\n";
                exit(0);
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
