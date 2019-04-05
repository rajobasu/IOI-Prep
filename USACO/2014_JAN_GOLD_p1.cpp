/*
SOLUTION: standard convexhull
*/

#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <stdio.h>
#include <cmath>
#include <queue>
#include <string>
#include <unordered_map>
#include <map>
#include <complex>
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i = 0;i < n; i++)
#define FORE(i,a,b) for(int i = a; i <= b ; i++)
#define ss second
#define ff first
#define ll long long int
#define ii pair<int,int>
#define il pair<int,ll>
#define li pair<ll,int>
#define x ff
#define y ss
#define piil pair<int ,pair<int,int> > 
#define iii pair<pair<int,int>,int> 
#define vi vector<int>
#define pb push_back
#define mp make_pair
using namespace std;

const int MOD = 1000000009;
const int INF = 1e9;
const int MAXN = 50001;

/*
*/
#define cin fin
#define cout fout
/*
*/
ll cross(ii p1,ii p2,ii p3){
	ll x1 = p2.x-p1.x;
	ll y1 = p2.y-p1.y;
	ll x2 = p3.x-p2.x;
	ll y2 = p3.y-p2.y;

	return x1*y2 - x2*y1;
}

vector<ii> convexHull(vector<ii> points){
	int n = points.size();
	FORE(i,1,n-1){
		if(points[i].x < points[0].x){
			swap(points[i],points[0]);
		}else if(points[i].x == points[0].x and points[i].y < points[0].y){
			swap(points[i], points[0]);
		}
	}
	// points[0] contains the leftmost point
	sort(points.begin()+1, points.end(),[&](ii p1,ii p2){
		return cross(points[0], p1, p2) > 0;
	});
	vector<ii> cvxhull;
	cvxhull.pb(points[0]);

	FORE(i,1,n-1){
		while(cvxhull.size() > 1 and cross(cvxhull[cvxhull.size()-2],cvxhull[cvxhull.size()-1],points[i]) < 0)
			cvxhull.pop_back();

		cvxhull.pb(points[i]);
	}
	while(cvxhull.size() > 1 and cross(cvxhull[cvxhull.size()-2],cvxhull[cvxhull.size()-1],cvxhull[0]) < 0)
		cvxhull.pop_back();

	return cvxhull;
}

int leftmost;
int rightmost;

vector<ii> upperHull;
vector<ii> lowerHull;

void processHull(vector<ii>& hull){
	leftmost = 0;
	rightmost = 0;
	lowerHull.clear();
	upperHull.clear();
	FOR(i,hull.size()){
		if(hull[i].x < hull[leftmost].x)leftmost = i;
		if(hull[i].x > hull[rightmost].x)rightmost = i;
	}
	FORE(i,leftmost,rightmost){
		lowerHull.pb(hull[i]);
	}
	FORE(i,rightmost,hull.size()-1){
		upperHull.pb(hull[i]);
	}
	upperHull.pb(hull[leftmost]);
	reverse(upperHull.begin(), upperHull.end());
}

inline long double getLineVal(ii p1,ii p2,int x){
	if(p1.x == p2.x){

	}
	long double y = p1.y + ((p1.y-p2.y)/((long double)(p1.x-p2.x)))*(x-p1.x);
	return y;
}

void print(ii p){
	//cout << "POINT : " << p.x << " " << p.y << endl;
}

bool isIn(vector<ii>& hull,ii point){

	//if(point.x == hull[leftmost].x or point.x == hull[rightmost].x)return true;
	if(point.x >= hull[leftmost].x and point.x <= hull[rightmost].x){
		if(point.x == hull[leftmost].x){
			if(hull[0].x == hull.back().x){
				return hull[0].y <= point.y and point.y <= hull.back().y;
			}else{
				return false;
			}
		}else if(point.x == hull[rightmost].x){
			if(hull[rightmost+1].x == hull[rightmost].x){
				return hull[rightmost].y <= point.y and point.y <= hull[rightmost+1].y;
			}else{
				return false;
			}
		}
		int ind1 = upper_bound(lowerHull.begin(), lowerHull.end(),point) - lowerHull.begin();
		int ind2 = upper_bound(upperHull.begin() , upperHull.end(),point) - upperHull.begin();



		long double low = getLineVal(lowerHull[ind1],lowerHull[ind1-1],point.x);
		long double high = getLineVal(upperHull[ind2],upperHull[ind2-1],point.x);
//		cout << "P :: " << endl;
//		print(lowerHull[ind1]);
//		print(lowerHull[ind1-1]);
//		print(upperHull[ind2]);
//		print(upperHull[ind2-1]);



//		cout << "VALS : " << low << " " << high << " :: " << point.x << " " << point.y << endl;

		if(low <= point.y and point.y <= high){
			return true;
		}else{
			return false;
		}


	}else{
		return false;
	}
}

int main(){
	ifstream fin;
	ofstream fout;
	/*
	*/
	fin.open("curling.in");
	fout.open("curling.out");
	/*
*/
	int n;
	cin >> n;
	vector<ii> set1;
	vector<ii> set2;
	FOR(i,n){
		int a,b;
		cin >> a >> b;
		set1.pb({a,b});
	}
	FOR(i,n){
		int a,b;
		cin >> a >> b;
		set2.pb({a,b});
	}
	//cout << set1.size() << endl;
	auto hull1 = convexHull(set1);
//	cout << endl;

	auto hull2 = convexHull(set2);
	int ctr1 = 0;
	processHull(hull1);
	for(auto pp : set2){
		ctr1 += isIn(hull1,pp);
	}	

	int ctr2 = 0;
	processHull(hull2);
	for(auto pp : set1){
		ctr2 += isIn(hull2,pp);
	}
	cout << ctr1 << " " << ctr2 << endl;
	return 0;
}
