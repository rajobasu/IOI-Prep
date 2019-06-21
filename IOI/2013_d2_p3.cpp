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
#include <random>
#include <stack>
#include <chrono>
#include <set>

#include "game.h"

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

mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
uniform_int_distribution<int> uid(1,1<<29);
int RAND(){
	return uid(rng);
}


ll gcd2(ll X, ll Y) {
    ll tmp;
    while (X != Y && Y != 0) {
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
    return X;
}
int ctr = 0;
struct Treap{
	struct Node{
		Node* left,*right;
		int prior;
		int value;
		ll gcdval;
		ll gcdele;
		Node(int p,int v,ll g,Node* lft = NULL,Node* rght = NULL){
			ctr++;
			// check if too many nodes are getting created.
			/*
			int x = 3;
			if(ctr >= 400)while(1){
				x = x*x;
				if(x == 0){
					

					break;
				}
			}
			*/
			prior = p;
			value = v;
			gcdele = g;
			left = lft;
			right = rght;
			gcdval = g;
		}
	};

	Node* head;
	Treap(){
		head = NULL;
	}
	void traverse(Node* node){
		if(node == NULL)return;
		traverse(node->left);
		cout << node->value << " ";
		traverse(node->right);
	}

	inline void updateNode(Node*& node){
		//return;
		if(node == NULL)return;
		node->gcdval = node->gcdele;
		
		if(node->left == NULL and node->right == NULL)return;
		if(node->right != NULL)node->gcdval = gcd2(node->gcdval,node->right->gcdval);
		if(node->left != NULL)node->gcdval = gcd2(node->gcdval,node->left->gcdval);
		
	}

	void split(Node* head,Node*& leftHalf,Node*& rightHalf,int key){
		if(head == NULL){
			leftHalf = NULL;
			rightHalf = NULL;
			return;
		}
		if(key < head->value){
			rightHalf = head;
			split(head->left,leftHalf,rightHalf->left,key);
		}else{
			leftHalf = head;
			split(head->right,leftHalf->right,rightHalf,key);
		}
		updateNode(head);
		//updateNode(leftHalf);
		//updateNode(rightHalf);
	}

	void merge(Node*& node,Node* leftHalf,Node* rightHalf){
		//cout << "nufdf" << endl;
		if(leftHalf == NULL)node = rightHalf;
		else if(rightHalf == NULL)node = leftHalf;
		else if(leftHalf == NULL and rightHalf == NULL)node = NULL;
		else{
		
			if(leftHalf->prior > rightHalf->prior){
				node = leftHalf;
				merge(node->right,leftHalf->right,rightHalf);
			}else{
				node = rightHalf;
				merge(node->left,leftHalf,rightHalf->left);
			}
		}
		
		updateNode(node);
		
	}
	inline ll search(int l,int r){
		if(head == NULL)return 0;
		Node* lft = NULL;
		Node* mid = NULL;
		Node* rgt = NULL;

		//traverse(head);
		//cout << "STEP1" << endl;
		//cout << head << endl;
		//traverse(head);cout << endl;
		split(head,mid,rgt,r);
		//cout << "STEP2" << endl;
		split(mid,lft,mid,l-1);

		ll ans = 0;
		if(mid != NULL)ans = mid->gcdval;
		Node* xx = NULL;
		merge(head,mid,rgt);
		merge(xx,lft,head);
		//cout << "STEP3" << endl;
		head = xx;
		return ans;
	}

	inline void insert(int pos,ll val){
		if(head == NULL){
			head = new Node(RAND(),pos,val);
		}else{
			Node* lft = NULL;
			Node* mid = NULL;
			Node* rgt = NULL;
			split(head,mid,rgt,pos);
			split(mid,lft,mid,pos-1);
			if(mid == NULL){
				if(val > 0)mid = new Node(RAND(),pos,val);
			}else{
				mid->gcdval = mid->gcdele = val;
			}
			if(val > 0){
				merge(head,mid,rgt);
				merge(head,lft,head);
			}else{
				merge(head,lft,rgt);
			}
		}
	}
};


struct SegTree{
	int ptr = 0;
	struct Node{
		int left,right;
		Treap t;
		Node(){
			left = -1;
			right = -1;
			//t = NULL;
		}
	};
	Node B[1000000];
	inline int get(){
		return ptr++;
	}
	
	int head;
	SegTree(){
		head = -1;
	}
	void update(int& node,int ss,int se,int p,int q,ll k){
		if(node == -1)node = get();
		if(ss > p or p > se)return;
		if(ss==se){
			B[node].t.insert(q,k);
			return;
		}
		int mid = (ss+se)/2;
		update(B[node].left,ss,mid,p,q,k);
		update(B[node].right,mid+1,se,p,q,k);
		//return;
		ll a1 = (B[node].left == NULL)?0:B[B[node].left].t.search(q,q);
		ll a2 = (B[node].right == NULL)?0:B[B[node].right].t.search(q,q);
		B[node].t.insert(q,gcd2(a1,a2));
	}
	ll search(int node,int ss,int se,int a,int b,int c,int d){
		if(node == -1)return 0;
		if(a > se or b < ss)return 0;
		if(a <= ss and se <= b)return B[node].t.search(c,d);
		int mid = (ss+se)/2;
		return gcd2(search(B[node].left,ss,mid,a,b,c,d),search(B[node].right,mid+1,se,a,b,c,d));
	}	
};

const int MAX_ = 1e9+1;
//Treap rows[2001];
SegTree st;
int r,c;

void init(int R, int C) {
    r = R;
    c = C;
}

void update(int P, int Q, ll K) {
	//cout << "update started" << endl;
//	cout << P << " " << Q << " " << K << endl;
	//if(ctr > 400)while(1);
	st.update(st.head,0,MAX_,P,Q,K);
    //rows[P].insert(Q,K);
   // cout << "update done" << endl;
    //rows[0].traverse(rows[0].head);cout << endl;
    //rows[1].traverse(rows[1].head);cout << endl;
	//cout << "UPDATED" << endl;
}

ll calculate(int P, int Q, int U, int V) {
    ll ans = st.search(st.head,0,MAX_,P,U,Q,V);
    //FORE(i,P,U){
    	//rows[i].traverse(rows[i].head);
    	//cout << endl;
    //	ans = gcd2(ans,rows[i].search(Q,V));
    //}
    return ans;
}

int mai1n(){
	int r,c,n;
	cin >> r >> c >> n;
	init(r,c);
	FOR(i,n){
		int id;
		cin >> id;
		if(id == 1){
			int a,b;ll c;
			cin >> a>> b >> c;
			update(a,b,c);
		}else{
			int a,b,c,d;
			cin >> a >> b >> c >> d;
			cout << calculate(a,b,c,d) << endl;
		}
	}
	return 0;
}


int main1(){
	init(2,3);
	update(0,0,20);
	update(0,2,15);
	update(1,1,12);
	cout << " -------------- " << calculate(0,0,0,2) << endl;
	cout << " -------------- " << calculate(0,0,1,1) << endl;
	update(0,1,6);
	update(1,1,14);
	cout << " -------------- " << calculate(0,0,0,2) << endl;
	cout << " -------------- " << calculate(0,0,1,1) << endl;
	
	return 0;
}
