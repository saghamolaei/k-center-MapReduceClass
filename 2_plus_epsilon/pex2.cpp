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
#define D 50
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
	for(int i = 0; i < 7; i++)
	{
		cout << i << endl;
		cout << argv[i] << endl;
	}
	IND n,m; // # points
	int K;
	double R; // # clusters
	vector< vector<Type> > points; //input points[N][D]
	vector< vector<Type> > xpoints; //input points[N][D]
	stringstream ssin;
	int temp=0;
	d=7;
	ssin.str(argv[1]);
	ssin >> n;
	ssin.clear();
	ssin.str(argv[2]);
	ssin>>K;
	ssin.clear();
	ssin.str(argv[3]);
	ssin >> R;
	ssin.clear();
	ssin.str(argv[4]);
	ssin >> m;
	ssin.clear();
	fstream cfile(argv[5],std::fstream::in);
	fstream xfile(argv[6],std::fstream::in);
	//read input points: all points to the first cluster
	vector<Type> point(d);
	vector<Type> xpoint(d);
	for(IND i = 0; i < n; i++ )
	{
		for(int j = 0; j < d; j++)
		{
			cfile >> point[j];
		}
		points.push_back(point);
	}
	cfile.close();
	for(IND i = 0; i < m; i++ )
	{
		for(int j = 0; j < d; j++)
		{
			xfile >> xpoint[j];
		}
		points.push_back(xpoint);
	}
	xfile.close();
	for(double r = R; r<=4*R; r+=r*eps)
	{
		//greedy
		vector<bool> mark(n,false);
		vector<bool> mark2(m,false);
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
					if( !mark[j] && dist(points[i],points[j]) <= r )
					{
						mark[j]=true;
					}
				}
				for(int j = 0; j < m; j++ )
				{
					if( !mark2[j] && dist(points[i],xpoints[j]) <= r )
					{
						mark2[j]=true;
					}
				}
			}
		}
		for(int i = 0; i < m; i++ )
			if( mark[i] == false )
			{
				mark[i] = true;
				centers[k]=i+n;
				k++;
				for( int j = i+1; j < m; j++ )
				{
					if(!mark2[j] && dist(xpoints[i],xpoints[j]) <= r )
						mark2[j] = true;
				}
			}
		if(k <= K)
		{
			//output the size of the core-set
			cerr << k << "\t" << r << endl;
			//output cluster centers and their counts
			for(int i = 0; i < k; i++ )
			{
				if(centers[i] < n )
				{
				for(int j = 0; j < d; j++)
					cout << points[centers[i]][j] << "\t";
				}
				else
				{
				for(int j = 0; j < d; j++)
					cout << xpoints[centers[i]-n][j] << "\t";
				}
				cout << endl;
			}
			return 0;
		}
	}
	return 0;
}
