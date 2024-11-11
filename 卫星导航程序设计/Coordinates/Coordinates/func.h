#pragma once
#include<iostream>
#include<math.h>
#include<string>
#include<iomanip>
#include<iomanip>
#define PI 3.14159265359
#define a 6378137.0//长半轴
#define f 1.0/298.257223563//e*e=2*f-f*f e为第一偏心率
using namespace std;
//空间直角坐标(笛卡尔坐标)
class CRDCARTESIAN {
public:
	double x;
	double y;
	double z;
	CRDCARTESIAN(double X=0, double Y=0, double Z=0):x(X),y(Y),z(Z){}
} ;
//大地坐标
class CRDGEODETIC {
public:
	double longitude;//B
	double latitude;//L
	double height;//H
	CRDGEODETIC(double X=0, double Y=0, double Z=0) :longitude(X), latitude(Y), height(Z) {}
} ;
//站心地平坐标(线坐标形式)
class CRDTOPOCENTRIC {
public:
	double northing;
	double easting;
	double upping;
	CRDTOPOCENTRIC(double X=0, double Y=0, double Z=0) :northing(X), easting(Y), upping(Z) {}
};
//站心地平坐标(极坐标形式)
class CRDTOPOCENTRICPOLAR {
public:
	double range;
	double azimuth;
	double elevation;
	CRDTOPOCENTRICPOLAR(double X=0, double Y=0, double Z=0) :range(X), azimuth(Y), elevation(Z) {}
};
//1.由笛卡尔坐标转换为大地坐标
void Cartesian2Geodetic(CRDCARTESIAN cg, CRDGEODETIC& cc){
	cc.latitude = atan(cg.y / cg.x);//L
	double R = sqrt(cg.x * cg.x + cg.y * cg.y + cg.z * cg.z);
	double PHI = atan(cg.z / sqrt(cg.x * cg.x + cg.y * cg.y));
	double W = sqrt(1 - (2 * f - f * f) * sin(cc.longitude) * sin(cc.longitude));
	double N = a / W;
	double B_temp = 0;
	double B = acos(R * cos(PHI) / N);
	while (1) {
		B_temp = atan(tan(PHI) * (1 + a * (2 * f - f * f) * sin(B) / (cg.z * W)));
		if (fabs(B - B_temp) < 1e-10)break;
		B = B_temp;
	}
	cc.longitude = B_temp;
	cc.height = R * cos(PHI) / cos(cc.longitude) - N;
}
//2.由大地坐标转换为笛卡尔坐标
void Geodetic2Cartesian(CRDCARTESIAN& cg, CRDGEODETIC cc){
	double N = a / sqrt(1 - (2 * f - f * f) * sin(cc.longitude) * sin(cc.longitude));
	cg.x = (N + cc.height) * cos(cc.longitude) * cos(cc.latitude);
	cg.y = (N + cc.height) * cos(cc.longitude) * sin(cc.latitude);
	cg.z = (N * (1 - (2 * f - f * f)) + cc.height) * sin(cc.longitude);
}
//3.由笛卡尔坐标转换为站心地平坐标
void Cartesian2Topocentric(CRDTOPOCENTRIC& ct, CRDCARTESIAN cc, CRDCARTESIAN ccCenter){
	double x_delta = cc.x - ccCenter.x;
	double y_delta = cc.y - ccCenter.y;
	double z_delta = cc.z - ccCenter.z;
	CRDGEODETIC cg;
	Cartesian2Geodetic(cc, cg);//XYZ->BLH
	ct.northing = (-sin(cg.longitude)) * cos(cg.latitude) * x_delta+ (-sin(cg.longitude)) * sin(cg.latitude) * y_delta + cos(cg.longitude) * z_delta;
	ct.easting = (-sin(cg.latitude)) * x_delta + cos(cg.latitude) * y_delta;
	ct.upping = cos(cg.longitude) * cos(cg.latitude) * x_delta + cos(cg.longitude) * sin(cg.latitude) * y_delta + sin(cg.longitude) * z_delta;
}
//4.由站心地平直角坐标转换为站心地平极坐标
void Topocentric2TopocentricPolar(CRDTOPOCENTRICPOLAR& ctp, CRDTOPOCENTRIC ct){
	ctp.range = sqrt(ct.northing * ct.northing + ct.easting * ct.easting + ct.upping * ct.upping);
	ctp.azimuth = atan(ct.easting / ct.northing);
	ctp.elevation = asin(ct.upping / ctp.range);
}