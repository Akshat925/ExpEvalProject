#include "eppcompiler.h"

EPPCompiler::EPPCompiler()
{
}

EPPCompiler::EPPCompiler(string out_file, int mem_limit)
{
    output_file = out_file;
    memory_size = mem_limit;
    for (int i = 0; i < memory_size; i++)
    {
        mem_loc.push_back(-1);
    }
}

void EPPCompiler::compile(vector<vector<string>> code)
{
    int i=0;
    while(i<code.size()){
        targ.parse(code[i]);
        if(targ.expr_trees[i]->left->type=="VAR"){
            int j=0;
            for(j;j<memory_size;j++){
                if(mem_loc[j]==-1){
                    mem_loc[j]=j;
                    break;
                }
            }
            targ.symtable->assign_address(targ.expr_trees[i]->left->id,j);
            write_to_file(generate_targ_commands());
        }
        else if(targ.expr_trees[i]->left->type=="DEL"){
            write_to_file(generate_targ_commands());
            int m = targ.symtable->search(targ.expr_trees[i]->right->id);
            mem_loc[m]=-1;
        }
        else if(targ.expr_trees[i]->left->type=="RET"){
            write_to_file(generate_targ_commands());
        }
        i++;
    }
}

void generateC(ExprTreeNode *&root, vector<string> &commandhelper, Parser &parz)
{
    if (root == nullptr)
    {
        return;
    }
    if (root->right)
    {
        generateC(root->right, commandhelper, parz);
    }
    if (root->left)
    {
        generateC(root->left, commandhelper, parz);
    }
    if (root->type == "VAL")
    {
        string a = "PUSH " + to_string(root->num);
        commandhelper.push_back(a);
    }
    else if (root->type == "VAR")
    {
        int ap = parz.symtable->search(root->id);
        string a = "PUSH mem[" + to_string(ap) + "]";
        commandhelper.push_back(a);
    }
    else if (root->type == "ADD")
    {
        string a = "ADD";
        commandhelper.push_back(a);
    }
    else if (root->type == "SUB")
    {
        string a = "SUB";
        commandhelper.push_back(a);
    }
    else if (root->type == "MUL")
    {
        string a = "MUL";
        commandhelper.push_back(a);
    }
    else if (root->type == "DIV")
    {
        string a = "DIV";
        commandhelper.push_back(a);
    }
}

vector<string> EPPCompiler::generate_targ_commands()
{
    vector<string> commands;
    ExprTreeNode *lastExpr = targ.expr_trees.back();
    if (lastExpr->left->type == "DEL")
    {
        int ap = targ.symtable->search(lastExpr->right->id);
        string a = "DEL = mem[" + to_string(ap) + "]";
        commands.push_back(a);
    }
    else
    {
        generateC(lastExpr->right , commands, targ);
        if (lastExpr->left->type == "VAR")
        {
            int ap = targ.symtable->search(lastExpr->left->id);
            string a = "mem[" + to_string(ap) + "] = POP";
            commands.push_back(a);
        }
        else if (lastExpr->left->type == "RET")
        {
            string a = "RET = POP";
            commands.push_back(a);
        }
    }
    return commands;
}

void EPPCompiler::write_to_file(vector<string> commands)
{
    std::ofstream outputFile;
        outputFile.open(output_file,std::ios::out | std::ios::app);
        for(string outputss:commands){
            outputFile<<outputss<<endl;
        }
        outputFile.close();
}

EPPCompiler::~EPPCompiler()
{
}