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
#define Type double
#define IND int

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
	double r;
	//IND kk;
  	//read n,d
	stringstream ssin;
	// argv[0] is the file path
	ssin.str(argv[1]);
	ssin >> n;
	ssin.clear();
	//ssin.str(argv[2]);
	//ssin >> d;
	//ssin.clear();
	//ssin.str(argv[3]);
	//ssin >> r; 
	d=7;
	//n=5875;
	//read input points: all points to the first cluster
	vector<Type> point(d);
	vector< vector<Type> > cluster;
	for(IND i = 0; i < n; i++ )
	{
		for(int j = 0; j < d; j++)
		{
			cin >> point[j];
		}
		cluster.push_back(point);
	}
	for(int kk = 1; kk <= 100; kk++)
	{
	vector< vector< vector<Type> > > clusters(K); //clusters[K][N][D]
	
	clusters[0] = cluster;
	
	//run greedy dual clustering [+Richness]
	vector< vector<Type> > centers(K);
	vector< double > radius(K,0);
	vector< IND > farthest(K,0);

	//copy center
	centers[0]=clusters[0][0];
	clusters[0].erase(clusters[0].begin());
	//compute farthest
	for(IND i = 0; i < clusters[0].size(); i++)
	{
		if(dist(centers[0],clusters[0][i])>radius[0])
		{
			farthest[0]=i;
			radius[0]=dist(centers[0],clusters[0][i]);
		}
	}
	// current farthest neighbor
	int k = 1;
	int cur = 0;
	while(k<=kk)
	{
		//add a new cluster
		//assign farthest[cur] as the new cluster's center
		centers[k]=clusters[cur][farthest[cur]];
		clusters[cur].erase(clusters[cur].begin()+farthest[cur]);
		//split the cur cluster (re-cluster)
		vector< vector<Type> > points(clusters[cur]);
		clusters[cur].erase(clusters[cur].begin(),clusters[cur].end());
		radius[cur] = radius[k] = 0;
		for(IND i = 0; i < points.size(); i++ )
		{
			if( dist(centers[k],points[i])>dist(centers[cur],points[i]) )
			{
				// add to cluster cur
				clusters[cur].push_back(points[i]);
				if (radius[cur] < dist(centers[cur], points[i]))
				{
					// update radius of cur
					radius[cur] = dist(centers[cur], points[i]);
					// update farthest
					farthest[cur] = clusters[cur].size() - 1;
				}
			}
			else if (dist(centers[k], points[i])<dist(centers[cur], points[i]))
			{
				// add to cluster num
				clusters[k].push_back(points[i]);
				if (radius[k] < dist(centers[k], points[i]))
				{
					// update radius of num
					radius[k] = dist(centers[k], points[i]);
					// update farthest
					farthest[k] = clusters[k].size() - 1;
				}
			}

		}//end for

		// update cluster count
		k++;

		//find the maximum radius cluster
		cur = 0;
		for (int i = 1; i < k; i++)
		{
			//This also should be random!
			if (radius[i] > radius[cur])
			{
				cur = i;
			}
		}
		points.erase(points.begin(),points.end());
		//cerr << radius[cur] << " " << k << endl;
	}//end while

	//output the size of the core-set
	cerr<< k << " " << radius[cur] << endl;
	//output cluster centers and their counts
	for(int i = 0; i < k; i++ )
	{
		for(int j = 0; j < d; j++)
			cout << centers[i][j] << "\t";
		cout << endl;		
		//cout << clusters[i].size() << endl;
	}
	}
	return 0;
}
