#include <iostream>
#include <tuple>
#include <cmath>
#include <limits>
using namespace std;

typedef tuple<double, double, double> tp;
double leftNum = 0, rightNum = 1;

class Line {
  public:
    tp p1, p2, linePoint;
    double t;
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
        return tp(x,y,z);
    }
    tp getPoint() {
        double x = (1-t)*get<0>(p1) + t*get<0>(p2);
        double y = (1-t)*get<1>(p1) + t*get<1>(p2);
        double z = (1-t)*get<2>(p1) + t*get<2>(p2);
        return tp(x,y,z);
    }
};

double getDist(tp p1, tp p2) {
    int dist;
    dist = pow(get<0>(p1)-get<0>(p2), 2) + pow(get<1>(p1)-get<1>(p2), 2) + pow(get<2>(p1)-get<2>(p2), 2) ;
    return (dist);
}
int endFlag = 0;
const double gap = 0.0001;
const double divide = 10000;

Line basePoint;
double midDist, leftDist, rightDist;

void op(Line inputLine, double t) {
    midDist = getDist(basePoint.linePoint, inputLine.getPoint(t));
    leftDist = getDist(basePoint.linePoint, inputLine.getPoint(t-gap));

    if (leftDist < midDist  && (t- ceil((t+leftNum)/2 * divide) / divide) > 0.0001) { // 1/2
        rightNum = t;
        t = ceil((t+leftNum)/2 * divide) / divide;
        endFlag = 0;
        op(inputLine, t);
        return;
    } else {
        rightDist = getDist(basePoint.linePoint, inputLine.getPoint(t+gap));

        if (rightDist < midDist && (ceil((t + rightNum) / 2 * divide)/divide - t > 0.0001)) { // 1/2
            leftNum = t;
            t = ceil((t + rightNum) / 2 * divide)/divide;
            endFlag = 0;
            op(inputLine, t);
            return;
        }
    }
    leftNum = 0;
    rightNum = 1;
    endFlag++;
    if (endFlag == 3) {
        cout << ceil(sqrt(midDist));
        return;
    }
    Line newInputPoint = basePoint;
    basePoint = Line(inputLine.p1, inputLine.p2, t);
    op(newInputPoint, newInputPoint.t);
}
int main() {
    int a1, a2, a3, b1, b2, b3, c1, c2, c3, d1, d2, d3;

    cin >> a1 >> a2 >> a3 >> b1 >> b2 >> b3 >> c1 >> c2>>c3>>d1>>d2>>d3;
    tp p1 = tp(a1, a2, a3);
    tp p2 = tp(b1, b2, b3);
    tp p3 = tp(c1, c2, c3);
    tp p4 = tp(d1, d2, d3);

    basePoint = Line(p1, p2, 0.5);
    Line inputLine = Line(p3, p4);


        op(inputLine, 0.5);


    return 0;
}
