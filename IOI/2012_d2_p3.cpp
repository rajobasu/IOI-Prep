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




using namespace std;

const int INF = 1e7+10;
const int MAXN = 100*100*10+10;



struct Segtree1{
	int st[4*MAXN];
	int lz[4*MAXN];
	inline void push(int node,int ss,int se){
		if(lz[node]){
			st[node] = 0;
			if(ss!=se){
				lz[node*2+1] = lz[node*2+2] = 1;
			}
			lz[node] = 0;
		}
	}
	void build(int node,int ss,int se){
		st[node] = se-ss+1;
		int mid = (ss+se)/2;
		if(ss==se)return;
		build(node*2+1,ss,mid);
		build(node*2+2,mid+1,se);
	}
	void update(int node,int ss,int se,int l,int r){
		push(node,ss,se);
		if(r < ss or l > se)return;
		if(l <= ss and se <= r){
			lz[node] = 1;
			push(node,ss,se);
			return;
		}
		int mid = (ss+se)/2;
		update(node*2+1,ss,mid,l,r);
		update(node*2+2,mid+1,se,l,r);
		st[node] = st[node*2+1] + st[node*2+2];
	}
	int get(int node,int ss,int se,int val){
		push(node,ss,se);
		if(st[node] < val)return MAXN;
		if(ss == se)return ss;
		int mid = (ss+se)/2;
		push(node*2+1,ss,se);
		push(node*2+2,ss,se);
		if(st[node*2+1] >= val)return get(node*2+1,ss,mid,val);
		else return get(node*2+2,mid+1,se,val - st[node*2+1]);

	}
};	

struct PersSegTreeMin{
	struct Node{
		Node* left,*right;
		int val;
		Node(Node* a,Node* b,int c){
			left = a;
			right = b;
			val = c;
		}
	};
	vector<Node*> heads;
	inline void expand(Node* node){
		//cout << "fg " << node << endl;
		if(node->left == NULL)node->left = new Node(NULL,NULL,INF);
		//cout << "mehh" << endl;
		if(node->right == NULL)node->right = new Node(NULL,NULL,INF);
	}
	PersSegTreeMin(){
		heads.pb(new Node(NULL,NULL,INF));
		//cout << heads[0] << endl;
	}
	Node* updat_e(Node* node,int ss,int se,int i,int val){
		//cout <<"d" << endl; 
		//cout << node << endl;
		expand(node);
		//cout << "d" << endl;
		if(i > se or i < ss)return node;
		if(ss == se){
			return new Node(NULL,NULL,min(node->val,val));
		}
		int mid = (ss+se)/2;
		auto l = updat_e(node->left,ss,mid,i,val);
		auto r = updat_e(node->right,mid+1,se,i,val);
		return new Node(l,r,min(l->val,r->val));
	}
	int get(Node* node,int ss,int se,int l,int r){
		//cout << "ds" << endl;
		if(l > se or r < ss)return INF;
		if(node == NULL)return INF;
		if(l <= ss and se <= r)return node->val;
		int mid = (ss+se)/2;
		return min(get(node->left,ss,mid,l,r),get(node->right,mid+1,se,l,r));
	}

	void update(int lft,int rgt,int tm){
		//cout << "hi" << endl;
		//cout << heads[0] << endl;
		//cout << heads.size() << " " << lft << endl;
		//cout << lft << " " << rgt << " " << tm << endl;
		while(1){
			//cout << "dd" << endl;
			int x = heads.size();
			//cout << "duh" << endl;
			if(x >= lft)break;
			Node* s = heads.back();

			//cout << "ok" << endl;
			heads.pb(s);
		}
		//cout << heads[0] << endl;
		if(heads.size() == lft+1){
		//	cout << heads[lft] << endl;
		//	cout << heads[0] << endl;
			Node* e = updat_e(heads[lft],0,MAXN,rgt,tm);
			heads[lft] = e;
		}else{
			heads.pb(updat_e(heads[lft-1],0,MAXN,rgt,tm));
		}
		//cout << "meh" << endl;
	}

	int query(int vers,int lft){
		if(vers < 0)return INF;
		if(vers >= heads.size()){
			return get(heads.back(),0,MAXN,lft,MAXN-3);
		}else{
			return get(heads[vers],0,MAXN,lft,MAXN - 3);
		}
	}
};	

struct PersSegTreeSum{
	struct Node{
		Node* left,*right;
		int val;
		Node(Node* a,Node* b,int c){
			left = a;
			right = b;
			val = c;
		}
	};
	vector<Node*> heads;
	inline void expand(Node* node){
		//cout << "fg " << node << endl;
		if(node->left == NULL)node->left = new Node(NULL,NULL,0);
		//cout << "mehh" << endl;
		if(node->right == NULL)node->right = new Node(NULL,NULL,0);
	}
	PersSegTreeSum(){
		heads.pb(new Node(NULL,NULL,0));
		//cout << heads[0] << endl;
	}
	Node* updat_e(Node* node,int ss,int se,int i,int val){
		//cout <<"d" << endl; 
		//cout << node << endl;
		expand(node);
		//cout << "d" << endl;
		if(i > se or i < ss)return node;
		if(ss == se){
			return new Node(NULL,NULL,node->val+val);
		}
		int mid = (ss+se)/2;
		auto l = updat_e(node->left,ss,mid,i,val);
		auto r = updat_e(node->right,mid+1,se,i,val);
		return new Node(l,r,l->val+r->val);
	}
	int get(Node* node,int ss,int se,int l,int r){
		//cout << "ds" << endl;
		if(l > se or r < ss)return 0;
		if(node == NULL)return 0;
		if(l <= ss and se <= r)return node->val;
		int mid = (ss+se)/2;
		return (get(node->left,ss,mid,l,r)+get(node->right,mid+1,se,l,r));
	}

	void update(int lft,int rgt,int tm){
		//cout << "hi" << endl;
		//cout << heads[0] << endl;
		//cout << heads.size() << " " << lft << endl;
		//cout << lft << " " << rgt << " " << tm << endl;
		while(1){
			//cout << "dd" << endl;
			int x = heads.size();
			//cout << "duh" << endl;
			if(x >= lft)break;
			Node* s = heads.back();

			//cout << "ok" << endl;
			heads.pb(s);
		}
		//cout << heads[0] << endl;
		if(heads.size() == lft+1){
		//	cout << heads[lft] << endl;
		//	cout << heads[0] << endl;
			Node* e = updat_e(heads[lft],0,MAXN,rgt,tm);
			heads[lft] = e;
		}else{
			heads.pb(updat_e(heads[lft-1],0,MAXN,rgt,tm));
		}
		//cout << "meh" << endl;
	}

	int query(int vers,int l,int r){
		if(vers < 0)return INF;
		if(vers >= heads.size()){
			return get(heads.back(),0,MAXN,l,r);
		}else{
			return get(heads[vers],0,MAXN,l,r);
		}
	}
};	





bool elimArray[MAXN];   //means after the ith cell, elimArray[i] had been eliminated.
vector<ii> modifRange;
int prevBest[MAXN];
int nextBest[MAXN];

int GetBestPosition(int n,int c,int r,int* arr,int* ss,int* ee){
	// first modify the range to their actual sizes;
	// this step O(nlogn).
	Segtree1 stree;
	stree.build(0,0,MAXN);
	FOR(i,c){
		int s = ss[i];
		int e = ee[i];
		int move = s;
		int actualS = stree.get(0,0,MAXN,s+1);
		int actualE = stree.get(0,0,MAXN,e+2) - 1;
		
		modifRange.pb({actualS,actualE});
		stree.update(0,0,MAXN,actualS+1,actualE);
		
	}
	// now for each position, find its closest left and right element greater than r;
	// this step is already O(n)
	int bestFound = -1;
	FOR(i,n-1){
		prevBest[i] = bestFound;
		if(arr[i] > r)bestFound = i;
	}
	prevBest[n-1] = bestFound;
	bestFound = n;
	for(int i = n-2;i >= 0;i-- ){
		nextBest[i+1] = bestFound;
		if(arr[i] > r)bestFound = i;
	}
	nextBest[0] = bestFound;
	
	/*
	FOR(i,n-1)cout << arr[i] << " ";cout << endl;
	for(auto e: modifRange){
		cout << e.ff << " " << e.ss << endl;
	}
	cout << endl;
	FOR(i,n)cout << prevBest[i] << " ";cout << endl;
	FOR(i,n)cout << nextBest[i] << " ";cout << endl;
	*/
	vector<pair<int,ii> > all;
	int xx = 0;
	vector<ii> a1;
	vector<ii> a2;
	for(auto e : modifRange){
		all.pb({e.ff,{e.ss,xx}});
		a1.pb({xx,e.ff});
		a2.pb({xx++,e.ss});
	}
	sort(all.begin(), all.end());
	sort(a1.begin(), a1.end());
	sort(a2.begin(), a2.end());
	PersSegTreeMin pstm;
	PersSegTreeSum psts1;
	PersSegTreeSum psts2;

	for(auto e : a1){
		psts1.update(e.ff,e.ss,1);
	}
	for(auto e : a2){
		psts2.update(e.ff,e.ss,1);
	}

	for(auto e : all){

		pstm.update(e.ff,e.ss.ff,e.ss.ss);
	}

	int mx = 0;
	int bestp = 0;
	FOR(i,n){
		int hit = 0;

		int lst = pstm.query(prevBest[i],i);
		lst = min(lst,pstm.query(i,nextBest[i]+1));
		int sum = 0;
		if(lst>0){
			int a = psts1.query(lst-1,i+1,MAXN-3);
			int b = psts2.query(lst-1,0,i-1);
			//cout << a << " " << b << endl;
			sum = a+b;
		}
		int hit2 = lst - sum;
		//lst--;
		//cout << i << " " << lst << endl;
		/*
		int xx = -1;
		for(auto e : modifRange){
			//break;
			xx++;
			if(e.ss < i or e.ff > i)continue;
			if(xx == lst){
				break;
			}
			hit++;
		}*/
		//cout << i << " " << hit2 <<  " " << hit << " " << lst << endl;
		if(hit2 > mx){
			mx = hit2;
			bestp = i;
		}
	}
	return bestp;
}

int mai1n(){
	int arr[7] = {1,0,2,4,3,6};
	int s[5] = {1,0,0,0,0};//{4,2,3,2,0};
	int e[5] = {3,1,1,1,1};//{5,3,4,3,2};
	cout << GetBestPosition(5,3,3,arr,s,e) << endl;
	return 0;
}

