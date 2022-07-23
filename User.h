#ifndef __USER_H_
#define __USER_H_

#include "Place.h"
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <map>
#include <utility>

using namespace std;

class User{
    public:
        User(string name_): name(name_) {}
        string getName(){return name;}
        void setNum_question(int num) {num_question = num;}
        int getNum_question() {return num_question;}
        vector<int>& getAnswer() {return answer;}
        string getMbti() {return mbti;}
        void setMbti(string mbti_) {mbti = mbti_;}
        vector <pair<vector<Place>, tuple<double, double, double>>> &getAll_possible_course() {return all_possible_course;} // Return type is call by reference to change the private variable
        int getVisit_place() {return visit_place;}
        void setVisit_place(int visit) {visit_place = visit;}
        pair<double, double> getMbti_degree() {return mbti_degree;}
        void setMbti_degree(pair<double, double> degree) {mbti_degree = degree;}
        map<string, vector<Place>> &getUser_place_list() {return user_place_list;}
        void setSymmetry_visit_place(bool symmetry_visit_place_) {symmetry_visit_place = symmetry_visit_place_;}
        bool getSymmetry_visit_place() {return symmetry_visit_place;}
    private:
        int num_question; // the number of the question that user wants to answer
        string name;
        vector <int> answer; // the vector of which elements are the answers of the question_list in simluator
        string mbti;
        pair<double, double> mbti_degree;
        int visit_place;
        vector <pair<vector<Place>, tuple<double, double, double>>> all_possible_course;
        map<string, vector<Place>> user_place_list;
        bool symmetry_visit_place;
};

#endif