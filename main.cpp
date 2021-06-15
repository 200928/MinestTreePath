#include "graph_data.h"
#include "graph_list.h"
#include "graph_matrix.h"
#include "menu.h"
#include "my_include.h"
#include "test.h"

using namespace std;

int main()
{
    menu(); // 功能入口

    time_t now = time(0);
    tm* ltm = localtime(&now);
    cout << endl << "当前时间为 : "
        << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec;

    //**********************************
    // minest_test_1();
    // minest_test_1_list();

    // minest_test_2();
    // minest_test_2_list();

    // minest_test_3();
    // minest_test_3_list();

    // minest_test_4();
    // minest_test_4_list();

    // minest_test_5();
    // minest_test_5_list();

    // //**********************************

    // dijkstra_1();
    // dijkstra_1_list();

    // dijkstra_2();
    // dijkstra_2_list();

    // dijkstra_3();
    // dijkstra_3_list();

    // //*********************************

    // floyd_1();
    // floyd_1_list();

    // floyd_2();
    // floyd_2_list();

    // floyd_3();
    // floyd_3_list();

    // floyd_4();
    // floyd_4_list();

    return 0;
}