#pragma once
#define _MAX_ 9999
#define _MAX_NUM_ 3000
#include<string>
#include<iostream>
using namespace std;
/* 通用时间定义*/
class  COMMONTIME{
public:
	unsigned short year;
	unsigned short month;
	unsigned short day;
	unsigned short hour;
	unsigned short minute;
	double second;
	COMMONTIME(int a = 0, int b = 0, int c = 0, int d = 0, int e = 0, double f = 0) :year(a), month(b), day(c), hour(d), minute(e), second(f) {}
};
//站心地平坐标(线坐标形式)
class CRDTOPOCENTRIC {
public:
	double northing;
	double easting;
	double upping;
	CRDTOPOCENTRIC(double X = 0, double Y = 0, double Z = 0) :northing(X), easting(Y), upping(Z) {}
};
//空间直角坐标(笛卡尔坐标)
class CRDCARTESIAN {
public:
	double x;
	double y;
	double z;
	CRDCARTESIAN(double X = 0, double Y = 0, double Z = 0) :x(X), y(Y), z(Z) {}
};
//UTC
class DELTA_UTC {
public:
	double A0;
	double A1;
	long T;
	long W;
};
//--------------导航文件--------------
class delta_utc {//时间改正参数
public:
	double A0;
	double A1;
	long T;
	long W;
	delta_utc(double a = 0, double b = 0, long c = 0, long d = 0) : A0(a), A1(b), T(c), W(d) {}
};
class VERSION_MESSAGE {//版本信息
public:
	string RINEX_VERSION;
	string TYPE;
	string PGM;
	string RUN_BY;
	string DATE;
	VERSION_MESSAGE() : RINEX_VERSION(""), TYPE(""), PGM(""), RUN_BY(""), DATE("") {}
};

//GNSS导航电文头
class GMNHDR {
public:
	VERSION_MESSAGE ver;

	double GPS_ion_alpha[4];//电离层改正参数
	double GPS_ion_beta[4];
	double BDS_ion_alpha[4];
	double BDS_ion_beta[4];

	DELTA_UTC BDS_delta_utc;
	DELTA_UTC GPS_delta_utc;

	long leap_seconds[4];//跳秒
	GMNHDR() {
		// 初始化 DELTA_UTC
		BDS_delta_utc = DELTA_UTC();
		GPS_delta_utc = DELTA_UTC();
	}
};
//GNSS导航电文记录
class GMNREC {
public:
	string PRN;
	COMMONTIME TOC;
	double ClkBias;
	double ClkDrift;
	double ClkDriftRate;
	double IODE;
	double Crs;
	double DetlaN;
	double M0;
	double Cuc;
	double e;
	double Cus;
	double SqrtA;
	double TOE;
	double Cic;
	double Omega;
	double Cis;
	double i0;
	double Crc;
	double omega;
	double OmegaDot;
	double iDot;
	double CodesOnL2Channel;
	double GPSWeek;
	double L2PDataFlag;
	double SVAccuracy;
	double SVHealth;
	double TGD;
	double IODC;
	double TransTimeOfMsg;
	double Spare1;//29
	double Spare2;
	double Spare3;
	GMNREC() : PRN(""), ClkBias(0), ClkDrift(0), ClkDriftRate(0), IODE(0), Crs(0), DetlaN(0), M0(0),
		Cuc(0), e(0), Cus(0), SqrtA(0), TOE(0), Cic(0), Omega(0), Cis(0), i0(0), Crc(0),
		omega(0), OmegaDot(0), iDot(0), CodesOnL2Channel(0), GPSWeek(0), L2PDataFlag(0),
		SVAccuracy(0), SVHealth(0), TGD(0), IODC(0), TransTimeOfMsg(0), Spare1(0), Spare2(0), Spare3(0) {}
	void PrintGMNREC() const {
		cout << "PRN: " << PRN << endl;
		cout << "ClkBias: " << ClkBias << endl;
		cout << "ClkDrift: " << ClkDrift << endl;
		cout << "ClkDriftRate: " << ClkDriftRate << endl;
		cout << "IODE: " << IODE << endl;
		cout << "Crs: " << Crs << endl;
		cout << "DetlaN: " << DetlaN << endl;
		cout << "M0: " << M0 << endl;
		cout << "Cuc: " << Cuc << endl;
		cout << "e: " << e << endl;
		cout << "Cus: " << Cus << endl;
		cout << "SqrtA: " << SqrtA << endl;
		cout << "TOE: " << TOE << endl;
		cout << "Cic: " << Cic << endl;
		cout << "Omega: " << Omega << endl;
		cout << "Cis: " << Cis << endl;
		cout << "i0: " << i0 << endl;
		cout << "Crc: " << Crc << endl;
		cout << "omega: " << omega << endl;
		cout << "OmegaDot: " << OmegaDot << endl;
		cout << "iDot: " << iDot << endl;
		cout << "CodesOnL2Channel: " << CodesOnL2Channel << endl;
		cout << "GPSWeek: " << GPSWeek << endl;
		cout << "L2PDataFlag: " << L2PDataFlag << endl;
		cout << "SVAccuracy: " << SVAccuracy << endl;
		cout << "SVHealth: " << SVHealth << endl;
		cout << "TGD: " << TGD << endl;
		cout << "IODC: " << IODC << endl;
		cout << "TransTimeOfMsg: " << TransTimeOfMsg << endl;
		cout << "Spare1: " << Spare1 << endl;
	}
};
//GNSS导航电文信息

class GMN {
public:
	GMNHDR hdr;
	GMNREC* record;
	void GetGMN(const char* FileName);
	void PrintHeader();
	GMN() {
		record = new GMNREC[_MAX_];
	}
	~GMN() {
		delete [] record;
	}

};

void GMN::PrintHeader() {
	cout << "RINEX_VERSION: " << hdr.ver.RINEX_VERSION << endl;
	cout << "TYPE: " << hdr.ver.TYPE << endl;
	cout << "PGM: " << hdr.ver.PGM << endl;
	cout << "RUN_BY: " << hdr.ver.RUN_BY << endl;
	cout << "DATE: " << hdr.ver.DATE << endl;

	cout << "GPS_ion_alpha: ";
	for (double alpha : hdr.GPS_ion_alpha) {
		cout << alpha << " ";
	}
	cout << endl;

	cout << "GPS_ion_beta: ";
	for (double beta : hdr.GPS_ion_beta) {
		cout << beta << " ";
	}
	cout << endl;

	cout << "BDS_ion_alpha: ";
	for (double alpha : hdr.BDS_ion_alpha) {
		cout << alpha << " ";
	}
	cout << endl;

	cout << "BDS_ion_beta: ";
	for (double beta : hdr.BDS_ion_beta) {
		cout << beta << " ";
	}
	cout << endl;

	cout << "BDS_delta_utc: A0=" << hdr.BDS_delta_utc.A0
		<< ", A1=" << hdr.BDS_delta_utc.A1
		<< ", T=" << hdr.BDS_delta_utc.T
		<< ", W=" << hdr.BDS_delta_utc.W << endl;

	cout << "GPS_delta_utc: A0=" << hdr.GPS_delta_utc.A0
		<< ", A1=" << hdr.GPS_delta_utc.A1
		<< ", T=" << hdr.GPS_delta_utc.T
		<< ", W=" << hdr.GPS_delta_utc.W << endl;

	cout << "Leap Seconds: ";
	for (long leap : hdr.leap_seconds) {
		cout << leap << " ";
	}
	cout << endl;
}

//--------------观测文件--------------
class GPS_OBSTYPE {
public:
	 int obs_type_number;
     string obs_type_list[_MAX_];
	 GPS_OBSTYPE() :obs_type_number(0) {}
};
class BDS_OBSTYPE {
public:
     int obs_type_number;
     string obs_type_list[_MAX_];
	 BDS_OBSTYPE() :obs_type_number(0) {}
};


//GNSS观测值信息头
class GMOHDR {
public:
	VERSION_MESSAGE ver;//• 版本及类型(RINEX VERSION / TYPE)
	string marker_name;//• 站名(MARKER NAME)
    string marker_number;
	string marker_type;

	string rec_sn;// REC # / TYPE / VERS 
	string rec_type;
	string rec_ver;

	string ant_sn;// ANT # / TYPE        
	string ant_type;

	CRDCARTESIAN approx_pos;//• 近似坐标(APPROX POSITION XYZ)

	CRDTOPOCENTRIC ant_delta;//• 天线偏差(ANTENNA: DELTA H / E / N)
	
	GPS_OBSTYPE gps_obstype;               //• 观测值类型(SYS / # / OBS TYPES )
	BDS_OBSTYPE bds_obstype;

	double interval;

	COMMONTIME start;
	COMMONTIME end;
	void PrintGMOHDR() const {
		cout << "版本及类型: " << ver.RINEX_VERSION << endl; 
		cout << "站名: " << marker_name << endl;
		cout << "站号: " << marker_number << endl;
		//cout << "站类型: " << marker_type << endl;

		cout << "接收机序列号: " << rec_sn << endl;
		cout << "接收机类型: " << rec_type << endl;
		cout << "接收机版本: " << rec_ver << endl;

		cout << "天线序列号: " << ant_sn << endl;
		cout << "天线类型: " << ant_type << endl;

		cout << "时间间隔: " << interval << endl;
		
	}
};



// GMO记录头
class GMORECHDR {
public:
	COMMONTIME epoch; // 历元时刻
	double rcvr_clk_bias; // 接收机钟的偏差
	short Epoch_flag;//0: OK  1: power failure between previous and current epoch  > 1: Special even
	short num_sat; // 卫星数
	GMORECHDR():rcvr_clk_bias(0),Epoch_flag(0),num_sat(0){}
	void PrintGMORECHDR() const {
		std::cout << "历元时刻: " << epoch.year <<" " << epoch.month << " " << epoch.day << " " << epoch.hour << " " << epoch.minute << " " << epoch.second << std::endl;
		std::cout << "历元标志: " << Epoch_flag << std::endl;
		std::cout << "卫星数: " << num_sat << std::endl;
	}
};
//GNSS观测值
class GNSSOBS {
public:
	string prn[_MAX_];
	string value[_MAX_];
	
};
//GNSS观测值信息记录
class GMOREC {
public:
	GMORECHDR gmorechdr;
	GNSSOBS gnssobs;
};


//GNSS观测值信息
class GMO {
public:
	GMOHDR gmohdr;
	GMOREC* record;
	GMO(){
		record = new GMOREC[_MAX_NUM_];
	}
	~GMO() {
		delete[] record;
	}
	void GetGMO(const char* FileName);
};