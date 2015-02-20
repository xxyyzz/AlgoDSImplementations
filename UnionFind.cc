/*	Technique: Union Find(Path Compression)
 *	Author:	   Ankit Sultana (bk2dcradle)
 *	Date:	   21 Feb 2015
 * * * * * * * * * * * * * */
#include <iostream>
#define Rep(i,n)	for(int i = 0; i < n; i++)

using namespace std;

class Union_Find
{
	private:
		int N;				//Number of elements
		int *P;				//Stores the parent of the given point/number
		int *Rank;			//Stores the size of the set for representative elements
	public:
		Union_Find(int a)
		{
			N = a;
			P = new int[a];
			Rank = new int[a];
			Rep(i,a)	P[i] = i;
			Rep(i,a)	Rank[i] = 1;
		}
		int find_root(int x);		//finds the root of given element
		void Union(int a,int b);	//Merges based on the size of the individual elem's sets
		//Just here for the sake of testing the implementation
		void print_Rank();			
		void print_P();
};

void Union_Find::print_P()
{
	Rep(i,N)	cout<<P[i]<<" ";
	cout<<'\n';
}

void Union_Find::print_Rank()
{
	Rep(i,N)	cout<<Rank[i]<<" ";
	cout<<'\n';
}

int Union_Find::find_root(int x)
{
	if(x != P[x])
		return find_root(P[x]);
	return x;
}

void Union_Find::Union(int x, int y)
{
	int xroot = find_root(x);	int yroot = find_root(y);
	if(xroot == yroot){
		return ;
	}
	if(Rank[xroot] >= Rank[yroot]){
		P[yroot] = xroot;
		Rank[xroot] += Rank[yroot];
	}
	else{
		P[xroot] = yroot;
		Rank[yroot] += Rank[xroot];
	}
}

int main()

{
	Union_Find A(5);
	int a[] = {0, 1, 2, 3, 4};
	int b[] = {4, 3, 1, 2, 0};
	Rep(i,5){
		A.Union(a[i], b[i]);
	}
	A.print_P();
	A.print_Rank();
	return 0;
}
