/*
SOLUTION: standard DSU + s2l for list of vertices maintainance.
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
#define lii pair<ll,pair<int,int> > 
#define piil pair<int ,pair<int,int> > 
#define iii pair<pair<int,int>,int> 
#define vi vector<int>
#define pb push_back
#define mp make_pair
using namespace std;

const int MOD = 1000000009;
const int INF = 1e9;
const int MAXN = 500*500+1;

/*
*/
#define cin fin
#define cout fout
/*
*/

struct DSU{
	int parent[MAXN];
	int sz[MAXN];
	vi* vertexList[MAXN];
	DSU(){
		FOR(i,MAXN){
			parent[i] = i;
			sz[i] = 1;
			vertexList[i] = new vi();
			vertexList[i]->pb(i);
		}
	}
	int find(int n){
		if(n != parent[n])parent[n] = find(parent[n]);
		return parent[n];
	}
	int onmerge(int a,int b){
		int pa = find(a);
		int pb = find(b);
		return sz[pa] + sz[pb];
	}
	int merge(int a,int b){
		int pa = find(a);
		int pb = find(b);
		parent[pa] = pb;
		sz[pb] += sz[pa];
		if(vertexList[pa]->size() < vertexList[pb]->size()){
			for(auto& a:*vertexList[pa])vertexList[pb]->pb(a);

		}else{
			for(auto& a:*vertexList[pb])vertexList[pa]->pb(a);
			vertexList[pb] = vertexList[pa];
		}

		return sz[pb];
	}
};

int main(){
	ifstream fin;
	ofstream fout;
	/*
	*/
	fin.open("skilevel.in");
	fout.open("skilevel.out");
	/*
	*/
	int n,m,t;
	cin >> n >> m >> t;
	int mat1[n][m];
	vector<lii> edges;
	FOR(i,n)FOR(j,m)cin >> mat1[i][j];
	int mat2[n][m];FOR(i,n)FOR(j,m)cin >> mat2[i][j];

	FOR(i,n){
		FOR(j,m){
			if(i > 0){
				edges.pb({abs(mat1[i][j] - mat1[i-1][j]),{i*m + j,(i-1)*m+j}});
			}
			/*if(i < n-1){
				edges.pb({abs(mat1[i][j] - mat1[i+1][j]),{i*m + j,(i+1)*m+j}});
			}
			if(j > 0){
				edges.pb({abs(mat1[i][j] - mat1[i][j-1]),{i*m + j,(i)*m+j-1}});
			}*/
			if(j < m-1){
				edges.pb({abs(mat1[i][j] - mat1[i][j+1]),{i*m + j,(i)*m+j+1}});
			}
		}
	}
	sort(edges.begin(), edges.end());
	DSU dsu;
	ll ans[MAXN];
	FOR(i,edges.size()){
		int d = edges[i].ff;
		int j = i+1;
		while(j < edges.size()-1 and edges[j].ff == d)j++;j--;
		FORE(k,i,j){
			if(dsu.find(edges[k].ss.ff) == dsu.find(edges[k].ss.ss))continue;
			int x = dsu.onmerge(edges[k].ss.ff,edges[k].ss.ss);
			//cout << k << " " << x << endl;
			if(x >= t){
				//cout << "alot" << endl;
				if(dsu.sz[dsu.find(edges[k].ss.ff)] < t){
				//	cout << "atleast here ---------------" << endl;
					for(auto nd :*dsu.vertexList[dsu.find(edges[k].ss.ff)]){
						//cout << "hi" << endl;
						//cout << nd << " - > " << d << endl;
						ans[nd] = d;
					}
				}
				if(dsu.sz[dsu.find(edges[k].ss.ss)] < t){
					for(auto nd :*dsu.vertexList[dsu.find(edges[k].ss.ss)]){
						//cout << nd << " - > " << d << endl;
						ans[nd] = d;
					}
				}
			}
			dsu.merge(edges[k].ss.ff,edges[k].ss.ss);
		}
		i = j;
		//cout << "xx : " << d << endl;
	}
	ll sum = 0;
	FOR(i,n){
		FOR(j,m){
			//cout << ans[i*m+j] << " ";
			if(mat2[i][j])sum += ans[i*m + j];
		}
		//cout << endl;
	}
	cout << sum << endl;
	return 0;
}
