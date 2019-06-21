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

#include "artclass.h"


using namespace std;

const int INF = 1e9+10;
const int MAXN = 1000*100*10+10;
const int MAXVAL = 1e9+10;

iii rgb[500][500];

inline bool vvdiff(int a,int b,int c,int x,int y,int z){
	return max(abs(a-x),max(abs(b-y),abs(c-z))) > 60;
}

inline bool vvdiff(iii a,iii b){
	return vvdiff(a.ff.ff,a.ff.ss,a.ss,b.ff.ff,b.ff.ss,b.ss);
}


inline bool kindaEqual(int a,int b,int c,int x,int y,int z){
	return max(abs(a-x),max(abs(b-y),abs(c-z))) <= 0;
}

inline bool kindaEqual(iii a,iii b){
	return kindaEqual(a.ff.ff,a.ff.ss,a.ss,b.ff.ff,b.ff.ss,b.ss);
}

inline bool nearlyEqual(int a,int b,int c,int x,int y,int z){
	return max(abs(a-x),max(abs(b-y),abs(c-z))) <= 30;
}

inline bool nearlyEqual(iii a,iii b){
	return nearlyEqual(a.ff.ff,a.ff.ss,a.ss,b.ff.ff,b.ff.ss,b.ss);
}

inline bool isGreen(int a,int b,int c){
	if(b >= 30 and (b - max(a,c)) >= 10 and max(a,c) < 130)return true;
	return false;
}

bool vis[500][500];
pair<ii,int> extend(int h,int w,int row,int col){
	int x = row;
	int y = col;
	if(vis[x][y])return {{x,y},0};
	int i=row,j=col;
	while(j < w-1){
		if(vis[i][j])break;
		vis[i][j] = 1;

		j++;
		if(nearlyEqual(rgb[x][y],rgb[i][j]))continue;
		break;
	}
	while(i < h-1){
		if(vis[i][j])break;
		vis[i][j] = 1;
		i++; 
		if(nearlyEqual(rgb[x][y],rgb[i][y]))continue;
		break;
	}
	int ctr = 0;
	FORE(m,x,i){
		FORE(n,y,j){
			vis[m][n] = 1;
			ctr += nearlyEqual(rgb[m][n],rgb[x][y]);
		}
	}
	int area =(abs(x-i)*abs(y-j)); 
	if(ctr > area)return {{i,j},(abs(x-i)*abs(y-j))};
	return {{x,y},0};
}

bool isStyle1(int h,int w){
	/*int sum = 0;
	FOR(i,h){
		FOR(j,w){
			auto e = extend(h,w,i,j);
			sum += e.ss;
		}
	}
	if(sum >= h*w/10)return 1;
	return 0;*/

	int ctr = 0;
	FOR(i,h){
		int j = 1;
		int frst = 0;
		int curr = 1;
		while(j<w){
			if(kindaEqual(rgb[i][j],rgb[i][frst]) and nearlyEqual(rgb[i][j],{{0,0},0})){
				curr++;
			}else{
				if(curr > w/20){
					ctr += 1;
				}
				curr = 1;
				frst = j;
			}
			j++;
		}
	}
	FOR(i,w){
		int j = 1;
		int frst = 0;
		int curr = 1;
		while(j<h){
			if(kindaEqual(rgb[j][i],rgb[frst][i]) and nearlyEqual(rgb[i][j],{{0,0},0})){
				curr++;
			}else{
				if(curr > h/20){
					ctr += 1;
				}
				curr = 1;
				frst = j;
			}
			j++;
		}
	}


	if(ctr > 10)return 1;
	return 0;
}

double dist(iii a,iii b){
	int x = a.ff.ff-b.ff.ff;
	int y = a.ff.ss-b.ff.ss;
	int z = a.ss-b.ss;

	return sqrt(x*x+y*y+z*z);
}

bool isStyle3(int h,int w){
	int ctr = 0;
	set<iii> st;
	FOR(i,h/1)FOR(j,w/1){
		st.insert(rgb[i][j]);
	}

	FOR(i,h-1){
		FOR(j,w-1){
			ctr += vvdiff(rgb[i][j],rgb[i+1][j+1]);
		}
	}
	return ctr >= h*w*0.03;

	int r,g,b;
	for(auto e : st){
		r += e.ff.ff;
		g += e.ff.ss;
		b += e.ss;
	}
	//return st.size() < h*w/10;
	r /= st.size();
	g /= st.size();
	b /= st.size();
	// r,g,b, are the mean values
	// find some sort of deviation
	double dev = 0;
	for(auto e : st){
		dev += dist(e,{{r,g},b});
	}
	dev /= st.size();
	return dev <= 10;
}

int style(int H, int W, int R[500][500], int G[500][500], int B[500][500]) {
	//return 2;
	FOR(i,H)FOR(j,W)rgb[i][j] = {{R[i][j],G[i][j]},B[i][j]};
	// start checking
	if(isStyle1(H,W))return 1;

	int cg = 0;
	FOR(i,H)FOR(j,W)cg += isGreen(R[i][j],G[i][j],B[i][j]);
	if(cg >= H*W/100)return 2;

	if(isStyle3(H,W))return 3;
	


	
	
	
	return 4;
}