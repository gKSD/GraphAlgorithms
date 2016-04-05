#include <iostream>
#include <vector>
#include <string>
#include <locale>

#include "Graph.h"
#include "BranchAndEdges.h"
#include "DijkstraAlgorithm.h"

int main()
{
    setlocale( LC_ALL,"Russian" );

    // задаем входные данные

    // матрица инцидентности Г1
    std::vector< std::vector<int> > G1 = {{1, 1, 1, 0, 0, 0, 0, 0, 0},
                                          {0, 0, 0, 1, 1, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 1, 0, 0},
                                          {0, 0, 0, 0, 0, 1, 0, 1, 0},
                                          {0, 0, 0, 0, 0, 0, 0, 0, 1},
                                          {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    // матрица инцидентности Г2
    std::vector< std::vector<int> >  G2 = {{0, 1, 0, 0, 0, 0},
                                           {0, 0, 1, 0, 0, 0},
                                           {0, 0, 0, 1, 0, 0},
                                           {0, 0, 0, 1, 0, 0},
                                           {0, 0, 0, 0, 1, 0},
                                           {0, 0, 0, 0, 1, 0},
                                           {0, 0, 0, 0, 0, 1},
                                           {0, 0, 0, 0, 0, 1},
                                           {0, 0, 0, 0, 0, 1}};

    // вектор, задающий вершины
    // TODO сделать стурктуру как для ребер   !!!!!
    std::vector<std::string> vertices = {"x1", "x2", "x3", "x4", "x5", "x6"};

    // вектор, задающий ребра и их веса
    std::vector<Graph::Edge> edges = {{"u1", 2}, {"u2", 4}, {"u3", 8}, {"u4",4} , {"u5",5}, {"u6", 6}, {"u7", 7}, {"u8", 4}, {"u9", 2}};

    // создам объект Графа
    Graph graph;
    //инициализация графа
    graph.static_init(vertices, edges, vertices.size(), edges.size(), G1, G2);
    // построение матрицы стоимости по заданным вершинам, ребра, матрицам Г1 и Г2
    graph.build_cost_x_matrix();

    std::cout << std::endl;
    std::cout <<"************************************МЕТОД ВЕТВЕЙ И ГРАНИЦ ****************************************** " <<std::endl;
    // инициализация алгоритма "Ветвей и границ"
    BranchAndEdges branch_and_edges;
    // запуск алгоритма
    branch_and_edges.run(0, 5, vertices.size(), graph.get_C1());

    std::cout << std::endl;
    std::cout <<"************************************МЕТОД ДЕЙКСТРЫ ****************************************** " << std::endl;
    // инициализация алгоритма "Дейкстры"
    DijkstraAlgorithm dijkstraAlgorithm;
    // запуск алгоритма
    dijkstraAlgorithm.run(0, 5, vertices.size(), graph.get_C1());

    return 0;
}