//
// Created by sofia on 04.04.16.
//

#ifndef BRANCHANDEDGES_BRANCHANDEDGES_H
#define BRANCHANDEDGES_BRANCHANDEDGES_H


#include <set>
#include <vector>

class BranchAndEdges {

    struct TreeNode
    {
        int number_in_tree;
        int vertice;
    };

    struct Path
    {
        std::vector<TreeNode> path;
        int F_n;
    };

public:
    void run(int start_vertice, int end_vertice, int n_vertices,  std::vector<std::vector<int>> const& C1);
    // C1 - матрица стоимости (матрица смежности с весами)
};


#endif //BRANCHANDEDGES_BRANCHANDEDGES_H
