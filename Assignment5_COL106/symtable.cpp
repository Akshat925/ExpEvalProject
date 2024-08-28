#include "symtable.h"

SymNode *searcher(SymNode *a, string b)
{
    SymNode *current = a;
    while (current != nullptr)
    {
        if (b == current->key)
        {
            return current;
        }
        else if (b < current->key)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return nullptr;
}

int get_height(SymNode *node)
{
    if (node == nullptr)
    {
        return -1;
    }
    return node->height;
}

int getbalancefactor(SymNode *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return get_height(node->left) - get_height(node->right);
}

SymNode *leftRotate(SymNode *y)
{
    SymNode *x = y->right;
    SymNode *leftnode = x->left;
    x->left = y;
    y->right = leftnode;
    y->height = 1 + max(get_height(y->left), get_height(y->right));
    x->height = 1 + max(get_height(x->left), get_height(x->right));
    return x;
}

SymNode *rightRotate(SymNode *x)
{
    SymNode *y = x->left;
    SymNode *rightnode = y->right;
    y->right = x;
    x->left = rightnode;
    x->height = 1 + max(get_height(x->left), get_height(x->right));
    y->height = 1 + max(get_height(y->left), get_height(y->right));
    return y;
}

SymNode *balancer(SymNode *node)
{
    int balance = getbalancefactor(node);
    if (balance > 1 && getbalancefactor(node->left) >= 0)
    {
        return rightRotate(node);
    }

    if (balance < -1 && getbalancefactor(node->right) <= 0)
    {
        return leftRotate(node);
    }

    if (balance > 1 && getbalancefactor(node->left) < 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && getbalancefactor(node->right) > 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

SymNode *inserter(SymNode *root, string k)
{
    if (root == NULL)
    {
        root = new SymNode(k);
    }
    else if (k < root->key)
    {
        root->left = inserter(root->left, k);
    }
    else if (k > root->key)
    {
        root->right = inserter(root->right, k);
    }
    else
    {
        root->key = k;
    }
    root->height = 1 + max(get_height(root->left), get_height(root->right));
    root = balancer(root);
    return root;
}

SymNode *findSuccessor(SymNode *node)
{
    while (node->left)
    {
        node = node->left;
    }
    return node;
}

SymNode *deleteNode(SymNode *root, string k)
{
    if (!root)
    {
        return nullptr;
    }
    if (root->key > k)
    {
        root->left = deleteNode(root->left, k);
    }
    else if (root->key < k)
    {
        root->right = deleteNode(root->right, k);
    }
    else
    {
        if (!root->left && !root->right)
        {
            delete root;
        }
        else if (!root->left)
        {
            SymNode *temp = root;
            root = root->right;
            delete temp;
        }
        else if (!root->right)
        {
            SymNode *temp = root;
            root = root->left;
            delete temp;
        }
        else
        {
            SymNode *successor = findSuccessor(root->right);
            root->key = successor->key;
            root->right = deleteNode(root->right, successor->key);
        }
    }
    if (root == nullptr)
    {
        return root;
    }
    root->height = 1 + max(get_height(root->left), get_height(root->right));
    root = balancer(root);
    return root;
}

SymbolTable::SymbolTable()
{
    size = 0;
}

SymbolTable::~SymbolTable()
{
    delete root;
}

void SymbolTable::insert(string k)
{
    root = inserter(root, k);
    size++;
}

void SymbolTable::remove(string k)
{
    deleteNode(root, k);
    size--;
}

int SymbolTable::search(string k)
{
    SymNode *node = searcher(root, k);
    int a = node->address;
    return a;
}

int SymbolTable::get_size()
{
    return size;
}

SymNode *SymbolTable::get_root()
{
    return root;
}

void SymbolTable::assign_address(string k, int idx)
{
    SymNode *node = searcher(root, k);
    if (node != nullptr)
    {
        node->address = idx;
    }
}