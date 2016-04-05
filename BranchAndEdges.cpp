//
// Created by sofia on 04.04.16.
//

#include <list>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "BranchAndEdges.h"


void BranchAndEdges::run (int start_vertice, int end_vertice, int n_vertices, std::vector<std::vector<int>> const& C1)
// TODO: сделать возращаемое значение - как массив оптимальных путей
{
    if (n_vertices == 0 || C1.empty() || start_vertice > n_vertices || end_vertice > n_vertices)
        return;

    int total_number = 0;

    // список путей
    // в начальный момент времени 1 вершина - start_vertice
    std::list<Path> paths = {
                                { { {total_number++, start_vertice} }, 0}
                           };


    // итератор, используемый для перемещения по имеющимся путям
    std::list<Path>::iterator cit;

    int F_op = -1; // F_оп
    int has_decision = 0; // 0 => пока не нашли ни одного полного решения TODO: убрать этот флаг

    while (1)
    {
        cit = paths.begin(); // устанвливаем итератор на начало списка путей

        // поиск пути, соответствующего минимальное значение целевой функции F_н
        int min = cit->F_n;
        for (std::list<Path>::iterator cit1 = cit; cit1 != paths.end(); cit1++)
        {
            if (cit1->F_n < min) {
                // найден  путь с F_н меньшей, чем уже были рассмотрены => сохраняем данный путь как минимальный для дальнейшего рассмотрения)
                min = cit1->F_n;
                cit = cit1;
            }
        }

        std::stringstream ss;
        ss << " >>> Рассматриваем узел: №" << cit->path.back().number_in_tree << " [" << cit->path.back().vertice + 1 << "]";
        ss << ", F_н: " << cit->F_n << " (минимальное)";
        ss << ", огибающая => (№ узла [номер вершины])";
        for (std::list<Path>::iterator p = paths.begin(); p != paths.end(); p++)
        {
            if (p != cit)
                ss << "№" << p->path.back().number_in_tree << "[" << p->path.back().vertice + 1 << "]; ";
        }
        std::cout << ss.str() << std::endl;

        if (cit != paths.end()) //just in case
        {
            int current_vertice = cit->path.back().vertice; // получение индекса текущей вершины

            int inserted = 0;

            // цикл по всем вершинам, для определения смежных вершин данной вершине current_vertice
            for (int i = 0; i < n_vertices; i++)
            {
                if (C1[current_vertice][i] > 0)
                {
                    // в матрице стоимости С1 найдена смежная вершина
                    // включаем эту вершину в новый путь
                    Path new_path = *cit;

                    new_path.path.push_back({total_number++, i});
                    new_path.F_n += C1[current_vertice][i]; // пересчет занчения целевой функции с учетом новой вершины

                    if (i == end_vertice) //нашли решение
                    {
                        // это решение - конечное решение, смежная вершина - целевая вершина

                        std::cout << "Решение найдено: ";
                        std::stringstream ss;
                        for (auto &q : new_path.path)
                        {
                            if (!ss.str().empty())
                                ss << " -> ";
                            ss << "№"<<q.number_in_tree << "[" << q.vertice + 1 << "]";
                        }
                        ss << ". F_n: " << new_path.F_n;
                        std::cout << ss.str() << std::endl;

                        if (!has_decision)
                        {
                            // это первое найденное решение, сохраняем F_оп как первое оптимальное значение

                            has_decision = 1;
                            F_op = new_path.F_n;

                            std::cout << "первое решение, задание F_оп: " << F_op << std::endl;
                        }
                        else if (new_path.F_n < F_op)
                        {
                            // нашли решение, и оно является более оптимальным, чем предыдущее конечное решение
                            // смена F_оп
                            F_op = new_path.F_n;
                            std::cout << "Решение более оптимальное, смена F_оп => " << F_op << std::endl;
                        }
                        std::cout << "Текущее F_оп => " << F_op << std::endl;
                    }

                    paths.insert(cit, new_path);

                    if (!inserted) inserted = 1;

                }

            }
            if (inserted == 1)
                paths.erase(cit);
        }

        if (has_decision)
        {
            // отсечение решений
            // отсечение можно, только когда есть F_оп (то есть получено хотя бы одно конечное решение)
            std::cout << " --- Отсечение неоптимальных решений ---" << std::endl;

            std::list<Path>::iterator p = paths.begin();
            std::list<Path>::iterator next;

            int counter = 0; // for logs

            while(p != paths.end())
            {
                if (p->F_n > F_op)
                {
                    counter++;
                    std::cout << "Отсечение решения: F_н: " << p->F_n << ", вершина: " << p->path.back().number_in_tree << std::endl;
                    next = p;
                    next++;
                    paths.erase(p);
                    p = next;
                }
                else p++;
            }

            if (counter == 0)
                std::cout << "Ни одного решения для отсечения не найдено!" << std::endl;
            std::cout << " ---  --- " << std::endl;
        }

        // проверка, что оптимальное решение найдено (ну или их несколько с одинаковой стоимостью)
        // выполняется проверка, что среди путей - все пути:
        // 1. представляют собой конечное решение
        // 2. все решение == F_oп - это обеспечивается отсечением неоптимальных решений выше
        if (has_decision)
        {
            int check = 1;
            for (auto &p : paths)
                if (p.path.back().vertice != end_vertice) {
                    check = 0;
                    break;
                }
            // вывод оптимальных решений, завершение алгоримта
            if (check) {
                std::cout << std::endl << "РЕШЕНИЕ НАЙДЕНО " << std::endl;
                for (auto &p : paths) {
                    std::stringstream ss;
                    for (auto &q : p.path) {
                        if (!ss.str().empty())
                            ss << " -> ";
                        ss << "№" << q.number_in_tree << "[" << q.vertice + 1 << "]";
                    }
                    ss << ". F_n (F_op): " << p.F_n;
                    std::cout << "Оптимальное решение: (№ узла [номер вершины]) " << ss.str() << std::endl;
                }
                break; // выходим из прогарммы
            }
        }
    }
}