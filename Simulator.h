#ifndef __SIMULATOR_H_
#define __SIMULATOR_H_

#include "User.h"
#include "Place.h"
#include <map>
#include <vector>
#include <string>
#include <utility>

using namespace std;

class Simulator {
    public:
        void start();
        void set_question();
        void set_place();
        void set_mbti_list();
        void test(User* user);
        void recommendation(User* user);
        void decide_mbti(User* user);
        void set_all_possible_course(User* user);
    private:
        map<string, pair<string, string>> mbti_list;
        vector<string> question_list;
        map<string, vector<Place>> place_list;
};

#endif