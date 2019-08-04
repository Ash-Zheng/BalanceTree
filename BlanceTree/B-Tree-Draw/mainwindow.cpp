#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);

    QPainter painter(this);//在Widget部件内部绘制

    //设置画笔风格
    QPen draw(Qt::green,3,Qt::SolidLine,Qt::RoundCap,Qt::BevelJoin);
    QPen num(Qt::black,4,Qt::SolidLine,Qt::RoundCap,Qt::BevelJoin);
    QPen fail(Qt::red,6,Qt::SolidLine,Qt::RoundCap,Qt::BevelJoin);

    if(Node_num==0)
        return;

    int hight = 0;
    Node*R = Root_Node;
    while (R != nullptr)
    {
        hight++;
        R = R->p[0];
    }

    queue<Node*>que;
    que.push(Root_Node);
    while (!que.empty())
    {
        Node*p = que.front();
        que.pop();
        painter.setPen(draw);
        QRectF ff(p->x-27,p->y-25,54,25);//以矩形下边中点为中心
        painter.drawRect(ff);//画出矩形

        for(int i=0;i<4;i++)//画出连接线
        {
            if(p->p[i]!=nullptr)
            {
                painter.drawLine(p->x,p->y,p->p[i]->x,p->p[i]->y-25);
                que.push(p->p[i]);
            }
        }
        QString s=QString::number(p->a[0]);
        if(p->num==2)
        {
            s+=' ';
            s+=QString::number(p->a[1]);
        }
        painter.setPen(num);
        painter.drawText(ff,Qt::AlignCenter,s);//写出节点内数字
    }

    if(insert_fail)
    {
        painter.setPen(fail);
        QRectF F(300,60,120,40);
        painter.drawRect(F);
        painter.drawText(F,Qt::AlignCenter,"插入失败!");
    }
    if(del_fail)
    {
        painter.setPen(fail);
        QRectF F(300,60,120,40);
        painter.drawRect(F);
        painter.drawText(F,Qt::AlignCenter,"删除失败!");
    }
    if(search_fail==1)
    {
        painter.setPen(fail);
        QRectF F(300,60,120,40);
        painter.drawRect(F);
        painter.drawText(F,Qt::AlignCenter,"Not Found!");
    }
    else if(search_fail==2)
    {
        painter.setPen(fail);
        painter.drawEllipse(xx-35,yy-32,70,40);
    }

}

void MainWindow::on_BT_insert_clicked()
{
    search_fail=0;
    del_fail=0;
    QString numberstr=ui->input->text();
    if(!numberstr.isEmpty())
    {
        int num;
        num=numberstr.toInt();
        if(Node_num==0)
        {
            init(Root_Node, num, 0, Root_Node);
            Node_num++;
        }
        else
        {
            insert_fail=insert(Root_Node,num);
            Node_num++;
        }
        set_axis(Root_Node);
        update();//重新绘图
    }
    ui->input->clear();
}

void MainWindow::on_BT_del_clicked()
{
    search_fail=0;
    insert_fail=0;
    QString numberstr=ui->input->text();
    if(!numberstr.isEmpty())
    {
        int num;
        num=numberstr.toInt();
        if(Node_num==0)
        {
            del_fail=true;
        }
        else
        {
            del_fail=del(Root_Node,num);
            Node_num--;
        }
        set_axis(Root_Node);
        if(Node_num>0)
            update();//重新绘图
        else
        {
            Root_Node=nullptr;
            update();//重新绘图
        }
    }
    ui->input->clear();
}

void MainWindow::on_BT_search_clicked()
{
    del_fail=0;
    insert_fail=0;
    QString numberstr=ui->input->text();
    if(!numberstr.isEmpty())
    {
        int num;
        num=numberstr.toInt();
        if(Node_num==0)
        {
            search_fail=true;
        }
        else
        {
            search_fail=search(Root_Node,num);
        }
        set_axis(Root_Node);
        update();//重新绘图
    }
    ui->input->clear();
}

Node* divide(Node*&Root)
{
    Node*p = new Node;
    Node*left = new Node;
    Node*right = new Node;
    for (int i = 0; i < 4; i++)
    {
        p->p[i] = nullptr;
        left->p[i] = nullptr;
        right->p[i] = nullptr;
    }
    p->a[0] = Root->a[1];
    p->num++;
    left->a[0] = Root->a[0];
    left->num++;
    right->a[0] = Root->a[2];
    right->num++;
    p->p[0] = left;
    p->p[1] = right;
    left->p[0] = Root->p[0];
    left->p[1] = Root->p[1];
    right->p[0] = Root->p[2];
    right->p[1] = Root->p[3];
    p->tag = Root->tag;
    left->tag = 1;
    right->tag = 2;
    for (int i = 0; i < 4; i++)
    {
        if (Root->p[i] != nullptr)
        {
            Root->p[i]->tag = i % 2 + 1;
        }
        Root->p[i] = p->p[i];
    }
    Root->num = p->num;
    for (int i = 0; i < 3; i++)
    {
        Root->a[i] = p->a[i];
    }
    Root->tag = p->tag;
    delete p;
    return Root;
}

void init(Node *&Root,int n,int tag, Node* &pre)
{
    Root = new Node;
    Root->a[0] = n;
    Root->num = 1;
    Root->tag = tag;
    for (int i = 0; i < 4; i++)
    {
        Root->p[i] = nullptr;
    }
    if (tag == 1)
    {
        Root->p[0] = pre->p[0];
        Root->p[1] = pre->p[1];
    }
    else if (tag == 2)
    {
        Root->p[0] = pre->p[2];
        Root->p[1] = pre->p[3];
    }
    return;
}

bool addnum(Node* &Root, int n)//在目标节点插入一个数
{
    Node*p = Root;
    p->a[p->num] = n;
    p->num++;
    for (int i = 0; i < p->num; i++)//插入数据后排序
    {
        for (int j = 0; j < p->num - i - 1; j++)
        {
            if (p->a[j] > p->a[j + 1])
            {
                int temp = p->a[j];
                p->a[j] = p->a[j + 1];
                p->a[j + 1] = temp;
            }
        }
    }
    if (p->num >= 3)return true;//返回1时需要分裂
    else return false;
}

void minnum(Node* &Root, int n)
{
    Node*p = Root;
    p->num--;
    if (n == 0)
    {
        p->a[0] = p->a[1];
    }
    p->a[1] = INT_MAX;
}

bool insert(Node* &Root,int n)
{
    Node*p = Root;
    stack<Node*> stk;//利用栈来保存搜索的路径
    while (1)
    {
        if (p == nullptr)
        {
            break;
        }
        stk.push(p);
        int node_num = p->num;
        int j = 0;
        for (int i = 0; i < node_num; i++)
        {
            if (n == p->a[j])return true;//返回0表示在树中找到了此元素，插入失败
            if (n > p->a[j])j++;
        }
        p = p->p[j];
    }
    p = stk.top();
    int tag = addnum(p, n);
    while (tag)
    {
        Node* now, *pre;
        now = stk.top();
        stk.pop();

        if (stk.empty())//若是根节点需要分裂
        {
            pre = Root;
            Node* test;
            test = divide(pre);
            pre = test;
            tag = 0;
        }
        else
        {
            pre = stk.top();
            if (pre->num == 1)
            {
                tag = addnum(pre, now->a[1]);//取中间节点值加入父节点
                if (now->tag == 2)
                {
                    init(pre->p[1], now->a[0], 1, now);
                    pre->p[1]->tag = 2;
                    init(pre->p[2], now->a[2], 2, now);
                    pre->p[2]->tag = 3;
                    delete now;
                }
                else
                {
                    pre->p[2] = pre->p[1];
                    init(pre->p[0], now->a[0], 1, now);
                    init(pre->p[1], now->a[2], 2, now);
                    delete now;
                }
                for (int i = 0; i < 3; i++)
                {
                    pre->p[i]->tag = i + 1;
                }
                tag = 0;//因为父节点现在元素总数为2，故不需要继续分裂，直接退出循环
            }
            else if (pre->num == 2)
            {
                tag = addnum(pre, now->a[1]);//取中间节点值加入根节点
                if (now->tag == 3)
                {
                    init(pre->p[2], now->a[0], 1, now);
                    init(pre->p[3], now->a[2], 2, now);
                    delete now;
                }
                else if (now->tag == 2)
                {
                    pre->p[3] = pre->p[2];
                    pre->p[3]->tag = 2;
                    init(pre->p[1], now->a[0], 1, now);
                    pre->p[1]->tag = 2;
                    init(pre->p[2], now->a[2], 2, now);
                    pre->p[2]->tag = 1;
                    delete now;
                }
                else
                {
                    pre->p[3] = pre->p[2];
                    pre->p[3]->tag = 2;
                    pre->p[2] = pre->p[1];
                    pre->p[2]->tag = 1;
                    init(pre->p[0], now->a[0], 1, now);
                    init(pre->p[1], now->a[2], 2, now);
                    delete now;
                }
            }
        }
    }
    return false;
}

bool del(Node* &Root, int n)
{
    Node*p = Root;
    int break_tag = 0;
    stack<Node*> stk;//利用栈来保存搜索的路径
    while (break_tag==0)
    {
        if (p == nullptr)
        {
            return true;//未找到要删除的元素，删除失败，返回0
        }
        stk.push(p);
        int node_num = p->num;
        int j = 0;
        for (int i = 0; i < node_num; i++)
        {
            if (n == p->a[j])
            {
                break_tag++;
                break;
            }
            if (n > p->a[j])j++;
        }
        p = p->p[j];
    }
    p = stk.top();
    stk.pop();
    Node* now, *pre;
    now = p;
    if (stk.empty())
        pre = Root;
    else
        pre = stk.top();

    //首先判断是不是叶节点
    int leaf_tag = 0;
    int sum = 0;
    for (int i = 0; i < 4; i++)
    {
        if (p->p[i] == nullptr)sum++;
    }
    if (sum == 4)leaf_tag = 1;//没有子结点，故为叶结点

    if(leaf_tag==0)
    {
        int pls;//记录待删除元素所在位置
        if (now->a[0] == n)pls = 1;
        else pls = 2;

        p = now->p[pls];

        stack<Node*> stk1;
        stk1.push(now);
        while (p != nullptr)
        {
            stk1.push(p);
            p = p->p[0];
        }
        p = stk1.top();
        int temp = p->a[0]; //交换后继元素

        while (!stk.empty())
        {
            stk.pop();
        }
        Node*q=Root;
        break_tag=0;
        while (break_tag==0)
        {
            if (q == nullptr)
            {
                return true;//未找到要删除的元素，删除失败，返回0
            }
            stk.push(q);
            int node_num = q->num;
            int j = 0;
            for (int i = 0; i < node_num; i++)
            {
                if (temp == q->a[j])
                {
                    break_tag++;
                    break;
                }
                if (temp > q->a[j])j++;
            }
            q = q->p[j];
        }
        q = stk.top();

        p->a[0]=n;
        now->a[pls - 1] = temp;

        stk.pop();
        now = q;

        if (stk.empty())
            pre = Root;
        else
            pre = stk.top();
    }


    //是叶节点
    {
        if (p->num == 2)//节点内有2个元素,直接删除
        {
            if (p->a[0] == n)
                p->a[0] = p->a[1];
            p->a[1] = INT_MAX;
            p->num--;
        }
        else//节点内只有一个元素
        {
            if (pre == now)//整棵树只有一个元素
            {
                Root->a[0] = INT_MAX;
                Root->num = 0;
            }
            else if (pre->p[now->tag] != nullptr && pre->p[now->tag]->num == 2)//右侧兄弟节点有2个元素
            {
                Node*bro = pre->p[now->tag];
                now->a[0] = pre->a[now->tag - 1];
                pre->a[now->tag - 1] = bro->a[0];
                bro->a[0] = bro->a[1];
                bro->a[1] = INT_MAX;
                bro->num -= 1;
            }
            else if (now->tag >= 2 && pre->p[now->tag - 2] != nullptr && pre->p[now->tag - 2]->num == 2)//左侧兄弟节点有2个元素
            {
                Node*bro = pre->p[now->tag - 2];
                now->a[0] = pre->a[now->tag - 2];
                pre->a[now->tag - 2] = bro->a[1];
                bro->a[1] = INT_MAX;
                bro->num -= 1;
            }
            else if (now->tag == 1 && pre->p[now->tag + 1] != nullptr && pre->p[now->tag + 1]->num == 2)//右右侧兄弟节点有2个元素
            {
                Node*bro1 = pre->p[now->tag];
                Node*bro2 = pre->p[now->tag + 1];
                now->a[0] = pre->a[0];
                pre->a[0] = bro1->a[0];
                bro1->a[0] = pre->a[1];
                pre->a[1] = bro2->a[0];
                bro2->a[0] = bro2->a[1];
                bro2->a[1] = INT_MAX;
                bro2->num -= 1;
            }
            else if (now->tag == 3 && pre->p[now->tag - 3] != nullptr && pre->p[now->tag - 2]->num == 2)//左左侧兄弟节点有2个元素
            {
                Node*bro1 = pre->p[now->tag - 2];
                Node*bro2 = pre->p[now->tag - 3];
                now->a[0] = pre->a[1];
                pre->a[1] = bro1->a[0];
                bro1->a[0] = pre->a[0];
                pre->a[0] = bro2->a[1];
                bro2->a[1] = INT_MAX;
                bro2->num -= 1;
            }
            else//需要合并节点
            {
                if (pre->num == 1)//父节点只有一个元素,兄弟节点和父节点合并
                {
                    int temp;
                    if (now->tag == 1)
                        temp = pre->p[1]->a[0];
                    else
                        temp = pre->p[0]->a[0];

                    for (int i = 0; i < 2; i++)//删除子节点
                    {
                        delete pre->p[i];
                        pre->p[i] = nullptr;
                    }
                    addnum(pre, temp);//在父节点中加入兄弟节点的元素

                    stk.pop();
                    int brk_tag = 0;
                    while (!stk.empty()&&brk_tag==0)
                    {
                        now = pre;
                        pre = stk.top();
                        stk.pop();
                        Node*bro;
                        if (pre->num == 1)//父节点只有一个元素
                        {
                            if (now->tag == 1)//向右合并
                            {
                                bro = pre->p[1];
                                if (bro->num == 1)
                                {
                                    addnum(pre, bro->a[0]);
                                    pre->p[1] = bro->p[0];
                                    pre->p[2] = bro->p[1];
                                    bro->p[0]->tag = 2;
                                    bro->p[1]->tag = 3;
                                    delete bro;
                                }
                                else
                                {
                                    addnum(pre, bro->a[0]);
                                    addnum(pre, bro->a[1]);
                                    pre->p[1] = bro->p[0];
                                    pre->p[2] = bro->p[1];
                                    pre->p[3] = bro->p[2];
                                    delete bro;
                                    divide(pre);
                                    brk_tag++; //退出循环
                                }
                            }
                            else //向左合并
                            {
                                bro = pre->p[0];
                                if (bro->num == 1)
                                {
                                    addnum(pre, bro->a[0]);
                                    pre->p[0] = bro->p[0];
                                    pre->p[1] = bro->p[1];
                                    pre->p[2] = now;
                                    now->tag = 3;
                                    delete bro;
                                }
                                else
                                {
                                    addnum(pre, bro->a[0]);
                                    addnum(pre, bro->a[1]);
                                    pre->p[0] = bro->p[0];
                                    pre->p[1] = bro->p[1];
                                    pre->p[2] = bro->p[2];
                                    pre->p[3] = now;
                                    bro->p[0]->tag = 2;
                                    bro->p[1]->tag = 1;
                                    bro->p[2]->tag = 2;
                                    delete bro;
                                    divide(pre);
                                    brk_tag++; //退出循环
                                }
                            }
                        }
                        else//父节点有两个元素
                        {
                            brk_tag++; //退出循环
                            if (now->tag == 1)//向右合并
                            {
                                bro = pre->p[1];
                                if (bro->num == 1)
                                {
                                    addnum(bro, pre->a[0]);
                                    bro->tag = 1;
                                    bro->p[0]->tag = 2;
                                    bro->p[1]->tag = 3;
                                    pre->p[2]->tag = 2;
                                    pre->a[0] = pre->a[1];
                                    pre->a[1] = INT_MAX;
                                    pre->num--;
                                    bro->p[2] = bro->p[1];
                                    bro->p[1] = bro->p[0];
                                    bro->p[0] = now;
                                    pre->p[0] = bro;
                                    pre->p[1] = pre->p[2];
                                    pre->p[2] = nullptr;
                                }
                                else
                                {
                                    Node* sis = new Node;
                                    sis->a[0] = pre->a[0];
                                    sis->num++;
                                    sis->p[0] = now;
                                    sis->p[1] = bro->p[0];
                                    bro->p[0]->tag = 2;
                                    bro->p[1]->tag = 1;
                                    bro->p[2]->tag = 2;
                                    sis->p[2] = nullptr;
                                    sis->p[3] = nullptr;
                                    sis->tag = 1;
                                    pre->a[0] = bro->a[0];
                                    bro->a[0] = bro->a[1];
                                    bro->a[1] = INT_MAX;
                                    bro->num--;
                                    bro->p[0] = bro->p[1];
                                    bro->p[1] = bro->p[2];
                                    bro->p[2] = nullptr;
                                    pre->p[0] = sis;
                                }
                            }
                            else if(now->tag==2)//向左合并
                            {
                                bro = pre->p[0];

                                if (bro->num == 1)
                                {
                                    addnum(bro, pre->a[0]);
                                    pre->a[0] = pre->a[1];
                                    pre->a[1] = INT_MAX;
                                    pre->num--;
                                    pre->p[1] = pre->p[2];
                                    pre->p[2] = nullptr;
                                    bro->p[2] = now;
                                    now->tag = 3;
                                }
                                else
                                {
                                    Node* sis = new Node;
                                    sis->tag=2;
                                    sis->num++;
                                    sis->a[0] = pre->a[0];
                                    pre->a[0]=bro->a[1];
                                    bro->a[1]=INT_MAX;
                                    sis->p[1] = now;
                                    now->tag=2;
                                    sis->p[0]=bro->p[2];
                                    sis->p[0]->tag=1;
                                    bro->p[2]=nullptr;
                                    bro->num--;
                                    pre->p[1] = sis;
                                    sis->p[2] = nullptr;
                                    sis->p[3] = nullptr;
                                }
                            }
                            else//向左合并
                            {
                                bro = pre->p[1];

                                if (bro->num == 1)
                                {
                                    addnum(bro, pre->a[1]);
                                    pre->a[1] = INT_MAX;
                                    pre->num--;
                                    pre->p[2] = nullptr;
                                    bro->p[2] = now;
                                    now->tag = 3;
                                }
                                else
                                {
                                    Node* sis = new Node;
                                    sis->tag=3;
                                    sis->num++;
                                    sis->a[0] = pre->a[1];
                                    pre->a[1]=bro->a[1];
                                    bro->a[1]=INT_MAX;
                                    sis->p[1] = now;
                                    now->tag=2;
                                    sis->p[0]=bro->p[2];
                                    sis->p[0]->tag=1;
                                    bro->p[2]=nullptr;
                                    bro->num--;
                                    pre->p[2] = sis;
                                    sis->p[2] = nullptr;
                                    sis->p[3] = nullptr;
                                }
                            }

                        }
                    }
                }
                else
                {
                    if (now->tag == 1)
                    {
                        now->a[0] = pre->a[0];
                        addnum(now, pre->p[1]->a[0]);
                        pre->a[0] = pre->a[1];
                        pre->a[1] = INT_MAX;
                        pre->num--;
                        pre->p[1]->a[0] = pre->p[2]->a[0];
                    }
                    else if (now->tag == 2)
                    {
                        now->a[0]=pre->a[1];
                        addnum(now, pre->p[2]->a[0]);
                        pre->a[1] = INT_MAX;
                        pre->num--;
                    }
                    else if (now->tag == 3)
                    {
                        addnum(pre->p[1], pre->a[1]);
                        pre->a[1] = INT_MAX;
                        pre->num--;
                    }
                    delete pre->p[2];
                    pre->p[2] = nullptr;
                }
            }
        }
    }
    return false;
}

int search(Node* &Root, int n)
{
    Node*p=Root;
    if(p==nullptr)
        return 1;//查找失败
    while(p!=nullptr)
    {
        int j=0;
        for(int i=0;i<p->num;i++)
        {
            if(n==p->a[i])
            {
                xx=p->x;
                yy=p->y;
                return 2;
            }
            else if(n>p->a[i])
                j++;
        }
        p=p->p[j];
    }
    return 1;
}

void set_axis(Node*&Root)
{
    int hight = 0;
    int basegap = 62;
    Node*R = Root;
    while (R != nullptr)
    {
        hight++;
        R = R->p[0];
    }
    queue<Node*>que;
    stack<Node*>stk;
    que.push(Root);
    stk.push(Root);
    Root->x = 650;
    Root->y = 100;
    Root->level = 1;
    Root->leaf = 0;
    while(!que.empty())//将所有节点存入栈内
    {
        Node*p;
        p=que.front();
        que.pop();
        for(int i=0;i<4;i++)
        {
            if(p->p[i]!=nullptr)
            {
                p->p[i]->level = p->level+1;
                p->p[i]->leaf=0;
                que.push(p->p[i]);
                stk.push(p->p[i]);
            }
        }
    }

    Node*tt;
    tt=stk.top();
    if(tt->level==4)//如果层数超过4层，调整根节点位置
    {
        Root->x = 750;
    }
    else if(tt->level>=5)//如果层数超过5层，调整根节点位置
    {
        Root->x = 950;
    }

    while(!stk.empty())//利用栈倒续计算同层节点之间的间隔
    {
        Node*p;
        p=stk.top();
        stk.pop();
        if(p->p[0]==nullptr)
            p->leaf=1;
        else
        {
            p->leaf=0;
            for(int i=0;i<=p->num;i++)
            {
                p->leaf+=p->p[i]->leaf;
            }
        }
    }



    que.push(Root);
    while (!que.empty())
    {
        Node*p = que.front();
        que.pop();
        //p->leaf+=hight-p->level-1;
        int gap;

        if(p->leaf%2==0)
        {
            gap=((p->leaf-1)/2)*basegap;
            //if(p->num==1&&p->level==1)
        }
        else           
        {
            gap =(p->leaf-1)/2*basegap-int(0.5*basegap);
            //if(p->num==1&&p->level==1)
        }

        if(p->leaf==2)gap=int(0.5*basegap);
        else if(p->leaf==3)gap=basegap;

        if (p->num == 1 && p->p[0] != nullptr)
        {
            p->p[0]->y = p->y + 150;
            p->p[0]->x = p->x - gap;
            p->p[1]->y = p->y + 150;
            p->p[1]->x = p->x + gap;
            que.push(p->p[0]);
            que.push(p->p[1]);
        }
        else if (p->num == 2 && p->p[0] != nullptr)
        {
            p->p[0]->y = p->y + 150;
            p->p[0]->x = p->x - gap;
            p->p[1]->y = p->y + 150;
            p->p[1]->x = p->x;
            p->p[2]->y = p->y + 150;
            p->p[2]->x = p->x + gap;
            que.push(p->p[0]);
            que.push(p->p[1]);
            que.push(p->p[2]);
        }
    }
}




