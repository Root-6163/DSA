#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Student {
    int roll;
    char name[10];
    char div;
    char add[10];
};

class StudentManager {
    Student rec;

public:
    void create();
    void display();
    int search();
    void Delete();
};

void StudentManager::create() {
    char ans;
    ofstream fout("stud.dat", ios::out | ios::binary);
    if (!fout) {
        cout << "\nError opening file!";
        return;
    }

    do {
        cout << "\nEnter Roll No of Student    : ";
        cin >> rec.roll;
        cout << "Enter Name of Student       : ";
        cin >> rec.name;
        cout << "Enter Division of Student   : ";
        cin >> rec.div;
        cout << "Enter Address of Student    : ";
        cin >> rec.add;

        fout.write((char*)&rec, sizeof(Student));

        cout << "\nDo you want to add more records (y/n)? ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    fout.close();
}

void StudentManager::display() {
    ifstream fin("stud.dat", ios::in | ios::binary);
    if (!fin) {
        cout << "\nError opening file!";
        return;
    }

    fin.seekg(0, ios::beg);
    cout << "\nStudent Records:";
    cout << "\nRoll\tName\tDiv\tAddress\n";

    bool found = false;
    while (fin.read((char*)&rec, sizeof(Student))) {
        if (rec.roll != -1) { // Ensure the record is valid
            cout << rec.roll << "\t" << rec.name << "\t" << rec.div << "\t" << rec.add << "\n";
            found = true;
        }
    }
    
    if (!found) {
        cout << "\nNo records found!\n";
    }
    fin.close();
}

int StudentManager::search() {
    int r;
    ifstream fin("stud.dat", ios::in | ios::binary);
    if (!fin) {
        cout << "\nError opening file!";
        return -1;
    }

    cout << "\nEnter Roll No to search: ";
    cin >> r;

    int pos = 0;
    while (fin.read((char*)&rec, sizeof(Student))) {
        if (rec.roll == r) {
            cout << "\nRecord Found:\n";
            cout << "Roll\tName\tDiv\tAddress\n";
            cout << rec.roll << "\t" << rec.name << "\t" << rec.div << "\t" << rec.add << "\n";
            fin.close();
            return pos;
        }
        pos++;
    }

    cout << "\nRecord Not Found!\n";
    fin.close();
    return -1;
}

void StudentManager::Delete() {
    int pos = search();
    if (pos == -1) {
        cout << "\nCannot delete. Record not found!\n";
        return;
    }

    fstream file("stud.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "\nError opening file!";
        return;
    }

    file.seekp(pos * sizeof(Student), ios::beg);
    rec.roll = -1;
    strcpy(rec.name, "NULL");
    rec.div = 'N';
    strcpy(rec.add, "NULL");

    file.write((char*)&rec, sizeof(Student));
    file.close();
    cout << "\nRecord Deleted Successfully.\n";
}

int main() {
    StudentManager obj;
    int choice;
    char ans;

    do {
        cout << "\n***** Student Information System *****";
        cout << "\n1. Create\n2. Display\n3. Delete\n4. Search\n5. Exit";
        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: obj.create(); break;
            case 2: obj.display(); break;
            case 3: obj.Delete(); break;
            case 4: obj.search(); break;
            case 5: return 0;
            default: cout << "\nInvalid choice! Please enter a valid option.\n";
        }

        cout << "\nDo you want to continue? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    return 0;
}
