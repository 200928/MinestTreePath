#ifndef _PRIM_H
#define _PRIM_H

#include "my_include.h"

class Edge {
    private:
        int start_vertex;   // 起始点
        int end_vertex;     // 终止点
        int weight;         // 上面两个点构成边的权值
    public:
        Edge(int start, int end, int we) {
            start_vertex = start;
            end_vertex = end;
            weight = we;
        }

        // 打印该边
        void Print() {
            printf(" %d\t %d\t %d\t\n", start_vertex, end_vertex, weight);
        }

        int get_start_vertex() {
            return start_vertex;
        }

        int get_end_vertex() {
            return end_vertex;
        }

        int get_weight() {
            return weight;
        }

};

#endif
