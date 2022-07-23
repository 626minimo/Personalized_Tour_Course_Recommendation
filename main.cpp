#include "Simulator.h"
#include <iostream>

using namespace std;

int main() {
    Simulator s;
    s.start();

    return 0;
}

// what main function do: making an object of the class Simulator and calling the function Simulator::start()

/*
관광객별 여행 선호도(여행 mbti)를 고려한 관광코스 추천 알고리즘 구현: 질문에 대한 응답을 통해 스스로에 대한 결과를
받아볼 수 있다는 점에서 MZ세대 사이에서는 mbti 검사와 같은 각종 심리 검사가 한참 유행을 타고 있다.
본 프로그램 작품에서는 심리 검사를 통해 사람별로 성향을 파악한다. 이때 관광객이 좋아하는 여행 성향을 2가지 기준에 따라
4가지 성향-(활동적인, 럭셔리한), (활동적인, 저렴한), (힐링하는, 럭셔리한), (힐링하는, 저렴한)으로 나누고, 그 성향을 나타내는 정도(0~1 사이 값)를
측정하여 관광객 별로 최적의 여행 코스를 추천해준다. 이를 위해 먼저 사용자가 방문을 원하는 장소의 개수를 입력받았다. 이후, 관광지의 카테고리를
카페(cafe), 식당(meal), 놀거리(activity)로 나누어 사용자가 원하는 카테고리의 장소들을 입력받았고, 해당 카테고리로 이루어진 코스 중 top 3를
추천해주는 방식을 택하였다. 따라서 해당 카테고리로 이루어지는 모든 코스들을 원소로 갖는 벡터를 만든 뒤 각 코스의 점수를 구하여 top3를 추천해주었다.
이를 위해 먼저 코스 이동 거리에 음의 선형관계를 갖도록 거리 점수를 부여한다. 이때 제주도의 실제
지형을 고려하여 이동거리를 구하기 어려웠기에 위도, 경도로부터 얻을 수 있는 직선 거리로 단순화하여 이동거리를 구한다. 다음으로 사용자와 관광지의
첫 번째 mbti 성향 일치도(0~1 사이의 값)를 구한 뒤, 여기에 방문자 리뷰 점수를 곱하여 첫 번째 성향 만족도 점수를 얻는다. 마찬가지로 두 번째
mbti 성향의 일치도에 방문자 리뷰 점수를 곱하여 두 번째 성향 만족도 점수를 얻는다. 이때 각 점수를 모든 장소 통틀어 갖는 최고점으로 나누어 최댓값을
1로 만듦으로써 같은 가중치를 부여한다. 이후 자동차의 존재 여부를 물어 거리의 제약이 큰지, 아니면 상대적으로 덜한지 물어본다.
거리의 제약이 적으면 거리 점수를 반으로 나누어 더 멀리 떨어져 있더라도 더 추천해줄만한 곳을 추천해주고, 거리의 제약이 크다면 거리 점수를
그대로 사용한다. 이 세 점수를 합한 값이 관광코스의 최종 점수이다. 이로써 최종 점수 top3인 코스들을 추천해주었다. 보통 여행 시 숙소는 매일 변경하지
않고, 놀러 다니는 곳은숙소로부터 먼 곳을 다닐 수도 있기 때문에, 숙소는 추천해주지 않는 방식을 택하였다. 또 코드에서는 특정한 업소를 홍보하지 않기
위해서 완전히 랜덤으로 장소들을 구현하였으나 실제로 프로그램을 상용화할 시에는 실제 장소들을 입력받으면 될 것이다.
*/

/*
알고리즘 구조:
1) Place class의 object로 다양한 장소들을 구현.
2) User class의 object로 다양한 사용자들을 구현 for 한 사용자가 프로그램을 반복적으로 사용할 때 처음부터 성향 파악용 질문을 받지 않도록.
    -> Simulator class의 start 함수에서 user를 가리키는 pointer로 이루어진 vector를 구현.
3) Simulator class는 s라는 object 하나 생성. 해당 클래스에서 위에서 설명했던 대부분의 동작이 구현됨.
4) 클래스 호출 관계:
    main -> Simulator
    Simulator -> User & Place
    User -> Place
*/