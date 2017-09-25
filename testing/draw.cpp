#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "../include/lsystem.cpp"
#define ll long long int

using namespace std;

int main()
{
	/*This file generates test cases for main.cpp , by writing drawing instructions to dInstr.txt*/
	ofstream ofil;
	ofil.open("/home/nitish/Documents/graphics/test/CMeDrawing/testing/dInstr.txt", ios_base::out);
	ifstream ifil;
	ifil.open("/home/nitish/Documents/graphics/test/CMeDrawing/testing/sample.txt");
	int t;
	ifil>>t;
	int n;
	string axiom;
	ifil>>n>>axiom;
	ifil.get();
	map<char,vector<string> > rule;
	int tem = n;
	string ans = "";
	while(tem>0)
	{
		string str;
		getline(ifil,str);
		ans=ans+str+"\n";
		tem--;
	}
	int iter,angle,length,thickness;
	ifil>>iter>>angle>>length>>thickness;
	point<double> sp,lb,ub;
	ifil>>sp.x>>sp.y;
	t=8;
	ifil.close();
	int type=1;
	int i;
	ofil<<t<<"\n";
	for(i=1;i<=t;i++)
	{
		ofil<<n<<" "<<axiom<<"\n";
		int tem = n;
		ofil<<ans;
		ofil<<i<<" "<<angle<<" "<<length<<" "<<thickness<<"\n";
		ofil<<sp.x<<" "<<sp.y<<"\n";
		ofil<<"1 100 100 650 650\n";
	}
	ofil.close();
	return 0;
}