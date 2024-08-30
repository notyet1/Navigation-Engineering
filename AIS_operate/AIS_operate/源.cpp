#include <fstream>
#include <iostream>
#include <cstring>
#include<sstream>
#include<vector>
#define n 999999
using namespace std;
string Maxl(const vector<string>& data) {
    int i, j; int max=0 ;
    for (i = 0; i < data.size(); i++) {
        int time = (data[i][9] - '0') * 600 + (data[i][10] - '0') * 60 + (data[i][12] - '0') * 10 + (data[i][13] - '0');
        if (data[i][11] == ':' && max <= time) {
            max = time;
            j = i;
            }  
}
    return data[j];
}
string Minl(const vector<string>& data) {
    {
        int i, j; int min = (data[0][8] - '0') * 600 + (data[0][9] - '0') * 60 + (data[0][11] - '0') * 10 + (data[0][12] - '0');
        for (i = 0; i < data.size(); i++) {
            int time = (data[i][8] - '0') * 600 + (data[i][9] - '0') * 60 + (data[i][11] - '0') * 10 + (data[i][12] - '0');
            if (data[i][10] == ':' && min>= time) {
                min = time;
                j = i;
            }
        }
        return data[j];
    }
}

double Maxl(const vector<double>& data) {
    double max = data[0];
    if (data.empty())return 0;
    for (int i = 1; i < data.size(); i++) {
        if (data[i] > max) {
            max = data[i];
        }
    }
    return max;
}
int Maxl(const vector<int>& data) {
    int max = data[0];
    if (data.empty())return 0;
    for (int i = 1; i < data.size(); i++) {
        if (data[i] > max) {
            max = data[i];
        }
    }
    return max;
}
double Minl(const vector<double>& data) {
    double min = data[0];
    if (data.empty())return 0;
    for (int i = 1; i < data.size(); i++) {
        if (data[i] < min) {
            min = data[i];
        }
    }
    return min;
}
int Minl(const vector<int>& data) {
    int min = data[0];
    if (data.empty())return 0;
    for (int i = 1; i < data.size(); i++) {
        if (data[i] < min) {
            min = data[i];
        }
    }
    return min;
}
int main() {
    char s1[n];
    vector<string>_time;
    vector<int> MMSI;
    vector<double> longitude;
    vector<double> latitude;
    string token;
    ifstream data("AIS数据20180101（局部水域）.txt");
    if (!data.fail()) {
        int i = 0;
        while ( i<n&&data.getline(s1, sizeof(s1) - 1)) {
          
                int count = 0;
                stringstream ss(s1);
                while (getline(ss, token, ',')) {
                    switch (count) {
                    case 0:
                        _time.push_back(token); break;
                    case 1:
                        MMSI.push_back(stoi(token)); break;
                    case 2:
                        longitude.push_back(stod(token)); break;
                    case 3:
                        latitude.push_back(stod(token)); break;
                    }
                    count++;
            }
            i++;
        }
        data.close();
    }
    else {
        exit(1);
    }

    cout << "最大时间：" << Maxl(_time) << " 最小时间：" << Minl(_time) << "\n" << "最大MMSI：" << Maxl(MMSI) << " 最小MMSI：" << Minl(MMSI) << "\n" <<"最大纬度：" << Maxl(longitude) << " 最小纬度：" << Minl(longitude) << "\n" <<"最大经度：" << Maxl(latitude) << " 最小经度：" << Minl(latitude) << endl;//arrar_test
    return 0;
}