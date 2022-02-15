#include <cstdlib>
#include <type_define.h>
#include <fastSA.h>
#include <init_placement.h>
using namespace std;

//void die_config(vector<float> &widch, vector<float> &heigth, vector<vector<float> > &a);

int main()
{
    int chiplet_num = 5;
    

    position p= {0, 0};
    size s = {8, 8};
    vector<pin> pi (32, {0, 0});
    chiplet a = {0, p, s, pi};
    vector<chiplet> chip(chiplet_num, a);

    size interposer = {100, 100};
    vector<vector<int>> nets = {{0, 0, 32, 0, 0},
                             {0, 0, 32, 0, 0},
                             {0, 0, 0, 32, 0},
                             {0, 0, 0, 0, 32},
                             {0, 0, 0, 0, 0}};
    cout << chip.size() << "\t"<< endl;
    init_placement(chip, nets, interposer);
    fastSA(chip, nets, interposer);
    return 0;
}

/*void die_config(vector<float> &widch, vector<float> &heigth, vector<vector<float> > &a){
    widch = {3,4,2,2,1,4,3,4};
}*/
