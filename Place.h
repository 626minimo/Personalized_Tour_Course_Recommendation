#ifndef __PLACE_H_
#define __PLACE_H_

#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <map>
#include <utility>

using namespace std;

class Place {
    public:
        Place(string name_, double latitude_, double longitude_, double grade_, pair<string, string> mbti_, pair<double, double> mbti_degree_, string category_):
            name(name_), latitude(latitude_), longitude(longitude_), grade(grade_), mbti(mbti_), mbti_degree(mbti_degree_), category(category_) {} // Constructor
        string getName(){return name;}
        double getLatitude(){return latitude;}
        double getLongitude(){return longitude;}
        double getGrade(){return grade;}
        pair<string, string> getMbti() {return mbti;}
        string getCategory() {return category;}
        pair<double, double> getMbti_degree() {return mbti_degree;}
        friend ostream& operator <<(ostream& outputStream, const Place& printed_place); // Operator << overloading
    private:
        string name;
        double latitude;
        double longitude;
        double grade; // Rate of the place
        pair<string, string> mbti; // Pair of tendency of the place for the first mbti criterion & tendency of the place for the second mbti criterion
        pair<double, double> mbti_degree; // Pair of degree for the first mbti tendency of the place & degree for the second mbti tendency of the place
        string category; // cafe or meal or activity
};
#endif