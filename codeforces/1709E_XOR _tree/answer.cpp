#include<bits/stdc++.h>
using namespace std;
int n;
vector<int>all;
vector<int>allb;
vector<set<int>>allp;
vector<vector<int>>adj;
int result=0;

void solvea(int u,int par){
	if(u==0){
		allb[u]=all[u];		
	}
	else{
		allb[u]=all[u]^allb[par];
	}
	for(auto x:adj[u])
	{
		if(x!=par){
			solvea(x,u);
		}
	}
}

void solve(int u,int par){
	bool f=0;
	allp[u].insert(allb[u]);
	for(auto x:adj[u]){
		if(x==par){
			continue;
		}
		solve(x,u);
		if(allp[u].size()<allp[x].size()){
			allp[u].swap(allp[x]);
		}
		for(auto y:allp[x]){
			if(allp[u].count(y^all[u])!=0){
				f=1;
			}
		}
		for(auto y:allp[x]){
			allp[u].insert(y);
		}
	}
	if(f){
		result++;
		allp[u].clear();
	}
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	cin>>n;
	all.resize(n+1);
	allb.resize(n+1);
	allp.resize(n+1);
	adj.resize(n+1);
	for(int i=0;i<n;i++){
		cin>>all[i];
	}
	for(int i=0;i<n-1;i++){
		int u,v;
		cin>>u>>v;
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	solvea(0,-1);
	solve(0,-1);
	cout<<result<<endl;
}
