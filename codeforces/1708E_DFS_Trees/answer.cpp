#include<bits/stdc++.h>
using namespace std;
long long n,m;
struct ed{
	long long u,v,w;
};
vector<vector<long long>>adj;
vector<vector<long long>>lca;
vector<ed>alled;
bool cmp(ed a,ed b){
	if(a.w<b.w)
	{
		return 1;
	}
	return 0;
}
vector<long long>par,sizea,parl,high,allres;

long long root(long long child){
	if(par[child]==child){
		return child;
	}
	par[child]=root(par[child]);
	return par[child];
}

void con(long long wh){
	long long u=alled[wh].u,v=alled[wh].v;
	long long rootu=root(u),rootv=root(v);
	if(rootu==rootv){
		return ;
	}
	if(sizea[rootu]>sizea[rootv]){
		par[rootv]=rootu;
		sizea[rootu]+=sizea[rootv];
	}
	else{
		par[rootu]=rootv;
		sizea[rootv]=sizea[rootu];
	}
	adj[u].push_back(v);
	adj[v].push_back(u);
}

void solve1(long long u=1,long long para=0,long long l=0){
	parl[u]=para;
	high[u]=l;
	for(auto x:adj[u]){
		if(x!=para){
			solve1(x,u,l+1);
		}
	}
}

void solve2(){
	for(int i=0;i<=20;i++){
		for(int j=1;j<=n;j++){
			if(j==1){
				continue;
			}
			if(i==0){
				lca[j].push_back(parl[j]);
				continue;
			}
			if((1<<i)>high[j]){
				continue;
			}
			lca[j].push_back(lca[lca[j][i-1]][i-1]);
		}
	}
}

void query(long long u,long long v)
{
	if(high[u]<high[v]){
		swap(u,v);
	}
	long long fu=u,fv=v;
	long long dis=high[u]-high[v];
	for(int i=0;i<20;i++){
		if(((dis>>i)&1)==1){
			u=lca[u][i];
		}
	}
	if(u==v){
		u=fu;
		dis=high[u]-high[v]-1;
		for(int i=0;i<20;i++){
			if(((dis>>i)&1)==1){
				u=lca[u][i];
			}
		}
		allres[u]++;
		allres[fu]--;
		return ;
	}
	allres[1]++;
	allres[fu]--;
	allres[fv]--;
}

void solve3(long long u=1,long long para=0){
	allres[u]+=allres[para];
	for(auto x:adj[u]){
		if(para==x){
			continue;
		}
		solve3(x,u);
	}
}

int main(){
	cin>>n>>m;
	sizea.resize(n+2,1);
	adj.resize(n+2);
	high.resize(n+2);
	allres.resize(n+2);
	lca.resize(n+2);
	alled.resize(m);
	par.resize(n+2);
	parl.resize(n+2);
	for(int i=1;i<=n;i++){
		par[i]=i;
	}
	for(int i=0;i<m;i++){
		cin>>alled[i].u>>alled[i].v;
		alled[i].w=i+1;
	}
	sort(alled.begin(),alled.end(),cmp);
	for(int i=0;i<m;i++){
		con(i);
	}
	solve1();
	solve2();
	for(int i=0;i<m;i++){
		query(alled[i].u,alled[i].v);
	}
	solve3();
	for(int i=1;i<=n;i++){
		if(allres[i]==0){
			cout<<1;
		}
		else{
			cout<<0;
		}
	}
	cout<<endl;
}
