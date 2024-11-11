#pragma once
#include<iostream>
#include<math.h>
#include<iomanip>
#include<string>

using namespace std;
/*�����ն��� �ӹ�Ԫǰ4713��1��1�����翪ʼ������*/
class JulianDay {
public:

	unsigned long day;//���������
	long sn;//��ǰ�����������
	double tos;//��ǰʱ������벿��
	JulianDay(int a = 0, int b = 0, double c = 0) : day(a), sn(b), tos(c) {}

	double JulianDay_Output() {
		double julianday = this->day + (this->sn + this->tos) / 86400.0;
		return julianday;
	}
};
/*�������� ��1858��11��17����ҹ��ʼ������*/
class MJulianDay {
public:

	unsigned long day;
	long sn;
	double tos;
	MJulianDay(int a = 0, int b = 0, double c = 0) : day(a), sn(b), tos(c) {}

	double MJulianDay_Output() {
		double mjulianday = this->day + (this->sn + this->tos) / 86400.0;
		return mjulianday;
	}
};

/*�����  �ӵ���1��1�տ�ʼ������*/
//class DOY {
//public:
//	unsigned short year;
//	unsigned short day;
//	long sn;
//	double tos;
//
//};

/* ͨ��ʱ�䶨��*/
class  COMMONTIME
{
public:
	unsigned short year;
	unsigned short month;
	unsigned short day;
	unsigned short hour;
	unsigned short minute;
	double second;
	COMMONTIME(int a = 0, int b = 0, int c = 0, int d = 0, int e = 0, double f = 0) :year(a), month(b), day(c), hour(d), minute(e), second(f) {}
};
/*GPSʱ���� �����1980��1��6��00ʱ00��00�룬���ܺ�����������ʾ*/
class GPSTime
{
public:
	int wn;
	long sn;
	double tos;
	GPSTime(unsigned short a = 0, int b = 0, double c = 0) :wn(a), sn(b), tos(c) {}
};
double frac(double x) {
	return x - int(x);
}
//������ת��������
double JulianDay2MJulianDay(double JD) {
	return JD - 2400000.5;
}
//��������ת������
double MJulianDay2JulianDay(double MJD) {
	return MJD + 2400000.5;
}
//1.ͨ��ʱ�������յ�ת��
void CommonTime2JulianDay(COMMONTIME ct, JulianDay& jd) {
	int y = 0, m = 0;
	y = (ct.month <= 2) ? (ct.year - 1) : ct.year;
	m = (ct.month <= 2) ? (ct.month + 12) : ct.month;
	double Day = int(365.25 * y) + int(30.6001 * (m + 1)) + ct.day + ct.hour / 24 + 1720981.5;//UT/24
	jd.day=int(Day);
	jd.sn = int(frac(Day) * 86400.0);
	jd.tos = frac(frac(Day) * 86400.0);
}
//2.������תͨ��ʱ
void JulianDay2CommonTime(COMMONTIME& ct, JulianDay& jd) {
	double x = jd.JulianDay_Output();
	int a = int(x + 0.5);
	int b = a + 1537;
	int c = int((b - 122.1) / 365.25);
	int d = int(365.25 * c);
	int e = int((b - d) / 30.6001);
	ct.day = b - d - int(30.6001 * e) + frac(x + 0.5);
	ct.month = e - 1 - 12 * int(e / 14);
	ct.year = c - 4715 - int((7 + ct.month) / 10);
	ct.hour = (jd.sn / 3600 + 12) % 24;
	ct.minute = (jd.sn % 3600) / 60;
	ct.second = jd.sn % 60 + jd.tos;
}
//3.GPSʱת������
void GPSTime2JulianDay(GPSTime gt, JulianDay& jd) {
	double MJD = 44244 + gt.wn * 7 + gt.sn / 86400;
	jd.day =int (MJulianDay2JulianDay(MJD));
	jd.sn = int(frac(MJulianDay2JulianDay(MJD)) * 86400.0);
	jd.tos = frac(frac(MJulianDay2JulianDay(MJD)) * 86400.0);
}
//4. �����յ�GPSʱ
void JulianDay2GPSTime(JulianDay jd, GPSTime& gt) {
	double MJD = JulianDay2MJulianDay(jd.JulianDay_Output());
	gt.wn = int((MJD - 44244) / 7);
	gt.sn = (MJD - 44244 - gt.wn * 7) * 86400;
}
//5. ͨ��ʱ��GPSʱ
void CommonTime2GPSTime(COMMONTIME ct, GPSTime& gt) {
	JulianDay jd;
	CommonTime2JulianDay(ct, jd);
	JulianDay2GPSTime(jd, gt);
}
//6. GPSʱ��ͨ��ʱ
void GPSTime2CommonTime(COMMONTIME& ct, GPSTime gt) {
	JulianDay jd;
	GPSTime2JulianDay(gt, jd);
	JulianDay2CommonTime(ct, jd);
}
