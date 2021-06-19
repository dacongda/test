#include <bits/stdc++.h>
#define MAX 3001
//数组的最大范围，可调整
using namespace std;
void randomn(){
    srand(time(0));
    int n=rand()%400;
    cout<<n<<endl;
    for(int i=1;i<=n;i++)
        cout<<rand()%400+1<<' '<<rand()%400+1<<endl;
    n=rand()%500;
    cout<<n<<endl;
    for(int i=1;i<=n;i++)
        cout<<rand()%400+1<<' '<<rand()%400+1<<endl;
}
class dset{//用类进行实现，方便运算于查看
private:
    int **graph;
    set<int,less<int>> dom;//定义域
    set<int,less<int>> ran;//值域
    set<int,less<int>> collect;//集合
    int x_max=0;//行最大值
    int y_max=0;//列最大值
    int Reflexive_stu=0;//是否自反，可以通过修改值实现预处理后再输出结果
    int symmetry_stu=0;//是否对称，可以通过修改值实现预处理后再输出结果
    int trans_stu=0;//是否传递，可用bool
public:
    dset(){
        graph=new int*[MAX];
        for(int i=0;i<MAX;i++){
            graph[i]=new int[MAX];
            memset(graph[i],0,sizeof(graph[i]));
        }//动态分配数组大小，防止过大导致堆空间的内存溢出
        int n,x,y;
        cout<<"请输入有序对数量"<<endl;cin>>n;
        cout<<"请输入"<<n<<"对有序对,最大值<=3000"<<endl;
        while(n--){
            cin>>x>>y;
            graph[x][y]=1;
            dom.insert(x);
            ran.insert(y);
            collect.insert(x);
            collect.insert(y);
            x_max=max(x,x_max);
            y_max=max(y,y_max);    
        }//进行关系的创建与预处理
        is_Reflexive();
        is_symmetry();
        is_trans();
    };
    dset(int a){
        graph=new int*[MAX];
        for(int i=0;i<MAX;i++){
            graph[i]=new int[MAX];
            memset(graph[i],0,sizeof(graph[i]));
        }
        
    }
    void show(){
        cout<<"{";
        for(int i=1;i<=x_max;i++){
            for(int j=1;j<=y_max;j++)
                if(graph[i][j])
                    cout<<'<'<<i<<','<<j<<'>'<<',';
        }
        cout<<"\b}"<<endl;
    };//对输入的关系进行再分析，并显示
    void show_dom(){
        cout<<"定义域如下"<<endl;
        cout<<"{";
        for(auto s:dom){
            cout<<s<<',';
        }
        cout<<"\b}";
        cout<<endl;
    };//输出定义域
    void show_ran(){
        cout<<"值域如下"<<endl;
        cout<<"{";
        for(auto s:ran){
            cout<<s<<',';
        }
        cout<<"\b}";
        cout<<endl;
    };//输出值域
    void show_fld(){
        cout<<"域如下"<<endl;
        cout<<"{";
        for(auto s:collect){
            cout<<s<<',';
        }
        cout<<"\b}";
        cout<<endl;
    };//输出域Ia
    void complex(){
        cout<<"复合运算"<<endl;
        dset b;
        int n=max(x_max,max(y_max,max(b.x_max,b.y_max)));//算出新矩阵最大大小
        int a=1;//无意义变量，负责使类的创建进入临时创建
        dset c(a);//创建临时关系方便输出，减少重复代码
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                for(int k=1;k<=n;k++){
                    c.graph[i][j]+=graph[i][k]*b.graph[k][j];//通过矩阵乘法进行运算
                }
        c.x_max=n;
        c.y_max=n;
        c.show();//输出复合运算结果
    }//矩阵的复合运算
    void is_Reflexive(){
        bool flagy=1;//自反
        bool flagn=1;//反自反
        for(auto s:collect){
            if(graph[s][s])
                flagn=0;
            else
                flagy=0;
        }
        if(flagy and !flagn){
            Reflexive_stu=1;
        }
        else if(!flagy and flagn){
            Reflexive_stu=2;
        }
        else
            Reflexive_stu=0;
    }//自反
    void show_Reflexive(){
        if(Reflexive_stu==1){
            cout<<"自反"<<endl;
        }
        else if(Reflexive_stu==2){
            cout<<"反自反"<<endl;
        }
        else
            cout<<"即不自反也不反自反"<<endl;
    }
    void is_symmetry(){
        bool flagy=1;
        bool flagn=1;
        for(int i=1;i<=x_max;i++){
            for(int j=1;j<=y_max;j++)
                if(graph[i][j]){
                    if(!graph[j][i])//检查对角线
                        flagy=0;
                    if(i!=j)
                        flagn=0;
                }
        }
        if(flagy and flagn){
            symmetry_stu=1;
        }else if(flagy and !flagn){
            symmetry_stu=2;
        }else if(!flagy and flagn){
            symmetry_stu=-1;
        }else
            symmetry_stu=0;
        cout<<endl;
    }//对称
    void show_symmetry(){
        if(symmetry_stu==1)
            cout<<"对称且反对称"<<endl;
        else if(symmetry_stu==2)
            cout<<"对称但非反对称"<<endl;
        else if(symmetry_stu==-1)
            cout<<"非对成但反对称"<<endl;
        else
            cout<<"非对称非反对称"<<endl;
    }
    void is_trans(){
        int **g2;
        g2=new int*[MAX];//创建临时的关系矩阵，用于存储R²
        bool flag=1;
        for(int i=0;i<MAX;i++){
            g2[i]=new int[MAX];
            memset(g2[i],0,sizeof(g2[i]));
        }
        int n=max(x_max,y_max);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                for(int k=1;k<=n;k++){
                    g2[i][j]+=graph[i][k]*graph[k][j];//进行矩阵相乘
                }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(g2[i][j] and !graph[i][j])//检测R²是否属于R
                    flag=0;
        if(flag){
            trans_stu=1;
        }
        else
            trans_stu=0;
        for(int i=0;i<MAX;i++)
            delete g2[i];

    }//传递
    void show_trans(){
        if(trans_stu)
            cout<<"传递"<<endl;
        else
            cout<<"非传递"<<endl;
    }
    void calt(){
         int **g2,**g1;
        g1=new int*[MAX];//结果
        g2=new int*[MAX];//M的n次方
        int n=max(x_max,y_max);
        for(int i=0;i<MAX;i++){
            g1[i]=new int[MAX];
            g2[i]=new int[MAX];
            memset(g1[i],0,sizeof(g1[i]));
            memset(g2[i],0,sizeof(g2[i]));
        }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)    
                g1[i][j]+=graph[i][j];
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                for(int k=1;k<=n;k++){
                    g2[i][j]+=graph[i][k]*graph[k][j];
                }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)    
                g1[i][j]+=g2[i][j];
        clock_t start,finish;
        start=clock();
        while(comp(g2,graph,n)){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                for(int k=1;k<=n;k++){
                    g2[i][j]+=g2[i][k]*graph[k][j];
                }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)    
                g1[i][j]+=g2[i][j];
        }
        finish=clock();
        cout<<"耗时"<<setiosflags(ios::fixed)<<setprecision(8)<<(double)(finish-start)/CLOCKS_PER_SEC<<"秒"<<endl;//输出消耗时间
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                if(g1[i][j])
                    cout<<'<'<<i<<','<<j<<'>'<<' ';//输出结果
        }
        cout<<endl;
        for(int i=0;i<MAX;i++){
            delete g1[i];
            delete g2[i];
        }//随手释放内存好习惯
    }//计算传递闭包t(R)
    bool comp(int **a,int **b,int n){
        for(int i=0;i<=n;i++)
            for(int j=0;j<=n;j++)
                if(a[i][j] and !b[i][j])
                    return 0;
        return 1;
    }
    void is_equel(){
        if(Reflexive_stu==1 and symmetry_stu>=0 and trans_stu)//判断是否为自反，对称，传递
            cout<<"是等价关系"<<endl;
        else{
            cout<<"不是等价关系"<<endl;
            return;
        }
        set<int> vis;//存储检测过的，防重复
        cout<<"A/R={";
        for(int i=1;i<=x_max;i++){
            if(vis.count(i) or !graph[i][i])
                continue;
            cout<<"{";
            for(int j=1;j<=x_max;j++){
                if(graph[i][j]){
                    cout<<j<<',';
                    vis.insert(j);
                }
            }
            cout<<'\b'<<"},";
        }
        cout<<'\b'<<"}"<<endl;
    }
    ~dset(){//用完类随手释放内存
        for(int i=0;i<MAX;i++)
            delete graph[i];
    }
};
int main(){
    FILE *fp;
    freopen("in.dat","w",stdout);
    randomn();
    fclose(stdout);
    cin.clear();
    freopen("out.dat","w",stdout);
    freopen("in.dat","r",stdin);
	dset test;
    test.show();
    test.show_dom();
    test.show_ran();
    test.show_fld();
    test.show_Reflexive();
    test.show_symmetry();
    test.show_trans();
    test.calt();
    test.is_equel();
    test.complex();
    //进行线性的检测，也可以更改部分顺序
}