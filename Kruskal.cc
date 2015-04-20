/*	Author: Ankit Sultana
 *	Algo: Kruskal to find MST of given graph using Union Find
 *	Input: |V| and |E| followed by |E| lines containing 
 *					»»	three integers a, b, c denoting bidirectional road between a, b 
 *					»»	with weight = c
 *	Output: Returns weight of MST, also stores all the nodes of MST in vector MST
 * * * * * * * * * * * * * */
#include <iostream>
#include <algorithm>
#include <vector>
#define PB push_back
#define gc getchar_unlocked
#define vi vector<int> 
using namespace std;

typedef vector < vi > Matrix;

void scanint(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

int find_root(int x, vector <int> &P)
{
	if(x != P[x])
		P[x] = find_root(P[x], P);
	return P[x];
}

void Union(int x, int y, vector <int> &Rank, vector <int> &P, bool &is_tree)
{
	int xroot = find_root(x, P); int yroot = find_root(y, P);
	if(xroot == yroot){
		is_tree = false;
		return ;
	}
	if(Rank[xroot] >= Rank[yroot]){
		Rank[xroot] += Rank[yroot];
		P[yroot] = xroot;
	}
	else{
		Rank[yroot] += Rank[xroot];
		P[xroot] = yroot;
	}
}

struct node{
	int u; int v;
	int wt;
};

//custom compare function used to sort vector<node> list
//sorts them in increasing order of weights
struct my_compare{
	bool operator()(
		node left, node right){
			return left.wt < right.wt;
	}	
};

int main()

{
	std::ios_base::sync_with_stdio(false);
	int V, E, a, b, w, result = 0;
	//V is number of vertices, E is number of edges
	cin>>V>>E;
	vector <int> Rank(V + 1, 1);
	//Stores the number of elements Rank[i], in set whose representative is i
	vector <int> P(V + 1, 0);
	//Points for given vertex j, to its set's representative P[j]
	for(int i = 1; i <= V; i++)	
		P[i] = i;
	//parent now points to the vertex themselves
	vector <node> list;
	node dummy;
	for(int i = 0; i < E; i++){
		cin>>a>>b>>w;
		dummy.u = a; dummy.v = b; dummy.wt = w;
		list.PB(dummy);
	}		
	//input done!
	//list created and adj list also created
	vector <node> MST;
	sort(list.begin(), list.end(), my_compare());
	for(int i = 0; i < E; i++){
		bool is_tree = true;
		Union(list[i].u, list[i].v, Rank, P, is_tree);
		if(is_tree){
			result += list[i].wt;
			MST.PB(list[i]);
		}
	}	
	cout<<result<<'\n';
	return 0;
}
