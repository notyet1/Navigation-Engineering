#include<math.h>
#include <cctype>
#include <fstream>
#include <iostream>
#include <cassert>
#include <string>
#include <cstring>
#include <iomanip>
#include<sstream>
#include <algorithm>
#include<vector>
#define MAX 999999
#define MU 3.9860050e+14
#define clight 299792458.0
#define OMGe 7.2921151467e-5//(rad/s)
using namespace std;
class g_time {//钟时间
public:
	int year;
	int month;
	int day;
	int hour;
	int minute;
	double second;
	int GPS_time;
	double toes;
	g_time(int x1 = 0, int x2 = 0, int x3 = 0, int x4 = 0, int x5 = 0, double x6 = 0) :year(x1), month(x2), day(x3), hour(x4), minute(x5), second(x6) { GPS_time = 0; toes = 0; }
};
class eph_t {
public:
	int prn;
	int svh;//卫星健康状况(svh)
	int week;//GPS周
	g_time toe;//卫星星历的参考时刻
	g_time toc;//卫星钟时间
	double A, e; // 轨道长半轴(A)，偏心率(e)
	double i0;//轨道倾角（i0)
	double OMG0;// 升交点经度(0MG0)
	double omg;//近地点角距（omg）
	double M0; //平近点角（M0）
	double deln;//平均角速度(deln)
	double OMGD; //升交点速率（OMGd）
	double idot;//轨道倾角变化率（idot）
	double crc, crs; //地心距的摄动改正项(crc, crs)
	double cuc, cus;  //升交角距的摄动改正项(cuc, cus)
	double cic, cis;  //倾角的摄动改正项（cic，cis）
	double toes;    //周内秒(toes)
	eph_t() {
		prn = 0; svh = 0; week = 0; A = 0.0; e = 0.0; i0 = 0.0; OMG0 = 0.0; omg = 0.0; M0 = 0.0; deln = 0.0; OMGD = 0.0; idot = 0.0; crc = 0.0; crs = 0.0; cuc = 0.0; cus = 0.0; cic = 0.0; cis = 0.0; toes = 0.0;
	}

};


class nav_t {
public:
	int  N, nmax; 
	eph_t* eph; 
	nav_t(int x1, int x2) :N(x1), nmax(x2) {
		eph = new eph_t[nmax];
	}
	~nav_t() {
		delete[] eph;
	}
};
double get_tk(double tk) {
	return (tk > 302400) ? tk - 604800 : ((tk < -302400) ? tk + 604800 : tk);
}
int main() {
	nav_t nav(32, 99);
	char s1[MAX];
	int PRN;
	vector<double>data;
	ifstream file("brdc0320.21n");

	if (!file.fail()) {
		g_time t;
		int i = 0;
		string line, s1;
		int lineNumber = 1;
		int count = 1;
		while (getline(file, line)) {
			lineNumber++;
			if (lineNumber >= 10) {

				if (!line.empty()) {
					if (count == 1) {

						if (line[0] == ' ') { PRN = line[1] - '0'; }
						else if (isdigit(line[0])) { PRN = line[1] - '0' + (line[0] - '0') * 10; }
						nav.eph[PRN];

						
						g_time referenceTime(2021, 2, 1, 0, 0, 30);
						(nav.eph[PRN]).toe = referenceTime;
						t.year = 2000 + (line[3] - '0') * 10 + (line[4] - '0');
						t.month = line[7] - '0';
						t.day = line[10] - '0';
						t.hour = line[13] - '0';
						t.minute = line[16] - '0';
						s1 = line.substr(19, 3);
						t.second = stod(s1);
						replace(line.begin(), line.end(), 'D', 'e');
						s1 = line.substr(22, 19);
						data.push_back(stod(s1));
						s1 = line.substr(41, 19);
						data.push_back(stod(s1));
						s1 = line.substr(60, 19);
						data.push_back(stod(s1));
						count++;
					}
					else if (count > 1 && count < 8) {
						replace(line.begin(), line.end(), 'D', 'e');
						for (int i = 0; i < 4; i++) {
							s1 = line.substr(3 + 19 * i, 19);
							data.push_back(stod(s1));

						}

						count++;
					}
					else if (count == 8) {
						replace(line.begin(), line.end(), 'D', 'e');
						for (int i = 0; i < 4; i++) {
							s1 = line.substr(3 + 19 * i, 19);
							data.push_back(stod(s1));
						}
						
						nav.eph[PRN].prn = PRN;
						nav.eph[PRN].toc = t;
						nav.eph[PRN].crs = data[4];
						nav.eph[PRN].deln = data[5];
						nav.eph[PRN].M0 = data[6];
						nav.eph[PRN].cus = data[7];
						nav.eph[PRN].e = data[8];
						nav.eph[PRN].cuc = data[9];
						nav.eph[PRN].A = pow(data[10], 2);
						nav.eph[PRN].toes = data[11];
						nav.eph[PRN].cic = data[12];
						nav.eph[PRN].OMG0 = data[13];
						nav.eph[PRN].cis = data[14];
						nav.eph[PRN].i0 = data[15];
						nav.eph[PRN].crc = data[16];
						nav.eph[PRN].omg = data[17];
						nav.eph[PRN].OMGD = data[18];
						nav.eph[PRN].idot = data[19];
						nav.eph[PRN].week = data[21];
						nav.eph[PRN].svh = data[24];
						data.clear();
						count = 1;
					}
				}
			}
		}
		file.close();
	}

	else exit(1);
	

	int Prn;
	cout << "Prn:" << endl;
	cin >> Prn;
	double n, Mk;
	double n0 = sqrt(MU / ((nav.eph[Prn].A) * (nav.eph[Prn].A) * (nav.eph[Prn].A)));
	nav.eph[Prn].toe.GPS_time = 2143;
	nav.eph[Prn].toe.toes = 86430;
	nav.eph[Prn].toc.GPS_time = 2143;
	nav.eph[Prn].toc.toes = 86400;
	double tk = 30.0;
	tk = get_tk(tk);

	n = n0 + nav.eph[Prn].deln;
	Mk = nav.eph[Prn].M0 + n * tk;
	double Ek = Mk, Ek_ = Mk;
	while (1) {
		Ek = Ek_ - (Ek_ - nav.eph[Prn].e * sin(Ek_) - Mk) / (1 - nav.eph[Prn].e * cos(Ek_));
		if (Ek - Ek_ < 1e-13)break;
		Ek_ = Ek;
	}
	double vk = atan2(sqrt(1 - nav.eph[Prn].e * nav.eph[Prn].e) * sin(Ek), cos(Ek) - nav.eph[Prn].e);
	double PHIk = vk + nav.eph[Prn].omg;
	double DEL_uk = nav.eph[Prn].cus * sin(2.0 * PHIk) + nav.eph[Prn].cuc * cos(2.0 * PHIk);//δ
	double DEL_rk = nav.eph[Prn].crs * sin(2.0 * PHIk) + nav.eph[Prn].crc * cos(2.0 * PHIk);
	double DEL_ik = nav.eph[Prn].cis * sin(2.0 * PHIk) + nav.eph[Prn].cic * cos(2.0 * PHIk);
	double uk = DEL_uk + PHIk;
	double rk = nav.eph[Prn].A * (1 - nav.eph[Prn].e * cos(Ek)) + DEL_rk;
	double ik = nav.eph[Prn].i0 + DEL_ik + nav.eph[Prn].idot * tk;
	double xk_ = rk * cos(uk);
	double yk_ = rk * sin(uk);
	double OMGk = nav.eph[Prn].OMG0 + (nav.eph[Prn].OMGD - OMGe) * tk - OMGe * nav.eph[Prn].toes;
	double xk = xk_ * cos(OMGk) - yk_ * cos(ik) * sin(OMGk);
	double yk = xk_ * sin(OMGk) + yk_ * cos(ik) * cos(OMGk);
	double zk = yk_ * sin(ik);


	cout << "G" << setfill('0') << setw(2) << Prn << " " << fixed<<setprecision(7)<<xk << " " << fixed << setprecision(7) << yk <<  " " << fixed << setprecision(7) << zk << endl;


	return 0;
}