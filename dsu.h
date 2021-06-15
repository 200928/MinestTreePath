#ifndef _DSU_H
#define _DSU_H

#include "my_include.h"

const int Min_Data = -32768;

class UF {
private:
    int* path; // 父亲节点
    int size; // 大小（容量）

public:
    UF(int size) : size(size) {
        path = new int[size];
        memset(path, -1, sizeof(path[0]) * size);    // 初始化为 0
    }

    // 查找，采用了路径压缩方式
    int Find(int x) {
        if (path[x] < 0) {
            return x;
        }
        // 递归赋值
        return path[x] = Find(path[x]);
    }

    // 合并 v1 和 v2 为一个集合
    // path[v] 表示当前集合的 相反数
    void Union(int v1, int v2) {
        v1 = Find(v1);
        v2 = Find(v2);
        if (path[v1] < path[v2]) {  // 把 v2 合并到 v1
            path[v1] += path[v2];
            path[v2] = v1;
        } else {   // 把 v1 合并到 v2
            path[v2] += path[v1];
            path[v1] = v2;
        }
        return;
    }

    // 检查 v1 点所在集合和 v2 点所在集合是否连通
    bool CheckCircle(int v1, int v2) {
        v1 = Find(v1);
        v2 = Find(v2);
        if (v1 == v2) { // 如果有回路返回 false
            return false;
        } else {
            Union(v1, v2);
        }
        return true;
    }
};

class MinHeap {
private:
    vector<Edge> Edges; //边集数组
    int capacity; //最大容量
    int size; //当前规模
public:
    //构造函数
    MinHeap(int size)
    {
        capacity = size * 2;
        size = 0;
        Edges.reserve(this->capacity);
        Edge edge = Edge(0, 0, Min_Data);
        Edges.push_back(edge);
    }

    //把Edge[n]为根的子堆调整为最小堆
    void PreDown(int n)
    {
        Edge edge = Edges[n]; //保存下标为n的边
        int parent, child;
        for (parent = n; parent * 2 <= size; parent = child) {
            child = parent * 2;
            if (child != this->size) {
                int wl = Edges[child].get_weight(); //左孩子权重
                int wr = Edges[child + 1].get_weight(); //右孩子权重
                if (wr < wl) { //右孩子权重小于左孩子权重
                    child++; //选择右孩子
                }
            }
            //如果根节点权重小于子堆，那么找到合适位置，跳出循环
            if (edge.get_weight() < Edges[child].get_weight()) {
                break;
            } else {
                Edges[parent] = Edges[child];
            }
        }
        Edges[parent] = edge;
    }

    //构造最小堆
    void Create(vector<Edge>& set)
    {
        for (int i = 0; i < set.size(); i++) {
            Edges[++size] = set[i];
        }
        //从最后一个元素的父亲开始，把自己为根的子堆调整为最小堆
        for (int i = size / 2; i >= 1; i--) {
            PreDown(i);
        }
    }

    //删除操作
    Edge DeleteMin()
    {
        if (IsEmpty()) {
            Edge edge = Edge(0, 0, Min_Data);
            return edge;
        }
        Edge min_edge = Edges[1];
        Edges[1] = Edges[size];
        size--;
        PreDown(1);
        return min_edge;
    }

    //判断最小堆是否为空
    bool IsEmpty()
    {
        return size == 0;
    }

    void Print()
    {
        cout << "最小堆的元素有：" << this->size << endl;
        for (int i = 1; i <= size; i++) {
            cout << Edges[i].get_start_vertex() << " " << Edges[i].get_end_vertex() << " " << this->Edges[i].get_weight() << endl;
        }
    }
};

#endif