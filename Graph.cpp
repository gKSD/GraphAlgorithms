//
// Created by sofia on 03.04.16.
//

#include <stdexcept>
#include <vector>
#include <algorithm>

#include "Graph.h"


// печать матриц, конкретная матрица для печати задается индентификатором identfier
void Graph::print_matrix(std::string const& identifier)
{
#define print_matrix_impl(m) \
{ \
    for (auto const &p : m) { \
        for (auto const &q : p) { \
            std::cout << q << " "; \
        } \
        std::cout << std::endl; \
    } \
} \


    std::cout << identifier << ": " << std::endl;
    if (identifier.compare("G1") == 0) print_matrix_impl(_incidence_matrix_G1)
    else if (identifier.compare("G2") == 0) print_matrix_impl(_incidence_matrix_G2)
    else if (identifier.compare("C1") == 0) print_matrix_impl(_cost_x_matrix)
    else if (identifier.compare("R1") == 0) print_matrix_impl(_adjacency_x_matrix)
    else
    {
        std::cout << "[DEBUG] unknown reference to incidence matrix" << std::endl;
        return;
    }

#undef print_matrix_impl
}

// *** получение образа и прообразов соответствующих вершин и ребер ***

// Г1x_i, возращает номера ребер, инцидентных данной вершине x_i
std::vector<int> Graph::get_image_G1(int x_i)
{
    std::vector<int> res;

    for (int j = 0; j < _vertices.size(); j++)
        if (_incidence_matrix_G1[x_i][j] == 1)
            res.push_back(j);

    return res;
}

// Г1u_j, возращает номера вершин, которым инцидентно ребро u_j
std::vector<int> Graph::get_inverse_image_G1(int u_j)
{
    std::vector<int> res;

    for (int i = 0; i < _vertices.size(); i++)
        if (_incidence_matrix_G1[i][u_j] == 1)
            res.push_back(i);

    return res;
}

// Г2u_j, возращает номера вершин, инцидентных данному ребру u_j
std::vector<int> Graph::get_image_G2(int u_j)
{
    std::vector<int> res;

    for (int i = 0; i < _edges.size(); i++)
        if (_incidence_matrix_G2[u_j][i] == 1)
            res.push_back(i);

    return res;
}

// Г2x_i, возращает номера ребер, которым инцидентна вершина x_i
std::vector<int> Graph::get_inverse_image_G2(int x_i)
{
    std::vector<int> res;

    for (int j = 0; j < _edges.size(); j++)
        if (_incidence_matrix_G2[j][x_i] == 1)
            res.push_back(j);

    return res;
}

// функция построения матрицы смежности x: 0 - если вершины не смежны, 1 - если они смежны
void Graph::build_adjacecny_x_matrix()
{
    if (_vertices.empty() || _edges.empty() || _incidence_matrix_G1.empty() || _incidence_matrix_G2.empty())
        throw std::runtime_error("[ERROR] not all Graph components have been set !");

    int vertices_size = _vertices.size();
    int edges_size = _edges.size();

    for (int i = 0; i < vertices_size; i++)
    {
        _adjacency_x_matrix.push_back({});
        for (int k = 0; k < vertices_size; k++)
        {
            std::vector<int> e; // ребра, инциндентные x_i и которым инцидентно x_k (их может быть несколько)
            for (int j = 0; j < edges_size; j++)
            {
                if (_incidence_matrix_G1[i][j] == 1 && _incidence_matrix_G2[j][k] == 1)
                    e.push_back(1);

            }

            _adjacency_x_matrix[i].push_back(( e.empty()? 0 : *(std::min_element(e.begin(), e.end())) ));
        }
    }

    print_matrix("R1");
}

// функция построения матрицы стоимости x: 0 - если вершины не смежны, вес ребра - если они смежны
void Graph::build_cost_x_matrix(bool min_cost) {
    if (_vertices.empty() || _edges.empty() || _incidence_matrix_G1.empty() || _incidence_matrix_G2.empty())
        throw std::runtime_error("[ERROR] not all Graph components have been set !");

    int vertices_size = _vertices.size();
    int edges_size = _edges.size();

    for (int i = 0; i < vertices_size; i++)
    {
        _cost_x_matrix.push_back({});
        for (int k = 0; k < vertices_size; k++)
        {
            std::vector<int> e; // ребра, инциндентные x_i и которым инцидентно x_k (их может быть несколько)
            for (int j = 0; j < edges_size; j++)
            {
                if (_incidence_matrix_G1[i][j] == 1 && _incidence_matrix_G2[j][k] == 1)
                    e.push_back(_edges[j]._weight);

            }

            _cost_x_matrix[i].push_back(( e.empty() ? 0 :
                                              ( min_cost ?
                                                *(std::min_element(e.begin(), e.end())) :
                                                *(std::max_element(e.begin(), e.end()))
                                              )
                                            ));
        }
    }

    print_matrix("C1");
}


#include "Graph.h"
