#ifndef _MENU_H
#define _MENU_H

#include "my_include.h"
#include "test.h"
#include "test.cpp"
#include "menu.h"

// 用来改变控制台输出的字体颜色
#define WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE) //设置三色相加
#define RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED)
#define YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN); //设置红色和绿色相加

//辅助函数：光标移动
void gotoxy(int x, int y)
{
    //调用win32 API 去设置控制台的光标位置
    //1.找到控制台的这个窗口
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //2.光标的结构体
    COORD coord;
    //
    //3.设置坐标
    coord.X = x;
    coord.Y = y;
    //4.同步到控制台
    SetConsoleCursorPosition(handle, coord);
}

void begin()
{
    RED;
    printf("\n----------欢迎使用【最小生成树】和【最短路径】功能----------\n\n");
    printf("\t\t\t1.prim、Kruskal\n\n");
    printf("\t\t\t2.Dijkstra\n\n");
    printf("\t\t\t3.Floyd\n\n");
    printf("------------------------------------------------------------\n");
    YELLOW;
    cout << "'0'退出,请选择功能:";
}

// prim功能入口
bool prim()
{
    RED;
    printf("-----------------------【Prim、Kruskal】---------------------\n");
    printf("----------------------下面是5组测试案例----------------------\n\n");
    printf("\t\t\t1.minest_test_1\n\n");
    printf("\t\t\t2.minest_test_2\n\n");
    printf("\t\t\t3.minest_test_3\n\n");
    printf("\t\t\t4.minest_test_4\n\n");
    printf("\t\t\t5.minest_test_5\n\n");
    printf("\t\t\t6.手动输入数据\n\n");
    printf("-------------------------------------------------------------\n");
    YELLOW;
    cout << "'0'退出,请选择功能:";
    char c;
    cin >> c;
    WHITE;
    switch (c) {
    case '1':
        minest_test_1_list();
        minest_test_1();
        break;
    case '2':
        minest_test_2_list();
        minest_test_2();
        break;
    case '3':
        minest_test_3_list();
        minest_test_3();
        break;
    case '4':
        minest_test_4_list();
        minest_test_4();
        break;
    case '5':
        minest_test_5_list();
        minest_test_5();
        break;
    case '6':
        prim_kruskal();
        break;
    default:
        break;
    }
    return c == '0' ? true : false;
}

// Dijkstra功能入口
bool Dijkstra()
{
    RED;
    printf("-------------------------【Dijkstra】------------------------\n");
    printf("----------------------下面是3组测试案例----------------------\n\n");
    printf("\t\t\t1.dijkstra_1\n\n");
    printf("\t\t\t2.dijkstra_2\n\n");
    printf("\t\t\t3.dijkstra_3\n\n");
    printf("\t\t\t4.手动输入数据\n\n");
    printf("-------------------------------------------------------------\n");
    YELLOW;
    cout << "'0'退出,请选择功能:";
    char c;
    cin >> c;
    WHITE;
    switch (c) {
    case '1':
        dijkstra_1_list();
        dijkstra_1();
        break;
    case '2':
        dijkstra_2_list();
        dijkstra_2();
        break;
    case '3':
        dijkstra_3_list();
        dijkstra_3();
        break;
    case '4':
        dijkstra_input();
        break;
    default:
        break;
    }
    return c == '0' ? true : false;
}

// Floyd功能入口
bool Floyd()
{
    RED;
    printf("--------------------------【Floyd】--------------------------\n");
    printf("----------------------下面是4组测试案例----------------------\n\n");
    printf("\t\t\t1.floyd_1\n\n");
    printf("\t\t\t2.floyd_2\n\n");
    printf("\t\t\t3.floyd_3\n\n");
    printf("\t\t\t4.floyd_4\n\n");
    printf("\t\t\t5.手动输入数据\n\n");
    printf("-------------------------------------------------------------\n");
    YELLOW;
    cout << "'0'退出,请选择功能:";
    char c;
    cin >> c;
    WHITE;
    switch (c) {
    case '1':
        floyd_1_list();
        floyd_1();
        break;
    case '2':
        floyd_2_list();
        floyd_2();
        break;
    case '3':
        floyd_3_list();
        floyd_3();
        break;
    case '4':
        floyd_4_list();
        floyd_4();
        break;
    case '5':
        floyd_input();
        break;
    default:
        break;
    }
    return c == '0' ? true : false;
}

// 几个主功能入口
bool KeyDown(char value)
{
    switch (value) {
    case '1':
        while (!prim()) {
            prim();
        }
        break;
    case '2':
        while (!Dijkstra()) {
            Dijkstra();
        }
        break;
    case '3':
        while (!Floyd()) {
            Floyd();
        }
        break;

    default:
        break;
    }
    return value == '0' ? true : false;
}

//菜单
void menu()
{
    char value = 1;
    while (true) {
        begin();
        scanf("%c", &value);
        if (value == '0') {
            cout << endl
                << "欢迎下一次使用" << endl;
            break;
        }
        WHITE;
        KeyDown(value);
    }
}

#endif