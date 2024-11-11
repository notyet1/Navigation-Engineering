#pragma once
#include"basic.h"
#include<math.h>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include<sstream>
#include<vector>
class GMN;
class GMO;
using namespace std;

void GMN::GetGMN(const char* FileName) {
    vector<double>ion;
    ifstream file(FileName);
    if (!file.fail()) {
        string line, s1, s2,s3,temp;
        int lineNumber = 0;
        int cot=0 ;//count
        int flag = 0;//1=GPS;2=BDS;
        int i = 0;
        int hdr_flag = 1;
        while (getline(file, line)) {
            lineNumber++;
            if (lineNumber > 9999)break;
            else if (!line.empty()&&lineNumber<=9999) {
                if (hdr_flag == 1) {
                    //信息头
             
                    s1 = line.substr(60);
                    s3 = line.substr(60, 13);
                    if (s1 == "RINEX VERSION / TYPE") {
                        hdr.ver.RINEX_VERSION = line.substr(5, 4);
                        hdr.ver.TYPE = line.substr(40, 2);
                        continue;
                    }
                    else if (s1 == "PGM / RUN BY / DATE ") {
                        hdr.ver.PGM = line.substr(0, 8);
                        hdr.ver.RUN_BY = line.substr(20, 5);
                        hdr.ver.DATE = line.substr(40, 19);
                        continue;
                    }
                    else if (s1 == "IONOSPHERIC CORR    ") {
                        s2 = line.substr(0, 4);
                        
                        for (int i_ = 0; i_ < 4; i_++) {
                            if (line.substr(6 + 12 * i_, 11)=="           ") {
                                ion.push_back(0);
                            }
                            else
                                ion.push_back(stod(line.substr(6 + 12 * i_, 11)));

                        }
                        if (ion.size() >= 4) {
                            if (s2 == "GPSA") { hdr.GPS_ion_alpha[0] = ion[0], hdr.GPS_ion_alpha[1] = ion[1], hdr.GPS_ion_alpha[2] = ion[2], hdr.GPS_ion_alpha[3] = ion[3]; }
                        else if (s2 == "GPSB") { hdr.GPS_ion_beta[0] = ion[0], hdr.GPS_ion_beta[1] = ion[1], hdr.GPS_ion_beta[2] = ion[2], hdr.GPS_ion_beta[3] = ion[3]; }
                        else if (s2 == "BDSA") { hdr.BDS_ion_alpha[0] = ion[0], hdr.BDS_ion_alpha[1] = ion[1], hdr.BDS_ion_alpha[2] = ion[2], hdr.BDS_ion_alpha[3] = ion[3]; }
                        else if (s2 == "BDSB") { hdr.BDS_ion_beta[0] = ion[0], hdr.BDS_ion_beta[1] = ion[1], hdr.BDS_ion_beta[2] = ion[2], hdr.BDS_ion_beta[3] = ion[3]; }
                            ion.clear();
                        }
                        else {
                            cout << "ion size is less than 4!" << endl;
                        }
                        continue;
                    }
                    else if (s1 == "TIME SYSTEM CORR    ") {
                        s2 = line.substr(0, 4);
                        if (s2 == "BDUT") {
                            hdr.BDS_delta_utc.A0 = stod(line.substr(5, 17));
                            hdr.BDS_delta_utc.A1 = stod(line.substr(22, 17));
                            hdr.BDS_delta_utc.T = stol(line.substr(38, 7));
                            hdr.BDS_delta_utc.W = stol(line.substr(45, 5));
                        }
                        else if (s2 == "GPUT") {
                            hdr.GPS_delta_utc.A0 = stod(line.substr(5, 17));
                            hdr.GPS_delta_utc.A1 = stod(line.substr(22, 17));
                            hdr.GPS_delta_utc.T = stol(line.substr(38, 7));
                            hdr.GPS_delta_utc.W = stol(line.substr(45, 5));
                        }
                        continue;
                    }
                    else if (s1 == "LEAP SECONDS        ") {
                        hdr.leap_seconds[0] = stol(line.substr(0, 6));
                        hdr.leap_seconds[1] = stol(line.substr(6, 6));
                        hdr.leap_seconds[2] = stol(line.substr(12, 6));
                        hdr.leap_seconds[3] = stol(line.substr(18, 6));
                        continue;
                    }
                }
                   if (s3 == "END OF HEADER") {
                       hdr_flag = 0;
                       s3.clear();
                     continue;
                   }
                 //信息记录
                   if (hdr_flag == 0) {
                     if (line[0] == 'G' && isdigit(line[1]) && isdigit(line[2])) {
                       flag = 1;
                       if (i == 0 && flag == 1) {
                           record[cot].PRN = line.substr(0, 3);
                           record[cot].TOC.year = stoi(line.substr(4, 4));
                           record[cot].TOC.month = stoi(line.substr(9, 2));
                           record[cot].TOC.day = stoi(line.substr(12, 2));
                           record[cot].TOC.hour = stoi(line.substr(15, 2));
                           record[cot].TOC.minute = stoi(line.substr(18, 2));
                           record[cot].TOC.second = stod(line.substr(21, 2));
                           record[cot].ClkBias = stod(line.substr(23, 19));
                           record[cot].ClkDrift = stod(line.substr(42, 19));
                           record[cot].ClkDriftRate = stod(line.substr(61, 19));
                           i++;
                           continue;
                       }
                     }
                   else if (i == 1 && flag == 1) {
                       record[cot].IODE = stod(line.substr(4, 19));
                       record[cot].Crs = stod(line.substr(23, 19));
                       record[cot].DetlaN = stod(line.substr(42, 19));
                       record[cot].M0 = stod(line.substr(61, 19));
                       i++;
                       continue;
                   }
                   else if (i == 2 && flag == 1) {
                       record[cot].Cuc = stod(line.substr(4, 19));
                       record[cot].e = stod(line.substr(23, 19));
                       record[cot].Cus = stod(line.substr(42, 19));
                       record[cot].SqrtA = stod(line.substr(61, 19));
                       i++;
                       continue;
                   }
                   else if (i == 3 && flag == 1) {
                       record[cot].TOE = stod(line.substr(4, 19));
                       record[cot].Cic = stod(line.substr(23, 19));
                       record[cot].Omega = stod(line.substr(42, 19));
                       record[cot].Cis = stod(line.substr(61, 19));
                       i++;
                       continue;
                   }
                   else if (i == 4 && flag == 1) {
                       record[cot].i0 = stod(line.substr(4, 19));
                       record[cot].Crc = stod(line.substr(23, 19));
                       record[cot].omega = stod(line.substr(42, 19));
                       record[cot].OmegaDot = stod(line.substr(61, 19));
                       i++;
                       continue;
                   }
                   else if (i == 5 && flag == 1) {
                       record[cot].iDot = stod(line.substr(4, 19));
                       record[cot].CodesOnL2Channel = stod(line.substr(23, 19));
                       record[cot].GPSWeek = stod(line.substr(42, 19));
                       record[cot].L2PDataFlag = stod(line.substr(61, 19));
                       i++;
                       continue;
                   }
                   else if (i == 6 && flag == 1) {
                       record[cot].SVAccuracy = stod(line.substr(4, 19));
                       record[cot].SVHealth = stod(line.substr(23, 19));
                       record[cot].TGD = stod(line.substr(42, 19));
                       record[cot].IODC = stod(line.substr(61, 19));
                       i++;
                       continue;
                   }
                   else if (i == 7 && flag == 1) {
                       record[cot].TransTimeOfMsg = stod(line.substr(4, 19));
                       record[cot].Spare1 = stod(line.substr(23, 19));
                       i == 0;
                       cot++;
                       flag = 0;
                       continue;
                   }


                   else if (line[0] == 'C' && isdigit(line[1]) && isdigit(line[2])) {
                       flag = 2;
                       if (i == 0 && flag == 2) {
                           record[cot].PRN = line.substr(0, 3);
                           record[cot].TOC.year = stoi(line.substr(4, 4));
                           record[cot].TOC.month = stoi(line.substr(9, 2));
                           record[cot].TOC.day = stoi(line.substr(12, 2));
                           record[cot].TOC.hour = stoi(line.substr(15, 2));
                           record[cot].TOC.minute = stoi(line.substr(18, 2));
                           record[cot].TOC.second = stod(line.substr(21, 2));
                           record[cot].ClkBias = stod(line.substr(23, 19));
                           record[cot].ClkDrift = stod(line.substr(42, 19));
                           record[cot].ClkDriftRate = stod(line.substr(61, 19));
                           i++;
                           continue;
                       }
                   }
                   else if (i == 1 && flag == 2) {
                       record[cot].IODE = stod(line.substr(4, 19));
                       record[cot].Crs = stod(line.substr(23, 19));
                       record[cot].DetlaN = stod(line.substr(42, 19));
                       record[cot].M0 = stod(line.substr(61, 19));
                       i++;
                       continue;
                   }
                   else if (i == 2 && flag == 2) {
                       record[cot].Cuc = stod(line.substr(4, 19));
                       record[cot].e = stod(line.substr(23, 19));
                       record[cot].Cus = stod(line.substr(42, 19));
                       record[cot].SqrtA = stod(line.substr(61, 19));
                       i++;
                       continue;
                   }
                   else if (i == 3 && flag == 2) {
                       record[cot].TOE = stod(line.substr(4, 19));
                       record[cot].Cic = stod(line.substr(23, 19));
                       record[cot].Omega = stod(line.substr(42, 19));
                       record[cot].Cis = stod(line.substr(61, 19));
                       i++;
                       continue;
                   }
                   else if (i == 4 && flag == 2) {
                       record[cot].i0 = stod(line.substr(4, 19));
                       record[cot].Crc = stod(line.substr(23, 19));
                       record[cot].omega = stod(line.substr(42, 19));
                       record[cot].OmegaDot = stod(line.substr(61, 19));
                       i++;
                       continue;
                   }
                   else if (i == 5 && flag == 2) {
                       record[cot].iDot = stod(line.substr(4, 19));
                       record[cot].CodesOnL2Channel = stod(line.substr(23, 19));
                       record[cot].GPSWeek = stod(line.substr(42, 19));
                       record[cot].L2PDataFlag = stod(line.substr(61, 19));
                       i++;
                       continue;
                   }
                   else if (i == 6 && flag == 2) {
                       record[cot].SVAccuracy = stod(line.substr(4, 19));
                       record[cot].SVHealth = stod(line.substr(23, 19));
                       record[cot].TGD = stod(line.substr(42, 19));
                       record[cot].IODC = stod(line.substr(61, 19));
                       i++;
                       continue;
                   }
                   else if (i == 7 && flag == 2) {
                       record[cot].TransTimeOfMsg = stod(line.substr(4, 19));
                       record[cot].Spare1 = stod(line.substr(23, 19));
                       i == 0;
                       cot++;
                       flag = 0;
                       continue;
                   }
                }

            }
        }
    }
    else {
        cout << "无法打开文件!" << endl;
    }
    file.close();
}
void GMO::GetGMO(const char* FileName) {
    ifstream file(FileName);
    if (!file.fail()) {
        string line, s1, s2,s3;
        int lineNumber = 1;
        int cot = -1;//count
        int cot_obs = 0;
        int flag = 0;//1=GPS;2=BDS;
        int k = 0;
        int hdr_flag = 1;
        while (getline(file, line)) {
            lineNumber++;
            if (lineNumber > 9999)break;
            else if (!line.empty() && lineNumber <= 9999){
                if (!line.empty()) {
                    if (hdr_flag == 1) {
                        //信息头
                        s1 = line.substr(60);
                        s3 = line.substr(60, 13);
                        if (s1 == "RINEX VERSION / TYPE") {
                            gmohdr.ver.RINEX_VERSION = line.substr(5, 4);
                            gmohdr.ver.TYPE = line.substr(20, 21);
                        }
                        else if (s1 == "PGM / RUN BY / DATE ") {
                            gmohdr.ver.PGM = line.substr(0, 15);
                            gmohdr.ver.RUN_BY = line.substr(37, 16);
                            gmohdr.ver.DATE = line.substr(40, 19);
                        }
                        else if (s1 == "MARKER NAME         ") {///**/
                            gmohdr.marker_name = line.substr(0, 10);
                        }
                        else if (s1 == "MARKER NUMBER       ") {
                            gmohdr.marker_number = line.substr(0, 9);
                        }
                        else if (s1 == "MARKER TYPE         ") {
                            gmohdr.marker_type = line.substr(0, 8);
                        }
                        else if (s1 == "REC # / TYPE / VERS ") {
                            gmohdr.rec_sn = line.substr(0, 7);
                            gmohdr.rec_type = line.substr(20, 14);
                            gmohdr.rec_ver = line.substr(40, 5);

                        }
                        else if (s1 == "ANT # / TYPE        ") {
                            gmohdr.ant_sn = line.substr(0, 4);
                            gmohdr.ant_type = line.substr(20, 20);
                        }
                        else if (s1 == "APPROX POSITION XYZ ") {
                            gmohdr.approx_pos.x = stod(line.substr(1, 13));
                            gmohdr.approx_pos.y = stod(line.substr(15, 13));
                            gmohdr.approx_pos.z = stod(line.substr(29, 13));
                        }
                        else if (s1 == "ANTENNA: DELTA H/E/N") {
                            gmohdr.ant_delta.easting = stod(line.substr(7, 7));
                            gmohdr.ant_delta.northing = stod(line.substr(21, 7));
                            gmohdr.ant_delta.upping = stod(line.substr(35, 7));
                        }
                        else if (s1 == "SYS / # / OBS TYPES ") {
                            if (line[0] == 'G') {
                                flag = 1;
                                gmohdr.gps_obstype.obs_type_number = stoi(line.substr(4, 2));
                                int j = ((gmohdr.gps_obstype.obs_type_number >= 13) ? 13 : gmohdr.gps_obstype.obs_type_number);
                                k = fabs(gmohdr.gps_obstype.obs_type_number - 13);
                                for (int i = 0; i < j; i++) {
                                    gmohdr.gps_obstype.obs_type_list[i] = line.substr(7 + 4 * i, 3);
                                }
                            }
                            if (line[0] == ' ' && flag == 1) {
                                for (int i = 0; i < k; i++) {
                                    gmohdr.gps_obstype.obs_type_list[i] = line.substr(7 + 4 * i, 3);

                                }
                                k = 0;
                                flag = 0;
                            }
                            if (line[0] == 'C') {
                                flag = 2;
                                gmohdr.bds_obstype.obs_type_number = stoi(line.substr(4, 2));
                                int j = ((gmohdr.bds_obstype.obs_type_number >= 13) ? 13 : gmohdr.bds_obstype.obs_type_number);
                                k = abs(gmohdr.bds_obstype.obs_type_number - 13);
                                for (int i = 0; i < j; i++) {
                                    gmohdr.bds_obstype.obs_type_list[i] = line.substr(7 + 4 * i, 3);
                                }
                            }
                            if (line[0] == ' ' && flag == 2) {
                                for (int i = 0; i < k; i++) {
                                    gmohdr.bds_obstype.obs_type_list[i] = line.substr(7 + 4 * i, 3);

                                }
                                k = 0;
                                flag = 0;
                            }
                        }
                        else if (s1 == "INTERVAL            ") {
                            gmohdr.interval = stod(line.substr(4, 6));
                        }
                        else if (s1 == "TIME OF FIRST OBS   ") {
                            gmohdr.start.year = stoi(line.substr(2, 4));
                            gmohdr.start.month = stoi(line.substr(10, 2));
                            gmohdr.start.day = stoi(line.substr(16, 2));
                            gmohdr.start.hour = stoi(line.substr(22, 2));
                            gmohdr.start.minute = stoi(line.substr(28, 2));
                            gmohdr.start.second = stod(line.substr(33, 10));
                        }
                        else if (s1 == "TIME OF LAST OBS    ") {
                            gmohdr.end.year = stoi(line.substr(2, 4));
                            gmohdr.end.month = stoi(line.substr(10, 2));
                            gmohdr.end.day = stoi(line.substr(16, 2));
                            gmohdr.end.hour = stoi(line.substr(22, 2));
                            gmohdr.end.minute = stoi(line.substr(28, 2));
                            gmohdr.end.second = stod(line.substr(33, 10));
                        }
                    }
                    if (s3 == "END OF HEADER") {
                        hdr_flag = 0;
                        s3.clear();
                        continue;
                    }
                    if (hdr_flag == 0) {
                        //信息记录//cot++;

                        if (line[0] == '>') {
                            cot++;
                            cot_obs = 0;
                            record[cot].gmorechdr.epoch.year = stoi(line.substr(2, 4));
                            record[cot].gmorechdr.epoch.month = stoi(line.substr(7, 2));
                            record[cot].gmorechdr.epoch.day = stoi(line.substr(10, 2));
                            record[cot].gmorechdr.epoch.hour = stoi(line.substr(13, 2));
                            record[cot].gmorechdr.epoch.minute = stoi(line.substr(16, 2));
                            record[cot].gmorechdr.epoch.second = stod(line.substr(19, 10));
                            record[cot].gmorechdr.Epoch_flag = stod(line.substr(31, 1));
                            record[cot].gmorechdr.num_sat = stod(line.substr(33, 2));
                        }
                        if (line[0] == 'C' && isdigit(line[1]) && isdigit(line[2]) && line[3] == ' ') {
                            record[cot].gnssobs.prn[cot_obs] = line.substr(0, 3);
                            record[cot].gnssobs.value[cot_obs] = line.substr(5);
                            cot_obs ++;
                        }
                    }


                }
        }
        }
    }
     else {
         cout << "无法打开文件!" << endl;
     }
    file.close();
}
