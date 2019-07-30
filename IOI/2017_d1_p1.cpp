#include <bits/stdc++.h>
 
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i = a;i<=b;i++)
#define ll long long int
#define pb push_back
#define vi vector<int>
#define ff first
#define ss second
#define vv vector
#define ii pair<int,int>
 
using namespace std;
 
const int MAXN = 1025;
int n,m,k;
 
char inp[MAXN][MAXN];
char tmp[MAXN][MAXN];
int best = -1;
char mat[MAXN][MAXN];
bool vis[MAXN][MAXN];
 
vv<ii> candidates;
int tot = 0;
void dfs1(int i,int j){
	if(i < 0 or j < 0 or i >= n or j >= m)return;
	if(inp[i][j] == '#')return;
	if(vis[i][j])return;
	///tot++;
	vis[i][j] = 1;
	dfs1(i+1,j);
	dfs1(i-1,j);
	dfs1(i,j+1);
	dfs1(i,j-1);
}
 
void blockCell(int a,int b,int c,int d){
	if(a > 0 and a-1 != c and mat[a-1][b] == '.'){
		mat[a-1][b] = 'X';
	}
	if(a+1 < n and a+1 != c and mat[a+1][b] == '.'){
		mat[a+1][b] = 'X';
	}	
	if(b > 0 and b-1 != d and mat[a][b-1] == '.'){
		mat[a][b-1] = 'X';
	}	
	if(b+1 < m and b+1 != d and mat[a][b+1] == '.'){
		mat[a][b+1] = 'X';
	}		
}
 
 
void dfs2(int i,int j,int pi = -1,int pj = -1,int ctr = 0){
	
	if(mat[i][j] != '.')return;
	//cout << i << " " << j << " " << pi << " " << pj << endl;
	//string s;cin >> s;
	//if(vis[i][j])cout << "wHY" << endl;
	
	
	
	if(i+1 < n and pi != i+1){
		if(vis[i+1][j])mat[i][j] = 'X';
	}
	if(i > 0 and pi != i-1){
		if(vis[i-1][j])mat[i][j] = 'X';
	}
	if(j+1 < m and pj != j+1){
		if(vis[i][j+1])mat[i][j] = 'X';
	}
	if(j > 0 and pj != j-1){
		if(vis[i][j-1])mat[i][j] = 'X';
	}
	if(mat[i][j] != '.')return;
	vis[i][j] = 1;
	ctr++;
	int frac = min(60,(int)(1*ctr / tot));
	bool block = (rand()%100) < frac;
	if(block){
		blockCell(i,j,pi,pj);
		return;
	}
	
	if(i+1 < n and pi != i+1){
		dfs2(i+1,j,i,j,1+ctr);
	}
	if(i > 0 and pi != i-1){
		dfs2(i-1,j,i,j,1+ctr);
	}
	if(j+1 < m and pj != j+1){
		dfs2(i,j+1,i,j,1+ctr);
	}
	if(j > 0 and pj != j-1){
		dfs2(i,j-1,i,j,1+ctr);
	}
}
 
void copyinp(){
	FOR(i,n)FOR(j,m)mat[i][j] = inp[i][j];
}
 
void copytmp(){
	FOR(i,n)FOR(j,m)tmp[i][j] = mat[i][j];
}
 
void clearVis(){
	FOR(i,n)FOR(j,m)vis[i][j] = 0;
}
 
void cleanup(){
	FOR(i,n){
		FOR(j,m){
			if(mat[i][j] == '.' and !vis[i][j])mat[i][j] = 'X';
		}
	}
}
 
int evalmat(){
	int sc = 0;
	FOR(i,n){
		FOR(j,m){
			if(mat[i][j] != '.')continue;
			int cnt = 0;
			if(i+1 < n){
				if(mat[i+1][j] == '.')cnt++;
			}
			if(i > 0){
				if(mat[i-1][j] == '.')cnt++;
			}
			if(j+1 < m){
				if(mat[i][j+1] == '.')cnt++;
			}
			if(j > 0){
				if(mat[i][j-1] == '.')cnt++;
			}
			if(cnt == 1)sc++;
		}
	}
	return sc;
}
 
bool validate(){
	bool ok = 1;
	int cnt1 = 0;int cnt2 = 0;
	FOR(i,n){
		FOR(j,m){
			if(tmp[i][j] == '.' and inp[i][j] != '.')ok = 0;
			if(tmp[i][j] == 'X' and inp[i][j] != '.')ok = 0;
			if(inp[i][j] == '#' and tmp[i][j] != '#')ok = 0;
		}
	}
	return ok;
}
 
int main(){
	srand(time(0));
	cin >> n >> m >> k;
	cout << n << m << endl;
	tot = n+m;
	FOR(i,n){
		string s;cin >> s;
		FOR(j,m){
			inp[i][j] = s[j];
		}
	}
	
	//cout << "sdf" << endl;
	FOR(i,n){
		FOR(j,m){
			if(!vis[i][j] and inp[i][j] == '.'){/*cout << "d" << endl*/; dfs1(i,j);candidates.pb({i,j});}
			else if(inp[i][j] == '.'){
				bool take = (rand()%10000) < 1;
				if(take)candidates.pb({i,j});
			}
		}
	}
	
	///cout << "SFds" << endl;
	int iter = 1;
	while(iter--){
		for(auto e : candidates){
			clearVis();
	
			//cout << e.ff << " " << e.ss << endl;
			copyinp(); 
			//cout << "Dd" << endl;
			clearVis();
			
			//ctr = 0;
			//cout << "gff" << endl;
			dfs2(e.ff,e.ss);
			//cout <<"DFdsdf" << endl;
			cleanup();
			int score = evalmat();
			if(score > best){
				best = score;
				copytmp();
			}
			
		}
	}
	FOR(i,n){
		FOR(j,m){
			cout << tmp[i][j];
		}
		cout << endl;	
	}
	cout << 10.0*best/k << endl;
	return 0;
}