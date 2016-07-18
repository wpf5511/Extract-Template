//
// Created by 王鹏飞 on 16/7/18.
//

#ifndef PATTERNARG_DEPGRAPH_H
#define PATTERNARG_DEPGRAPH_H

#include "ZparTree.h"
#include <vector>


struct  Edge{
    int adjvex;
    std::string Dep_relation;
    Edge* next;
    Edge(int target,std::string dependency){
        this->adjvex = target;
        this->Dep_relation = dependency;
    }
};



struct  Vertex{

    int id;
    int sentence_position;
    std::string lexeme;
    std::string pos;

    Edge * first_edge;

    Vertex(ZparNode znode){
        this->id  = znode.id;
        this->sentence_position = znode.sentense_position;
        this->lexeme = znode.lexeme;
        this->pos = znode.pos;
        this->first_edge= nullptr;
    }

    Vertex(Vertex other,Edge *first_edge){
        this->id  = other.id;
        this->sentence_position = other.sentence_position;
        this->lexeme = other.lexeme;
        this->pos = other.pos;
        this->first_edge= first_edge;
    }

    Vertex(){
        id = -1;
        first_edge = nullptr;
    }
    bool operator <(const Vertex& other)const{
        if(this->sentence_position!=other.sentence_position){
            return this->sentence_position<other.sentence_position;
        }else{
            return this->id>other.id;
        }
    }
};

class Pattern{
public:
    std::set<Vertex> predicates;
    std::set<Vertex> args;
};



class DepGraph {
public:
    void Convert_from_zpar(ZparTree ztree);
    void CreateVertexes(ZparTree ztree);
    void ProcessDependencyNode(ZparNode znode,ZparTree ztree);
    void add_DepEdge(ZparNode from,ZparNode to,std::string relation);
    bool is_end(int nodeid);
    void dfs(int start,int previous,int *visited,Pattern* extract_pattern);
    std::vector<Pattern*> extract_Template();
private:
    Vertex* adjList;
    int VertexNum;
};



#endif //PATTERNARG_DEPGRAPH_H
