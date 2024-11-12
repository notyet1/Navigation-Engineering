#include<iostream>
#include<math.h>
#define PI 3.141592653
using namespace std;
class Point {
public:
	double x,y,z;
	Point(double a=0, double b=0, double c=0) :x(a),y(b),z(c){}
};


//叉积
Point crossProduct(const Point& v1, const Point& v2) {
    Point cross(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
    return cross;
}

//模
double magnitude(const Point& v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// 计算坡度和坡向
void SlopeAndAspect(const Point& p1, const Point& p2, const Point& p3, double& slope, double& aspect) {
    
    Point v1 ( p2.x - p1.x, p2.y - p1.y, p2.z - p1.z );
    Point v2 ( p3.x - p1.x, p3.y - p1.y, p3.z - p1.z );
    Point normal = crossProduct(v1, v2);
    double normalMag = magnitude(normal);

    // 计算坡度
    slope = acos(abs(normal.z) / normalMag) * 180.0 / PI;

    // 计算坡向
    aspect = atan2(normal.y, normal.x) * 180.0 / PI;
    if (aspect < 0) {
        aspect += 360.0;
    }
}

int main() {//给定一片散点（数字高程）坐标及高程值，计算每个面上的坡度坡向值。
    // 定义三个点
    Point p1 (0.0, 0.0, 0.0 );
    Point p2 (1.0, 1.0, 0.0 );
    Point p3 (0.0, 1.0, 1.0 );

    double slope, aspect;
    SlopeAndAspect(p1, p2, p3, slope, aspect);

    cout << "坡度: " << slope << "°"<<std::endl;
    cout << "坡向: " << aspect <<"°"<< std::endl;

    return 0;
}
