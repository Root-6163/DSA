/*
Problem Statement :
	there are flight paths between cities 
	if there is a flight between city A and city B 
	then there is an edge between the cities 
	the cost of the edge can be the time that flight take to reach city A to city B
	the amount of fuel used for the journey . represent this as a graph .
	the  node can be represented by airport name or name of city..
	use adjacent list representation of the graph or use adjacency matrix representaion of the graph 
	justify the storage representaion used .
*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

struct node {
    string vertex;
    int time;
    node *next;
};

class adjmatlist {
    int m[10][10], n, i, j;
    char ch;
    string v[20];
    node *head[20];
    node *temp = NULL;

public:
    adjmatlist() {
        for (i = 0; i < 20; i++) {
            head[i] = NULL;
        }
    }

    void getgraph();
    void adjlist();
    void displaym();
    void displaya();
};

void adjmatlist::getgraph() {
    cout << "\n\tEnter the *Number* of Cities (max 20): ";
    cin >> n;

    cout << "\n\tEnter the *Names* of the cities: ";
    for (i = 0; i < n; i++) {
        cin >> v[i];
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cout << "\nPath Between --" << v[i] << "-- and -- " << v[j] << ".. ?(y/n): ";
            cin >> ch;

            if (ch == 'y') {
                cout << "\nEnter Time Required to Reach --" << v[j] << "-- from --" << v[i] << "in Minutes:- ";
                cin >> m[i][j];
            } else if (ch == 'n') {
                m[i][j] = 0;
            } else {
                cout << "\nInvalid input! Enter 'y' or 'n'..";
                j--;  // Re-prompt for valid input
            }
        }
    }
    adjlist();
}

void adjmatlist::adjlist() {
    cout << "\n****-Adjacency_List-****";

    for (i = 0; i < n; i++) {
        node *p = new node;
        p->next = NULL;
        p->vertex = v[i];
        head[i] = p;
        cout << "\n" << head[i]->vertex;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (m[i][j] != 0) {
                node *p = new node;
                p->vertex = v[j];
                p->time = m[i][j];
                p->next = NULL;

                if (head[i]->next == NULL) {
                    head[i]->next = p;
                } else {
                    temp = head[i];
                    while (temp->next != NULL) {
                        temp = temp->next;
                    }
                    temp->next = p;
                }
            }
        }
    }
}

void adjmatlist::displaym() {
    cout << "\n****-Adjacency_Matrix-****";
    
    cout << "\n\t";
    for (j = 0; j < n; j++) {
        cout << v[j] << "\t";
    }

    for (i = 0; i < n; i++) {
        cout << "\n" << v[i] << "\t";
        for (j = 0; j < n; j++) {
            cout << m[i][j] << "\t";
        }
        cout << "\n";
    }
}

void adjmatlist::displaya() {
    cout << "\n****-Adjacency_List-****";
    
    for (i = 0; i < n; i++) {
        if (head[i] == NULL) {
            cout << "\n+----Adjacency_list_Not_Present.---+";
            break;
        } else {
            cout << "\n" << head[i]->vertex;
            temp = head[i]->next;
            while (temp != NULL) {
                cout << " -> " << temp->vertex;
                temp = temp->next;
            }
        }
    }

    cout << "\n\n*----Path and Time Required to Reach Cities----*";
    
    for (i = 0; i < n; i++) {
        if (head[i] == NULL) {
            cout << "\n*----Adjacency_list_Not present.";
            break;
        } else {
            temp = head[i]->next;
            while (temp != NULL) {
                cout << "\n" << head[i]->vertex << " -> " << temp->vertex;
                cout << "\n   [Time required: " << temp->time << " min]";
                temp = temp->next;
            }
        }
    }
}

int main() {
    int m;
    adjmatlist a;

    while (true) {
        cout << "\n\nEnter your choice:";
        cout << "\n1. Enter graph";
        cout << "\n2. Display adjacency matrix";
        cout << "\n3. Display adjacency list";
        cout << "\n4. Exit";
        cout << "\nChoice: ";
        cin >> m;

        switch (m) {
            case 1:
                a.getgraph();
                break;
            case 2:
                a.displaym();
                break;
            case 3:
                a.displaya();
                break;
            case 4:
                exit(0);
            default:
                cout << "\nUnknown choice!";
        }
    }
    return 0;
}

