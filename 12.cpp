#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstring>

using namespace std;

// Employee class Declaration
class Employee {
private:
    int code;
    char name[20];
    float salary;
    char designation[20];

public:
    void read();
    void display();
    int getEmpCode() { return code; }
    float getSalary() { return salary; }
    void updateSalary(float s) { salary = s; }
};

// Read employee record
void Employee::read() {
    cout << "Enter employee code: ";
    cin >> code;
    cin.ignore();  // Ignore newline from previous input
    cout << "Enter name: ";
    cin.getline(name, 20);
    cout << "Enter Designation: ";
    cin.getline(designation, 20);
    cout << "Enter salary: ";
    cin >> salary;
}

// Display employee record
void Employee::display() {
    cout << code << " " << name << "\t" << salary << endl;
}

// Global file stream
fstream file;

// Delete file when the program starts
void deleteExistingFile() {
    remove("EMPLOYEE.DAT");
}

// Function to append record into file
void appendToFile() {
    Employee x;
    x.read();

    file.open("EMPLOYEE.DAT", ios::binary | ios::app);
    if (!file) {
        cout << "ERROR IN CREATING FILE\n";
        return;
    }
    file.write((char*)&x, sizeof(x));
    file.close();
    cout << "Record added successfully.\n";
}

// Function to display all records
void displayAll() {
    Employee x;
    file.open("EMPLOYEE.DAT", ios::binary | ios::in);
    if (!file) {
        cout << "ERROR IN OPENING FILE\n";
        return;
    }
    cout << "\nEmployee Records:\n";
    while (file.read((char*)&x, sizeof(x))) {
        x.display();
    }
    file.close();
}

// Function to search for a record
void searchForRecord() {
    Employee x;
    int c, isFound = 0;
    cout << "Enter employee code: ";
    cin >> c;

    file.open("EMPLOYEE.DAT", ios::binary | ios::in);
    if (!file) {
        cout << "ERROR IN OPENING FILE\n";
        return;
    }
    while (file.read((char*)&x, sizeof(x))) {
        if (x.getEmpCode() == c) {
            cout << "RECORD FOUND\n";
            x.display();
            isFound = 1;
            break;
        }
    }
    if (!isFound) {
        cout << "Record not found!\n";
    }
    file.close();
}

// Function to increase salary
void increaseSalary() {
    Employee x;
    int c, isFound = 0;
    float sal;

    cout << "Enter employee code: ";
    cin >> c;

    file.open("EMPLOYEE.DAT", ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "ERROR IN OPENING FILE\n";
        return;
    }

    while (file.read((char*)&x, sizeof(x))) {
        if (x.getEmpCode() == c) {
            cout << "Current salary: " << x.getSalary() << "\nEnter salary hike: ";
            cin >> sal;
            x.updateSalary(x.getSalary() + sal);

            // Move write pointer back to update the salary
            file.seekp(-sizeof(Employee), ios::cur);
            file.write((char*)&x, sizeof(x));

            isFound = 1;
            break;
        }
    }
    file.close();
    
    if (isFound)
        cout << "Salary updated successfully.\n";
    else
        cout << "Record not found!\n";
}

// Insert record in sorted order (by employee code)
void insertRecord() {
    Employee x, newEmp;
    newEmp.read();

    fstream fin;
    file.open("EMPLOYEE.DAT", ios::binary | ios::in);
    fin.open("TEMP.DAT", ios::binary | ios::out);

    if (!file || !fin) {
        cout << "Error opening file!\n";
        return;
    }

    bool inserted = false;
    while (file.read((char*)&x, sizeof(x))) {
        if (!inserted && x.getEmpCode() > newEmp.getEmpCode()) {
            fin.write((char*)&newEmp, sizeof(newEmp));
            inserted = true;
        }
        fin.write((char*)&x, sizeof(x));
    }

    if (!inserted) {
        fin.write((char*)&newEmp, sizeof(newEmp));  // Insert at end if not inserted earlier
    }

    fin.close();
    file.close();

    remove("EMPLOYEE.DAT");
    rename("TEMP.DAT", "EMPLOYEE.DAT");

    cout << "Record inserted successfully.\n";
}

// Main function
int main() {
    char ch;
    deleteExistingFile();

    do {
        int n;
        cout << "\n***** Employee Management System *****\n";
        cout << "1. Add an Employee\n2. Display\n3. Search\n4. Increase Salary\n5. Insert Record\n";
        cout << "Enter your choice: ";
        cin >> n;

        switch (n) {
            case 1: appendToFile(); break;
            case 2: displayAll(); break;
            case 3: searchForRecord(); break;
            case 4: increaseSalary(); break;
            case 5: insertRecord(); break;
            default: cout << "Invalid Choice\n";
        }

        cout << "Do you want to continue? (y/n): ";
        cin >> ch;

    } while (ch == 'Y' || ch == 'y');

    return 0;
}
