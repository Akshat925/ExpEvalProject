/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include"entry.h"

SymEntry::SymEntry(){
    key="";
    val=new UnlimitedRational(new UnlimitedInt("1"),new UnlimitedInt("1"));
    left=nullptr;
    right=nullptr;
}

SymEntry::~SymEntry(){
    delete val;
    if(left!=nullptr){
        delete left;
    }
    if(right!=nullptr){
        delete right;
    }
}

SymEntry::SymEntry(string k, UnlimitedRational* v){
    key=k;
    val=v;
    left=nullptr;
    right=nullptr;
}