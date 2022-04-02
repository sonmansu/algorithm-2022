#include <iostream>
#include "../smtool.h"
#include <cmath>
#include <limits>
using namespace std;

typedef tuple<double, double, double> tp;

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
}
int endFlag = 0;
const double gap = 0.05;

Line basePoint;

double midDist, leftDist, rightDist;
double preMidDist = numeric_limits<double>::max(), preLeftDist=numeric_limits<double>::max(), preRightDist=numeric_limits<double>::max();


int pointFlag = 0;
int leftPlus = 0.01, rightPlus = 1;
void op(Line inputLine, double t) {
    cout<<"base t: " << basePoint.t << "/" <<"input t: " << t << endl;
    midDist = getDist(basePoint.linePoint, inputLine.getPoint(t));
    leftDist = getDist(basePoint.linePoint, inputLine.getPoint(t-gap));
    rightDist = getDist(basePoint.linePoint, inputLine.getPoint(t+gap));
    cout<<"mid, left, rightDist: " << midDist << '/' << leftDist << '/' << rightDist << endl;

//    if (leftDist < midDist && leftDist < preLeftDist &&(midDist - leftDist)>0.01 ) { // 1/2
    if (leftDist < midDist &&(midDist - leftDist)>0.01 && t>0.05) { // 1/2

        double tempDist = getDist(basePoint.linePoint, inputLine.getPoint(floor(t*0.5*1000)/1000));
        if (tempDist > leftDist) {
            cout << "줄인게 더크다!!\n";
            t -= gap;
        } else
            t = floor(t*0.5*1000)/1000;

        cout << "left\n";
        preLeftDist = leftDist;
        preRightDist = rightDist;

        if (t > 0.001) {
            inputLine.endFlag = 0;
            endFlag = 0;
            op(inputLine, t);
            return;
        }
    } else {
//        if (rightDist < midDist && rightDist < preRightDist && (midDist - rightDist)>0.01) { // 1/2
        if (rightDist < midDist && (midDist - rightDist)>0.01&& t<9.95) { // 1/2
            leftPlus = leftPlus*1.05;

            cout << "right\n";
            preLeftDist = leftDist;
            preRightDist = rightDist;

            double tempDist = getDist(basePoint.linePoint, inputLine.getPoint(ceil(((1+t)*0.5)*1000)/1000));
            if (tempDist > rightDist) {
                cout << "줄인게 더크다!!\n";
//                t = ceil(((1+t)*0.5)*1000)/1000;

                t += gap;
            } else
                t = ceil(((1+t)*0.5)*1000)/1000;

            if ( 1- t > 0.001) {
                endFlag = 0;
                inputLine.endFlag = 0;
                op(inputLine, t);
                return;
            }
        }
    }
    // either of them are bigger than midPointDist
    // change basePoint
    inputLine.endFlag = 1;
    endFlag++;
    pointFlag++;
    cout<<"점뒤집음===================\n";
    if (pointFlag % 2 == 0) cout << "p1,p2가 베이스 포인트\n";
    else cout << "p3,p4가 베이스 포인트\n";
    if (endFlag == 4) {
        double minDist = getDist(basePoint.linePoint, inputLine.getPoint(t));
        cout << minDist << endl;
        cout << "HAHA";
        return;
    }
    Line newInputPoint = basePoint;  // current base point
    basePoint = Line(inputLine.p1, inputLine.p2, t); // current input point
    op(newInputPoint, newInputPoint.t);
}
int main() {
    tp p1 = make_tuple(350, 150, 350);
    tp p2 = make_tuple(0, 0, 0);
    // tp p3 = tp(10, -6, 30);
    // tp p4 = tp(56, 21, 120);
    tp p3 = make_tuple(10, -6, 30);
    tp p4 = make_tuple(56, 21, 120);

    basePoint = Line(p1, p2, 0.5);
    Line inputLine = Line(p3, p4);



//    cout<< getDist(Line(p1,p2,0.9).linePoint, Line(p3,p4,0.2).linePoint)<<endl;

    cout << "p1,p2가 베이스 포인트\n";
    op(inputLine, 0.5);



    return 0;
}
