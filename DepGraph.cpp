//
// Created by 王鹏飞 on 16/7/18.
//

#include "DepGraph.h"
#include <iostream>

void DepGraph::CreateVertexes(ZparTree ztree) {

    int ztree_size = ztree.nodes.size();

    VertexNum = ztree_size;

    adjList = new Vertex[VertexNum];  //以防添加节点的情况

    for(int i=0;i<ztree.nodes.size();i++){

        ZparNode znode = ztree.get_Node(i);

        adjList[i] = Vertex(znode);
    }
}

void DepGraph::Convert_from_zpar(ZparTree ztree) {

    ZparNode root_node = ztree.get_Node(ztree.root_id);

    CreateVertexes(ztree);

    ProcessDependencyNode(root_node,ztree);
}

void DepGraph::ProcessDependencyNode(ZparNode znode, ZparTree ztree) {

    std::vector<int> children_id = ztree.get_children(znode.id);

    for (int i = 0; i < children_id.size(); i++){

        int child_id = children_id[i];

        ZparNode child_node = ztree.get_Node(child_id);

        std::string bet_dep = child_node.dependency;

        add_DepEdge(znode,child_node,bet_dep);

        ProcessDependencyNode(child_node,ztree);

    }
}

void DepGraph::add_DepEdge(ZparNode from, ZparNode to,std::string Dep_relation) {

    Edge *dep_edge= new Edge(to.id,Dep_relation);
    Edge *r_dep_edge = new Edge(from.id,"");

    Vertex &from_vertex = adjList[from.id];  //parent vertex
    Vertex &to_vertex = adjList[to.id];

    //添加dependency边
    dep_edge->next=from_vertex.first_edge;
    from_vertex.first_edge = dep_edge;

    //添加逆边
    r_dep_edge->next=to_vertex.first_edge;
    to_vertex.first_edge = r_dep_edge;

}

void DepGraph::dfs(int start,int previous, int *visited, Pattern *extract_pattern) {

    auto vertex = adjList[start];

    visited[start] = 1;

    if(is_end(start)){

        for(auto ptr=vertex.first_edge;ptr!= nullptr;ptr=ptr->next){

            //对于arg节点  只保留一条边
            if(ptr->adjvex==previous){
                auto end_vertex = Vertex(vertex,ptr);
                extract_pattern->args.insert(end_vertex);
            }
        }
        //是arg节点的话  访问后再置为false
        visited[start]=0;
    }
    else{

        extract_pattern->predicates.insert(vertex);
        for(auto edge_ptr = vertex.first_edge;edge_ptr!= nullptr; edge_ptr=edge_ptr->next){

            if(visited[edge_ptr->adjvex] == 0){
                dfs(edge_ptr->adjvex,start,visited, extract_pattern);
            }

        }

    }

}



std::vector<Pattern*> DepGraph::extract_Template() {

    int *visited = new int[VertexNum];

    std::vector<Pattern*> res_pattern;
    for(int i=0;i<VertexNum;i++){
        visited[i]=0;
    }

    for(int i=0;i<VertexNum;i++){
        if(visited[i] ==0&&!is_end(i)) //找一个没被访问过,并且不是arg的开始遍历
        {
            Pattern* new_pattern= new Pattern();
            dfs(i, -1,visited, new_pattern);  //起始点的previous置为-1
            res_pattern.push_back(new_pattern);
            //std::cout<<"hello"<<std::endl;
        }
    }

    return res_pattern;
}

bool DepGraph::is_end(int nodeid) {

    auto vertex = adjList[nodeid];

    auto pos = vertex.pos;
    if(pos=="NN"||pos=="NR"||pos=="NT"){
        return true;
    }else{
        return false;
    }
}