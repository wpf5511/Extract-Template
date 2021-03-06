//
// Created by 王鹏飞 on 16/6/23.
//

#ifndef INFER_FROM_TREE_ZPARTREE_H
#define INFER_FROM_TREE_ZPARTREE_H

#include <map>
#include <vector>
#include <set>
#include <string>

class ZparNode{
    public:
         int get_parent();
         std::string get_pos();
         std::string get_dependency();
         std::string get_lexeme();
         int get_id();


        ZparNode(std::string lexeme,std::string pos,int parent_id,std::string dependency);

        ZparNode(const ZparNode &node);


        int id;  //word position in the sentence
        int sentense_position;
        std::string lexeme;  //word
        std::string pos;   //pos tag
        int parent_id;
        std::string dependency;  //dependency relation
};


class ZparTree {
public:
    std::vector<ZparNode> nodes;
    std::map<int,std::vector<int>> children_array;
    int root_id;

    void add_node(ZparNode node);
    void add_node(ZparNode node,int sentence_position);
    void set_children_array();
    ZparNode& get_Node(int id);
    std::vector<int> get_children(int id);
    std::string to_sentence();

    void preprocessing(std::set<std::string>verb_dict);


};


#endif //INFER_FROM_TREE_ZPARTREE_H
