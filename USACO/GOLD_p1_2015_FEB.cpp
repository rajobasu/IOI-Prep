/*
SOLUTION: optimize usual DP with a segtree for each color where index is column number. 
COMPLEXITY: nlogn

PS: TRY USING BIT for full points
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

const int MOD = 1000000007;
const int INF = 1000000000;
const int MAXN = 100001;
const int MAXK = 750*750 +1;
const int MAXR = 754;

struct node{
	int left;
	int right;
	ll val;
};
node* BUFFER[30000000];
node* dummy;
int PTR = 0;
inline int get(){
	BUFFER[PTR] = new node();
	BUFFER[PTR]->left = BUFFER[PTR]->right = -1;
	//if(PTR == 50000000-1)while(1);
	return PTR++;
}
inline node* getNode(int n){
	if(dummy == NULL)
	{
		dummy = new node();
		dummy->left = dummy->right = -1;
	}
	if(n == -1)return dummy;
	//if(n >= 20000000 or n < 0)while(true);
	return BUFFER[n];
}
int ctr = 0;
class dynSegtree{
	int head;
	int mxk;

	inline void expand(int* node){
		if(*node == -1)*node = ::get();
		/*
		if(getNode(node)->left == -1)getNode(node)->left = ::get();
		if(getNode(node)->right == -1)getNode(node)->right = ::get();*/
	}
	void upd(int& node,int ss,int se,int i,ll a){
		//cout << "enter " << node << " : : " << i << endl;
		//if(ctr > 10000)while(true);
		if(i < ss or i > se)return;
		expand(&node);
		
		//cout << node << endl;
		if(ss==se){
			getNode(node)->val += a;
			getNode(node)->val %= MOD;
			return;
		}
		int mid = (ss+se)/2;
		upd(getNode(node)->left,ss,mid,i,a);
		upd(getNode(node)->right,mid+1,se,i,a);
		getNode(node)->val = (getNode(getNode(node)->left)->val + getNode(getNode(node)->right)->val)%MOD;
	}
	ll gt(int& node,int ss,int se,int l,int r){
		ctr ++ ;

		//if(ctr > 10000)while(true);
		if(se < l or ss > r)return 0;
		//expand(node);
		
		if(node == -1)return 0;
		if(l <= ss and se <= r)return getNode(node)->val;
		int mid = (ss+se)/2;
		return (gt(getNode(node)->left,ss,mid,l,r) + gt(getNode(node)->right,mid+1,se,l,r))%MOD;
	}

	public:
	dynSegtree(){
		head = ::get();
	}

	void init(int val){
		mxk = val;
	}
	void update(int i,int a){
		ctr = 0;
		upd(head,0,mxk,i,a);
	}
	ll get(int l,int r){
		ctr = 0;
		return gt(head,0,mxk,l,r);
	}
};

/*
class segtree{
	dynSegtree st[MAXK*4];
	public:
	void update(int node,int ss,int se,int i,ll val,int row){
		if(i < ss or i > se)return;
		if(ss == se){
			st[node] += val;
			st[node] %= MOD;
			return;
		}
		int mid = (ss+se)/2;
		update(node*2+1,ss,mid,i,val);
		update(node*2+2,mid+1,se,i,val);
		st[node] = (st[node*2+1] + st[node*2+2])%MOD;
	}
	ll get(int node,int ss,int se,int l,int r,int row){
		if(ss > r or se < l)return 0;
		if(l <= ss and se <= r)return st[node];
		int mid = (ss+se)/2;
		return (get(node*2+1,ss,mid,l,r) + get(node*2+2,mid+1,se,l,r))%MOD;
	}
};
*/

int mat[MAXR][MAXR];
ll dp[MAXR][MAXR];
//#define cin fin
//#define cout fout
vi colors[MAXK];
vi color[MAXK];
int main(){
	ifstream fin;
	ofstream fout;
	fin.open("hopscotch.in");
	fout.open("hopscotch.out");

	int R,C,K;
	cin >> R >> C >> K;
	if(R == C and C == K and K == 4){
		//cout << "5" << endl;
		//return 0;
	}
	FOR(i,R)FOR(j,C)cin >> mat[i][j];
	FOR(i,R)FOR(j,C)dp[i][j] = 0;
	dp[0][0] = 1;
	//segtree s;
	dynSegtree allS[K+2];
	dynSegtree globalS;
	globalS.init(MAXR+4);
	//cout << "INITED" << endl;
	
	FOR(i,R)FOR(j,C)colors[mat[i][j]].pb(j);
	FOR(i,K+2){
		//sort(color[i].begin(), color[i].end());
		sort(colors[i].begin(), colors[i].end());
		for(auto el:colors[i]){
			if(color[i].empty() or el != color[i].back())
			color[i].pb(el);
		}
		//cout <<i << endl;
		allS[i].init(color[i].size()+3);
		//allS[i].init(MAXR+3);
		colors[i].clear();
	}
	//cout << endl;
	//return 0;
	FOR(i,R){
		FOR(j,C){
			if(i == R-1 or j == C-1)continue;
			//cout << "went in" << endl;
			int jj = lower_bound(color[mat[i][j]].begin(), color[mat[i][j]].end(),j) - color[mat[i][j]].begin();

			cout << j << " " << mat[i][j] << " " << color[mat[i][j]].size() << " " << jj << endl;
			allS[mat[i][j]].update(jj,dp[i][j]);
			//cout << "came out" << endl;
			globalS.update(j,dp[i][j]);
			if(j == 0){
			//	cout << "VALUE UPDATED : " << dp[i][j] << endl;
			}
			//s.update(0,0,MAXK,mat[i][j],dp[i][j]);
			ll a = globalS.get(0,j);
			ll b = allS[mat[i+1][j+1]].get(0,jj);
			//cout << i+1 <<":" << j+1 << " == " << a << " : " << b << endl;
			dp[i+1][j+1] = (a - b + MOD)%MOD;
		}
		//cout << endl;
	}
	//cout << endl;
	FOR(i,R){
		//FOR(j,C)cout << dp[i][j] << " ";
		//cout << endl;
	}
	cout << dp[R-1][C-1] << endl;// << " " << PTR <<endl;
	return 0;
}

