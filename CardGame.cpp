#include <bits/stdc++.h>
#include <conio.h>

using namespace std;
class CCard
{
private:
    int naPip[5]; //一共五张牌
    int nNumber;  //实际发了多少牌
    int nDollar;  //有多少钱
    int nGameble; //赌注
    int nWin;     //赢局数
    int nLose;    //输局数
    int nDraw;    //平局数
    string Level;
    string Name;
    string Password;

public:
    CCard(string name, string password, string level);
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
    string getName();
    int getDollar();
    int getWin();
    int getDraw();
    int getLose();
};
int CCard::getDollar()
{
    return this->nDollar;
}
int CCard::getWin()
{
    return this->nWin;
}
int CCard::getDraw()
{
    return this->nDraw;
}
int CCard::getLose()
{
    return this->nLose;
}
string CCard::getName()
{
    return this->Name;
}
CCard::CCard(string name, string password, string level)
{
    memset(naPip, 0, sizeof(naPip));
    nNumber = 0;
    nDollar = 1000;
    nGameble = 50;
    nWin = 0;
    nLose = 0;
    nDraw = 0;
    Level = level;
    Name = name;
    Password = password;
}
CCard::~CCard()
{
}
CCard *Player;
CCard *Computer;
inline void Create();
inline void Login();
inline void Welcome();
inline void MainFrame();
inline void NewGame();
inline void Info();
inline void PlayerTurn();   //玩家回合
inline void ComputerTurn(); //电脑回合
inline bool OpenNew();      //尝试开启新一轮游戏
inline void NewTurn();      //新一轮游戏
inline void NewTurn()
{
    return;
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
        printf("请键入一行用户名, 退出请键入/exit:\n");
        getline(cin, name);
        if (name == "/exit")
        {
            file.close();
            file.clear();
            Welcome();
            return;
        }
        if (name == "exit")
        {
            printf("无效用户名,请重新输入\n");
            Create();
        }
        name = "Name " + name;
        file.seekg(0, std::ios::beg); //回到文件开头读取
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
        {
            printf("\n");
            break;
        }
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
    string name, password;
    string name_list;
    string level;
    bool check;
    ifstream file;
    file.open("./Users_LogInfo.txt");
    while (true)
    {
        check = false;
        printf("请输入用户名,退出请键入/exit:\n");
        getline(cin, name);
        if (name == "/exit")
        {
            file.close();
            file.clear();
            Welcome();
            return;
        }
        name = "Name " + name;
        file.seekg(0, std::ios::beg);
        while (getline(file, name_list))
        {
            if (name.compare(name_list) == 0)
            {
                check = true;
                break;
            }
        }
        if (!check)
            printf("未找到该用户,请考虑创建用户\n");
        else
            break;
    }
    getline(file, name_list);
    while (true)
    {
        printf("请输入密码,退出请键入/exit:\n");
        char ch;
        while (true)
        {
            ch = getch();
            if (ch == '\r')
            {
                printf("\n");
                break;
            }
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
        if (password == "/exit")
        {
            file.close();
            file.clear();
            Welcome();
            return;
        }
        password = "Password " + password;
        if (password != name_list)
            printf("密码错误,请重新输入:\n");
        else
            break;
    }
    Player = new CCard(name, password, "Level " + level);
    Computer = new CCard("Name Computer", "Password Computer", "Level normal");
    printf("登陆成功! %s\n", Player->getName().c_str());
    MainFrame();
}
inline void Welcome()
{
    printf("输入'/create'进行角色创建,输入'/login'进行角色登录,输入/exit退出程序\n");
    string log;
    getline(cin, log);
    if (log == "/create")
    {
        Create();
        Welcome();
    }
    else if (log == "/login")
        Login();
    else if (log == "/exit")
        return;
    else
    {
        printf("无效指令，请重新输入\n");
        Welcome();
    }
    return;
}
inline void MainFrame()
{
    string order;
    printf("请输入指令,输入/help查看指令列表:\n");
    getline(cin, order);
    if (order == "/help")
    {
        printf("输入/new开始新游戏\n输入/exit退出登录\n输入/info查看总对局统计\n");
        MainFrame();
    }
    else if (order == "/new")
        NewGame();
    else if (order == "/exit")
    {
        delete Player;
        delete Computer;
        Welcome();
    }
    else if (order == "/info")
    {
        Info();
        MainFrame();
    }
    else
    {
        printf("无效指令,请重新输入\n");
        MainFrame();
    }
    return;
}
inline void Info()
{
    printf("总对局统计:\n");
    printf("账户名:%s\n", Player->getName().c_str());
    printf("剩余本金:%d\n", Player->getDollar());
    printf("本局胜场数:%d\n", Player->getWin());
    printf("本局平场数:%d\n", Player->getDraw());
    printf("本局败场数:%d\n", Player->getLose());
    return;
}
inline void NewGame()
{
    while(OpenNew()&&Player->getDollar()>0)
    NewTurn();
    Info();
    delete Player;
    delete Computer;
    printf("本次游戏已结束\n");
    Welcome();
    return;
}
inline bool OpenNew()
{
    Info();
    string order;
    while (true)
    {
        printf("是否要进行下一轮?[Y/N]");
        getline(cin, order);
        if (order == "Y" || order == "y")
            return true;
        else if (order == "N" || order == "n")
            return false;
        printf("无效指令,请重新输入\n");
    }
}
int main()
{
    srand((unsigned)time(NULL)); //以当前时间初始化随机数种子
    printf("欢迎来到21点游戏!\n");
    Welcome();
    return 0;
}