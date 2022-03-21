#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>
using namespace std;

#define N 10000
#define D 50
#define K N
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
	IND n; // # points
	double R; // # clusters
	vector< vector<Type> > points; //input points[N][D]
	stringstream ssin;
	int temp=0;
	d=7;
	ssin.str(argv[1]);
	ssin >> n;
	ssin.clear();
	ssin.str(argv[2]);
	ssin >> R;
	ssin.clear();
	//read input points: all points to the first cluster
	vector<Type> point(d);
	for(IND i = 0; i < n; i++ )
	{
		for(int j = 0; j < d; j++)
		{
			cin >> point[j];
		}
		points.push_back(point);
	}
	for(double r = R; r<=2*R; r+=r*eps)
	{
		//greedy
		vector<bool> mark(n,false);
		vector< IND > centers(K);
		int k = 0;
		for(int i = 0; i < n; i++ )
		{
			if(mark[i]==false)
			{
				mark[i] = true;
				centers[k]=i;
				k++;
				for(int j=i+1; j<n; j++)
				{
					if( dist(points[i],points[j]) <= r )
					{
						mark[j]=true;
					}
				}
			}
		}
		//output the size of the core-set
		cerr << k << "\t" << r << endl;
		//output cluster centers and their counts
		for(int i = 0; i < k; i++ )
		{
			for(int j = 0; j < d; j++)
				cout << points[centers[i]][j] << "\t";
			cout << endl;
		}
	}
	return 0;
}