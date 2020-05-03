/*
SOlution : Keep a list of places where we need to change. 
Claim : everything will get changed atmost once. 
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
#define vi vector<ll>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define vv vector
#define endl '\n'

using namespace std;

const int MAXN = 1e6 + 5;
const int BLOCK = 300;


ll arr[MAXN];
int assignment[MAXN];
int n;
bool doWeNeedToChange(int i){
	int next = (i+1)%n;
	int prev = (i+n-1)%n;

	bool nextAssigned = 0;
	bool prevAssigned = 0;
	if(assignment[next] == next)nextAssigned = 1;
	if(assignment[prev] == i)prevAssigned = 1;
	if(assignment[i] == i){
		if(!nextAssigned and !prevAssigned and arr[next] > arr[i])return 1;
		else if(!nextAssigned and prevAssigned and arr[next]*2 > arr[i])return 1;
		else if(nextAssigned and !prevAssigned and arr[next]>2*arr[i])return 1;
		else if(prevAssigned and nextAssigned and arr[next] > arr[i])return 1;
	}
	if(assignment[i] == next){
		if(!nextAssigned and !prevAssigned and arr[next] < arr[i])return 1;
		else if(!nextAssigned and prevAssigned and arr[next]*2 < arr[i])return 1;
		else if(nextAssigned and !prevAssigned and arr[next]< 2*arr[i])return 1;
		else if(prevAssigned and nextAssigned and arr[next] < arr[i])return 1;
	}
	return 0;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	FOR(i,n)cin >> arr[i];//FOR(i,n)arr[i];
	queue<int> q;

	FOR(i,n)assignment[i] = i;
	FOR(i,n){
		if(doWeNeedToChange(i))q.push(i);
	}

	while(!q.empty()){
		int item = q.front();q.pop();
		int next = (item+1)%n;
		int prev = (item+n-1)%n;

		if(doWeNeedToChange(item)){
			if(assignment[item] == item){
				assignment[item] = next;
			}else{
				assignment[item] = item;
			}
		}
		if(doWeNeedToChange(prev))q.push(prev);
		if(doWeNeedToChange(next))q.push(next);

	}

	FOR(i,n){
		cout << assignment[i]+1 << " ";
	}
	cout << endl;
	return 0;
}



