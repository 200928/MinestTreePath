#ifndef _GRAPH_MATRIX_H
#define _GRAPH_MATRIX_H

#include "prim.h"
#include "my_include.h"
#include "graph_data.h"
#include "dsu.h"

#define MAX 500
#define INF 0x7fffffff

class GraphMatrix {
private:
    int G[MAX][MAX]; //邻接矩阵
    int* isvisited; //访问数组
    int Nv; //顶点数
    int Ne = 0; //边数
    vector<Edge> MST;   // 最小生成树的集合

    /**
     * @brief 下面是用于 prim 的存储变量
     */
    int* dist;  // 距离数组，为prim、Dijiksta提供
    int* parent; // 父亲节点数组，为prim、Dijiksta提供

    /**
     * @brief 下面是用于 Kruskal 的存储变量
     */
    vector<Edge> edge_set;  // 边集合

    /**
     * @brief 下面用于 Dijiksta
     */
    int* collected; // 收录数组
    int* path;      // 路径数组

    /**
     * @brief 用于 Floyd 
     */
    int** dist_p;   // 距离数组
    int** path_p;   // 路径数组
public:

    int get_Nv() {
        return Nv;
    }

    int get_Ne() {
        return Ne;
    }

    // 该函数用来统计非孤立节点的个数
    int real_vertex() {
        int i = 0;
        int j = 0;
        int count = 0;
        for (i = 0; i < Nv; i++) {
            for (j = 0; j < Nv; j++) {
                if (G[i][j] != INF) {
                    break;
                }
            }
            if (Nv == j) {
                count++;
            }
        }
        return Nv - count;
    }

    list<GraphData> input(string path) {
        GraphData graph_data;   // 创建一个读取数据的实例
        list<GraphData> data = graph_data.input(path);
        // for (auto& i : data) {
        //     add(i.get_vertex1(), i.get_vertex2(), i.get_weight());
        // }
        return data;
    }

    //构造函数
    GraphMatrix(int nv)
    {
        Nv = nv; // 初始化点数量
        isvisited = new int[nv]; // 初始化访问数组大小为点数量
        dist = new int[nv + 1]; // 初始化距离数组，大小为点数量
        parent = new int[nv]; // 初始化父亲节点数组大小，大小为点数量
        collected = new int[nv];
        path = new int[nv];

        dist_p = new int*[nv];
        path_p = new int*[nv];

        memset(isvisited, 0, sizeof(isvisited[0]) * nv);
        memset(path, -1, sizeof(path[0]) * nv);
        memset(collected, 0, sizeof(collected[0]) * nv);
        for (int i = 0; i < nv + 1; i++) {
            *(dist + i) = INF; // 每两个点的初始距离为 INF
            dist_p[i] = new int[nv];
            path_p[i] = new int[nv];
            memset(path_p[i], -1, sizeof(path_p[0][0]) * nv); // 初始化路径数组为 -1
            for (int j = 0; j < nv; j++) {
                G[i][j] = dist_p[i][j] = INF;
            }
            dist_p[i][i] = INF;
        }
    }

    // 类构造函数
    void set_graphMatrix(int nv)
    {
        Nv = nv; // 初始化点数量
        isvisited = new int[nv]; // 初始化访问数组大小为点数量
        dist = new int[nv + 1]; // 初始化距离数组，大小为点数量
        parent = new int[nv]; // 初始化父亲节点数组大小，大小为点数量
        collected = new int[nv];
        path = new int[nv];

        dist_p = new int*[nv];
        path_p = new int*[nv];

        memset(isvisited, 0, sizeof(isvisited[0]) * nv);
        memset(path, -1, sizeof(path[0]) * nv);
        memset(collected, 0, sizeof(collected[0]) * nv);
        for (int i = 0; i < nv + 1; i++) {
            *(dist + i) = INF; // 每两个点的初始距离为 INF
            dist_p[i] = new int[nv];
            path_p[i] = new int[nv];
            memset(path_p[i], -1, sizeof(path_p[0][0]) * nv); // 初始化路径数组为 -1
            for (int j = 0; j < nv; j++) {
                G[i][j] = dist_p[i][j] = INF;
            }
            dist_p[i][i] = INF;
        }
    }

    GraphMatrix() {
        Nv = 0;
        Ne = 0;
    }

    void add(int v1, int v2, int weight) {
        G[v1][v2] = weight;
        G[v2][v1] = weight;
        Edge edge(v1, v2, weight);
        edge_set.push_back(edge);   // 添加到边集合中
        Ne++;
        this->dist_p[v1][v2] = this->dist_p[v2][v1] = weight;
    }

    void Print() {
        cout << "-------------------------------------------" << endl;
        for (int i = 0; i < Nv; i++) {
            for (int j = 0; j < Nv; j++) {
                if (G[i][j] == INF) {
                    printf("  %3s", "∞");
                } else {
                    printf("%3d", G[i][j]);
                }
            }
            cout << endl;
        }
        cout << "-------------------------------------------" << endl;
    }

    //重置函数
    void reset()
    {
        memset(this->isvisited, 0, sizeof(this->isvisited[0]) * (this->Nv + 1));
    }

    /**
     * @brief 将最小生成树的边集合 MST 清零
     * 
     */
    void reset_MST() {
        MST.clear();
    }

    // prim算法的一些函数
    // 寻找最小距离点函数
    int find_min_dist() {
        int minDist = INF;
        int minVertex = 0;
        for (int i = 0; i < Nv; i++) {
            if (*(dist +i) != 0 && *(dist + i) < minDist) {
                minDist = *(dist + i);
                minVertex = i;
            }
        }
        // 找到了就返回 minVertex, 没有就返回 -1
        return minDist < INF ? minVertex : -1;
    }

    /**
     * @brief 
     * prim 算法过程，以vertex为根节点生成最小生成树
     * @param vertex 从该点开始
     * @return int 返回最小生成树总权值
     */
    int prim(int vertex) {
        reset_MST();    // 第一件事就是将 MST 集合数组清零
        int count = 0;
        int min_weight = 0; // 生成树的权重和
        for (int i = 0; i < Nv; i++) {
            parent[i] = vertex;
            dist[i] = G[vertex][i]; // 暂时把距离初始化为i顶点到vertex顶点的权值
        }
        parent[vertex] = -1;    // 根节点标记为 -1
        dist[vertex] = 0;   // 根节点到本身距离为 0
        count++;
        while (true) {
            int cur_vertex = find_min_dist();
            count++;
            // 这里为 cur_vertex == -1 的情况就是生成树已经找到了即需要退出循环
            if (-1 == cur_vertex) {
                break;
            }
            min_weight += dist[cur_vertex];
            Edge edge = Edge(parent[cur_vertex], cur_vertex, dist[cur_vertex]);
            MST.push_back(edge);
            dist[cur_vertex] = 0;   // 已经收录的点距离变为0，防止下一步检索
            // 依次遍历图中所有点，如果需要更新父节点和距离就把他们更新
            for (int i = 0; i < Nv; i++) {
                // 不在生成树中的点，且该点和cru_vertex的权值不是INF，并且小于 dist[i]
                if (dist[i] != 0 && G[cur_vertex][i] < INF && G[cur_vertex][i] < dist[i]) {
                        dist[i] = G[cur_vertex][i];
                        parent[i] = cur_vertex;
                }
            }
        }
        if (count - 1 != real_vertex()) {
            min_weight = -1;
        }
        return min_weight;
    }
    
    int kruskal() {
        reset_MST();    // 第一件事就是将 MST 集合数组清零
        int min_weight = 0;
        UF uf = UF(Nv); // 初始化 Nv 个集合的并查集
        int count = 0;  // 用来保存边的个数
        // 构造边集合最小堆
        MinHeap min_heap = MinHeap(get_Ne());
        min_heap.Create(edge_set);

        int edge_count = 1;
        while (edge_count != real_vertex() && !min_heap.IsEmpty()) {
            // 取出最小的边
            Edge min = min_heap.DeleteMin();
            int v1 = min.get_start_vertex();
            int v2 = min.get_end_vertex();
            if (uf.CheckCircle(v1, v2)) {   // 不是回路则变成回路(合并)并返回 true
                MST.push_back(min);
                MST[edge_count++] = min;
                min_weight += min.get_weight();
            }
        }
        // 调试
        // cout << "edge_count" << edge_count << " " << real_vertex() << endl;
        if (edge_count != real_vertex()) {
            min_weight = -1;
        }
        return min_weight;
    }

    // 打印最小生成树边集合
    void PrintMST() {
        int cnt = 1;
        cout << endl << "------------------最小生成树如下----------------" << endl << endl;
        vector<Edge>::iterator it;
        printf("边数\t\t起点\t终点\t权值\t\n");
        for (it = MST.begin(); it != MST.end(); it++) {
            printf("第%d条边:\t", cnt++);
            it->Print();
        }
        cout << "-----------------------------------------------" << endl;
    }

    // 遍历邻接点寻找最小距离的点
    int find_min_vertex() {
        int min_dist = INF; // 默认以最大为边距离
        int v = 0;
        int min_v = 0;
        for (v = 0; v < get_Nv(); v++) {
            if (collected[v] == 0 && dist[v] < min_dist) {
                // v 未被收录且 dist[v] 更小，松弛操作
                min_dist = dist[v];
                min_v = v;
            }
        }
        if (min_dist < INF) {   // 找到最小的 dist
            return min_v;
        } else {    // 为未找到最小的
            return -1;  
        }
    }

    bool Dijikstra(int vertex) {
        for (int i = 0; i < get_Nv(); i++) {
            dist[i] = G[vertex][i];
            if (dist[i] < INF) {
                path[i] = vertex;
            }
        }
        dist[vertex] = 0;   // 初始节点的距离为 0
        collected[vertex] = 1;  // 初始节点表示已经收录
        while (true) {
            int v = find_min_vertex();
            if (-1 == v) {
                break;
            }
            collected[v] = 1;   // 标记已经收录
            for (int i = 0; i < get_Nv(); i++) {
                if (collected[i] == 0 && G[v][i] < INF) {
                    if (G[v][i] < 0) {  // 存在负数权值,直接结束
                        return false;
                    }
                    // 若收录 v 使得 dist[i] 变小
                    if (dist[v] + G[v][i] < dist[i]) {
                        // 松弛操作，更新 dist[i]
                        dist[i] = dist[v] + G[v][i];
                        path[i] = v;    // 更新路径
                    }
                }
            }
        }
        return true;
    }

    // 输出最短路径
    void Print_Dijikstra(int vertex)
    {
        cout << endl << "----------Dijkstra生成的最小路径如下------------" << endl;
        for (int i = 1; i < get_Nv(); i++) {
            if (i == vertex) {
                continue;
            }
            stack<int> stack;
            stack.push(i);
            if (INF == dist[i]) {
                printf("\n%2d 到 %2d 的最短路径为: ∞ ,路径:", vertex, i);
            } else {
                printf("\n%2d 到 %2d 的最短路径为:%2d ,路径", vertex, i, dist[i]);
            }
            int j = i;
            while (-1 != path[j]) { // 路径上的元素依次入栈
                j = path[j];
                stack.push(j);
            }
            // 打印路径
            cout << stack.top();
            stack.pop();
            while (!stack.empty()) {
                printf("-->%d", stack.top());
                stack.pop();
            }
            // printf(" (%d)", dist[i]);
        }
        cout << endl << "-----------------------------------------------" << endl;;
    }

    bool Floyd() {
        int row = 0;
        int col = 0;
        for (row = 0; row < this->Nv; row++) {
            for (col = 0; col < this->Nv; col++) {
                //把矩阵D初始化为邻接矩阵的值
                this->dist_p[row][col] = this->G[row][col];
                //矩阵P的初值则为各个边的终点顶点的下标
                this->path_p[row][col] = col;
            }
        }

        //三重循环，用于计算每个点对的最短路径
        int temp = 0;
        int select = 0;
        for (temp = 0; temp < this->Nv; temp++) {
            for (row = 0; row < this->Nv; row++) {
                for (col = 0; col < this->Nv; col++) {
                    //为了防止溢出，所以需要引入一个select值
                    select = (dist_p[row][temp] == INT_MAX || dist_p[temp][col] == INT_MAX) ? INT_MAX : (dist_p[row][temp] + dist_p[temp][col]);
                    if (this->dist_p[row][col] > select) {
                        //更新我们的D矩阵
                        this->dist_p[row][col] = select;
                        //更新我们的P矩阵
                        this->path_p[row][col] = this->path_p[row][temp];
                    }
                }
            }
        }
        return true;
    }

    void Print_Floyd()
    {
        cout << "--------------最小路径表(Floyd)-------------" << endl << endl;
        int row = 0;
        int col = 0;
        int temp = 0;
        for (row = 0; row < this->Nv; row++) {
            for (col = row + 1; col < this->Nv; col++) {
                cout << row << "---" << col << " 最短路径: "
                    << this->dist_p[row][col] << ", 路径为: " << row;
                temp = path_p[row][col];
                //循环输出途径的每条路径。
                while (temp != col) {
                    cout << "-->" << temp;
                    temp = path_p[temp][col];
                }
                cout << "-->" << col << endl;
            }
            cout << endl;
        }
        cout << "-------------------------------------------" << endl;
    }

    void Print_Floyd_matrix()
    {
        cout << "--------------Cost Table-------------" << endl << endl;
        for (int i = 0; i < Nv; i++) {
            for (int j = 0; j < Nv; j++) {
                if (i == j || dist_p[i][j] == INF) {
                    printf("  %4s", "∞");
                } else {
                    printf("%4d", dist_p[i][j]);
                }
            }
            cout << endl;
        }
        cout << "-------------------------------------" << endl;
    }
};


#endif