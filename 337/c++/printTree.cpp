#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

struct TreeNode { //树结点定义
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    void read(int input[], int& num); //读入输入函数
    TreeNode* buildTree(int input[], int& num); //生成二叉树函数
};

void Solution::read(int input[], int& num)
{
    string buffer;
    cin >> buffer; //输入
    string::iterator ster = buffer.begin();
    for (; ster < buffer.end(); ++ster) {
        if (*ster == '[' || *ster == ',')
            continue;
        else if (*ster == ']')
            break;
        else if (*ster != 'n')
            input[num] = atoi(&(*ster));
        else {
            input[num] = -1; //如果为null,val赋值为-1
            ster += 4;
        }
        ++num; //指向下一个
    }
    --num; //指向末尾
}

TreeNode* Solution::buildTree(int input[], int& num)
{
    TreeNode* treenode[32]; //存入树节点的指针
    for (int i = 1; i <= num; ++i) {
        TreeNode* temp = new TreeNode(input[i]); //生成树节点
        treenode[i] = temp; //记录指向结点的指针，方便连接树结构
        if (i != 1) { //不是根节点
            if (i % 2 == 0) {
                treenode[i / 2]->left = temp; //该结点为其根节点的左孩子
            }
            else {
                treenode[i / 2]->right = temp; //该结点为其根节点的右孩子
            }
        }     
    }
    return treenode[1]; //返回根节点
}

//树形打印函数
int getHeight(const TreeNode* node) //二叉树的高度
{	
    int treeHeight = 0;
    if (node != NULL) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        treeHeight = leftHeight >= rightHeight ? leftHeight + 1 : rightHeight + 1;
    }
    return treeHeight;
}

void getLine(const TreeNode* root, int depth, vector<int>& vals) 
{
    int placeholder = -1;
    if (depth <= 0 && root != NULL) {
        vals.push_back(root->val);
        return;
    }
    if (root->left != NULL)
        getLine(root->left, depth - 1, vals);
    else if (depth - 1 <= 0)
        vals.push_back(placeholder);
    if (root->right != NULL)
        getLine(root->right, depth - 1, vals);
    else if (depth - 1 <= 0)
        vals.push_back(placeholder);
}

int flag = 0;

void printRow(const TreeNode* p, int depth) {
    vector<int> vec;
    int placeholder = -1;
    getLine(p, depth, vec);
    cout << setw(flag--); // scale setw with depth
    bool toggle = true; // start with left
    if (vec.size() > 1) {
        for (int v = 0; v < vec.size(); ++v) {
            if (vec[v] != placeholder) {
                if (toggle)
                    cout << "/";
                else
                    cout << " \\" << setw(2 * (depth - 1));
            }
            else {
                if (toggle)
                    cout << " ";
                else
                    cout << "  ";
            } 
            toggle = !toggle;
        }
        cout << endl;  
        cout << setw(flag--); //输出宽度递减，为输出叶子做准备
    }
    toggle = true; // start with left
    for (int v = 0; v < vec.size(); v++) {
        if (vec[v] != -1) {
            if (toggle)
                cout << vec[v] << "   "; //第一个空格占位
            else
                cout << vec[v] << setw(pow(2, flag + 1) - 1);
        }
        else {
            if (v == 0)
                cout << " "; //第一个空格占位
            if (toggle)
                cout << " " << setw(3);  
        }
        toggle = !toggle;
    }
    cout << endl;
}

void postorder(TreeNode* p) {
    int height = getHeight(p);
    flag = height + 2; //取齐第一次减减
    for (int i = 0; i < getHeight(p); i++) {
        printRow(p, i);
        height--;
    }
}

int main()
{
    int num = 1, input[32]; //input 存入结点值 从1开始存入, num 记录结点数
    Solution solu;

    solu.read(input, num); //读入数据，并加以处理
    TreeNode* root = solu.buildTree(input, num); //生成二叉树
    postorder(root);

}
