#include <bits/stdc++.h>
#include <conio.h>

using namespace std;
class CCard
{
private:
    double naPip[5]; //一共五张牌
    int nNumber;     //实际发了多少牌
    int nDollar;     //有多少钱
    int nGameble;    //赌注
    int nWin;        //赢局数
    int nLose;       //输局数
    int nDraw;       //平局数
    int Level;       //权限标识符

public:
    CCard();
    ~CCard();
    void FirstPlayTwo();
    int GetNumber();
    double GetPip();
    void DisplayPip(int);
    void TurnPlay();
    void Win();
    void Lose();
    void Draw();
    int SetGamble(int);
    int GetMoney;
    void DisplayInfo();
    char *GetCurrentCard();
    void DeleteCard(void);
    void ModifyCard(double);
    int AddGamble(int);
    void setLevel(int);
};

CCard::CCard(/* args */)
{
}

CCard::~CCard()
{
}
inline void Create()
{
    string name, password;
    string name_list;
    string level;
    bool check;
    ifstream file;
    ofstream ofile;
    file.open("./Users_LogInfo.txt");
    while (true)
    {
        check = true;
        printf("请键入一行用户名：\n");
        getline(cin, name);
        name = "Name " + name;
        file.seekg(0, std::ios::beg);
        while (getline(file, name_list))
        {
            if (name.compare(name_list) == 0)
            {
                printf("用户名已被使用\n");
                check = false;
                break;
            }
        }
        if (check)
            break;
    }
    printf("用户名创建成功!\n");
    file.close();
    file.clear();
    ofile.open("./Users_LogInfo.txt", ios::app);
    printf("请输入密码:\n");
    char ch;
    while (true)
    {
        ch = getch();
        if (ch == '\r')
            break;
        if (ch == '\b')
        {
            printf("\b");
            password = password.substr(0, password.length() - 1);
        }
        else
        {
            printf(" ");
            password += ch;
        }
    }
    printf("密码创建成功!\n");
    printf("请输入权限[super/advanced/normal]:\n");
    getline(cin, level);
    while (level != "super" && level != "advanced" && level != "normal")
    {
        printf("无效指令,请输入权限[super/advanced/normal]:\n");
        getline(cin, level);
    }
    ofile << name << endl;
    ofile << "Password " << password << endl;
    ofile << "Level " << level << endl;
    ofile.close();
    ofile.clear();
    printf("用户创建成功！\n");
}
inline void Login()
{
}
inline void Welcome() //获取登录或创建指令
{
    printf("输入'create'进行角色创建,输入'login'进行角色登录\n");
    string log;
    getline(cin, log);
    if (log == "create")
    {
        Create();
        Welcome();
    }
    else if (log == "login")
        Login();
    else
    {
        printf("无效指令，请重新输入\n");
        Welcome();
    }
    return;
}
int main()
{
    srand((unsigned)time(NULL)); //以当前时间初始化随机数种子
    printf("欢迎来到21点游戏!\n");
    Welcome();
    return 0;
}