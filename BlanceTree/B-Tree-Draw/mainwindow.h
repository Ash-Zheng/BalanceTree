#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<iostream>
#include<limits.h>
#include<stack>
#include<queue>
#include<math.h>
using namespace std;

struct Node
{
    int num = 0; //节点中元素的数目,用于检测节点是否需要分裂
    int tag = 0;//表示是上一个节点的第几个指针指向的节点,0表示根节点
    int a[3] = { INT_MAX,INT_MAX ,INT_MAX };//用于保存节点元素
    Node *p[4];//用于保存指向下一个节点的指针
    int x;     //绘图x坐标
    int y;     //绘图y坐标
    int level; //节点所在层数
    int leaf;  //子树所拥有的叶节点个数
};

extern Node*Root_Node;
extern int Node_num;
extern int xx;
extern int yy;
extern bool insert_fail;
extern bool del_fail;
extern int search_fail;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_BT_insert_clicked();

    void on_BT_del_clicked();

    void on_BT_search_clicked();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *);//重写基类的绘图方法
};


extern Node* divide(Node*&Root);
extern void init(Node *&Root,int n,int tag, Node* &pre);
extern bool addnum(Node* &Root, int n);
extern void minnum(Node* &Root, int n);
extern bool insert(Node* &Root,int n);
extern bool del(Node* &Root, int n);
extern int search(Node* &Root, int n);
extern void set_axis(Node*&Root);

#endif // MAINWINDOW_H
