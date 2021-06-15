#ifndef _GRAPH_LIST_H
#define _GRAPH_LIST_H

#include "my_include.h"
#include "graph_data.h"

//边表类
class EdgeList {
private:
    int vertex;
    int weight;
    EdgeList* next;

public:
    // 申请一个点
    EdgeList* create(int vertex, int we)
    {
        EdgeList* list = new EdgeList;
        list->vertex = vertex;
        list->weight = we;
        list->next = nullptr;
        return list;
    }

    //寻找最后一个结点
    EdgeList* find_last(EdgeList* list)
    {
        if (list == nullptr) {
            return nullptr;
        }
        EdgeList* cur = list;
        while (cur) {
            if (cur->next == nullptr) {
                return cur;
            }
            cur = cur->next;
        }
        return nullptr;
    }

    //插入函数
    EdgeList* add(EdgeList* list, int vertex, int we)
    {
        EdgeList* last = this->find_last(list);
        EdgeList* insert = insert->create(vertex, we);
        last->next = insert;
        return list;
    }

    // 获取第一个点
    int get_vertex(EdgeList* list)
    {
        return list->vertex;
    }

    // 输出每个点的边
    void Print(EdgeList* list)
    {
        EdgeList* cur = list;
        while (cur) {
            // 如果不是最后一个输出 ->
            if (cur->next != nullptr) {
                printf("%2d[%d] --> ", cur->vertex, cur->weight);
            } else { // 最后一个不输出 ->
                printf("%d[%d]", cur->vertex, cur->weight);
            }
            cur = cur->next;
        }
    }

    EdgeList* get_next()
    {
        return this->next;
    }
};

class GraphList {
private:
    vector<EdgeList*> Edgelist; //邻接表
    int* isvisited; //访问数组
    int Nv; //顶点数
    int Ne; //边数
public:
    //构造函数
    GraphList(int nv)
    {
        this->Nv = nv;
        this->Edgelist.reserve(nv);
        this->isvisited = new int[nv + 1];
        memset(this->isvisited, 0, sizeof(this->isvisited[0]) * (this->Nv + 1));
        //依次构造图的结点
        for (int i = 0; i < this->Nv; i++) {
            this->Edgelist[i] = new EdgeList;
            this->Edgelist[i] = this->Edgelist[i]->create(i, 0);
        }
    }

    GraphList() {
        Nv = 0;
        Ne = 0;
    }

    void set_graphList(int nv)
    {
        this->Nv = nv;
        this->Edgelist.reserve(nv);
        this->isvisited = new int[nv + 1];
        memset(this->isvisited, 0, sizeof(this->isvisited[0]) * (this->Nv + 1));
        //依次构造图的结点
        for (int i = 0; i < this->Nv; i++) {
            this->Edgelist[i] = new EdgeList;
            this->Edgelist[i] = this->Edgelist[i]->create(i, 0);
        }
    }

    int get_Nv() {
        return Nv;
    }

    int get_Ne() {
        return Ne;
    }

    void add(int v1, int v2, int weight)
    {
        EdgeList* s1 = Find(v1);
        EdgeList* s2 = Find(v2);
        s1->add(s1, v2, weight);
        s2->add(s2, v1, weight);
        Ne++;
        return;
    }

    // 输入函数
    list<GraphData> input(string path)
    {
        GraphData graph_data; // 创建一个读取数据的实例
        list<GraphData> data = graph_data.input(path);
        // for (auto& i : data) {
        //     add(i.get_vertex1(), i.get_vertex2(), i.get_weight());
        // }
        return data;
    }

    EdgeList* search(int v) {
        return Edgelist[v];
    }

    //按指定结点查找
    EdgeList* Find(int vertex)
    {
        for (int i = 0; i < Nv; i++) {
            if (Edgelist[i]->get_vertex(Edgelist[i]) == vertex) {
                return this->Edgelist[i];
            }
        }
        return nullptr;
    }

    //打印邻接表函数
    void Print()
    {
        cout << "-------------------------------------------" << endl;
        for (int i = 0; i < this->Nv; i++) {
            EdgeList* list = this->Edgelist[i];
            list->Print(list);
            cout << endl;
        }
        cout << "-------------------------------------------" << endl;
    }

    //广度优先遍历(BFS)
    void BFS(int vertex)
    {
        EdgeList* cur = this->Find(vertex); //找到当前结点
        queue<int> queue; //初始化队列
        queue.push(cur->get_vertex(cur)); //当前结点入队
        while (!queue.empty()) {
            int index = queue.front(); //队头元素出队
            queue.pop();
            isvisited[index] = 1; //标记为已访问
            cout << index << " ";
            cur = this->Find(index);
            while (cur) { //与当前结点相邻且未被访问的结点入队
                index = cur->get_vertex(cur);
                if (isvisited[index] == 0) {
                    queue.push(index);
                    isvisited[index] = 1;
                }
                cur = cur->get_next();
            }
        }
    }

    //重置访问数组
    void reset()
    {
        memset(this->isvisited, 0, sizeof(this->isvisited[0]) * (this->Nv + 1));
    }

    //递归深度优先遍历(DFS)
    void DFS1(int vertex)
    {
        vector<int> node;
        //找到当前结点
        EdgeList* cur = this->Find(vertex);
        while (cur) { //寻找当前结点的邻接点
            node.push_back(cur->get_vertex(cur));
            cur = cur->get_next();
        }
        //打印当前结点
        cur = this->Find(node[0]);
        int index = cur->get_vertex(cur);
        this->isvisited[index] = 1;
        cout << index << " ";
        //一次堆当前结点的邻接点进行DFS
        for (int i = 1; i < node.size(); i++) {
            cur = this->Find(node[i]);
            index = cur->get_vertex(cur);
            if (this->isvisited[index] == 0) {
                this->isvisited[index] = 1;
                this->DFS1(index);
            }
        }
    }

    //非递归深度优先遍历(DFS)
    void DFS2(int vertex)
    {
        stack<int> stack;
        EdgeList* cur = this->Find(vertex); //查找当前元素
        int index = cur->get_vertex(cur); //当前元素的顶点
        stack.push(index); //顶点入栈
        this->isvisited[index] = 1; //标记为已访问
        while (!stack.empty()) { //栈不空一直循环
            index = stack.top(); //栈顶的顶点出栈
            stack.pop();
            cout << index << " "; //打印当前顶点
            cur = this->Find(index);
            while (cur) { //把当前顶点的邻接点依次入栈
                index = cur->get_vertex(cur);
                if (this->isvisited[index] == 0) {
                    stack.push(index);
                    this->isvisited[index] = 1;
                }
                cur = cur->get_next();
            }
        }
    }
};

#endif