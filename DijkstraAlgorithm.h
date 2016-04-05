//
// Created by sofia on 04.04.16.
//

#ifndef BRANCHANDEDGES_DIJKSTRAALGORITHM_H
#define BRANCHANDEDGES_DIJKSTRAALGORITHM_H


#include <vector>

class DijkstraAlgorithm {

    // локальная структура узла в дереве решений
    struct TreeNode
    {
        int number_in_tree;
        int vertice;
    };

    // локальная структура, хранящая пути
    struct Path
    {
        std::vector<TreeNode> path;
        int F_n;
    };

public:
    void run(int start_vertice, int end_vertice, int n_vertices, std::vector<std::vector<int>> const& C1);
};


#endif //BRANCHANDEDGES_DIJKSTRAALGORITHM_H
