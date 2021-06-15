#ifndef _GRAPH_DATA_H
#define _GRAPH_DATA_H

#include "my_include.h"

class GraphData {
public:
    GraphData(void) { }
    GraphData(const int& v1, int v2, int weight)
        : vertex1(v1)
        , vertex2(v2)
        , weight(weight)
    {
    }
    friend ostream& operator<<(ostream& out, const GraphData& p);
    friend istream& operator>>(istream& in, GraphData& p);
    friend bool operator<(const GraphData& lhs, const GraphData& rhs);

    int get_vertex1() {
        return vertex1;
    }

    int get_vertex2() {
        return vertex2;
    }

    int get_weight() {
        return weight;
    }

    // 提供给外部的接口，传入一个路径，返回一个包含3个数据的列表
    list<GraphData> input(string path)
    {
        ifstream fin(path);
        if (!fin) {
            cout << "can't open file data.txt" << endl;
        }
        list<GraphData> data;
        while (true) {
            GraphData per;
            fin >> per;
            if (!fin) {
                break;
            }
            data.push_back(per);
        }
        return data;
    }

private:
    int vertex1;
    int vertex2;
    int weight;
};

ostream& operator<<(ostream& out, const GraphData& p)
{
    out << setw(2) << p.vertex1
        << setw(3) << p.vertex2
        << setw(3) << p.weight;
        return out;
}

istream& operator>>(istream& in, GraphData& p)
{
    string s;
    getline(in, s);
    istringstream iss(s);
    iss >> p.vertex1 >> p.vertex2 >> p.weight;
    return in;
}

    // vector<GraphData> arrayPerson;
    // arrayPerson.push_back(GraphData("2", 1, 22));
    // arrayPerson.push_back(GraphData("4", 1, 22));
    // arrayPerson.push_back(GraphData("5", 2, 23));
    // arrayPerson.push_back(GraphData("6", 2, 23));
    // //容器数据写入文件
    // ofstream fout("person.txt");
    // for (auto& i : arrayPerson) {
    //     fout << i << endl;
    // }
    // fout.close();


#endif