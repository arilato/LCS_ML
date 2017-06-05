#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

ifstream input;
ofstream output;

struct TEAM{
    string name;
    int id;
    int record[10];
    TEAM(int id2, string name2){
        id = id2;
        name = name2;
        for (int i=0;i<10;i++){
            record[i] = 0;
        }
    }
    string toString(){
        string s = to_string(id);
        for (int i=0;i<10;i++){
            s += "," + to_string(record[i]);
        }
        return s;
    }
};
vector<TEAM> teams;

void error(string message){
    cout<<message;
    exit(0);
}

int getTeam(string name){
    for (int i=0;i<teams.size();i++){
        if (teams[i].name == name){
            return i;
        }
    }
    return -1;
}

void updateMatch(int week, int day){
    string name1, name2, record;
    input>>name1>>record>>name2;
    int score = (record[0] - '0') - (record[2] - '0');
    int id1 = getTeam(name1);
    int id2 = getTeam(name2);
    output<<teams[id1].toString()<<","<<teams[id2].toString()<<","<<week<<","<<day<<","<<score<<"\n";
    teams[id1].record[id2] += score;
    teams[id2].record[id1] -= score;
}


int main(int argc, char *argv[]){
    teams.push_back(TEAM(0, "TSM"));
    teams.push_back(TEAM(1, "IMT"));
    teams.push_back(TEAM(2, "C9"));
    teams.push_back(TEAM(3, "CLG"));
    teams.push_back(TEAM(4, "TL"));
    teams.push_back(TEAM(5, "NV"));
    teams.push_back(TEAM(6, "APX"));
    teams.push_back(TEAM(7, "P1"));
    teams.push_back(TEAM(8, "NRG"));
    teams.push_back(TEAM(9, "FOX"));
    input.open("MatchHistory.txt");
    output.open("Data.csv");
    output<<"Team ID, v TSM, v IMT, v C9, v CLG, v TL, v NV, v APX, v P1, v NRG, v FOX,";
    output<<"Opponent ID, ov TSM, ov IMT, ov C9, ov CLG, ov TL, ov NV, ov APX, ov P1, ov NRG, ov FOX,";
    output<<"Week, Day, Score\n";
    int tmpi, id1, id2;
    string tmps, name1, name2, record;
    for (int week = 1; week <= 9; week++){
        input>>tmpi;
        if (tmpi != week){
            error("Week number does not match!");
        }
        for (int day = 1; day <= 3; day++){
            input>>tmpi;
            if (tmpi != day){
                error("Day number does not match!");
            }
            if (day == 1){
                for (int match = 1; match <= 2; match++){
                    updateMatch(week, day);
                }
            }
            else{
                for (int match = 1; match <= 4; match++){
                    updateMatch(week, day);
                }
            }
        }
    }
    return 0;
}
