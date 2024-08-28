/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

SymEntry* inserter(SymEntry* root, string k, UnlimitedRational *v)
{
    if(root==NULL){
        root=new SymEntry(k, v);
    }

    else if(k < root->key){
        root->left=inserter(root->left,k,v);
    }

    else if(k > root->key){
        root->right=inserter(root->right,k,v);
    }

    else{
        root->key=k;
        root->val=v;
    }
    return root;
}

SymEntry *findSuccessor(SymEntry *node)
{
    while (node->left)
    {
        node = node->left;
    }
    return node;
}

SymEntry* deleteNode(SymEntry *root, string k)
{
    if (!root)
    {
        return nullptr;
    }
    if (root->key > k)
    {
        root->left=deleteNode(root->left, k);
    }
    else if (root->key < k)
    {
        root->right=deleteNode(root->right, k);
    }
    else
    {
        if (!root->left && !root->right)
        {
            delete root;
        }
        else if (!root->left)
        {
            SymEntry *temp = root;
            root = root->right;
            delete temp;
        }
        else if (!root->right)
        {
            SymEntry *temp = root;
            root = root->left;
            delete temp;
        }
        else
        {
            SymEntry *successor = findSuccessor(root->right);
            root->val = successor->val;
            root->right=deleteNode(root->right, successor->key);
        }
    }
    return root;
}

SymbolTable::SymbolTable()
{
    size = 0;
    root = new SymEntry();
}

SymbolTable::~SymbolTable()
{
    delete root;
}

void SymbolTable::insert(string k, UnlimitedRational *v)
{
    inserter(root,k,v);
    size++;
}

void SymbolTable::remove(string k)
{
    deleteNode(root, k);
    size--;
}

UnlimitedRational *SymbolTable::search(string k)
{
    SymEntry *current = root;

    while (current != nullptr)
    {
        if (k == current->key)
        {
            return current->val;
        }
        else if (k < current->key)
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

int SymbolTable::get_size()
{
    return size;
}

SymEntry *SymbolTable::get_root()
{
    return root;
}
