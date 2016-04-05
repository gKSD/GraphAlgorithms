//
// Created by sofia on 03.04.16.
//

#ifndef BRANCHANDEDGES_GRAPH_H
#define BRANCHANDEDGES_GRAPH_H


#include <vector>
#include <string>
#include <iostream>

//template < typename VerticeType, typename EdgeType>
class Graph
{
public:

    struct Edge
    {
        std::string _name;
        int _weight;
    };

private:
    std::vector<std::string> _vertices; // векор вершин // TODO: тоже задать в виде структуры
    std::vector<Edge> _edges; // вектор ребер с весами

    std::vector<std::vector<int>> _incidence_matrix_G1; // матрица инцидентности G1
    std::vector<std::vector<int>> _incidence_matrix_G2; // матрица инцидентности G2

    std::vector<std::vector<int>> _adjacency_x_matrix; // матрица смежности, 0 - если вершины не смежны, 1 - если вершины смежны
    std::vector<std::vector<int>> _cost_x_matrix; // матрица стоимости ( аналогична матрице смежности), 0 - если вершины не смежны, вес ребра (>0) - если вершины смежны

public:
    Graph() {}
    ~Graph() {}

    void interactive_init()  {/*TODO пользователь сам задает вводом данных*/}

    void static_init(std::vector<std::string> const& vertices,
                     std::vector<Edge> const& edges,
                     int n_vertices,
                     int n_edges,
                     std::vector<std::vector<int>> const& incidence_matrix_G1,
                     std::vector<std::vector<int>> const& incidence_matrix_G2)
    {
        _vertices = vertices;
        _edges = edges;
        _incidence_matrix_G1 = incidence_matrix_G1;
        _incidence_matrix_G2 = incidence_matrix_G2;


        print_matrix("G1");
        print_matrix("G2");
    }

    void build_adjacecny_x_matrix();

    void build_cost_x_matrix(bool min_cost = true);

    //дополнительные функции
    void print_matrix(std::string const& identifier);

    //getters
    std::vector<std::vector<int>> const& get_incidence_matrix_G1() { return _incidence_matrix_G1; }
    std::vector<std::vector<int>> const& get_incidence_matrix_G2() { return _incidence_matrix_G2; }
    int vertices_size () { return _vertices.size(); }
    int edges_size () { return _edges.size(); }
    std::vector<std::vector<int>> const& get_R1 () {return _adjacency_x_matrix;}
    std::vector<std::vector<int>> const& get_C1 () {return _cost_x_matrix;}

    // получение образов и прообразов вершин и ребер
    std::vector<int> get_image_G1(int x_i);
    std::vector<int> get_inverse_image_G1(int u_j);
    std::vector<int> get_image_G2(int u_j);
    std::vector<int> get_inverse_image_G2(int x_i);
};


#endif //BRANCHANDEDGES_GRAPH_H
