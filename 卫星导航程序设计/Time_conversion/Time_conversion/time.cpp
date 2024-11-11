#include<iostream>
#include<math.h>
#include<iomanip>
#include<string>
#define SECOND1 316051200
#define SECOND2 315964800
using namespace std;

/* 通用时间定义*/
class  COMMONTIME
{
public:
	unsigned short Year;
	unsigned short Month;
	unsigned short Day;
	unsigned short Hour;
	unsigned short Minute;
	double Second;
	COMMONTIME(int a=0,int b=0,int c=0,int d=0,int e=0,double f=0):Year(a),Month(b),Day(c),Hour(d),Minute(e),Second(f){}
};
/*GPS时定义 起点是1980年1月6日00时00分00秒，用周和周内秒来表示*/
class GPSTime
{
public:
	int Week;
	double Second;
	GPSTime(unsigned short a=0, double b=0):Week(a),Second(b){}
};
/*unix time时间定义 定义为从格林威治时间1970年01月01日00时00分起至现在的总秒数，不计算闰秒。*/
class gtime_t
{
public:
	long  time;
	double second;
	gtime_t(long long a=0,double b=0):time(a),second(b){}
};
int daysFromCommonTime(COMMONTIME t) {
	int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int leapYear = 0;
	int days = 0;
	for (int i = 1970; i < t.Year; i++) {
		if (i % 4 == 0)leapYear++;
	}
	 days = (t.Year - 1970) * 365 +leapYear;
	for (int i = 1; i < t.Month; i++) {
		days += daysInMonth[i];
	}
	days += t.Day;
	return days;
}

gtime_t str2time(string s, gtime_t &t0, COMMONTIME &t1) { //通用时转Unix time
	
		t1.Year = (s[0] - '0') * 1000 + (s[1] - '0') * 100 + (s[2] - '0') * 10 + (s[3] - '0');
		t1.Month= (s[5] - '0') * 10 + (s[6] - '0');
		t1.Day = (s[8] - '0') * 10 + (s[9] - '0');
		t1.Hour = (s[11] - '0') * 10 + (s[12] - '0');
		t1.Minute = (s[14] - '0') * 10 + (s[15] - '0');
		t1.Second = (double)((s[17] - '0') * 10 + (s[18] - '0')) ;
		t0.time = daysFromCommonTime(t1) *86400 + t1.Hour * 3600 + t1.Minute * 60 + (int)(floor(t1.Second));
		t0.second = t1.Second - floor(t1.Second);

	return t0;
}
gtime_t gpst2time(GPSTime& t1, gtime_t& t0) {//GPS时转Unix time
	t0.time = 86400 * 7 * t1.Week + int(t1.Second) + SECOND2;//表示GPS时的起点距Unix time起点的秒数
	t0.second = t1.Second - int(t1.Second);
	return t0;
}
GPSTime time2gpst(gtime_t &t0, GPSTime &t1, COMMONTIME t2) {// Unix time 转GPS时
	t1.Week = int((t0.time - SECOND1) / (86400 * 7));
	t1.Second = (double)(t0.time - SECOND1 - t1.Week * 86400 * 7) + t0.second;
	return t1;
}
COMMONTIME time2epoch(gtime_t& t0, COMMONTIME& t1) {// Unix time转通用时
	int d, mon;
	int Days = t0.time / 86400;//Days：表示Unix time 起点到当前通用时的天数
	int secs = (int)(t0.time - Days * 86400);
	int mday[] = { 31,28,31,30,31,30,31,31,30,31,30,31,
				   31,28,31,30,31,30,31,31,30,31,30,31,
				   31,29,31,30,31,30,31,31,30,31,30,31,
				   31,28,31,30,31,30,31,31,30,31,30,31 };
	for (d = Days % 1461, mon = 0; mon < 48; mon++) {
		if (d >= mday[mon]) d -= mday[mon];
		else break;
	}
	t1.Year = 1970 + Days / 1461 * 4 + mon / 12;
	t1.Month = mon % 12 + 1;
	t1.Day = d + 1;
	t1.Hour = (int)(secs / 3600);
	t1.Minute = (int)((secs - t1.Hour * 3600) / 60);
	t1.Second = double(secs - t1.Hour * 3600 - t1.Minute * 60);
	return t1;
}
int main() {
	char a;
	cout << "1.通用时转GPS时 2.GPS时转通用时 " << endl;
	cin >> a;
	if (a == '1') {
		string s;
		gtime_t t0;
		GPSTime t1;
		COMMONTIME t2;
		cin.ignore();
		getline(cin, s);
		str2time(s, t0, t2);
		time2gpst(t0, t1, t2);
		cout << t1.Week << " " << fixed << setprecision(2) <<t1.Second << endl;
	}
	else if (a == '2') {
		int week;
		double sec;
		cin >> week >> sec;
		GPSTime t1(week, sec);
		gtime_t t0;
		COMMONTIME t2;
		gpst2time(t1,t0);
		time2epoch(t0, t2);
		cout << t2.Year << "/" << setfill('0') << setw(2) << t2.Month << "/" << setfill('0') << setw(2) << t2.Day << " " << setfill('0') << setw(2) << t2.Hour << ":" << setfill('0') << setw(2) << t2.Minute << ":" << setfill('0') << setw(2) << t2.Second << endl;
	}
	else
		cout << "error!" << endl;
	return 0;
}
//2021/05/21 02:14:45
//2000/02/29 00:00:00
//1999/12/31 01:01:10

//2158    440085.00
//1051    172800.00
//1042    435670.00

