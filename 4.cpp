/*
Problem statement : 
	Begininning with an empty binary search tree.
	construct binary tree by insertinf values  in the order gien .
	after construting a binary tree --
1. insert new node
2. find number of nodes in longest path
3. minimum data value found in the tree
4. change a tree soo that the roles of the left and right pointers are swapped at every node
5. search a value
*/
#include <iostream>
using namespace std;

class node {
    public:
        int data;
        node *left;
        node *right;
};

class bst {
    public:
        node *root;

        bst() {
            root = NULL;
        }

        void create();
        void insert();
        void postorder(node*);
        void inorder(node*);
        void preorder(node*);
        void search(int key);
        void minimum();
        int height(node*);
};

void bst::minimum() {
    if (root == NULL) {
        cout << "Tree is empty!" << endl;
        return;
    }

    node *temp = root;
    while (temp->left != NULL) {
        temp = temp->left;
    }
    cout << "Minimum number is: " << temp->data << endl;
}

int bst::height(node *root) {
    if (root == NULL) {
        return -1; // Height of an empty tree is -1
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + max(leftHeight, rightHeight);
}

void bst::create() {
    node *curr, *temp;
    bool ans = true; // Change ans to bool

    cout << "Enter data: ";
    while (ans) {
        curr = new node;
        cin >> curr->data;
        curr->left = curr->right = NULL;

        if (root == NULL) {
            root = curr;
        } else {
            temp = root;
            while (true) {
                if (curr->data <= temp->data) {
                    if (temp->left == NULL) {
                        temp->left = curr;
                        break;
                    }
                    temp = temp->left;
                } else {
                    if (temp->right == NULL) {
                        temp->right = curr;
                        break;
                    }
                    temp = temp->right;
                }
            }
        }
        cout << "Want to continue? (1 for Yes, 0 for No): ";
        cin >> ans;
    }
}

void bst::inorder(node *root) {
    if (root != NULL) {
        inorder(root->left);
        cout << " " << root->data;
        inorder(root->right);
    }
}

void bst::preorder(node *root) {
    if (root != NULL) {
        cout << " " << root->data;
        preorder(root->left);
        preorder(root->right);
    }
}

void bst::postorder(node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        cout << " " << root->data;
    }
}

void bst::insert() {
    node *curr, *temp;

    cout << "Enter data: ";
    curr = new node;
    cin >> curr->data;
    curr->left = curr->right = NULL;

    if (root == NULL) {
        root = curr;
    } else {
        temp = root;
        while (true) {
            if (curr->data <= temp->data) {
                if (temp->left == NULL) {
                    temp->left = curr;
                    break;
                }
                temp = temp->left;
            } else {
                if (temp->right == NULL) {
                    temp->right = curr;
                    break;
                }
                temp = temp->right;
            }
        }
    }
}

void bst::search(int key) {
    node *curr = root;

    while (curr != NULL) {
        if (curr->data == key) {
            cout << "Key found!" << endl;
            return; // Return immediately after finding the key
        }
        curr = (key < curr->data) ? curr->left : curr->right;
    }

    cout << "Key not found!" << endl;
}

int main() {
    bst b;
    int key, ch;

    do {
        cout << "\n1. Create\n2. Insert\n3. Inorder\n4. Preorder\n5. Postorder\n6. Search\n7. Minimum\n8. Height\nPress 0 to Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                b.create();
                break;
            case 2:
                b.insert();
                break;
            case 3:
                cout << "Inorder traversal: ";
                b.inorder(b.root);
                cout << endl;
                break;
            case 4:
                cout << "Preorder traversal: ";
                b.preorder(b.root);
                cout << endl;
                break;
            case 5:
                cout << "Postorder traversal: ";
                b.postorder(b.root);
                cout << endl;
                break;
            case 6:
                cout << "Enter key: ";
                cin >> key;
                b.search(key);
                break;
            case 7:
                b.minimum();
                break;
            case 8:
                cout << "Height of tree: " << b.height(b.root) << endl;
                break;
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (ch != 0);

    return 0;
}
