#include "graph_data.h"
#include "graph_list.h"
#include "graph_matrix.h"
#include "my_include.h"

// 用来统计文件中存储的点的个数
int size_vertex(list<GraphData> data) {
    int max = -1;
    for (auto& i : data) {
        int tmp = i.get_vertex1() < i.get_vertex2() ? i.get_vertex2() : i.get_vertex1();
        max = max < tmp ? tmp : max;
    }
    return max + 1;
}

// 用邻接矩阵建立图并且做相应的处理
void input_and_output(GraphMatrix& g, string path)
{
    list<GraphData> data = g.input(path);
    int size_v = size_vertex(data);
    if(size_v != 0) {
        g.set_graphMatrix(size_v);
        // cout << "图的顶点个数为" << g.get_Nv() << endl;
        cout << endl << "邻接矩阵实现 : ";
        // cout << "图的顶点：" << data.size() << endl;
        // 建立边
        for (auto& i : data) {
            // printf("%d %d %d\n",i.get_vertex1(), i.get_vertex2(), i.get_weight());
            g.add(i.get_vertex1(), i.get_vertex2(), i.get_weight());
        }

        printf("图的点和边数 : G(%d, %d)\n", g.get_Nv(), g.get_Ne());
        g.Print();
        int prim_weight = g.prim(0);
        if (-1 != prim_weight) {
            printf("\nPrim算法生成了权值为:%d 的最小生成树\n", prim_weight);
            g.PrintMST();
        }
        int kruskal_weight = g.kruskal();
        if (-1 != kruskal_weight) {
            printf("\nKruskal算法生成了权值为:%d 的最小生成树\n", kruskal_weight);
            g.PrintMST();
        }
    } else {
        cout << "读入数据出错" << endl;
    }
}

// 用邻接表建立图并且做相应的处理
void input_and_output(GraphList& g, string path)
{
    cout << endl << "邻接表实现 : ";
    list<GraphData> data = g.input(path);
    int size_v = size_vertex(data);
    if (size_v != 0) {
        g.set_graphList(size_v);
        // 建立边
        for (auto& i : data) {
            // printf("%d %d %d\n", i.get_vertex1(), i.get_vertex2(), i.get_weight());
            g.add(i.get_vertex1(), i.get_vertex2(), i.get_weight());
        }

        printf("图的点和边数 : G(%d, %d)\n", g.get_Nv(), g.get_Ne());
        g.Print();
        // cout << g.get_Ne() << endl;
    } else {
        cout << "读入数据出错";
    }
}

void my_input(GraphMatrix& g) {
    int nv = 0;
    int ne = 0;
    cout << "请输入顶点个数和边数: ";
    cin >> nv >> ne;
    g.set_graphMatrix(nv);
    for (int i = 0; i < ne; i++) {
        printf("请输入第%d条边: ", i + 1);
        int v1, v2, weight;
        cin >> v1 >> v2 >> weight;
        g.add(v1, v2, weight);
    }
}

// 建立图并且使用 prim_kruskal 算法解决最小生成树问题
void prim_kruskal() {
    GraphMatrix g = GraphMatrix();
    my_input(g);
    cout << endl << "邻接矩阵实现 : ";
    printf("图的点和边数 : G(%d, %d)\n", g.get_Nv(), g.get_Ne());
    g.Print();
    int prim_weight = g.prim(0);
    if (-1 != prim_weight) {
        printf("\nPrim算法生成了权值为:%d 的最小生成树\n", prim_weight);
        g.PrintMST();
    }
    int kruskal_weight = g.kruskal();
    if (-1 != kruskal_weight) {
        printf("\nKruskal算法生成了权值为:%d 的最小生成树\n", kruskal_weight);
        g.PrintMST();
    }
}

// 建立图并且使用 dijkstra 算法解决最短路径问题
void dijkstra_input() {
    GraphMatrix g = GraphMatrix();
    my_input(g);
    cout << endl << "邻接矩阵实现 : ";
    printf("图的点和边数 : G(%d, %d)\n", g.get_Nv(), g.get_Ne());
    g.Print();
    int prim_weight = g.prim(0);
    if (-1 != prim_weight) {
        printf("\nPrim算法生成了权值为:%d 的最小生成树\n", prim_weight);
        g.PrintMST();
    }
    int kruskal_weight = g.kruskal();
    if (-1 != kruskal_weight) {
        printf("\nKruskal算法生成了权值为:%d 的最小生成树\n", kruskal_weight);
        g.PrintMST();
    }
    if (g.Dijikstra(0)) {
        g.Print_Dijikstra(0);
    } else {
        cout << "Dijkstra 生成树失败" << endl;
    }
}

// 建立图并且使用多源算法 Floyd 解决最短路径问题
void floyd_input() {
    GraphMatrix g = GraphMatrix();
    my_input(g);
    cout << endl << "邻接矩阵实现 : ";
    printf("图的点和边数 : G(%d, %d)\n", g.get_Nv(), g.get_Ne());
    g.Print();
    int prim_weight = g.prim(0);
    if (-1 != prim_weight) {
        printf("\nPrim算法生成了权值为:%d 的最小生成树\n", prim_weight);
        g.PrintMST();
    }
    int kruskal_weight = g.kruskal();
    if (-1 != kruskal_weight) {
        printf("\nKruskal算法生成了权值为:%d 的最小生成树\n", kruskal_weight);
        g.PrintMST();
    }
    cout << endl << "Floyd算法的结果如下" << endl << endl;
    g.Floyd();
    g.Print_Floyd_matrix();
    g.Print_Floyd();
}

void minest_test_1()
{
    GraphMatrix g;
    input_and_output(g, "./resources/minest_test_1");
}

void minest_test_1_list()
{
    GraphList g;
    input_and_output(g, "./resources/minest_test_1");
}

void minest_test_2()
{
    GraphMatrix g;
    input_and_output(g, "./resources/minest_test_2");
}

void minest_test_2_list()
{
    GraphList g = GraphList();
    input_and_output(g, "./resources/minest_test_2");
}

void minest_test_3()
{
    GraphMatrix g;
    input_and_output(g, "./resources/minest_test_3");
}

void minest_test_3_list()
{
    GraphList g = GraphList();
    input_and_output(g, "./resources/minest_test_3");
}

void minest_test_4()
{
    GraphMatrix g;
    input_and_output(g, "./resources/minest_test_4");
}

void minest_test_4_list()
{
    GraphList g = GraphList();
    input_and_output(g, "./resources/minest_test_4");
}

void minest_test_5()
{
    GraphMatrix g;
    input_and_output(g, "./resources/minest_test_5");
}

void minest_test_5_list()
{
    GraphList g = GraphList();
    input_and_output(g, "./resources/minest_test_5");
}

void dijkstra_1()
{
    GraphMatrix g;
    input_and_output(g, "./resources/dijkstra_1");
    if (g.Dijikstra(0)) {
        g.Print_Dijikstra(0);
    } else {
        cout << "Dijkstra 生成树失败" << endl;
    }
}

void dijkstra_1_list()
{
    GraphList g;
    input_and_output(g, "./resources/dijkstra_1");
}

void dijkstra_2()
{
    GraphMatrix g;
    input_and_output(g, "./resources/dijkstra_2");
    if (g.Dijikstra(0)) {
        g.Print_Dijikstra(0);
    } else {
        cout << "Dijkstra 生成树失败" << endl;
    }
}

void dijkstra_2_list()
{
    GraphList g;
    input_and_output(g, "./resources/dijkstra_2");
}

void dijkstra_3()
{
    GraphMatrix g;
    input_and_output(g, "./resources/dijkstra_3");
    if (g.Dijikstra(0)) {
        g.Print_Dijikstra(0);
    } else {
        cout << "Dijkstra 生成树失败" << endl;
    }
}

void dijkstra_3_list()
{
    GraphList g;
    input_and_output(g, "./resources/dijkstra_3");
}

void floyd_1()
{
    GraphMatrix g;
    input_and_output(g, "./resources/floyd_1");
    cout << endl << "Floyd算法的结果如下" << endl << endl;
    g.Floyd();
    g.Print_Floyd_matrix();
    g.Print_Floyd();
}

void floyd_1_list()
{
    GraphList g;
    input_and_output(g, "./resources/floyd_1");
}

void floyd_2()
{
    GraphMatrix g;
    input_and_output(g, "./resources/floyd_2");
    cout << endl << "Floyd算法的结果如下" << endl << endl;
    g.Floyd();
    g.Print_Floyd_matrix();
    g.Print_Floyd();
}

void floyd_2_list()
{
    GraphList g;
    input_and_output(g, "./resources/floyd_2");
}

void floyd_3()
{
    GraphMatrix g;
    input_and_output(g, "./resources/floyd_3");
    cout << endl << "Floyd算法的结果如下" << endl << endl;
    g.Floyd();
    g.Print_Floyd_matrix();
    g.Print_Floyd();
}

void floyd_3_list()
{
    GraphList g;
    input_and_output(g, "./resources/floyd_3");
}

void floyd_4()
{
    GraphMatrix g;
    input_and_output(g, "./resources/floyd_4");
    cout << endl << "Floyd算法的结果如下" << endl << endl;
    g.Floyd();
    g.Print_Floyd_matrix();
    g.Print_Floyd();
}

void floyd_4_list()
{
    GraphList g;
    input_and_output(g, "./resources/floyd_4");
}
