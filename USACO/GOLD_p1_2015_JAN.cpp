/*
SOLUTION: Select all upper and lower boundaries, and do a linear scan for the left and right boundaries.
COMPLEXITY: nlogn + n^3
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
#include <map>
#include <complex>
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>

using namespace std;

const int INF = 1000000000;

#define cin fin
#define cout fout


int main(){
	ifstream fin;
	ofstream fout;
	fin.open("cowrect.in");
	fout.open("cowrect.out");


	int n;
	cin >> n;
	pair<ii,char> points[n];
	FOR(i,n)cin >> points[i].ff.ff >> points[i].ff.ss >> points[i].ss;
	vector<int> distinctY;
	set<int> st;
	FOR(i,n)st.insert(points[i].ff.ss);
	set<int>::iterator it;
	for(it = st.begin();it!=st.end();it++){
		distinctY.pb(*it);
	}
	int num = 1;int best = 0;
	sort(points,points+n,[&](pair<ii,int> a,pair<ii,int> b){
		if(a.ff.ff != b.ff.ff){
			return a.ff.ff < b.ff.ff;
		}else{
			return a.ss < b.ss;
		}
	});
	//sort(distinctY.begin(), distinctY.end());
	FOR(i,distinctY.size()){
		FOR(j,i+1){

			int sz = 0;
			int last = -1;
			int low = distinctY[j];
			int high = distinctY[i];
			int lstOCC = -1;
			FOR(k,n){
				if(points[k].ff.ss > high or points[k].ff.ss < low)continue;
				if(!(points[k].ff.ff > lstOCC))continue;
				if(points[k].ss == 'G'){
					last = -1;
					lstOCC = points[k].ff.ff;
					sz = 0;
				}else{
					if(last == -1){
						last = points[k].ff.ff;
					}
					sz++;
					int area = (high - low)*(points[k].ff.ff - last);
					if(sz > num){
						num = sz;
						best = area;
					}else if(sz == num){
						best = min(best,area);
					}
				}
			}
		}
	}
	cout << num << endl; 
	cout << best << endl;
	return 0;
}