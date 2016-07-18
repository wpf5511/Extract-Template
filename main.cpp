#include <iostream>
#include <fstream>
#include <sstream>
#include "ZparTree.h"
#include "DepGraph.h"
using namespace std;

int main() {

    ifstream Zparfile("/Users/wangpf/Downloads/reference-4.txt",ios::in);

    string line;
    string lexeme,pos,parent_id,dependency;

    std::vector<ZparTree> zpars;

    ZparTree *zparTree=new ZparTree();
    while(getline(Zparfile,line)){
        if(line.empty()){
            zparTree->set_children_array();
            zpars.push_back(*zparTree);
            delete zparTree;
            zparTree = new ZparTree();
        }
        else{
            istringstream is(line);
            is>>lexeme>>pos>>parent_id>>dependency;

            zparTree->add_node(ZparNode(lexeme,pos,stoi(parent_id),dependency));
        }
    }

    cout<<zpars.size()<<endl;

    ifstream verb_file("/Users/wangpf/ClionProjects/Infer-from-tree/普通动词表");
    set<std::string>verb_dict;
    string word;
    while(getline(verb_file,word)){
        verb_dict.insert(word);
    }
    verb_file.close();


    zpars[0].preprocessing(verb_dict);

    //cout<<zpars[0].to_sentence();

    for(int i=0;i<805;i++){

        DepGraph depGraph;
        depGraph.Convert_from_zpar(zpars[i]);

        auto res_pattern = depGraph.extract_Template();

        cout<<res_pattern.size()<<endl;

        for(int j=0;j<res_pattern.size();j++){
            cout<<res_pattern[j]->args.size()<<endl;
        }

    }

    return 0;
}