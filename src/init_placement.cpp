#include <init_placement.h>

void init_placement(vector<chiplet> &chip, vector<vector<int>> &nets, size &interposer)
{
    void createBiTree(BiTree &T);
    void initplace(BiTree &T, vector<chiplet> &chip, int flag);
    BiTree a;
    a->TreeNum = 0;
    printf("请输入根节点：\n");
    createBiTree(a);
    initplace(a, chip, 1);
    cout<<"hello"<<endl;
}

void createBiTree(BiTree &T){
    int a;
    cin >> a;
    if(-1 == a){
        T = NULL;
    }
    else{
        T = new TreeNode;
        T ->TreeNum = int(a);
        printf("请输入节点%d的左节点\n",a);
        createBiTree(T->left);
        printf("请输入节点%d的右节点\n",a);
        createBiTree(T->right);
    }
}

void initplace(BiTree &T, vector<chiplet> &chip, int flag){
    if(flag == 1){
        cout<< T->TreeNum <<endl;
        chip[T->TreeNum].point.x = (chip[T->TreeNum].size.width*cos(chip[T->TreeNum].rotate) + chip[T->TreeNum].size.heigth*sin(chip[T->TreeNum].rotate))/2;
        chip[T->TreeNum].point.y = (chip[T->TreeNum].size.heigth*cos(chip[T->TreeNum].rotate) + chip[T->TreeNum].size.width*sin(chip[T->TreeNum].rotate))/2;
    }
    if (T)
    {
        
        initplace(T->left, chip, 0);
        initplace(T->right, chip, 0);
    }
    
}