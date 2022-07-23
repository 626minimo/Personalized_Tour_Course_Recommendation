#include "Place.h"
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <map>
#include <utility>

using namespace std;

// Print the information of the place (operator << overloading)
ostream& operator <<(ostream& outputStream, const Place &printed_place) {
    cout << "The " << printed_place.name << " is located at " << printed_place.latitude << " degrees north latitude and "
        << printed_place.longitude <<" degrees east longitude." <<endl; // print name, latitude, longitude of the place
    cout << "The rating here is " << printed_place.grade << ", and it has a mbti of " << printed_place.mbti.first
        << " to the degree of " << printed_place.mbti_degree.first << " and " << printed_place.mbti.second << " to the degree of "
        << printed_place.mbti_degree.second << "."; //print rate, mbti tendency and degree of the place
    return outputStream;
}