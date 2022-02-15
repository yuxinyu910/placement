#include <fastSA.h>
void fastSA(vector<chiplet> &chip, vector<vector<int>> &nets, size &interposer)
{
    int tot_iter, inner_iter, success_sum, move_lim;
    int inner_num = 10;
    float t, rlim, cost, std_dev, av_cost;
    float* old_cost;
    
    float comp_cost(vector<chiplet> &chip, vector<vector<int>> &nets, size &interposer);
    int try_swap(vector<chiplet> &chip, vector<vector<int>> &nets, size &interposer);
    int check_place(vector<chiplet> &chip, vector<vector<int>> &nets, size &interposer);
    float starting_t();
    void update_t();
    void update_rlim();
    int exit_crit();
    
    cost = comp_cost(chip, nets, interposer);
    
    move_lim = inner_num*pow(chip.size(), 1.333);
    old_cost = (float* )malloc(move_lim*sizeof(float));
    t = starting_t();
    tot_iter = 0;
    printf("----------initial placement cost = %f--------------------\n", cost);
    printf("move_lim = %d\n", move_lim);
    rlim =(float)_max(interposer.heigth, interposer.width);
    std_dev = cost;
    try_swap(chip, nets, interposer);
    while (exit_crit() == 1)
    {
        printf("---------start fastSA circuit-----------\n");
        av_cost = 0.;
        success_sum = 0;
        old_cost[0] = cost; 

        for (inner_iter = 0; inner_iter < move_lim; inner_iter++)
        {
            if(try_swap(chip, nets, interposer) == 1){
                old_cost[success_sum] = cost;
                success_sum++;
                av_cost += cost;
            }
        }
        
    }
    cout<<"yuxinyu"<<endl;
}

float comp_cost(vector<chiplet> &chip, vector<vector<int>> &nets, size &interposer){
    float cost = 0;
    for (int i = 0; i < nets.size(); i++)
    {
        float xmin, xmax, ymin, ymax;
        float i_width, i_heigth;
        i_heigth = chip[i].size.heigth*cos(chip[i].rotate) + chip[i].size.width*cos(chip[i].rotate);
        i_width = chip[i].size.width*cos(chip[i].rotate) + chip[i].size.heigth*cos(chip[i].rotate);
        xmin = chip[i].point.x - i_width/2;
        xmax = chip[i].point.x + i_width/2;
        ymin = chip[i].point.y - i_heigth/2;
        ymax = chip[i].point.y + i_heigth/2;
        for (int j = 0; j < nets[i].size(); j++)
        {
            if ((i != j)&&(nets[i][j] != 0))
            {
                float j_heigth = chip[j].size.heigth*cos(chip[j].rotate) + chip[j].size.width*cos(chip[j].rotate);
                float j_width = chip[j].size.width*cos(chip[j].rotate) + chip[j].size.heigth*cos(chip[j].rotate);
                xmin = _min(xmin, chip[j].point.x - j_width/2);
                xmax = _max(xmax, chip[j].point.x + j_width/2);
                ymin = _min(ymin, chip[j].point.y - j_heigth/2);
                ymax = _max(ymax, chip[j].point.y + j_heigth/2);
            }
            
        }
        cost += (ymax- ymin) + (xmax - xmin);
    }
    cout<<"----------finish init cost----------------"<<endl;
    cout<<cost<<endl;
    return cost;
}

int double_die_check(chiplet &chip_i, chiplet &chip_j){
    float i_width, i_heigth, j_width, j_heigth;
    i_heigth = chip_i.size.heigth*cos(chip_i.rotate) + chip_i.size.width*cos(chip_i.rotate);
    i_width = chip_i.size.width*cos(chip_i.rotate) + chip_i.size.heigth*cos(chip_i.rotate);
    j_heigth = chip_j.size.heigth*cos(chip_j.rotate) + chip_j.size.width*cos(chip_j.rotate);
    j_width = chip_j.size.width*cos(chip_j.rotate) + chip_j.size.heigth*cos(chip_j.rotate);
    if ((fabs(chip_i.point.x - chip_j.point.x) <= (i_width + j_width)/2)||(fabs(chip_i.point.y - chip_j.point.y) <= (i_heigth + j_heigth)/2))
    {
        return 0;
    }
    else{
        return 1;
    }
}

int check_place(vector<chiplet> &chip, vector<vector<int>> &nets, size &interposer){
    printf("----------start check placement------------\n");
    int current_place = 0;
    float xmin, xmax, ymin, ymax;
    float i_width, i_heigth;
    for(int i = 0; i < chip.size(); i++){
        i_heigth = chip[i].size.heigth*cos(chip[i].rotate) + chip[i].size.width*cos(chip[i].rotate);
        i_width = chip[i].size.width*cos(chip[i].rotate) + chip[i].size.heigth*cos(chip[i].rotate);
        xmin = chip[i].point.x - i_width/2;
        xmax = chip[i].point.x + i_width/2;
        ymin = chip[i].point.y - i_heigth/2;
        ymax = chip[i].point.y + i_heigth/2;
        if((xmin <= 0)||(xmax >= interposer.width)||(ymin <= 0)||(ymax >= interposer.heigth)){
            current_place =1;
            printf("chiplet %d 超出interposer，current_place = %d\n", i, current_place);
            break;
        }
        for(int j = 0; j < i; j++){
            if(double_die_check(chip[i], chip[j]) == 0){
                current_place = 1;
                printf("chiplet %d 与chiplet %d发生重叠，current_place = %d\n", i, j, current_place);
                break;
            }
        }
    }
    if(current_place == 0){
        return 1;
    }
    else if(current_place == 1){
        return 0;
    }
    else{
        printf("检测程序出现问题\n");
    }
}


int try_swap(vector<chiplet> &chip, vector<vector<int>> &nets, size &interposer){
    cout<<"----------start random swap chiplet---------"<<endl;
    while(check_place(chip, nets, interposer) == 1){
        srand((unsigned)time(0));
        int rand_num = rand()%(chip.size());
        cout<<"随机移动的die为 = "<<rand_num<<endl;
    }
    return 0;
}




float starting_t(){
    float a = 100;
    return a;
}


void update_t(){

}


void update_rlim(){

}


int exit_crit(){
    return 0;
}
