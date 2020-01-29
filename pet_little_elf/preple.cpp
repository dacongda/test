#include "ple.h"
namespace ple {
    wstring Player_Name(L"¹ùshit");
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
        for (int a = 0; a < SP.size(); a++)
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
}