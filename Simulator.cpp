#include "Simulator.h"
#include "User.h"
#include "Place.h"

#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <map>
#include <utility>
#include <random>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <Windows.h>

using namespace std;

//It's for making a random map. In real uses, the program should get input the real places.
const int place_in_a_category = 12; //number of places per category. You can change this int type number for making more random places per a category
random_device rd;
mt19937_64 mt(rd());
uniform_real_distribution<double> dist1(33.1127, 33.3350); // random latitude in jeju island
uniform_real_distribution<double> dist2(126.0843, 126.5820); //random longitude in jeju island
uniform_real_distribution<double> dist3(1.7, 4.8); //random rate of the place
uniform_real_distribution<double> dist4(0, 1); // random degree of first mbti
uniform_real_distribution<double> dist5(0, 1); // random degree of second mbti


/*
First, it declares vector which saves all the users. And then, it sets mbti_list, place_list, and question list.
It saves all the inputed users while -1 isn't inputed. If inputed user exists in the user_list, recommendation function is called.
But if user doens't exist in the user_list, test and travel-MBTI decision is done first. And then recommendation function is called.
*/
void Simulator::start() {
    cout<< "program started"<<endl<<endl;
    vector <User*> userlist;

    set_mbti_list();
    set_place();
    set_question();

    while(1) {
        string name;
        cout <<"Input your name or input -1 to terminate the program: ";
        cin>>name;
        if(name == "-1")
            break;
        bool user_exist=false;
        User* user;
        for(auto elem: userlist) {
            if(elem->getName() == name) {
                user = elem;
                user_exist = true;
                break;
            }
        }
        if(!user_exist) {
            user = new User(name);
            user->getUser_place_list() = place_list;
            test(user);
            userlist.push_back(user);
        }

        recommendation(user);
    }

    cout <<"Program is terminated"<<endl;
}


//map of (name of the travel-MBTI, (first_element of the MBTI, second_element of the MBTI)) is made here.
void Simulator::set_mbti_list() {
    mbti_list.insert({"passionate explorer", make_pair("active", "luxury")});
    mbti_list.insert({"brave backpacker", make_pair("active", "reasonable")});
    mbti_list.insert({"comfortable vacationer", make_pair("healing", "luxury")});
    mbti_list.insert({"reasonable traveler", make_pair("healing", "reasonable")});

    cout<< "Below is the traveler-mbti list."<<endl;
    for(auto elem: mbti_list) {
        cout << elem.first <<": " << elem.second.first << ", "<< elem.second.second<<endl;
    }
    cout <<endl;

    Sleep(4000);
    system("cls");
}

/*
Jeju island's latitude and longitude are 33.1127~33.3350 and 126.0843~126.5820
Let's suppose that jeju island's shape is rectangle
make completely random (3 X place_in_a_category) places
map of (category, vector<Place>) is made here.
*/
void Simulator::set_place() {
    vector <Place> v1;
    vector <Place> v2;
    vector <Place> v3;
    place_list.insert(make_pair("cafe", v1));
    place_list.insert(make_pair("meal", v2));
    place_list.insert(make_pair("activity", v3));

    for(int i=1; i<=place_in_a_category; i++) {
        if(i%4==0)
            place_list["cafe"].push_back(Place("cafe "+to_string(i), dist1(mt), dist2(mt), dist3(mt), make_pair("active", "reasonable"), make_pair(dist4(mt), dist5(mt)), "cafe"));
        else if(i%4==1)
            place_list["cafe"].push_back(Place("cafe "+to_string(i), dist1(mt), dist2(mt), dist3(mt), make_pair("active", "luxury"), make_pair(dist4(mt), dist5(mt)), "cafe"));
        else if(i%4==2)
            place_list["cafe"].push_back(Place("cafe "+to_string(i), dist1(mt), dist2(mt), dist3(mt), make_pair("healing", "reasonable"), make_pair(dist4(mt), dist5(mt)), "cafe"));
        else if(i%4==3)
            place_list["cafe"].push_back(Place("cafe "+to_string(i), dist1(mt), dist2(mt), dist3(mt), make_pair("healing", "luxury"), make_pair(dist4(mt), dist5(mt)), "cafe"));
    }
    for(int i=1; i<=place_in_a_category; i++) {
        if(i%4==0)
            place_list["meal"].push_back(Place("restaurant "+to_string(i), dist1(mt), dist2(mt), dist3(mt), make_pair("active", "reasonable"), make_pair(dist4(mt), dist5(mt)), "meal"));
        else if(i%4==1)
            place_list["meal"].push_back(Place("restaurant "+to_string(i), dist1(mt), dist2(mt), dist3(mt), make_pair("active", "luxury"), make_pair(dist4(mt), dist5(mt)), "meal"));
        else if(i%4==2)
            place_list["meal"].push_back(Place("restaurant "+to_string(i), dist1(mt), dist2(mt), dist3(mt), make_pair("healing", "reasonable"), make_pair(dist4(mt), dist5(mt)), "meal"));
        else if(i%4==3)
            place_list["meal"].push_back(Place("restaurant "+to_string(i), dist1(mt), dist2(mt), dist3(mt), make_pair("healing", "luxury"), make_pair(dist4(mt), dist5(mt)), "meal"));
    }
    for(int i=1; i<=place_in_a_category; i++) {
        if(i%4==0)
            place_list["activity"].push_back(Place("attraction "+to_string(i), dist1(mt), dist2(mt), dist3(mt), make_pair("active", "reasonable"), make_pair(dist4(mt), dist5(mt)), "activity"));
        else if(i%4==1)
            place_list["activity"].push_back(Place("attraction "+to_string(i), dist1(mt), dist2(mt), dist3(mt), make_pair("active", "luxury"), make_pair(dist4(mt), dist5(mt)), "activity"));
        else if(i%4==2)
            place_list["activity"].push_back(Place("attraction "+to_string(i), dist1(mt), dist2(mt), dist3(mt), make_pair("healing", "reasonable"), make_pair(dist4(mt), dist5(mt)), "activity"));
        else if(i%4==3)
            place_list["activity"].push_back(Place("attraction "+to_string(i), dist1(mt), dist2(mt), dist3(mt), make_pair("healing", "luxury"), make_pair(dist4(mt), dist5(mt)), "activity"));
    }
    cout<< "Below is the virtual places list."<<endl;
    for(auto elem: place_list) {
        cout <<endl << "For " << elem.first << ", there are " << elem.second.size() << " places." <<endl;
        for(auto elem2: elem.second) {
            cout << elem2 <<endl;
        }
    }
    cout <<endl;
    Sleep(7000);
    system("cls");
}

//vector question_list is made here.
void Simulator::set_question() {
    question_list.push_back("I prefer playing outdoors to playing indoors.");
    question_list.push_back("When I shop, I make a purchase list in advance.");
    question_list.push_back("It is easily misled by advertisements appearing in SNS media such as Instagram and YouTube.");
    question_list.push_back("I prefer rolling around at home to going out on weekends.");
    question_list.push_back("It's better to sit down and talk to my friends than to do something active when you meet them.");
    question_list.push_back("If I want something, I buy it without much consideration of the budget.");
    question_list.push_back("I think that life is only once, and when I want to do something, I try it recklessly.");
    question_list.push_back("I prefer vacation or hotel to travel to the city or tourist attractions.");
    question_list.push_back("I usually enjoy challenging tasks such as hiking and bungee jumping.");
    question_list.push_back("If an appointment is suddenly canceled, I often rest at home rather than make another appointment.");
    question_list.push_back("When shopping, I often buy things that I didn't plan.");
    question_list.push_back("I tend to keep a steady account book.");
    question_list.push_back("I think price is more important than fun and interest.");
    question_list.push_back("I think the purpose of the trip is enjoying.");
    question_list.push_back("I tend to recharge my energy by playing outside.");
    question_list.push_back("I've heard the word miser once in a while.");
    question_list.push_back("I think I am economically poor.");
    question_list.push_back("When I travel, I tend to find things that I can't do and challenge them.");
    question_list.push_back("I value experience over money.");
    question_list.push_back("I know a lot of ways to play alone at home.");
    question_list.push_back("I tend to eat delicious-looking food rather than thinking about the price at a restaurant.");
    question_list.push_back("I choose cheap work even if it's a little harder than comfortable and easy.");
    question_list.push_back("I've heard that I'm a homebody.");
    question_list.push_back("I like to find new ways and try them rather than doing stereotyped things.");
    cout << "Quesetion list was made."<<endl<<endl;
    Sleep(3000);
    system("cls");
}

/*
First it asks how many question user wants to answer. If user wants accurate result, user should input biggest number(24).
But if user can't be bothered to do, then user can input small number.
It prints the qusetions and get answers of user, and save them in the class User's vector which saves answers.
Lastly, it calls the function which decides mbti of user.
*/
void Simulator::test(User* user) {
    do{
        int question;
        cout << "How many questions do you want? (16, 20, 24)" <<endl;
        cout <<"For accurate result, please choose big number: ";
        cin >> question;
        user ->setNum_question(question);
        if(question!=16 && question!=20 && question!=24)
            cout << endl << "Please input 16 or 20 or 24"<<endl;
    } while(user->getNum_question()!=16 && user->getNum_question()!=20 && user->getNum_question()!=24);

    cout <<"Answer 1 to 5 according to the degree to which you correspond to the sentence"<<endl<<endl;
    for(int i=0; i<user ->getNum_question(); i++) {
        cout << question_list[i]<< " : ";
        int answer;
        cin >>answer;
        if(answer != 1 && answer != 2 && answer != 3 && answer != 4 && answer != 5) {
            i--;
            cout <<"Input 1 or 2 or 3 or 4 or 5 please."<<endl;
            continue;
        }
        user ->getAnswer().push_back(answer);
    }
    Sleep(1000);
    system("cls");
    decide_mbti(user);
}

/*
From answer_list of user, travel-mbti and degree of the travel-mbti's element is decided.
For doing that, it calculates each tendency's answers.
Then, it compares them to decide mbti.
The way it decides the degree of the travel-mbti's element is that when difference of opposite tendency is biggest, degree is 1 and
when difference of opposite tendency is smallest(0), degree is 0. If difference is between of them, then it follows linear relationship.
*/
void Simulator::decide_mbti(User* user){
    double active(0), healing(0), luxury(0), reasonable(0);
    active = user->getAnswer()[0] + user->getAnswer()[8] + user->getAnswer()[13] + user->getAnswer()[14];
    healing = user->getAnswer()[3] + user->getAnswer()[4] + user->getAnswer()[7] + user->getAnswer()[9];
    luxury = user->getAnswer()[2] + user->getAnswer()[5] + user->getAnswer()[6] + user->getAnswer()[10];
    reasonable = user->getAnswer()[1] + user->getAnswer()[11] + user->getAnswer()[12] + user->getAnswer()[15];
    if(user ->getAnswer().size() == 20 || user ->getAnswer().size() == 24) {
        active += user->getAnswer()[17];
        healing += user->getAnswer()[19];
        luxury += user->getAnswer()[18];
        reasonable += user->getAnswer()[16];
    }
    if(user->getAnswer().size() ==24) {
        active += user->getAnswer()[23];
        healing += user->getAnswer()[22];
        luxury += user->getAnswer()[20];
        reasonable += user->getAnswer()[21];
    }

    string mbti_first, mbti_second, mbti_name;
    if(active > healing) {
        mbti_first = "active";
    } else {
        mbti_first = "healing";
    }
    if(luxury > reasonable) {
        mbti_second = "luxury";
    } else {
        mbti_second = "reasonable";
    }
    double mbti_first_degree = abs(active-healing)/(user -> getAnswer().size()); // highest degree is (5-1) * (number of answer)/4 = number of answer
    double mbti_second_degree = abs(luxury-reasonable)/(user -> getAnswer().size());
    
    for(auto elem: mbti_list) {
        if(elem.second.first == mbti_first && elem.second.second == mbti_second) {
            mbti_name = elem.first;
            break;
        }
    }
    user ->setMbti(mbti_name);
    user ->setMbti_degree(make_pair(mbti_first_degree, mbti_second_degree));

    cout <<endl<< "Your travel-mbti is " << user ->getMbti()<<"."<<endl;
    cout << "Below is the degree of the travel-mbti."<<endl<<endl;

    if(mbti_first == "active")
        cout << setw(6) << "active" << setw(8) << mbti_first_degree*50+50 <<"% " << "|" << setw(8) << 100-(mbti_first_degree*50+50) << "%" << setw(11) <<"healing"<< endl;
    else
        cout << setw(6) << "active" << setw(8) << 100-(mbti_first_degree*50+50) <<"% " << "|" << setw(8) << mbti_first_degree*50+50 << "%" << setw(11) <<"healing"<< endl;
    
    if(mbti_first == "luxury")
        cout << setw(6) << "luxury" << setw(8) << mbti_second_degree*50+50 <<"% " << "|" << setw(8) << 100-(mbti_second_degree*50+50) << "%" << setw(11) <<"reasonable"<< endl;
    else
        cout << setw(6) << "luxury" << setw(8) << 100-(mbti_second_degree*50+50) <<"% " << "|" << setw(8) << mbti_second_degree*50+50 << "%" << setw(11) <<"reasonable"<< endl;

    cout <<endl;

    Sleep(5000);
    system("cls");
}

//compare scores of all the possible courses and recommend best 3 courses for only user
void Simulator::recommendation(User* user) {
    set_all_possible_course(user);
    double score_len(0), score_first_mbti(0), score_second_mbti(0);

    // calculate distance score
    int length;
    for(int j=0; j<user->getAll_possible_course().size(); j++) {
        score_len = 0;
        for(int i=0; i< user->getVisit_place()-1; i++) {
            length = sqrt(pow((user->getAll_possible_course()[j].first[i].getLatitude() - user->getAll_possible_course()[j].first[i+1].getLatitude())*1000,2) + pow((user->getAll_possible_course()[j].first[i].getLongitude() - user->getAll_possible_course()[j].first[i+1].getLongitude())*1000,2));
            score_len += length;
        }
        get<0>(user->getAll_possible_course()[j].second) = score_len;
    }

    //find highest length and make shorter length higher score
    vector<double> score_len_big_than_1;
    for(auto elem:user->getAll_possible_course()) {
        score_len_big_than_1.push_back(get<0>(elem.second));
    }
    double max_score_len_big_than_1 = *max_element(score_len_big_than_1.begin(), score_len_big_than_1.end());
    for(auto& elem: user->getAll_possible_course()) {
        get<0>(elem.second) = max_score_len_big_than_1 - get<0>(elem.second);
    }

    //find highest score
    score_len_big_than_1.clear();
    for(auto elem:user->getAll_possible_course()) {
        score_len_big_than_1.push_back(get<0>(elem.second));
    }
    max_score_len_big_than_1 = *max_element(score_len_big_than_1.begin(), score_len_big_than_1.end());

    //divide score by max score
    //if all the score is 0 -> make all the score 1
    if(max_score_len_big_than_1 != 0) {
        for(auto& elem: user->getAll_possible_course()) {
            get<0>(elem.second) /= max_score_len_big_than_1;
        }
    } else {
        for(auto &elem: user->getAll_possible_course()) {
            get<0>(elem.second) = 1;
        }
    }
    
    // calculate first mbti score
    float first_mbti_concordance;
    for(int i=0; i<user->getAll_possible_course().size(); i++) {
        score_first_mbti = 0;
        for(auto elem2: user->getAll_possible_course()[i].first) {
            if(mbti_list[user ->getMbti()].first == elem2.getMbti().first) {
                first_mbti_concordance = 1-abs(user ->getMbti_degree().first - elem2.getMbti_degree().first)/2;
            } else {
                first_mbti_concordance = 1-abs(user ->getMbti_degree().first + elem2.getMbti_degree().first)/2;
            }
            score_first_mbti += elem2.getGrade() * first_mbti_concordance;
        }
        get<1>(user->getAll_possible_course()[i].second) = score_first_mbti;
    }
    
    vector<double> score_first_mbti_big_than_1;
    for(auto elem:user->getAll_possible_course()) {
        score_first_mbti_big_than_1.push_back(get<1>(elem.second));
    }
    double max_score_mbti_first_big_than_1 = *max_element(score_first_mbti_big_than_1.begin(), score_first_mbti_big_than_1.end());
    for(int i=0; i<user->getAll_possible_course().size(); i++) {
        get<1>(user->getAll_possible_course()[i].second) /= max_score_mbti_first_big_than_1;
    }
    

    // calculate second mbti score
    float second_mbti_concordance;
    for(int i=0; i<user->getAll_possible_course().size(); i++) {
        score_second_mbti = 0;
        for(auto elem2: user->getAll_possible_course()[i].first) {
            if(mbti_list[user ->getMbti()].second == elem2.getMbti().second) {
                second_mbti_concordance = 1-abs(user ->getMbti_degree().second - elem2.getMbti_degree().second)/2;
            } else {
                second_mbti_concordance = 1-abs(user ->getMbti_degree().second + elem2.getMbti_degree().second)/2;
            }
            score_second_mbti += elem2.getGrade() * second_mbti_concordance;
        }
        get<2>(user->getAll_possible_course()[i].second) = score_second_mbti;
    }

    vector<double> score_second_mbti_big_than_1;
    for(auto elem:user->getAll_possible_course()) {
        score_second_mbti_big_than_1.push_back(get<2>(elem.second));
    }
    double max_score_mbti_second_big_than_1 = *max_element(score_second_mbti_big_than_1.begin(), score_second_mbti_big_than_1.end());
    for(int i=0; i<user->getAll_possible_course().size(); i++) {
        get<2>(user->getAll_possible_course()[i].second) /= max_score_mbti_second_big_than_1;
    }        

    //consider distance constraint 
    int distance_constraint;
    cout << "Do you have a car? If distance constraint is small, input 1. If not, input 0."<<endl;
    cin >> distance_constraint;
    if(distance_constraint == 1) {
        for(int i=0; i<user->getAll_possible_course().size(); i++) {
            get<0>(user->getAll_possible_course()[i].second) /= 2;
        }
    }

    Sleep(1500);
    system("cls");

    //compare the score of courses &recommend three courses
    vector <double> total_score;

    for(auto elem: user->getAll_possible_course()) {
        total_score.push_back(get<0>(elem.second)+get<1>(elem.second)+get<2>(elem.second));
    }

    sort(total_score.rbegin(), total_score.rend());
    if(user->getSymmetry_visit_place()) {
        int size=total_score.size();
        for(int i=size-1; i>0; i-=2) {
            total_score.erase(total_score.begin()+i);
        }
    }

    cout << "Program will recommend 3 travel courses."<<endl<<"It's only for you."<<endl<<endl;
    if(user->getSymmetry_visit_place()) {
        cout <<"The categories you want to visited are symmetric, so you can visit with reverse order too."<<endl;
        cout <<"For example, if program recommends courses with (A->B->C), you can choose either (A->B->C) or (C->B->A)!"<<endl<<endl;
    }

    for(auto elem: user->getAll_possible_course()) {
        if(total_score[0] == get<0>(elem.second)+get<1>(elem.second)+get<2>(elem.second)) {
            cout << "First course: " << elem.first[0].getName();
            for(int i=1; i<elem.first.size(); i++) {
                cout << " -> " << elem.first[i].getName();
            }
            if(distance_constraint ==1)
                cout <<endl <<"Score is " << total_score[0] <<"/2.5" <<endl;
            else
                cout <<endl <<"Score is " << total_score[0] <<"/3" <<endl;
            break;
        }
    }
    for(auto elem: user->getAll_possible_course()) {
        if(total_score[1] == get<0>(elem.second)+get<1>(elem.second)+get<2>(elem.second)) {
            cout << "Second course: " << elem.first[0].getName();
            for(int i=1; i<elem.first.size(); i++) {
                cout << " -> " << elem.first[i].getName();
            }
            if(distance_constraint ==1)
                cout <<endl <<"Score is " << total_score[1] <<"/2.5" <<endl;
            else
                cout <<endl <<"Score is " << total_score[1] <<"/3" <<endl;
            break;
        }
    }
    for(auto elem: user->getAll_possible_course()) {
        if(total_score[2] == get<0>(elem.second)+get<1>(elem.second)+get<2>(elem.second)) {
            cout << "Third course: " << elem.first[0].getName();
            for(int i=1; i<elem.first.size(); i++) {
                cout << " -> " << elem.first[i].getName();
            }
            if(distance_constraint ==1)
                cout <<endl <<"Score is " << total_score[2] <<"/2.5" <<endl;
            else
                cout <<endl <<"Score is " << total_score[2] <<"/3" <<endl;
            break;
        }
    }
    int num_course;
    cout <<endl<<"What course do you want to choose? Input 1 or 2 or 3: ";
    cin >>num_course;

    for(auto elem: user->getAll_possible_course()) {
        if(total_score[num_course - 1] == get<0>(elem.second)+get<1>(elem.second)+get<2>(elem.second)) {
            cout <<"Below are informations of the places you want to visit."<<endl<<endl;
            for(auto elem2: elem.first) {
                cout << elem2<<endl<<endl;
            }
            cout <<"Next time, program will recommend the courses except for these places."<<endl <<endl;

            for(auto &elem2: user->getUser_place_list()) {
                for(auto elem3: elem.first) {
                    for(int i=0; i< elem2.second.size(); i++) {
                        if(elem2.second[i].getName() == elem3.getName()) {
                            elem2.second.erase(elem2.second.begin()+i);
                            break;
                        }
                    }
                }
            }
            break;
        }
    }
    cout <<endl;
    Sleep(7000);
    system("cls");
}

//Find all possible courses with the number of which user wants to visit places and save them in vector all_possible_course of user
void Simulator::set_all_possible_course(User* user) {
    user->getAll_possible_course().clear();
    int visit_place;
    cout << "How many places do you want to visit in a day?"<<endl;
    cout << "Program can recommend courses including more than 4 places, but it takes about 5 minutes for recommending courses with 5 places, so please input up to 4: ";
    cin >> visit_place;
    user->setVisit_place(visit_place);
    string* category_to_visit_list = new string[visit_place];
    
    for(int i=0; i<visit_place; i++){
        if(i==0)
            cout << "What category(cafe, meal, activity) of place do you want to visit in " << i+1 << "st order?: ";
        else if(i==1)
            cout << "What category(cafe, meal, activity) of place do you want to visit in " << i+1 << "nd order?: ";
        else if(i==2)
            cout << "What category(cafe, meal, activity) of place do you want to visit in " << i+1 << "rd order?: ";
        else
            cout << "What category(cafe, meal, activity) of place do you want to visit in " << i+1 << "th order?: ";
        cin >> category_to_visit_list[i];
    }

    //fill first place
    for(auto elem: user->getUser_place_list()[category_to_visit_list[0]]) {
        for(int i=0; i< pow(place_in_a_category,visit_place-1); i++) {
            vector<Place> p;
            p.push_back(elem);
            user->getAll_possible_course().push_back(make_pair(p,make_tuple(0,0,0)));
        }
    }

    //fill second~(last-1) place
    int n;
    for(int k=1; k<visit_place-1; k++) {
        n = 0;
        for(int i=0; i< user -> getAll_possible_course().size(); i++) {
            i--;
            for(int j=0; j<pow(place_in_a_category,visit_place-k-1); j++) {
                i++;
                user->getAll_possible_course()[i].first.push_back(user->getUser_place_list()[category_to_visit_list[k]][n%place_in_a_category]);
            }
            n++;
        }
    }

    //fill last place
    n=0;
    if(visit_place != 1) {
        for(int i=0; i< user->getAll_possible_course().size(); i++) {
            user->getAll_possible_course()[i].first.push_back(user->getUser_place_list()[category_to_visit_list[visit_place-1]][n%place_in_a_category]);
            n++;
        }
    }

    //delete courses which have same places
    for(int i=0; i< user ->getAll_possible_course().size(); i++) {
        vector <string> v1;
        for(auto elem: user->getAll_possible_course()[i].first) {
            v1.push_back(elem.getName());
        }
        vector <string> v2=v1;
        sort(v2.begin(), v2.end());
        sort(v1.begin(), v1.end());
        v1.erase(unique(v1.begin(), v1.end()), v1.end());
        if(v2 != v1)
            user ->getAll_possible_course().erase(user ->getAll_possible_course().begin()+i);
    }

    //if(symmetric course): user->setSymmetry_visit_place(true)
    user->setSymmetry_visit_place(true);
    for(int i=0; i<visit_place/2; i++) {
        if(category_to_visit_list[i] != category_to_visit_list[visit_place-1-i]) {
            user->setSymmetry_visit_place(false);
            break;
        }
    }
}