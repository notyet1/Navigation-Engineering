#include<iostream>
#include<math.h>
#include<string>
#include<iomanip>
#include <sstream>
#include<iomanip>
using namespace std;
#define PI 3.14159265359
#define a 6378137.0
#define f 1.0/298.257223563

class XYZ {//空间直角坐标(m) a = 6378137.0 (m) f = 1.0 / 298.257223563
public:
	double x;
	double y;
	double z;
	XYZ(double x1=0, double y1=0, double z1=0):x(x1),y(y1),z(z1){}
};
class BLH {//大地坐标(弧度/m)
public:
	double B;//longitude
	double L;//latitude
	double H;//height
	BLH(double B1 = 0, double L1 = 0, double H1 = 0) :B(B1), L(L1), H(H1) {}
};
XYZ BLH2XYZ(BLH c1, XYZ& c2) {//大地转空间坐标系
	double N = a / sqrt(1 - (2*f-f*f) * sin(c1.B )* sin(c1.B));
	c2.x = (N + c1.H) * cos(c1.B ) * cos(c1.L );
	c2.y= (N + c1.H) * cos(c1.B ) * sin(c1.L );
	c2.z = (N * (1 - (2*f-f*f)) + c1.H) * sin(c1.B );
	return c2;
}

BLH XYZ2BLH(XYZ c1, BLH& c2) {//空间转大地坐标系
	double N,temp_B=0;
	c2.L = atan(c1.y / c1.x);
	c2.B = 0;
	while (1) { 
		N = a / sqrt(1 - (2 * f - f * f) * sin(c2.B) * sin(c2.B));
		temp_B= atan((c1.z + N * (2 * f - f * f) * sin(c2.B)) / sqrt(c1.x * c1.x + c1.y * c1.y));
		if (fabs(temp_B - c2.B) <= 1e-10)break;
		c2.B=temp_B;
	}
	c2.H = sqrt(c1.x * c1.x + c1.y * c1.y) / cos(c2.B) - N;
	return c2;
}

int main() {
	char s0;
	cout << "1.大地坐标转空间直角坐标 2.空间直角坐标转大地坐标 " << endl;
	cin >> s0;
	if (s0 == '1') {
		int b, l, h;
		XYZ c1;
		cin >> b >> l>> h;
		BLH c2(b / 180.0 * PI , l / 180.0 * PI,h);
		BLH2XYZ(c2,c1);
		cout <<"XYZ:" <<fixed<<setprecision(4)<< c1.x << "," << fixed <<setprecision(4) << c1.y << "," << fixed << setprecision(0) << c1.z << endl;
	}
	else if (s0 == '2') {
		XYZ c1;
		BLH c2;
		cin >> c1.x >> c1.y >> c1.z;
		XYZ2BLH(c1, c2);
		cout << "BLH:"  << round(c2.B* 180.0 / PI)<< "," << round(180+c2.L * 180.0 / PI) << "," << round(c2.H )<< endl;
	}
	else
		cout << "error!" << endl;
	return 0;
}
//BLH:32°N，112°E，100     //32 112 100
//XYZ: -2028173.6746  5019905.9985  3360484