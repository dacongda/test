#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <sstream>
#include <array>
#include <conio.h>
#include <random>
#include <Windows.h>
#define UP_KEY 372
#define DOWN_KEY 380
#define LEFT_KEY 375
#define RIGHT_KEY 377
#define M_L_EXIT 101
#define M_R_EXIT 102
#define M_T_EXIT 103
#define M_B_EXIT 104
enum Player_Direct { UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4 };
using namespace std;
typedef short int sint;
typedef int_fast8_t fnt;
wstring Player_Name(L"郭shit");
int Task_num = 9;
int kbscan()
{
    char a = 0;
    a = _getch();
    if (a != -32)
    {
        return a;
    }
    else
    {
        a = _getch();
        return a + 300;
    }
}
typedef struct Pl_pos
{
    sint x_pos;
    sint y_pos;
    Player_Direct dir;

}PL_pos;
typedef struct Map_Exit
{
    fnt Left_exit;
    fnt Right_exit;
    fnt Up_exit;
    fnt Down_exit;
}Map_Exit;
enum nTypes{ Shoper, Task, Normal };//NPC类型
class Diolog {
private:
    std::map<std::shared_ptr<std::wstring>, std::vector<std::pair<sint, std::wstring>>>SWS;//"我"的对话与NPC对话的关系
    std::map<sint, std::vector<std::pair<fnt, std::shared_ptr<std::wstring>>>> SpecialWords;//NPC对话与任务键匹配
    std::vector<std::wstring> GreetingWords;//欢迎对话
    std::wstring  NPC_name;//NPC名字
public:
    Diolog(std::wifstream& is, std::wstring& NPC_name);
    ~Diolog() {};
    void ViewSw(int& task);
    void ViewGw();
};
Diolog::Diolog(std::wifstream& is, wstring& NPC_name) :NPC_name(NPC_name) {
    wstring ws;
    int cracks = 0;
    sint task = 9;
    while (getline(is, ws))
    {
        wistringstream wsi(ws);
        wstring name;
        wsi >> name;
        if (name != NPC_name)
            continue;
        wchar_t Dtype;
        bool If_Have_My_Word;
        sint Tk_num, uid, mwst;
        wsi >> Dtype;
        switch (Dtype)
        {
        case L'G': {
           
            wstring Diolog_Content(ws.begin() + name.size() + 3, ws.end());
            auto a = Diolog_Content.find(L'#');
            vector<wstring> special;
            while (a != -1)
            {
                auto oa = a;
                a++;
                while (Diolog_Content[a] != L'#')
                    a++;
                wstring tmp(Diolog_Content, oa + 1, a - oa - 1);
                special.push_back(tmp);
                if (tmp == L"PlayerName")
                {
                    Diolog_Content.replace(oa, a - oa + 1, Player_Name);
                    a = oa;
                    a = Diolog_Content.find(L'#', a);
                }
                else {
                    Diolog_Content.replace(oa, a - oa + 1, L"<Invaild String>");
                    a = oa;
                    a = Diolog_Content.find(L'#', a);
                }
            }
            //         wcout << name << L':' << Diolog_Content << endl;
            for (auto vc : special)
                //              wcout << vc << endl;
                Diolog_Content.shrink_to_fit();
            GreetingWords.push_back(Diolog_Content);
            wcout << Diolog_Content << endl;
            kbscan();
            break;
        }
        case L'S': {
            sint times, My_Word_Times;
            wsi >> Tk_num >> uid >> times >> If_Have_My_Word;
            int uids = Tk_num * 100 + uid;
            if (If_Have_My_Word)
            {
                wsi >> mwst;
                wstring gast;
                shared_ptr<wstring> Diolog_Content(new wstring);
                vector<pair<sint, wstring>> tesera;
                while (wsi >> gast)
                {
                    if (gast == L"#PlayerName#")
                    {
                        *Diolog_Content += Player_Name + L' ';
                    }
                    else
                        *Diolog_Content += gast + L' ';
                }
                Diolog_Content->shrink_to_fit();
                for (int n = 0; n < mwst; n++)
                {
                    getline(is, ws);

                    wstring tmp(ws.begin() + 6, ws.end());
                    wstring tmps(ws.begin() + 2, ws.begin() + 5);
                    tmp.resize(tmp.size());
                    My_Word_Times = stoi(tmps);
                    pair<sint, wstring> tmpm(My_Word_Times, tmp);
                    SWS[Diolog_Content].push_back(tmpm);
                    tesera.push_back(tmpm);
                }
                //             wcout << name << L':' << *Diolog_Content << endl;
                //             for (auto a : tesera) {
                //                wcout << "ME" << L':' << a.second << endl;
                //            }
                tesera.shrink_to_fit();
                pair<sint, shared_ptr<wstring>> tmpa(times, Diolog_Content);
                SpecialWords[task].push_back(tmpa);
            }
            else {
                wstring gast;
                shared_ptr<wstring> Diolog_Content(new wstring);
                while (wsi >> gast)
                {
                    if (gast == L"#PlayerName#")
                    {
                        *Diolog_Content += Player_Name + L' ';
                    }
                    else
                        *Diolog_Content += gast + L' ';
                }
                Diolog_Content->shrink_to_fit();
                //               wcout << name << L':' << *Diolog_Content << endl;
                pair<sint, shared_ptr<wstring>> tmpa(times, Diolog_Content);
                SpecialWords[task].push_back(tmpa);
            }
            break;
        }
        default:
            break;
        }
        //       wcout << endl;
    }
    SpecialWords[task].shrink_to_fit();
    GreetingWords.shrink_to_fit();
    // wcout << endl << endl << endl;
     ///////////////分割线//////////////////
   //  wcout << L"//////////以上为构造输出//////////";
};
void Diolog::ViewGw() {
    std::default_random_engine dre;
    std::uniform_int_distribution<unsigned> u(0, (int)GreetingWords.size());
    int a = u(dre);
    wcout << L"[" << NPC_name << "]" << GreetingWords[a] << endl;;
    kbscan();
};
void  Diolog::ViewSw(int& task)
{
    //wcout << L"/////////////////SPECIALTEST///////////////////" << endl;
    auto SP = SpecialWords[task];
    for (unsigned int a = 0; a < SP.size(); a++)
    {
        system("cls");
        auto pos = SWS.find(SP[a].second);
        if (pos != SWS.end())
        {
            auto s = SWS[SP[a].second];
            size_t chose = 0;
            int tp = 0;
            while (tp != 100)
            {
                wcout << L"[" << NPC_name << L"]" << *SP[a].second << endl;
                tp = 0;
                for (auto b : s)
                {
                    if (tp == chose)
                    {
                        wcout << L'>' << L"[" << Player_Name << L"]" << L"[" << b.first << L"]" << b.second << tp << endl;
                    }
                    else
                        wcout << L' ' << L"[" << Player_Name << L"]" << L"[" << b.first << L"]" << b.second << tp << endl;
                    tp++;
                }
                int ak = kbscan();
                // cout << ak << endl;;
                switch (ak)
                {
                case 'w': {
                    if (chose == 0)
                    {
                        chose = (s.size() - 1);
                        cout << s.size();
                    }
                    else
                        chose -= 1;
                    break;
                }
                case UP_KEY: {
                    if (chose == 0)
                        chose = (s.size() - 1);
                    else
                        chose -= 1;
                    break;
                }
                case 's': {
                    if ((chose + 1) > (s.size() - 1))
                        chose = 0;
                    else
                        chose += 1;
                    break;
                }
                case DOWN_KEY: {
                    if ((chose + 1) > (s.size() - 1))
                        chose = 0;
                    else
                        chose += 1;
                    break;
                }
                default: {tp = 100; break; }
                }
                system("cls");
            }
            // cout << chose << endl << s[chose].first << endl;
            switch (s[chose].first)
            {
            case 100:break;
            case 101: {kbscan(); return; break; };
            default: {a = (s[chose].first - 2); break; };
            }
        }
        else
        {
            wcout << L"[" << NPC_name << L"]" << *SP[a].second << endl;
            switch (SP[a].first) {
            case 100: {break; };
            case 101: {kbscan(); return; break; };
            default: {a = (SP[a].first - 2);  break; };
            }
            kbscan();
        }
    };
};
class NPC {
private:
    int type;
    fnt uuid;
    wstring name;
    Diolog dg;
public:
    //NPC(fnt& NPC_UID) {};
    NPC(int ntp, fnt& uid, wstring& n, wifstream& wis) :type(ntp), uuid(uid), name(n),dg(wis,name){};//临时构造函数
    ~NPC() {};
    void talk() {
        dg.ViewGw();
        int task = 9;
        dg.ViewSw(task);
    };
    wstring getname() { wstring a(name); return a; }
};
wstring an(L"alian");
wstring bn(L"teser");
wifstream wis("t.txt");
fnt anid = 1;
fnt bnid = 2;
class maps {
    //////MAP DEFINE 0=AIR 1-100-RESOURCE 101-110-EXIT 111-120-NPC//////
private:
    sint uuid;
    int siz[24][24];
    wchar_t oupic[24][24];
    sint tpuuid[4];
    wchar_t describe[100];
    PL_pos pp;
    Map_Exit Mp;
    vector<NPC> npcs;
public:
    maps():siz{ 0 }, Mp{ 0,0,0,0 }, pp{ 0,0,UP }, npcs{ NPC((int)Task,anid,an,wis), NPC((int)Task,bnid,bn,wis) }
    {
        pp.x_pos = 12;
        pp.y_pos = 12;
        pp.dir = UP;
        siz[12][0] = M_L_EXIT;
        siz[11][0] = M_L_EXIT;
        siz[7][8] = 111;
        siz[6][5] = 112;
        //////////以上为debug定义/////////////
        for (int n = 0; n < 24; n++)
            for (int j = 0; j < 24; j++)
            {
                if (siz[n][j] == 0)
                {
                    oupic[n][j] = L'□';
                }
                else if (110 < siz[n][j] and 120 >= siz[n][j])
                {
                    oupic[n][j] = L'◆';
                }
                else if (101 <= siz[n][j] and siz[n][j] <= 104)
                {
                    oupic[n][j] = L'Π';
                }
            }
    }
    ~maps() {};
    bool if_invaild(sint x, sint y) {
        if (x < 0 or x >= 24 or y < 0 or y >= 24)
            return true;
        else if (siz[y][x] >= 101 and siz[y][x] <= 104)
            return true;
        else if (siz[y][x] > 110 and siz[y][x] <= 120)
            return true;
        return false;
    }
    int view() {
        sint tj = 0;
        sint React = 0;
        while (1) {
            system("cls");
            wchar_t wt = oupic[pp.y_pos][pp.x_pos];
            switch (pp.dir) {
            case UP:oupic[pp.y_pos][pp.x_pos] = L'▲'; break;//
            case DOWN:oupic[pp.y_pos][pp.x_pos] = L'▼'; break; //
            case LEFT:oupic[pp.y_pos][pp.x_pos] = L'﹛'; break;//
            case RIGHT:oupic[pp.y_pos][pp.x_pos] = L'﹜'; break;//玩家方向
            }
            for (int n = 0; n < 24; n++)
            {
                for (int j = 0; j < 24; j++)
                    wcout << oupic[n][j];
                wcout << endl;
            }
            switch (pp.dir)
            {
            case UP: {                
                if (pp.y_pos - 1 <= 0)
                    break;
                else {
                    int forward_item = siz[pp.y_pos - 1][pp.x_pos];
               if (101 <= forward_item and 104 >= forward_item)
                    wcout << L"按E互动" << endl;
                else if (110 < forward_item and 120 >= forward_item)
                    wcout << L"按E与" << npcs[forward_item - 111].getname() <<L"互动";
                break;
                }
            }
            case DOWN: {
                if (pp.y_pos + 1 >= 24)
                    break;
                else {
                    int forward_item = siz[pp.y_pos + 1][pp.x_pos];
                    if (101 <= forward_item and 104 >= forward_item)
                        wcout << L"按E互动" << endl;
                    else if (110 < forward_item and 120 >= forward_item)
                        wcout << L"按E与" << npcs [forward_item - 111].getname() << L"互动";
                    break;
                }
            }
            case LEFT: {
                if (pp.x_pos - 1 >= 24)
                    break;
                else {
                    int forward_item = siz[pp.y_pos][pp.x_pos - 1];
                    if (101 <= forward_item and 104 >= forward_item)
                        wcout << L"按E互动" << endl;
                    else if (110 < forward_item and 120 >= forward_item)
                        wcout << L"按E与" <<npcs[forward_item - 111].getname() << L"互动";
                    break;
                }
            }
            case RIGHT: {
                if (pp.x_pos + 1 >= 24)
                    break;
                else {
                    int forward_item = siz[pp.y_pos][pp.x_pos + 1];
                    if (101 <= forward_item and 104 >= forward_item)
                        wcout << L"按E互动" << endl;
                    else if (110 < forward_item and 120 >= forward_item)
                        wcout << L"按E与" << npcs[forward_item- 111].getname() << L"互动";
                    break;
                }
            };
            }
            oupic[pp.y_pos][pp.x_pos] = wt;
            sint ks = kbscan();
            switch (ks) {
            case 'w': {
                if (if_invaild(pp.x_pos, pp.y_pos - 1))
                {
                    pp.dir = UP;
                    break;
                }
                else pp.y_pos--;
                pp.dir = UP;
                break;
            };
            case 'a': {
                if (if_invaild(pp.x_pos - 1, pp.y_pos))
                {
                    pp.dir = LEFT;
                    break;
                }
                else
                    pp.x_pos--;
                pp.dir = LEFT;
                break;
            };
            case 's': { if (if_invaild(pp.x_pos, pp.y_pos + 1))
            {
                pp.dir = DOWN;
                break;
            }
                    else
                pp.y_pos++;
                pp.dir = DOWN;
                break;
            };
            case 'd': { if (if_invaild(pp.x_pos + 1, pp.y_pos))
            {
                pp.dir = RIGHT;
                break;
            }
                    else
                pp.x_pos++;
                pp.dir = RIGHT;
                break;
            };
            case UP_KEY: {
                if (if_invaild(pp.x_pos, pp.y_pos - 1))
                {
                    pp.dir = UP;
                    break;
                }
                else pp.y_pos--;
                pp.dir = UP;
                break;
            };
            case LEFT_KEY: {
                if (if_invaild(pp.x_pos - 1, pp.y_pos))
                {
                    pp.dir = LEFT;
                    break;
                }
                else
                    pp.x_pos--;
                pp.dir = LEFT;
                break;
            };
            case DOWN_KEY: { if (if_invaild(pp.x_pos, pp.y_pos + 1))
            {
                pp.dir = DOWN;
                break;
            }
                         else
                pp.y_pos++;
                pp.dir = DOWN;
                break;
            };
            case RIGHT_KEY: { if (if_invaild(pp.x_pos + 1, pp.y_pos))
            {
                pp.dir = RIGHT;
                break;
            }
                          else
                pp.x_pos++;
                pp.dir = RIGHT;
                break;
            };
            case 'e': {
                system("cls");
                switch (pp.dir)
                {
                case UP: {
                    int forward_item = siz[pp.y_pos - 1][pp.x_pos];
                    if (101 <= forward_item and 104 >= forward_item)
                        switch (forward_item)
                        {
                        case M_L_EXIT: {if (Mp.Left_exit == 0) { wcout << "NOT EXIST"; kbscan(); } else return Mp.Left_exit; break; }
                        case M_R_EXIT: {if (Mp.Right_exit == 0) { wcout << "NOT EXIST"; kbscan(); } else return Mp.Right_exit; break; }
                        case M_T_EXIT: {if (Mp.Up_exit == 0) { wcout << "NOT EXIST"; kbscan(); } else return Mp.Up_exit; break; }
                        case M_B_EXIT: {if (Mp.Down_exit == 0) { wcout << "NOT EXIST"; kbscan(); } else return Mp.Down_exit;  break; }
                        }
                    else if (110 < forward_item and 120 >= forward_item)
                        npcs[forward_item - 111].talk();
                    break;
                }
                case DOWN: {
                    int forward_item = siz[pp.y_pos + 1][pp.x_pos];
                    if (101 <= forward_item and 104 >= forward_item)
                        switch (forward_item)
                        {
                        case M_L_EXIT: {if (Mp.Left_exit == 0)wcout << "NOT EXIST"; else return Mp.Left_exit; break; }
                        case M_R_EXIT: {if (Mp.Right_exit == 0)wcout << "NOT EXIST"; else return Mp.Right_exit; break; }
                        case M_T_EXIT: {if (Mp.Up_exit == 0)wcout << "NOT EXIST"; else return Mp.Up_exit; break; }
                        case M_B_EXIT: {if (Mp.Down_exit == 0)wcout << "NOT EXIST"; else return Mp.Down_exit;  break; }
                        }
                    else if (110 < forward_item and 120 >= forward_item)
                        npcs[forward_item - 111].talk();
                    break;
                }
                case LEFT: {
                    int forward_item = siz[pp.y_pos][pp.x_pos - 1];
                    if (101 <= forward_item and 104 >= forward_item)
                        switch (forward_item)
                        {
                        case M_L_EXIT: {if (Mp.Left_exit == 0) { wcout << "NOT EXIST"; kbscan(); } else return Mp.Left_exit; break; }
                        case M_R_EXIT: {if (Mp.Right_exit == 0) { wcout << "NOT EXIST"; kbscan(); } else return Mp.Right_exit; break; }
                        case M_T_EXIT: {if (Mp.Up_exit == 0) { wcout << "NOT EXIST"; kbscan(); } else return Mp.Up_exit; break; }
                        case M_B_EXIT: {if (Mp.Down_exit == 0) { wcout << "NOT EXIST"; kbscan(); } else return Mp.Down_exit;  break; }
                        }
                    else if (110 < forward_item and 120 >= forward_item)
                        npcs[forward_item - 111].talk();
                    break;
                }
                case RIGHT: {
                    int forward_item = siz[pp.y_pos][pp.x_pos + 1];
                    if (101 <= forward_item and 104 >= forward_item)
                        switch (forward_item)
                        {
                        case M_L_EXIT: {if (Mp.Left_exit == 0) { wcout << "NOT EXIST"; kbscan(); } else return Mp.Left_exit; break; }
                        case M_R_EXIT: {if (Mp.Right_exit == 0) { wcout << "NOT EXIST"; kbscan(); } else return Mp.Right_exit; break; }
                        case M_T_EXIT: {if (Mp.Up_exit == 0) { wcout << "NOT EXIST"; kbscan(); } else return Mp.Up_exit; break; }
                        case M_B_EXIT: {if (Mp.Down_exit == 0) { wcout << "NOT EXIST"; kbscan(); } else return Mp.Down_exit;  break; }
                        }
                    else if (110 < forward_item and 120 >= forward_item)
                        npcs[forward_item - 111].talk();
                    break;
                }
                }
            }
            default:break;
            }
        };
    }
};
int main() {
    //setlocale(LC_ALL, "zh_CN.UTF-8");
    locale china("zh_CN.UTF-8");
    locale::global(china);
    wstring a(L"alian");
    Diolog dg(wis,a);
    int t = 9;
    dg.ViewSw(t);
    maps mp;
    mp.view();
}