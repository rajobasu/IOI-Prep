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

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<ll,ll>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 

const int INF = 1e9;

using namespace std;
const int MAXN = 702;
int n,m;
string grid[MAXN];
int firstDay[MAXN][MAXN];
bool vis[MAXN][MAXN];
inline void cover(int x,int y,int val){
	for(int i = x;i>=0;i--){
		if(grid[i][y] != 'I'){
			firstDay[i][y] = min(firstDay[i][y],val);
		}else break;
	}
	for(int i = x;i<n;i++){
		if(grid[i][y] != 'I'){
			firstDay[i][y] = min(firstDay[i][y],val);
		}else break;
	}
	for(int i = y;i>=0;i--){
		if(grid[x][i] != 'I'){
			firstDay[x][i] = min(firstDay[x][i],val);
		}else break;
	}
	for(int i = y;i<m;i++){
		if(grid[x][i] != 'I'){
			firstDay[x][i] = min(firstDay[x][i],val);
		}else break;
	}
}

int main(){
	cin >> n >> m;
	FOR(i,MAXN)FOR(j,MAXN)firstDay[i][j] = INF;
	FOR(i,n)cin >> grid[i];
	int xv,yv,xs,ys;
	FOR(i,n){
		FOR(j,m){
			if(grid[i][j] == 'V'){
				xv = i;yv = j;
			}
			if(grid[i][j] == 'Y'){
				xs = i;ys = j;
			}
		}
	}

	queue<pair<ii,int> > q;
	q.push({{xv,yv},0});
	while(!q.empty()){
		auto cell = q.front();q.pop();
		if(!(cell.ff.ff >= 0 and cell.ff.ff < n and cell.ff.ss >= 0 and cell.ff.ss < m and grid[cell.ff.ff][cell.ff.ss] != 'I'))continue;
		if(vis[cell.ff.ff][cell.ff.ss])continue;
		vis[cell.ff.ff][cell.ff.ss] = 1;
		
		cover(cell.ff.ff,cell.ff.ss,cell.ss);

		q.push({{cell.ff.ff-1,cell.ff.ss},cell.ss+1});
		q.push({{cell.ff.ff+1,cell.ff.ss},cell.ss+1});
		q.push({{cell.ff.ff,cell.ff.ss-1},cell.ss+1});
		q.push({{cell.ff.ff,cell.ff.ss+1},cell.ss+1});
	}
	FOR(i,n)FOR(j,m)if(firstDay[i][j] == 0)firstDay[i][j] = 1;
	FOR(i,n)FOR(j,m)vis[i][j] = 0;
	q.push({{xs,ys},0});
	while(!q.empty()){
		auto cell = q.front();q.pop();
		if(!(cell.ff.ff >= 0 and cell.ff.ff < n and cell.ff.ss >= 0 and cell.ff.ss < m and grid[cell.ff.ff][cell.ff.ss] != 'I'))continue;
		if(vis[cell.ff.ff][cell.ff.ss])continue;
		if(firstDay[cell.ff.ff][cell.ff.ss] <= cell.ss)continue;
		vis[cell.ff.ff][cell.ff.ss] = 1;
		if(grid[cell.ff.ff][cell.ff.ss] == 'T'){
			cout << "YES" << endl;
			return 0;
		}

		q.push({{cell.ff.ff-1,cell.ff.ss},cell.ss+1});
		q.push({{cell.ff.ff+1,cell.ff.ss},cell.ss+1});
		q.push({{cell.ff.ff,cell.ff.ss-1},cell.ss+1});
		q.push({{cell.ff.ff,cell.ff.ss+1},cell.ss+1});

	}
	cout << "NO" << endl;

    return 0;
}