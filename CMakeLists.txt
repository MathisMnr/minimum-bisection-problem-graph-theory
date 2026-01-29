cmake_minimum_required(VERSION 3.18)
project(graph_project)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        graph_project
        main.cpp
        src/model/Graph_class/Graph.cpp
        src/model/Graph_class/Vertex.cpp
        src/method/tabu_search/tabu_search.cpp
        src/method/local_search/local_search.cpp
        src/method/exact/exact.cpp
        src/method/constructive/constructive.cpp


)
