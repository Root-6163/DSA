#include<iostream>
#include<string>
using namespace std;

class dict
{
    dict *root, *node, *left, *right, *tree1;
    string s1, s2;
    int flag, flag1, flag2, flag3, cmp;

public:
    dict() {
        flag = flag1 = flag2 = flag3 = cmp = 0;
        root = NULL;
    }
    
    void input();
    void create_root(dict*, dict*);
    void check_same(dict*, dict*);
    void input_display();
    void display(dict*);
    void input_remove();
    dict* remove(dict*, string);
    dict* findmin(dict*);
    void input_find();
    dict* find(dict*, string);
    void input_update();
    dict* update(dict*, string);
};

void dict::input()
{
    node = new dict;
    cout << "\nEnter the keyword:\n";
    cin >> node->s1;
    cout << "Enter the meaning of the keyword:\n";
    cin.ignore();
    getline(cin, node->s2);
    create_root(root, node);
}

void dict::create_root(dict *tree, dict *node1)
{
    if (root == NULL) {
        root = node1;
        root->left = root->right = NULL;
        cout << "\nRoot node created successfully" << endl;
        return;
    }
    check_same(tree, node1);
    if (flag == 1) {
        cout << "The word you entered already exists.\n";
        flag = 0;
        return;
    }
    if (tree->s1 > node1->s1) {
        if (tree->left != NULL)
            create_root(tree->left, node1);
        else {
            tree->left = node1;
            tree->left->left = tree->left->right = NULL;
            cout << "Node added to left of " << tree->s1 << "\n";
        }
    } else {
        if (tree->right != NULL)
            create_root(tree->right, node1);
        else {
            tree->right = node1;
            tree->right->left = tree->right->right = NULL;
            cout << "Node added to right of " << tree->s1 << "\n";
        }
    }
}

void dict::check_same(dict *tree, dict *node1)
{
    if (tree->s1 == node1->s1) {
        flag = 1;
        return;
    }
    if (tree->s1 > node1->s1 && tree->left != NULL)
        check_same(tree->left, node1);
    else if (tree->s1 < node1->s1 && tree->right != NULL)
        check_same(tree->right, node1);
}

void dict::input_display()
{
    if (root != NULL) {
        cout << "The words entered in the dictionary are:\n\n";
        display(root);
    } else {
        cout << "\nThere are no words in the dictionary.\n";
    }
}

void dict::display(dict *tree)
{
    if (tree == NULL)
        return;
    display(tree->left);
    cout << tree->s1 << " = " << tree->s2 << "\n\n";
    display(tree->right);
}

void dict::input_remove()
{
    if (root != NULL) {
        cout << "\nEnter a keyword to be deleted:\n";
        cin >> s1;
        root = remove(root, s1);
        if (flag1 == 0)
            cout << "\nThe word '" << s1 << "' has been deleted.\n";
        flag1 = 0;
    } else {
        cout << "\nThere are no words in the dictionary.\n";
    }
}

dict* dict::remove(dict *tree, string s3)
{
    if (tree == NULL) {
        cout << "\nWord not found.\n";
        flag1 = 1;
        return tree;
    }
    if (tree->s1 > s3)
        tree->left = remove(tree->left, s3);
    else if (tree->s1 < s3)
        tree->right = remove(tree->right, s3);
    else {
        if (tree->left == NULL)
            return tree->right;
        else if (tree->right == NULL)
            return tree->left;
        dict *temp = findmin(tree->right);
        tree->s1 = temp->s1;
        tree->s2 = temp->s2;
        tree->right = remove(tree->right, temp->s1);
    }
    return tree;
}

dict* dict::findmin(dict *tree)
{
    while (tree->left != NULL)
        tree = tree->left;
    return tree;
}

void dict::input_find()
{
    if (root != NULL) {
        cout << "\nEnter the keyword to be searched:\n";
        cin >> s1;
        find(root, s1);
    } else {
        cout << "\nThere are no words in the dictionary.\n";
    }
}

dict* dict::find(dict *tree, string s3)
{
    if (tree == NULL) {
        cout << "\nWord not found.\n";
        return NULL;
    }
    if (tree->s1 == s3) {
        cout << "\nWord found.\n" << tree->s1 << ": " << tree->s2 << "\n";
        return tree;
    } else if (tree->s1 > s3)
        return find(tree->left, s3);
    else
        return find(tree->right, s3);
}

void dict::input_update()
{
    if (root != NULL) {
        cout << "\nEnter the keyword to be updated:\n";
        cin >> s1;
        dict *res = find(root, s1);
        if (res) {
            cout << "\nEnter the updated meaning of the keyword:\n";
            cin.ignore();
            getline(cin, res->s2);
            cout << "\nThe meaning of '" << s1 << "' has been updated.\n";
        }
    } else {
        cout << "\nThere are no words in the dictionary.\n";
    }
}

int main()
{
    int ch;
    dict d;
    do {
        cout << "\n1. Add new keyword\n2. Display\n3. Delete\n4. Find\n5. Update\n6. Exit\n";
        cin >> ch;
        switch (ch) {
            case 1: d.input(); break;
            case 2: d.input_display(); break;
            case 3: d.input_remove(); break;
            case 4: d.input_find(); break;
            case 5: d.input_update(); break;
            case 6: return 0;
            default: cout << "\nInvalid option!\n"; break;
        }
    } while (ch != 6);
    return 0;
}

