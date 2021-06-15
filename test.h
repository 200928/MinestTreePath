#ifndef _TEST_H
#define _TEST_H

#include "graph_data.h"
#include "graph_list.h"
#include "graph_matrix.h"
#include "my_include.h"

// 用来统计文件中存储的点的个数
int size_vertex(list<GraphData> data);

// 用邻接矩阵建立图并且做相应的处理
void input_and_output(GraphMatrix& g, string path);

// 用邻接表建立图并且做相应的处理
void input_and_output(GraphList& g, string path);

void my_input(GraphMatrix& g);

// 建立图并且使用 prim_kruskal 算法解决最小生成树问题
void prim_kruskal();

// 建立图并且使用 dijkstra 算法解决最短路径问题
void dijkstra_input();

// 建立图并且使用多源算法 Floyd 解决最短路径问题
void floyd_input();

void minest_test_1();
void minest_test_1_list();

void minest_test_2();
void minest_test_2_list();

void minest_test_3();
void minest_test_3_list();

void minest_test_4();
void minest_test_4_list();

void minest_test_5();
void minest_test_5_list();

void dijkstra_1();
void dijkstra_1_list();

void dijkstra_2();
void dijkstra_2_list();

void dijkstra_3();
void dijkstra_3_list();

void floyd_1();
void floyd_1_list();

void floyd_2();
void floyd_2_list();

void floyd_3();
void floyd_3_list();

void floyd_4();
void floyd_4_list();

#endif