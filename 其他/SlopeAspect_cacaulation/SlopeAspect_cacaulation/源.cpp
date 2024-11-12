#include<iostream>
#include<math.h>
#define PI 3.141592653
using namespace std;
class Point {
public:
	double x,y,z;
	Point(double a=0, double b=0, double c=0) :x(a),y(b),z(c){}
};


//���
Point crossProduct(const Point& v1, const Point& v2) {
    Point cross(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
    return cross;
}

//ģ
double magnitude(const Point& v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// �����¶Ⱥ�����
void SlopeAndAspect(const Point& p1, const Point& p2, const Point& p3, double& slope, double& aspect) {
    
    Point v1 ( p2.x - p1.x, p2.y - p1.y, p2.z - p1.z );
    Point v2 ( p3.x - p1.x, p3.y - p1.y, p3.z - p1.z );
    Point normal = crossProduct(v1, v2);
    double normalMag = magnitude(normal);

    // �����¶�
    slope = acos(abs(normal.z) / normalMag) * 180.0 / PI;

    // ��������
    aspect = atan2(normal.y, normal.x) * 180.0 / PI;
    if (aspect < 0) {
        aspect += 360.0;
    }
}

int main() {//����һƬɢ�㣨���ָ̣߳����꼰�߳�ֵ������ÿ�����ϵ��¶�����ֵ��
    // ����������
    Point p1 (0.0, 0.0, 0.0 );
    Point p2 (1.0, 1.0, 0.0 );
    Point p3 (0.0, 1.0, 1.0 );

    double slope, aspect;
    SlopeAndAspect(p1, p2, p3, slope, aspect);

    cout << "�¶�: " << slope << "��"<<std::endl;
    cout << "����: " << aspect <<"��"<< std::endl;

    return 0;
}
