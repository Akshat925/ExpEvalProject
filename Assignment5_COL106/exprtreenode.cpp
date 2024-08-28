/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

// Write your code below this line

ExprTreeNode::ExprTreeNode()
{
    type = "";
    num = -1;
    id = "";
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::ExprTreeNode(string t, int v)
{
    type = t;
    num = v;
    id = "";
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::~ExprTreeNode()
{
    delete left;
    delete right;
    num = -1;
}
