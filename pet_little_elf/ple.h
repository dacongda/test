#ifndef _PREPLR_H
#define _PREPLR_H
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
namespace ple {
#define UP_KEY 372
#define DOWN_KEY 380
#define LEFT_KEY 375
#define RIGHT_KEY 377
#define M_L_EXIT 101
#define M_R_EXIT 102
#define M_T_EXIT 103
#define M_B_EXIT 104
#define B_IN 105
#define B_OUT 106
#define resadr "./res/res.dat"
#define Maindir "./res"
#define Mapdir "./res/map"
    //uuid 编码
    //num 数量
    using std::int_fast8_t;
    using std::string;
    using namespace std;
    typedef short int sint;
    typedef int_fast8_t fnt;
    enum pTypes { Fire, Water, Metal, Rock, Wood };
    enum nTypes { Shop, Task, Normal };
    enum tType { Collect, Fight, ToPos, UseItem };
    enum btype { Shop, Stop, Hospital, Home };
    enum MMode { Add, Del };
    enum Player_Direct { UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4 };
    typedef struct status {
        fnt stop;
        bool HP_down;
        bool HP_up;
        fnt k_time;
        int HP_Cg_N;
    }status;
    typedef struct skill {
        sint uuid;
        effect ef[5];
        bool g_or_b;
    }skill;
    typedef struct task {
        int uuid;
        tType tT;
        int statue;
    }task;
    typedef struct save {
        int uuid;
        char name[20];
        char creator[20];
        sint taskst;
        bool mod_open;
        long cr_time;
    }save;
    typedef struct effect {
        bool imm_kill;
        int HPdown;
        int HPup;
        sint st_time;
        int kp_time;
    }effect;
    typedef struct Item {
        fnt uuid;
        string name;
        effect ef[5];
    };
    typedef struct pet {
        pTypes types;
        fnt uuid;
        fnt skill[5];
        status status[5];
        int hp;
        char poname[20];
    }pet;
    typedef struct bag {
        Item* item;
        fnt num;
    }bag;
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
    class player {
    private:
        char name[20];
        int money;
        fnt pet_num;
        pet pet[20];
        bag bag[20];
        fnt pos;
    public:
        player();
        ~player();
        void read_player();
        void save_player();
        bool Money_Cg(MMode md, int num);
        void pet_change(MMode md, int uuid);
    };
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
    class NPC {
    private:
        nTypes type;
        fnt uuid;
        fnt dialog_num;
        fnt bag[20];
    public:
        NPC();
        ~NPC();
        void talk();
    };
    class maps {
    private:
        sint uuid;
        int siz[24][24];
        int* spawnpos;
        sint tpuuid[4];
        char describe[100];
    public:
        maps();
        ~maps();
        void read_maps();
        void view();
    };
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
}
#endif