#include <iostream>
#include <fstream>
#include <filesystem>
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
#define S "./res"
using namespace std;
using namespace std::filesystem;
/*int main()
{
	if (!exists(S)) {
		create_directory(S);
	}
	int ssr = 65;
	ofstream os("./res/save.dat", ios::binary);
	os.write((char*)&ssr, sizeof(ssr));
	os.close();
	ifstream is("./res/save.dat", ios::binary);
	int aa = 0;
	is.read((char*)&aa, sizeof(aa));
	cout << ssr;
	cout << aa;
}*/
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
int main() {
    locale china("zh_CN.UTF-8");
    locale::global(china);
    wifstream ws("a.txt");
    wstring wi(L"teser");
    Diolog dg(ws,wi);
    int t = 9;
    dg.ViewSw(t);
}