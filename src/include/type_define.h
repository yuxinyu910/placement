#ifndef _TYPE_DEFINE_H_
#define _TYPE_DEFINE_H_
#define _max(a,b)    (((a) > (b)) ? (a) : (b))
#define _min(a,b)    (((a) < (b)) ? (a) : (b))
#include <vector>
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
using namespace std;
#define MARGIN_IN_CHIP 2
#define MARGIN_OFF_INTERPOSER 2

typedef struct position_s
{
    int x;
    int y;
}position;

typedef struct TreeNode_s{
    int TreeNum;
    struct TreeNode_s* left;
    struct TreeNode_s* right;
}TreeNode, *BiTree;

typedef struct size_s
{
    int width;
    int heigth;
}size;

typedef struct pin_s
{
    int x_p;
    int y_p;
}pin;

typedef struct chiplet_s
{
    int rotate;
    position point;
    size size;
    vector<pin> pins;
}chiplet;

#endif