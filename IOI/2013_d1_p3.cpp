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
#include <fstream>
#include <complex>
#include <stack>
#include <set>

#include "wombats.h"

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
#define cd complex<double> 
#define ld long double
#define pld pair<ld,ld>
#define iii pair<ii,int>
#define vv vector

using namespace std;

const int INF = 1e9+10;
const int MAXN = 100*100*10+10;

int sum = 0;
int r;
int c;
int h[100][100];
int v[100][100];
int distMAIN[100][100];
int dist[100][100];
void calcDist(){
	FOR(i,c){
		priority_queue<pair<int,ii>, vector<pair<int,ii> >, greater<pair<int,ii> > > pq;
		//pq.reserve(100*100*10);
		//queue<pair<int,ii> > pq;
		FOR(x,r)FOR(y,c)dist[x][y] = INF;
		pq.push({0,{0,i}});
		while(!pq.empty()){
			auto e  = pq.top();pq.pop();
			if(dist[e.ss.ff][e.ss.ss] <= e.ff)continue;
			dist[e.ss.ff][e.ss.ss] = e.ff;
			if(e.ss.ff == r-1){
				distMAIN[i][e.ss.ss] = e.ff;

			}
			// add the next 3 edges
			if(e.ss.ss > 0 and h[e.ss.ff][e.ss.ss-1]+e.ff < dist[e.ss.ff][e.ss.ss-1])pq.push({h[e.ss.ff][e.ss.ss-1]+e.ff,{e.ss.ff,e.ss.ss-1}});
			if(e.ss.ss < c-1 and h[e.ss.ff][e.ss.ss]+e.ff < dist[e.ss.ff][e.ss.ss+1])pq.push({h[e.ss.ff][e.ss.ss]+e.ff,{e.ss.ff,e.ss.ss+1}});
			if(e.ss.ff < r-1 and v[e.ss.ff][e.ss.ss]+e.ff < dist[e.ss.ff+1][e.ss.ss])pq.push({v[e.ss.ff][e.ss.ss]+e.ff,{e.ss.ff+1,e.ss.ss}});
		}
	}
}

void init(int R, int C, int H[5000][200], int V[5000][200]) {
	r = R;
	c = C;
	FOR(i,R)FOR(j,C)h[i][j] = H[i][j],v[i][j] = V[i][j];
	FOR(i,R)sum += V[i][0];
	calcDist();
}

 void changeH(int P, int Q, int W) {
    h[P][Q] = W;
    //calcDist();
}

 void changeV(int P, int Q, int W) {
    //sum -= v[P][Q];
    //sum += W;
    v[P][Q] = W;
    //calcDist();
}

 int escape(int V1, int V2) {
	calcDist();
    return distMAIN[V1][V2];
}



