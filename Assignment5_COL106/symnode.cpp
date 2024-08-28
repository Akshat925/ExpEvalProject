/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    key="";
    height=0;
    address=-1;
    par=nullptr;
    left=nullptr;
    right=nullptr;
}

SymNode::SymNode(string k){
    key=k;
    height=0;
    address=-1;
    par=nullptr;
    left=nullptr;
    right=nullptr;
}

SymNode* SymNode::LeftLeftRotation(){
    
}

SymNode* SymNode::RightRightRotation(){
    
}

SymNode* SymNode::LeftRightRotation(){
    
}

SymNode* SymNode::RightLeftRotation(){
    
}

SymNode::~SymNode(){
    par=nullptr;
    if(left!=nullptr){
        delete left;
    }
    if(right!=nullptr){
        delete right;
    }
}