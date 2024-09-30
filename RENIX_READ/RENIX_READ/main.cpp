//#include"basic.h"
#include"file.h"
using namespace std;
int main() {
	GMN gmn;
	GMO gmo;
	gmn.GetGMN("BRDM00DLR_S_20242470000_01D_MN.rnx");
	gmn.PrintHeader();
	gmn.record[0].PrintGMNREC();
	/*gmo.GetGMO("TWTF00TWN_R_20242460000_01D_30S_MO.rnx");
	gmo.gmohdr.PrintGMOHDR();
	gmo.record[0].gmorechdr.PrintGMORECHDR();*/
	return 0;
}