#include <iostream>
#include "../smtool.h"
#include <cmath>
#include <limits>
using namespace std;

typedef tuple<double, double, double> tp;
double leftNum = 0, rightNum = 1;

class Line {
  public:
    tp p1, p2;
    tp linePoint;
    double t;
    int endFlag = 0;
    Line() {}
    Line(tp _p1, tp _p2) {
        p1 = _p1;
        p2 = _p2;
        t = 0;
    }
    Line(tp _p1, tp _p2, double _t) {
        p1 = _p1;
        p2 = _p2;
        t = _t;
        linePoint = getPoint(_t);
    }
    tp getPoint(double inputT) {
        double x = (1-inputT)*get<0>(p1) + inputT*get<0>(p2);
        double y = (1-inputT)*get<1>(p1) + inputT*get<1>(p2);
        double z = (1-inputT)*get<2>(p1) + inputT*get<2>(p2);
        tp point = make_tuple(x,y,z);

        return point;
    }
    tp getPoint() {
        double x = (1-t)*get<0>(p1) + t*get<0>(p2);
        double y = (1-t)*get<1>(p1) + t*get<1>(p2);
        double z = (1-t)*get<2>(p1) + t*get<2>(p2);
        tp point = make_tuple(x,y,z);

        return point;
    }
    int isOnLine(tp p) {
        tp temp;
        double x = (1-get<0>(p))*get<0>(p1) + get<0>(p)*get<0>(p2);
        double y = (1-get<1>(p))*get<1>(p1) + get<1>(p)*get<1>(p2);
        double z = (1-get<2>(p))*get<2>(p1) + get<2>(p)*get<2>(p2);
//        if(x == get<0>(p1) && y == get<1>(p1) && z == get<2>(p1))
//            return 1;
//        if (x == get<0>(p2) && y == get<1>(p2) && z == get<2>(p2))
//            return 1;
//        return 0;
        if(x == get<0>(p) && y == get<1>(p) && z == get<2>(p))
            return 1;
        return 0;
    }
};

void printTp(tp tp1) {
    std::cout << get<0>(tp1) << " ";
    cout << get<1>(tp1) << " ";
    cout << get<1>(tp1) << endl;
}

double getDist(tp p1, tp p2) {
    int dist;
    dist = pow(get<0>(p1)-get<0>(p2), 2) + pow(get<1>(p1)-get<1>(p2), 2) + pow(get<2>(p1)-get<2>(p2), 2) ;
    return sqrt(dist);
//    return (dist);
}
int endFlag = 0;
const double gap = 0.001;
const double divide = 10000;

Line basePoint;

double midDist, leftDist, rightDist;
double preMidDist = numeric_limits<double>::max(), preLeftDist=numeric_limits<double>::max(), preRightDist=numeric_limits<double>::max();


int pointFlag = 0;
void op(Line inputLine, double t) {
    cout<<"base t: " << basePoint.t << "/" <<"input t: " << t << endl;
    midDist = getDist(basePoint.linePoint, inputLine.getPoint(t));
    leftDist = getDist(basePoint.linePoint, inputLine.getPoint(t-gap));
    rightDist = getDist(basePoint.linePoint, inputLine.getPoint(t+gap));
    cout<<"mid, left, rightDist: " << midDist << '/' << leftDist << '/' << rightDist << endl;

//    if (leftDist < midDist && leftDist < preLeftDist &&(midDist - leftDist)>0.01 ) { // 1/2
    if (leftDist < midDist &&(midDist - leftDist)>gap) { // 1/2
        rightNum = t;
        t = ceil((t+leftNum)/2 * divide) / divide;

        cout << "left\n";

        if (t > gap) {
            inputLine.endFlag = 0;
            endFlag = 0;
            op(inputLine, t);
            return;
        }
    } else {
//        if (rightDist < midDist && rightDist < preRightDist && (midDist - rightDist)>0.01) { // 1/2
        if (rightDist < midDist && (midDist - rightDist)>gap) { // 1/2
            leftNum = t;
            t = ceil((t + rightNum) / 2 * divide)/divide;

            cout << "right\n";

            if ( 1- t > gap) {
                endFlag = 0;
                inputLine.endFlag = 0;
                op(inputLine, t);
                return;
            }
        }
    }
    // either of them are bigger than midPointDist
    // change basePoint
    leftNum = 0;
    rightNum = 1;
    inputLine.endFlag = 1;
    endFlag++;
    pointFlag++;
    cout<<"점뒤집음===================\n";
    if (pointFlag % 2 == 0) cout << "p1,p2가 베이스 포인트\n";
    else cout << "p3,p4가 베이스 포인트\n";
    if (endFlag == 3) {
//        double minDist = getDist(basePoint.linePoint, inputLine.getPoint(t));
//        cout << ceil(minDist) << endl;
        cout << ceil((midDist)) << endl;
        cout << "HAHA";
        return;
    }
    Line newInputPoint = basePoint;  // current base point
    basePoint = Line(inputLine.p1, inputLine.p2, t); // current input point
    op(newInputPoint, newInputPoint.t);
}
int main() {
//    tp p1 = make_tuple(350, 150, 350);
//    tp p2 = make_tuple(0, 0, 0);
//    tp p3 = make_tuple(10, -6, 30);
//    tp p4 = make_tuple(56, 21, 120);

//    tp p1 = make_tuple(700, -940, -854);
//    tp p2 = make_tuple(-390, 619, 340);
//    tp p3 = make_tuple(3, 907, -17);
//    tp p4 = make_tuple(111, 222, 333);
//
    tp p1 = make_tuple(0,0,0);
    tp p2 = make_tuple(0, 10000, 10000);
    tp p3 = make_tuple(0, 5000,5000);
    tp p4 = make_tuple(5000,5000, 5000);

//    int a1, a2, a3, b1, b2, b3, c1, c2, c3, d1, d2, d3;
//    cin >> a1 >> a2 >> a3 >> b1 >> b2 >> b3 >> c1 >> c2>>c3>>d1>>d2>>d3;
//    tp p1 = make_tuple(a1, a2, a3);
//    tp p2 = make_tuple(b1, b2, b3);
//    tp p3 = make_tuple(c1, c2, c3);
//    tp p4 = make_tuple(d1, d2, d3);


    basePoint = Line(p1, p2, 0.5);
    Line inputLine = Line(p3, p4);


    if (basePoint.isOnLine(p3) == 1 || basePoint.isOnLine(p4) == 1)
        cout << 0;
    else if (inputLine.isOnLine(p1) == 1|| inputLine.isOnLine(p2) == 1)
        cout << 0;
    else {
        cout << "p1,p2가 베이스 포인트\n";
        op(inputLine, 0.5);
    }

//    cout<< getDist(Line(p1,p2,0.9).linePoint, Line(p3,p4,0.2).linePoint)<<endl;


    return 0;
}
