/*
SOLUTION : use segment tree merge method instead of s2l
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

#define FOR(i,n) for(int i = 0;i < n; i++)
#define FORE(i,a,b) for(int i = a; i <= b ; i++)
#define ss second
#define ff first
#define ii pair<int,int>
#define ll long long int
#define piil pair<pair<int,int>,ll> 
#define iii pair<pair<int,int>,int> 
#define vi vector<int>
#define pb push_back
#define mp make_pair

using namespace std;

const int MAXN = 1000005;


struct SegmentTree{
    struct Node{
        Node* left;
        Node* right;
        ll sz;
        
        Node():left(NULL), right(NULL),sz(0) {}
    };
    Node* head;
    inline void expand(Node*& node){
        if(node == NULL)node = new Node();
    }
    void update(Node*& node,int ss,int se,int i){
        if(i < ss or i > se){
            return;
        }
        expand(node);
        if(ss == se){
         //   cout << ss << "  " << se << endl;
            node->sz = 1;
            return;
        }
        int mid = (ss+se)/2;
        update(node->left,ss,mid,i);update(node->right,mid+1,se,i);
        node->sz = 0;
        if(node->left != NULL){node->sz += node->left->sz;}
        if(node->right != NULL){node->sz += node->right->sz;}
       // cout << node->sz << endl;
    }
    Node* merge(Node* node1,Node* node2,ll& cnt){// we maintain that node1 is the smaller segtree

        if(node1 == NULL and node2 == NULL)return NULL;
        if(node1 == NULL)return node2;
        if(node2 == NULL)return node1;

        //Node* nd = new Node();

        if(node1->right != NULL and node2->left != NULL){
      //      cout << node1->right->sz << " " << node2->left->sz << endl; 
            cnt += node1->right->sz * node2->left->sz;

        }

        int vals = 0;
        Node* pt1,*pt2;
        vals = node1->sz + node2->sz;
        pt1 = merge(node1->left,node2->left,cnt);
        pt2 = merge(node1->right, node2->right,cnt);
        node1->sz = vals;
        node1->left = pt1;
        node1->right = pt2;
        return node1;
    }

    
    SegmentTree(Node* node) : head(node){
    }

    SegmentTree(): SegmentTree(new Node()){
        
    }
    
    inline void insert(int i){
        update(head,0,MAXN,i);
    }
    inline SegmentTree* merge(SegmentTree* segtree,ll& cnt){
        head = merge(head,segtree->head,cnt);
        return this;
    }

};



int ctr = 0;
struct Node{
    Node* left;
    Node* right;
    int val;
    ll p;

    ll sz;
    SegmentTree* segtree;
    Node(int val0){
        left = right = NULL;
        val = val0;
        //segtree = new SegmentTree();
            
        if(val0 != 0){
            ctr++;
            segtree = new SegmentTree();
            segtree->insert(val0);
          //  cout << "::  " << segtree->head->sz << endl;
        }
    }
};



void dfs(Node* node){
    if(node == NULL)return;
    //cout << node->val << endl;
    dfs(node->left);
    dfs(node->right);
    ll cnt = 0;
   // cout << "Doing calculations for node VAL : " << node->val << endl;
    if(node->val == 0){
        node->segtree = node->left->segtree->merge(node->right->segtree,cnt);
    }
    //if(node->left != NULL)node->segtree = node->left->segtree->merge(node->segtree,cnt);
    //if(node->right !=NULL)node->segtree = node->segtree->merge(node->right->segtree,cnt);
   // cout << "Ending calculations for node VAL : " << node->val << endl;

    ll sz = node->segtree->head->sz;
    node->p = cnt;
    if(node->left != NULL and node->right != NULL){
        node->p = min(cnt,node->left->sz * node->right->sz - cnt);
    }
    node->sz = node->segtree->head->sz;
}
ll dfs2(Node* node){
    if(node == NULL)return 0;
  //  cout << node->p << " " << node->segtree->head->sz << endl;;
    return node->p + dfs2(node->left) + dfs2(node->right);
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    int x;cin >>x;
    if(x != 0){
        cout << 0 << endl;
        return 0;
    }
    Node* head = new Node(0);
    stack<Node*> nodes;
    nodes.push(head);
    
    while(ctr < n){
        int p;
        cin >> p;
        if(p != 0){
            if(nodes.top()->left == NULL){
                nodes.top()->left = new Node(p);
            }else{
                nodes.top()->right = new Node(p);
            }
        }else{
            if(nodes.top()->left == NULL){
                nodes.top()->left = new Node(p);
                nodes.push(nodes.top()->left);
            }else{
                nodes.top()->right = new Node(p);
                nodes.push(nodes.top()->right);
            }
        }

        while(nodes.size()>0 and nodes.top()->right != NULL)nodes.pop();
    }
    //dfs2(head);
    dfs(head);
    cout << dfs2(head) << endl;

    return 0;
}