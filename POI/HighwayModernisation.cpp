/*
SOLUTION : figure out which edge to break. while doing tree travarsal just make it easy to find 
diameter if we break a certain edge. after that its just easy for both cases. (optimistic:join 
at the midpoints of diameter) (pessimistic: join endpoints of diameter.)


*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <deque>
#include <iomanip>
#include <cmath>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long 
//#define int long long
#define ld long double
#define vi vector<int>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define vv vector
#define endl '\n'

using namespace std;

const int MAXN = 5e5 + 5;

vi g[MAXN];
int longestPath[MAXN];
int longestPathEnding[MAXN];
//vi prefixMax[MAXN];
//vi suffixMax[MAXN];
multiset<int,greater<int> > allAns[MAXN];
multiset<int,greater<int> > allBSP[MAXN];

inline int findDiameter(int node){
	if(allAns[node].size() == 1)return *(allAns[node].begin());
	int mx1 = *(allAns[node].begin());
	allAns[node].erase(allAns[node].begin());
	int mx2 = *(allAns[node].begin());
	allAns[node].insert(mx1);
	return mx1 + mx2;
}

void dfs_initialDP(int node,int p = -1){
	//vi results;
	for(auto e : g[node]){
		if(e != p){
			dfs_initialDP(e,node);
			allAns[node].insert(longestPathEnding[e]+1);
			allBSP[node].insert(longestPath[e]);
			longestPath[node] = max(longestPath[node],longestPath[e]);
		}else
			allAns[node].insert(0);
	}
	allBSP[node].insert(0);
	longestPathEnding[node] = *(allAns[node].begin());

	longestPath[node] = max(longestPath[node],findDiameter(node));
}
int bestMax;
ii edge1;

int bestMin;
ii edge2;


void dfs_getAnswers(int node,int p = -1,int longestUpward = 0,int bestFullDiam = 0){
	int sz = g[node].size();
	FOR(i,g[node].size()){
		int e = g[node][i];
		if(e == p)continue;
		
		int diam1 = longestPath[e];
		int diam2 = max(longestUpward,bestFullDiam);
		
		int a = *(allAns[node].begin());
		allAns[node].erase(allAns[node].begin());
		int b = *(allAns[node].begin());
		allAns[node].erase(allAns[node].begin());
		int c = *(allAns[node].begin());

		allAns[node].insert(a);
		allAns[node].insert(b);

		int check = 0;
		if(a == longestPathEnding[e]+1){
			check = b;
		}else check = a;


		if(a == longestPathEnding[e]+1){
			if(longestUpward >= b){
				diam2 = longestUpward + b;
			}else{
				diam2 = b + max(longestUpward,c);
			}
		}else if(b == longestPathEnding[e]+1){
			if(longestUpward >= a){
				diam2 = longestUpward + a;
			}else{
				diam2 = a + max(longestUpward,c);
			}
		}else{
			if(longestUpward >= a){
				diam2 = longestUpward + a;
			}else{
				diam2 = a + max(longestUpward,b);
			}
		}

		int d = *(allBSP[node].begin());
		allBSP[node].erase(allBSP[node].begin());
		int f = *(allBSP[node].begin());
		allBSP[node].insert(d);
		if(d == longestPath[e]){
			diam2 = max(diam2,f);
		}else{
			diam2 = max(diam2,d);
		}
		diam2 = max(diam2,bestFullDiam);
		diam2 = max(diam2,longestUpward);

		dfs_getAnswers(g[node][i],node,max(longestUpward,check) + 1,max(bestFullDiam,diam2));

		//cout << node << " " << e << " " << diam1 << " " << diam2 << " " << bestFullDiam << endl;
		if(diam1 + diam2 > bestMax){
			edge1 = {node,e};
			bestMax = diam1 + diam2;
		}
		int diamnow = max(max(diam1,diam2),1 + (diam1/2 + diam1%2) + (diam2/2 + diam2%2));

		if(diamnow < bestMin){
		//	cout << diam1 << " " << diamnow << endl;
			edge2 = {node,e};
			bestMin = diamnow;
		}
	}
}


int m1 = -1;
int x1;
void dfs_sed(int node, ii forbiddenEdge,int p = -1,int l = 0){
	if(l >= m1){
		m1 = l;x1 = node;
	}
	for(auto e : g[node]){
		if(e == p or (e == forbiddenEdge.ff and node == forbiddenEdge.ss) or (e == forbiddenEdge.ss and node == forbiddenEdge.ff)){
			continue;
		}else{
			dfs_sed(e,forbiddenEdge,node,l+1);
		}
	}
}
int m2 = -1;
int midpoint = -1;
bool findDiamMidpoint(int node,ii forbiddenEdge,int depthWanted,int depthnow,int p = -1){
	//cout << node << " ";
	bool ok = 0;
	for(auto e : g[node]){
		if(e == p or (e == forbiddenEdge.ff and node == forbiddenEdge.ss) or (e == forbiddenEdge.ss and node == forbiddenEdge.ff)){
			continue;
		}else{
			ok |= findDiamMidpoint(e,forbiddenEdge,depthWanted,depthnow+1,node);
		}
	}
	if(depthWanted == depthnow)ok = 1;
	if(ok and depthnow == depthWanted/2){

		midpoint = node;
		return 1;
	}else{
		return ok;
	}
}

ii getFarthestNode(int x,ii edge){
	m1 = -1;
	dfs_sed(x,edge);
	//cout << x << " " << m1 << " " << x1 << endl;
	return {x1,m1};
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n = (1<<18);
	cin >> n;
	if(n == 2){
		cout << "1 1 2 1 2" << endl;
		cout << "1 1 2 1 2" << endl;
		return 0;
	}
	FOR(i,n-1){
		int a,b;
		a = i;
		b = i/2;
		cin >> a >> b;
		a--;b--;
		g[a].pb(b);
		g[b].pb(a);
	}
	FOR(i,n)allAns[i].insert(0),allAns[i].insert(0);
	FOR(i,n)allAns[i].insert(0),allAns[i].insert(0);
	bestMin = n+5;
	dfs_initialDP(0);
	//cout << "WOWOWOW" << endl;
	dfs_getAnswers(0);
	//cout << "WATTAWOW" << endl;

	ii a = getFarthestNode(edge1.ff,edge1);
	int end_max_component1 = a.ff;
	ii b = getFarthestNode(edge1.ss,edge1);
	int end_max_component2 = x1;

	
	ii c = getFarthestNode(edge2.ff,edge2);
	ii d = getFarthestNode(c.ff,edge2);
	//cout << c.ff << endl;
	//cout << d.ss << endl;
	findDiamMidpoint(c.ff,edge2,d.ss,0);
	//cout << endl;
	int mid1 = midpoint;
	ii e = getFarthestNode(edge2.ss,edge2);
	ii f = getFarthestNode(e.ff,edge2);
	findDiamMidpoint(e.ff,edge2,f.ss,0);
	//cout << endl;
	int mid2 = midpoint;

	
	cout << bestMin << " " << edge2.ff+1 << " " << edge2.ss+1 << " " << mid1+1 << " " << mid2+1 << endl;
	cout << bestMax+1 << " " << edge1.ff+1 << " " << edge1.ss+1 << " " << end_max_component1+1 << " " << end_max_component2+1 << endl;



	return 0;
}