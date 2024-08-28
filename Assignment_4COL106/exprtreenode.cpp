/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode()
{
    UnlimitedInt *a = new UnlimitedInt("1");
    UnlimitedRational *b = new UnlimitedRational(a, a);
    type = "";
    val = b;
    evaluated_value = val;
    id = "";
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt *v)
{
    type = t;
    val = new UnlimitedRational(v, new UnlimitedInt("1"));
    evaluated_value = val;
    id = "";
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational *v)
{
    type = t;
    val = v;
    evaluated_value = v;
    id = "";
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::~ExprTreeNode()
{
    delete left;
    delete right;
    delete val;
    delete evaluated_value;
}
