#include <bits/stdc++.h>
#include <conio.h>

using namespace std;
int card;
int card_list[13];
int cnt_list;
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
    string Level;
    string Name;
    string Password;
    char Card[5];

public:
    CCard(string name, string password, string level);
    ~CCard();
    void FirstPlayTwo();
    int GetNumber(); //返回牌数
    double GetPip(); //返回点数大小
    void DisplayPip();
    void DisplayPip(int);
    void TurnPlay(); //加一张牌
    void Win();
    void Lose();
    void Draw();
    int SetGamble(int);
    int GetMoney;
    void DisplayInfo(); //对局统计
    char *GetCurrentCard();
    void DeleteCard(void);
    void ModifyCard(double);
    int AddGamble(int);
    void setLevel(int);
    int getDollar();
    void init();
};
int CCard::getDollar()
{
    return this->nDollar;
}
void CCard::init()
{
    this->nNumber = 0;
    this->nGameble = 0;
}
double CCard::GetPip()
{
    double ans = 0;
    for (int i = 0; i < this->nNumber; ++i)
        ans += naPip[i];
    return ans;
}
void CCard::TurnPlay()
{
    card = card_list[cnt_list++];
    char ch;
    if (card == 11)
        ch = 'J';
    else if (card == 12)
        ch = 'Q';
    else if (card == 13)
        ch = 'K';
    else
        ch = card + '0';
    if (card > 10)
    {
        this->naPip[this->nNumber] = 0.5;
        this->Card[this->nNumber] = ch;
        this->nNumber++;
    }
    else
    {
        this->naPip[this->nNumber] = (double)card;
        this->Card[this->nNumber] = ch;
        this->nNumber++;
    }
}
int CCard::GetNumber()
{
    return this->nNumber;
}
void CCard::FirstPlayTwo()
{
    TurnPlay();
    TurnPlay();
    return;
}
void CCard::DisplayPip()
{
    printf("cardnum %d\n", this->GetNumber());
    printf("玩家手牌:");
    for (int i = 0; i < this->GetNumber(); ++i)
    {
        printf(" %c   ", this->Card[i]);
    }
    printf("\n玩家点数:");
    for (int i = 0; i < this->GetNumber(); ++i)
    {
        printf("%4.1f ", this->naPip[i]);
    }
    printf("\n玩家总点数:%.1f\n\n", this->GetPip());
}
void CCard::DisplayPip(int x)
{
    printf("电脑手牌:");
    for (int i = 0; i < this->GetNumber(); ++i)
    {
        printf(" %c   ", (i == 0) ? '?' : this->Card[i]);
    }
    printf("\n电脑点数:");
    printf(" %c   ", '?');
    for (int i = 1; i < this->GetNumber(); ++i)
    {
        printf("%4.1f ", this->naPip[i]);
    }
    printf("\n电脑总点数:? + %.1f\n\n", this->GetPip() - this->naPip[0]);
}
void CCard::DisplayInfo()
{
    printf("对局统计:\n");
    printf("账户名:%s\n", this->Name.c_str());
    printf("剩余本金:%d\n", this->nDollar);
    printf("本局胜场数:%d\n", this->nWin);
    printf("本局平场数:%d\n", this->nDraw);
    printf("本局败场数:%d\n", this->nLose);
    return;
}
CCard::CCard(string name, string password, string level)
{
    memset(this->naPip, 0, sizeof(this->naPip));
    nNumber = 0;
    nDollar = 1000;
    nGameble = 50;
    nWin = 0;
    nLose = 0;
    nDraw = 0;
    this->Level = level;
    this->Name = name;
    this->Password = password;
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
    printf("\n----------------------------------------------------\n");//分割线
    srand((unsigned)time(NULL)); //以当前时间初始化随机数种子
    int cnt = 0;
    while (cnt != 13)
    {
        bool check = true;
        card = rand() % 13 + 1;
        for (int i = 0; i < cnt; ++i)
        {
            if (card == card_list[i])
            {
                check = false;
                break;
            }
        }
        if (check)
        {
            card_list[cnt++] = card;
        }
    }
    printf("\n");
    cnt_list = 0;
    Player->init();
    Computer->init();
    //初始化完毕,正式开始游戏
    Player->FirstPlayTwo();
    Computer->FirstPlayTwo();
    printf("初始牌已发放\n");
    //初始两张牌发放完毕
    Player->DisplayPip();
    Computer->DisplayPip(1);
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
        file.open("./Users_LogInfo.txt");
        while (getline(file, name_list))
        {
            if (name.compare(name_list) == 0)
            {
                check = true;
                break;
            }
        }
        if (!check)
        {
            file.close();
            file.clear();
            printf("未找到该用户,请考虑创建用户\n");
        }
        else
            break;
    }
    getline(file, name_list);
    while (true)
    {
        printf("请输入密码,退出请键入/exit:\n");
        char ch;
        password = "";
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
    printf("登陆成功!\n");
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
    Player->DisplayInfo();
}
inline void NewGame()
{
    while (OpenNew() && Player->getDollar() > 0)
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
    printf("欢迎来到21点游戏!\n");
    Welcome();
    return 0;
}