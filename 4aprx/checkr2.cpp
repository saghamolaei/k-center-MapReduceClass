#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <fstream>
using namespace std;

#define N 10000
#define Type float
#define IND int
#define eps 0.01

int d; // # dimensions


//distance function
Type dist(vector<Type> a, vector<Type> b)
{
	Type sum = 0;
	for(int i = 0; i < a.size(); i++)
	{
		sum += (a[i] - b[i])*(a[i] - b[i]);
	}
	return sqrt(sum);
}

int main(int argc, char *argv[])
{
	//cerr<<"0:" << argv[0] << endl;
	//cerr<<"1:" << argv[1] << endl;
	//cerr<<"2:" << argv[2] << endl;
	//cerr<<"3:" << argv[3] << endl;
	//cerr<<"4:" <<argv[4] << endl;
	//cerr<<"5:" <<argv[5] << endl;
	IND n,m; // # points
	vector< vector<Type> > point; //input points[N][D]
	vector< vector<Type> > center; //input points[N][D]
	stringstream ssin;
	d=7;
	ssin.str(argv[1]);
	ssin >> n;
	ssin.clear();
	ssin.str(argv[2]);
	ssin >> m;
	ssin.clear();
	fstream cfile(argv[3],std::fstream::in);
	fstream xfile(argv[4],std::fstream::in);
	//cerr<< n << " " << m << " " << argv[3] << " " << argv[4] << "*" << endl;
	//read input points: all points to the first cluster
	vector<Type> temp(d);
	for(IND i = 0; i < n; i++ )
	{
		for(int j = 0; j < d; j++)
		{
			cfile >> temp[j];
		}
		center.push_back(temp);
	}
	cfile.close();
	for(IND i = 0; i < m; i++ )
	{
		for(int j = 0; j < d; j++)
		{
			xfile >> temp[j];
		}
		point.push_back(temp);
	}
	xfile.close();
	//cerr<< point.size() << " " << n << " " << center.size() << " " << m << endl;
	//greedy
	vector<bool> mark(n,false);
	double R;
	for(int i = 0; i < point.size(); i++ )
	{
		double r=dist(point[i],center[0]);
		for(int j = 0; j < center.size(); j++ )
			if(dist(point[i],center[j]) < r )
			{
				r=dist(point[i],center[j]);
			}
		if( i== 0 || R < r )
			R=r;
	}
	cout << R << endl;
	
	return 0;
}
