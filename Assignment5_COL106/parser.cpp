/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

// Write your code below this line

Parser::Parser()
{
    symtable = new SymbolTable();
}

ExprTreeNode *parsehelper(vector<string> code)
{
    if (code.size() == 1)
    {
        if (!isdigit(code[0][0]))
        {
            ExprTreeNode *variable = new ExprTreeNode("VAR",-1);
            variable->id = code[0];
            return variable;
        }
        else
        {
            int a = stoi(code[0]);
            ExprTreeNode *node = new ExprTreeNode("VAL", a);
            return node;
        }
    }
    int count = 0;
    int mid = -1;
    ExprTreeNode *newnodes = new ExprTreeNode("VAR", -1);
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
    }
    vector<string> a(code.begin() + 1, code.begin() + mid);
    vector<string> b(code.begin() + mid + 1, code.end() - 1);
    newnodes->left = parsehelper(a);
    newnodes->right = parsehelper(b);
    return newnodes;
}

void Parser::parse(vector<string> expression)
{
    if (expression[0] == "del" && expression[1] == ":=")
    {
        ExprTreeNode *root = new ExprTreeNode(":=", -1);
        root->left = new ExprTreeNode("DEL", -1);
        vector<string> newParseTree(expression.begin() + 2, expression.end());
        root->right = parsehelper(newParseTree);
        expr_trees.push_back(root);
    }
    else if (expression[0] == "ret" && expression[1] == ":=")
    {
        ExprTreeNode *root = new ExprTreeNode(":=", -1);
        root->left = new ExprTreeNode("RET", -1);
        vector<string> newParseTree(expression.begin() + 2, expression.end());
        root->right = parsehelper(newParseTree);
        expr_trees.push_back(root);
    }
    else
    {
        ExprTreeNode *root = new ExprTreeNode();
        root->type = ":=";
        root->id = expression[1];
        ExprTreeNode *leftnode = new ExprTreeNode();
        leftnode->type = "VAR";
        leftnode->id = expression[0];
        symtable->insert(leftnode->id);
        vector<string> newParseTree(expression.begin() + 2, expression.end());
        root->left = leftnode;
        root->right = parsehelper(newParseTree);
        expr_trees.push_back(root);
    }
}

Parser::~Parser()
{
    expr_trees.clear();
}