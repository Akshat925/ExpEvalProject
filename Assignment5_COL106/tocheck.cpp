#include<iostream>
#include<vector>
#include <fstream>
using namespace std;
class SymNode {
public:
    string key;
    int height;
    int address=-1;
    
    SymNode* par;
    SymNode* left;
    SymNode* right;

    SymNode(){
        key="";
        height=1;
        par=NULL;
        left=NULL;
        right=NULL;
    }
    SymNode(string k){
        key=k;
        height=1;
        par=NULL;
        left=NULL;
        right=NULL;

    }

    SymNode* LeftLeftRotation(); // case 1
    SymNode* RightRightRotation(); // case 2
    SymNode* LeftRightRotation(); // case 3
    SymNode* RightLeftRotation(); // case 4

    ~SymNode(){

    }
    
};
class SymbolTable {
private:
    int size;
    SymNode* root;

public: 

    SymbolTable(){
        size=0;
        root=NULL;
    }
    void destructre(SymNode*root){
        if(root==NULL) return ;
        destructre(root->left);
        destructre(root->right);
        delete root;
    }
    ~SymbolTable(){
        destructre(root);
        
    }
    int height1(SymNode* &node){
        if(node==NULL) return 0;
        return node->height;
    }
    int getbalancefactor(SymNode* &n){
        if(n==NULL) return 0;
        else return (height1(n->left)-height1(n->right));
    }
    SymNode* rightRotate(SymNode*&node){
        SymNode*leftpart=node->left;
        SymNode*rightsubtree=leftpart->right;
        leftpart->right=node;
        node->left=rightsubtree;
        node->height=max(height1(node->left),height1(node->right))+1;
        leftpart->height=max(height1(leftpart->left),height1(leftpart->right))+1;
        return leftpart;
    }
    SymNode* leftRotate(SymNode*&node){
        cout<<2;
        SymNode*rightpart=node->right;
        SymNode*leftsubtree=rightpart->left;
        rightpart->left=node;
        node->right=leftsubtree;
        node->height=max(height1(node->left),height1(node->right))+1;
        rightpart->height=max(height1(rightpart->left),height1(rightpart->right))+1;
        return rightpart;
    }
    
    SymNode* insertnode(SymNode* &node,string k){
        if(node==NULL){
            SymNode*root=new SymNode(k);
            return root;
        }
        if(k<node->key){
            node->left=insertnode(node->left,k);
        }
        else if(k>node->key){
            node->right=insertnode(node->right,k);
        }
        else return node;

        node->height = 1 + max(height1(node->left),height1(node->right));
        int bf = getbalancefactor(node);

        if(bf>1){
            if(k<node->left->key){
                return rightRotate(node);
            }
            else if(k>node->left->key){
                node->left=leftRotate(node->left);
                return rightRotate(node);
            }
        }
        if(bf<-1){
            if (k>node->right->key) {
                return leftRotate(node);
            } 
            else if (k<node->right->key) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
    }
    // Insert a key in the symbol table, there is no value now
    void insert(string k){
        root=insertnode(root,k);
        size++;
    }
    SymNode *nodeWithMimumValue(SymNode *node) {
  SymNode *current = node;
  while (current->left != NULL)
    current = current->left;
  return current;
}

    // Remove a key (and it's memory address) in the symbol table
    SymNode *deleteNode(SymNode *root, string key) {
  // Find the node and delete it
  if (root == NULL)
    return root;
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    if ((root->left == NULL) ||(root->right == NULL)) {
      SymNode *temp = root->left ? root->left : root->right;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } 
      else
    //   delete temp;
        *root = *temp;
      free(temp);
    } 
    else {
      SymNode *temp = nodeWithMimumValue(root->right);
      root->key = temp->key;
      root->right = deleteNode(root->right,temp->key);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height1(root->left),
               height1(root->right));
  int balanceFactor = getbalancefactor(root);
  if (balanceFactor > 1) {
    if (getbalancefactor(root->left) >= 0) {
      return rightRotate(root);
    } else {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
  }
  if (balanceFactor < -1) {
    if (getbalancefactor(root->right) <= 0) {
      return leftRotate(root);
    } else {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
  }
  return root;
}
    void remove(string k){
        SymNode*node= deleteNode(root,k);
        if(node!=NULL){
            size--;
        }

    }
    int search(string k){
        SymNode* temp=root;
        while(temp!=NULL){
            if(k>temp->key) temp=temp->right;
            else if(k<temp->key) temp=temp->left;
            else{
                return temp->address;
            }
        }
        return 0;

    }

    void assign_address(string k,int idx){
        SymNode* temp=root;
        while(temp!=NULL){
            if(k>temp->key) temp=temp->right;
            else if(k<temp->key) temp=temp->left;
            else{
                temp->address=idx;
                break;
            }
        }

    }

    int get_size(){
        return size;
    }

    SymNode* get_root(){
        return root;
    }

};
class ExprTreeNode {
public:
    string type; // Can be "ADD", "SUB", "MUL", "DIV", "VAL", "DEL", "RET" or "VAR" (for variable)

    // Stores the variable name if type is "VAR"
    string id;
    //Store the value of the number if type is "VAL"
    int num;

    ExprTreeNode* left=NULL;
    ExprTreeNode* right=NULL;

    ExprTreeNode(){
        type="";
        left=NULL;
        right=NULL;
        id="";
        num=-7;
    }
    ExprTreeNode(string t,int v){
        type=t;
        left=NULL;
        right=NULL;
        id="";
        num=v;
    }

    ~ExprTreeNode(){
        delete left;
        delete right;
    }
};
class Parser {
public:
    vector<ExprTreeNode*> expr_trees;
    SymbolTable* symtable;
    int last_deleted;

    Parser(){
        symtable=new SymbolTable();
    }
    
    vector<string> subvec(vector<string> v,int j,int l){//helper function 
        vector<string> ans;
        for(int i=j;i<=l;i++) ans.push_back(v[i]);
        return ans;
    }
    ExprTreeNode* parse_helper(vector<string> code,SymbolTable*s){// helper function
        if(code.size()==1){
            if(!isdigit(code[0][0])){
                ExprTreeNode* vari=new ExprTreeNode("VAR",0);
                vari->type="VAR";
                vari->id=code[0];
                return vari;
            }
            else{
                int value=stoi(code[0]);
                ExprTreeNode* node=new ExprTreeNode("VAL",value);
                node->type="VAL";
                node->num=value;
                return node;
            }
        }
        int c=0;
        int k=-1;
        ExprTreeNode* op=new ExprTreeNode("VAR",0);
        for(int i=0;i<code.size();i++){
            k++;
            if(code[i]=="(") c++;
            if(code[i]==")") c--;
            if(code[i]=="/" ||code[i]=="*" || code[i]=="-" || code[i]=="%" || code[i]=="+" ){
                if(c==1){
                    
                    if(code[i]=="/"){
                        op->type="DIV";
                        break;
                    }
                    if(code[i]=="+"){
                        op->type="ADD";
                        break;
                    }
                    if(code[i]=="-"){ 
                        op->type="SUB";
                        break;
                    }
                    if(code[i]=="*"){
                        op->type="MUL";
                        break;
                    }
                    
                }
            }
        }
        op->left=parse_helper(subvec(code,1,k-1),s);
        op->right=parse_helper(subvec(code,k+1,code.size()-2),s);
        return op;
        
    }
    void parse(vector<string> expression){
        ExprTreeNode* node;
        if(expression[0]=="del"){
            node=new ExprTreeNode("DEL",0);
            node->type="DEL";
        }
        else if(expression[0]=="ret"){
            node=new ExprTreeNode("RET",0);
            node->type="RET";
        }
        else{
            node=new ExprTreeNode("VAR",0);
            node->type="VAR";
            node->id=expression[0];
            symtable->insert(node->id);
        }
        ExprTreeNode* root=new ExprTreeNode("VAR",0);
        root->type="VAR";
        root->id=expression[1];
        root->left=node;
        root->right=parse_helper(subvec(expression,2,expression.size()-1),symtable);
        expr_trees.push_back(root);
    }

    ~Parser(){
        expr_trees.clear();
    }
};
class EPPCompiler{
  private:
    Parser targ;
    int memory_size;
    string output_file;
    vector<int> mem_loc;
//   MinHeap least_mem_loc;

  public:

  EPPCompiler(){
    
  }
  EPPCompiler(string out_file,int mem_limit){
    memory_size=mem_limit;
    output_file=out_file;
    for(int i=0;i<memory_size;i++){
        mem_loc.push_back(-1);
    }
  }

  
  void compile(vector<vector<string>> code){
    for(int i=0;i<code.size();i++){
        targ.parse(code[i]);

        if(targ.expr_trees[i]->left->type=="VAR" ){
            int j=0;
            for(j;j<memory_size;j++){
                
                if(mem_loc[j]==-1) break;
            }
            cout<<"z="<<targ.symtable->search("z")<<endl;
            targ.symtable->assign_address(targ.expr_trees[i]->left->id,j);
            cout<<"z="<<targ.symtable->search("z")<<endl;
            cout<<targ.expr_trees[i]->left->id<<"="<<targ.symtable->search(targ.expr_trees[i]->left->id)<<endl;
            mem_loc[j]=1;
            
            write_to_file(generate_targ_commands());
            // memory_size--;
        }
        else if(targ.expr_trees[i]->left->type=="DEL"){
            write_to_file(generate_targ_commands());
            mem_loc[targ.symtable->search(targ.expr_trees[i]->right->id)]=-1;
            
            targ.last_deleted=targ.symtable->search(targ.expr_trees[i]->right->id);
            targ.symtable->remove(targ.expr_trees[i]->right->id);
            cout<<"id="<<targ.expr_trees[i]->right->id<<endl;
            cout<<"size="<<targ.symtable->get_root()->key<<endl;
        }
        else if(targ.expr_trees[i]->left->type=="RET"){
            write_to_file(generate_targ_commands());
        }
        
        
    }
}
  void generate_commands(ExprTreeNode*&root,vector<string> &v,Parser &p){
    if(root==NULL) return;
    generate_commands(root->right,v,p);
    generate_commands(root->left,v,p);
    
    if(root->type=="VAL"){
        string commd="PUSH "+to_string(root->num);
        v.push_back(commd);
    }
    else if(root->type=="VAR"){
        int k=p.symtable->search(root->id);
        string s1="PUSH ";
        string s2="mem[";
        string s3=to_string(k)+"]";
        string commd=s1+s2+s3;
        v.push_back(commd);
    }
    
    
    
    else if(root->type=="ADD") v.push_back("ADD");
    else if(root->type=="MUL") v.push_back("MUL");
    
    else if(root->type=="SUB") v.push_back("SUB");
    
    else if(root->type=="DIV") v.push_back("DIV");
    
}
  vector<string> generate_targ_commands(){
    // cout<<targ.symtable->get_root()<<endl;
    vector<string> commands;
    int siz=targ.expr_trees.size()-1;
    
    if(targ.expr_trees[siz]->left->type=="VAR"){
        generate_commands(targ.expr_trees[siz]->right,commands,targ);
        string s1=" POP";
        string s2="mem[";
        string s3=to_string(targ.symtable->search(targ.expr_trees[siz]->left->id))+"]";
        // cout<<"h="<<targ.symtable->search(targ.expr_trees[siz]->left->id)<<endl;
        string s4= " =";
        string commd =s2+s3+s4+s1;
        commands.push_back(commd);
    }
    else if(targ.expr_trees[siz]->left->type=="DEL"){
        string s1="DEL = ";
        string s2="mem[";
        string s3=to_string(targ.symtable->search(targ.expr_trees[siz]->right->id))+"]";
        string comd=s1+s2+s3;
        commands.push_back(comd);
    }
    else if(targ.expr_trees[siz]->left->type=="RET"){
        generate_commands(targ.expr_trees[siz]->right,commands,targ);
        string commd="RET = POP";
        commands.push_back(commd);
    }
     
    // for(int i=0;i<commands.size();i++){
    //     cout<<commands[i]<<endl;
    // }
    
    return commands;
  }
  void write_to_file(vector<string> commands){
        std::ofstream outputFile;
        outputFile.open(output_file,std::ios::out | std::ios::app);
        
        for(string s:commands){
            outputFile<<s<<endl;
        }
        outputFile.close();
  }
  
  ~EPPCompiler(){
        // delete targ;
  }
};
int main(){
    
    Parser *p=new Parser();
    vector<string> x={"w",":=","(","5","+","(","z","/","2",")",")"};
    vector<string> x1={"x",":=","3"};
    vector<string> x2={"y",":=","5"};
    vector<string> delll={"del",":=","x"};
    vector<string> x3={"z",":=","7"};
    vector<string> y={"y",":=","(","1","+","2",")"};
    vector<string> z={"z",":=","(","x","-","y",")"};
    vector<string> w={"w",":=","(","(","z","*","z",")","-","1000",")"};
    vector<string> dd={"ret",":=","w"};
    vector<string> ret={"ret",":=","(","w","+","7",")"};
    // vector<string> r={"ret",":=","1"};
    vector<string> v1={"a",":=","(","(","2","*","4",")","+","10",")"};
    vector<string> v2={"b",":=","(","3","*","4",")"};
    vector<string> d={"e",":=","3"};
    vector<string> v3={"c",":=","(","(","(","4","/","2",")","*","4",")","+","(","8","+","4",")",")"};
    vector<string> del={"del",":=","y"};
    vector<string> del2={"del",":=","e"};
    vector<string> v4={"ret",":=","(","(","a","+","(","b","*","6",")",")","+","6",")"};
    vector<string> ans;
    vector<vector<string>> v5={x1,x2,x3,delll,del,x,dd};
    // EPPCompiler *compiler=new EPPCompiler("vipul.txt",10);
    // compiler->compile(v5);
    
    // ans=compiler->generate_targ_commands();
    // SymNode*root=new SymNode("k");
    // SymNode*one=new SymNode("k");
    // SymNode*two=new SymNode("k");
    // SymNode*three=new SymNode("k");
    // SymbolTable s;
    // root->right=one;
    // one->right=two;
    // two->right=three;
    // cout<<s.height1(root);
    // for(int i=0;i<ans.size();i++){
    //     cout<<ans[i]<<endl;
    // }
    // p->parse(del);
    // p->parse(v2);
    // delete p;
    // cout<<p->expr_trees[0]->right->id;

    // SymNode* one=new SymNode("A");
    // SymNode* two=new SymNode("B");
    // SymNode* three=new SymNode("C");
    // SymNode* five=new SymNode("E");
    // SymNode* four=new SymNode("D");
    SymbolTable s;
    s.insert("a");
    s.insert("b");
    s.insert("c");
    s.insert("d");
    s.insert("e");
    // s.insert("f");
    // s.insert("g");
    // s.insert("h");
    // s.insert("i");
    SymNode* one=s.get_root();
    cout<<one->right->left->key;
    // cout<<s.get_size();
}