#include "evaluator.h"

Evaluator::Evaluator()
{
    symtable = new SymbolTable;
}

Evaluator::~Evaluator()
{
    expr_trees.clear();
}

ExprTreeNode *parsehelper(vector<string> code)
{
    if (code.size() == 1)
    {
        if (!isdigit(code[0][0]))
        {
            ExprTreeNode *variable = new ExprTreeNode();
            variable->type = "VAR";
            variable->id = code[0];
            return variable;
        }
        else
        {
            UnlimitedInt *value = new UnlimitedInt(code[0]);
            ExprTreeNode *node = new ExprTreeNode("VAL", value);
            node->type = "VAL";
            return node;
        }
    }
    int count = 0;
    int mid = -1;
    UnlimitedInt *zero = new UnlimitedInt("0");
    ExprTreeNode *newnodes = new ExprTreeNode("VAR", zero);
    int lengtho = code.size();
    for (int i = 0; i < lengtho; i++)
    {
        if (code[i] == "(")
        {
            count++;
        }
        if (code[i] == ")")
        {
            count--;
        }
        mid++;
        if (code[i] == "+" && count == 1)
        {
            newnodes->type = "ADD";
            break;
        }
        if (code[i] == "-" && count == 1)
        {
            newnodes->type = "SUB";
            break;
        }
        if (code[i] == "*" && count == 1)
        {
            newnodes->type = "MUL";
            break;
        }
        if (code[i] == "/" && count == 1)
        {
            newnodes->type = "DIV";
            break;
        }
        if (code[i] == "%" && count == 1)
        {
            newnodes->type = "MOD";
            break;
        }
    }
    vector<string> a(code.begin() + 1, code.begin() + mid);
    vector<string> b(code.begin() + mid + 1, code.end() - 1);
    newnodes->left = parsehelper(a);
    newnodes->right = parsehelper(b);
    return newnodes;
}

void Evaluator::parse(vector<string> code)
{
    ExprTreeNode *left = new ExprTreeNode();
    left->type = "VAR";
    left->id = code[0];
    ExprTreeNode *root = new ExprTreeNode();
    root->id = code[1];
    root->type = "VAR";
    root->left = left;
    vector<string> newparsetree(code.begin() + 2, code.end());
    root->right = parsehelper(newparsetree);
    expr_trees.push_back(root);
}

UnlimitedRational *evalhelper(ExprTreeNode *rootnode, SymbolTable *symtable)
{
    if (rootnode == nullptr)
        return nullptr;
    else if (rootnode->type == "VAL")
    {
        return rootnode->val;
    }
    else if (rootnode->type == "VAR")
    {
        UnlimitedRational *result = symtable->search(rootnode->id);
        return result;
    }
    else
    {
        string op = rootnode->type;
        UnlimitedRational *leftresult = evalhelper(rootnode->left, symtable);
        UnlimitedRational *rightresult = evalhelper(rootnode->right, symtable);
        UnlimitedRational *result;
        if (op == "ADD")
        {
            result = UnlimitedRational::add(leftresult, rightresult);
        }
        else if (op == "SUB")
        {
            result = UnlimitedRational::sub(leftresult, rightresult);
        }
        else if (op == "MUL")
        {
            result = UnlimitedRational::mul(leftresult, rightresult);
        }
        else if (op == "DIV")
        {
            result = UnlimitedRational::div(leftresult, rightresult);
        }
        rootnode->evaluated_value = result;
        return result;
    }
    return nullptr;
}

void Evaluator::eval()
{
    ExprTreeNode *rootnode = expr_trees.back();
    UnlimitedRational *ans = evalhelper(rootnode->right, symtable);
    symtable->insert(rootnode->left->id, ans);
}
