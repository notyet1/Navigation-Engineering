
// MFCApplication2.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MFCApplication2.h"
#include "MainFrm.h"

#include<math.h>
#include <fstream>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <io.h>
#include <string>
#include <cstring>
#include <iomanip>
#include<sstream>
#include<vector>
#define n 999999
#define M_PI 3.14
#define R 6378.137
using namespace std;
#include "MFCApplication2Doc.h"
#include "MFCApplication2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication2App

BEGIN_MESSAGE_MAP(CMFCApplication2App, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMFCApplication2App::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CMFCApplication2App 构造

CMFCApplication2App::CMFCApplication2App() noexcept
{
	m_bHiColorIcons = TRUE;


	m_nAppLook = 0;
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MFCApplication2.AppID.NoVersion"));

	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的 CMFCApplication2App 对象

CMFCApplication2App theApp;


// CMFCApplication2App 初始化

BOOL CMFCApplication2App::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要 AfxInitRichEdit2()
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。  文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMFCApplication2Doc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CMFCApplication2View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。  如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CMFCApplication2App::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CMFCApplication2App 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAboutDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CMFCApplication2App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMFCApplication2App 自定义加载/保存方法

void CMFCApplication2App::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CMFCApplication2App::LoadCustomState()
{
}

void CMFCApplication2App::SaveCustomState()
{
}

// CMFCApplication2App 消息处理程序
class AIS {////////////////////////////////////
	public:
	char s1[n];
	vector<string>_time;
	vector<int>minutes;
	vector<int> MMSI;
	vector<double> longitude;
	vector<double> latitude;
	vector<double> dist;
	vector<double> velocity;
	string token;
string Maxl(const vector<string>& data) {
	int i, j=0; int max = 0;
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
		int i, j=0; int min = (data[0][8] - '0') * 600 + (data[0][9] - '0') * 60 + (data[0][11] - '0') * 10 + (data[0][12] - '0');
		for (i = 0; i < data.size(); i++) {
			int time = (data[i][8] - '0') * 600 + (data[i][9] - '0') * 60 + (data[i][11] - '0') * 10 + (data[i][12] - '0');
			if (data[i][10] == ':' && min >= time) {
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
string finaltime(const string& data, int Minute) {
	int year = 2018, month = 1, day = 1, hour = 0, minute = data.back()-'0', remaining_minute=0;
	int total_minutes = year * 365 * 24 * 60 + 31 * 24 * 60 + 24 * 60 + minute + Minute;
	year = total_minutes / (365 * 24 * 60);
	remaining_minute = total_minutes % (365 * 24 * 60);
	month = remaining_minute / (31 * 24 * 60);
	remaining_minute %= 31 * 24 * 60;
	day = remaining_minute / (24 * 60);
	remaining_minute %= 24 * 60;
	hour = remaining_minute / 60;
	minute = remaining_minute % 60;
	ostringstream formattedTime;
	formattedTime << year << "/" << month << "/" << day << " " << hour << ":" << std::setw(2) << minute;
	return formattedTime.str();
}
};
double degTorad(double deg) {
	return deg * M_PI / 180.0;
}
class PLACE {///////////////////////////////1
	double lng;
	double lat;

public:
	PLACE(double x=0, double y=0) :lng(x), lat(y) {}
	void setlng(double x) { this->lng = x; }
	void setlat(double x) { this->lat = x; }
	double operator- (const PLACE& obj) {
		double LNG = fabs(this->lng - obj.lng);
		double LAT = fabs(this->lat - obj.lat);
		double C = sin(LAT / 2) * sin(LNG / 2) + cos(this->lat) * cos(obj.lat) * sin(LNG / 2) * sin(LNG / 2);
		return fabs(2 * R * asin(C));
	}
};
PLACE HANKO(59.81647, 22.9667); 
PLACE OBJ;
AIS A;
void CAboutDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码//
	CString CsvPathName;
	
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Text Files(*.txt)|*.txt||"), NULL);
	if (dlg.DoModal() == IDOK) {
		CsvPathName = dlg.GetPathName();
	}
	ifstream data(CsvPathName);
	if (!data.fail()) {
		int i = 0;
		while (i < n && data.getline(A.s1, sizeof(A.s1) - 1)) {	//<-------------------------
		
			int count = 0;
			stringstream ss(A.s1);
			while (getline(ss, A.token, ',')) {
				switch (count) {
				case 0:
					A._time.push_back(A.token); break;
				case 1:
					A.MMSI.push_back(stoi(A.token)); break;
				case 2:
					A.longitude.push_back(stod(A.token)); break;
				case 3:
					A.latitude.push_back(stod(A.token)); break;
				case 5:
					A.velocity.push_back(stod(A.token)); break;
				}
				count++;
			}
			i++;
		}
		int length = A.velocity.size();
		for (int i = 0; i < length; i++) {//距离
			OBJ.setlat(degTorad(A.latitude[i]));
			OBJ.setlng(degTorad(A.longitude[i]));
			A.dist.push_back(OBJ - HANKO);
		}
		for (int i = 0; i < length; i++) {//时间
			if (A.velocity[i] == 0) {
				A.minutes.push_back(0);
			}
			else {
				A.minutes.push_back(int(A.dist[i] / (A.velocity[i] * 1.852)));
				A._time[i] = A.finaltime(A._time[i], A.minutes[i]);
			}
		}
		/*CString message1;
		message1.Format(_T("时间：%hs,%hs\nMMSI：%d,%d\n经度：%f,%f\n纬度：%f,%f"),A.Maxl(A._time).c_str(), A.Minl(A._time).c_str(), A.Maxl(A.MMSI), A.Minl(A.MMSI), A.Maxl(A.longitude), A.Minl(A.longitude), A.Maxl(A.latitude), A.Minl(A.latitude));
		MessageBox(message1);*/
		CString message2;
		message2.Format(_T("船舶到港时间:"));
		for (int i = 0; i < A.dist.size(); i++) {

			CStringA utf8Str(A._time[i].c_str());
			CString distStr(utf8Str);
			message2 += distStr;
			if (i < A.dist.size() - 1) {
				message2 += _T(", ");
			}
		}

		MessageBox(message2);
		data.close();
	}
	else {
		AfxMessageBox(_T("无法打开文件"), MB_OK | MB_ICONERROR);
	}
}

