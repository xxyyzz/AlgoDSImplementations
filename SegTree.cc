/*	Author: Ankit Sultana
 *	Motivation: http://letuskode.blogspot.ch/2013/01/segtrees.html?view=classic
 *	Data Structure: Segment Tree
 *	Functionality: Supports two types of queries:-
 *			1> Set all elements from [u, v] to x for given array
 *			2> Get the sum of all elements from [u, v] for the same
 * * * * * * * * * */
#include <iostream>
#include <algorithm>
#include <vector>
#define PB push_back
#define Rep(i,n)	for(int i = 0; i < n; i++)
#define LIMIT 100000
#define INF 1000000007
using namespace std;

//val is sum of elements of that interval
//down is used for lazy propagation..
//	»» it stores the value all the leaf nodes corresponding to the given node are set to in a range_update operation
//	»» so if down for a node which represents interval [1, 3] is 3.. => all elements from [1, 3] were set to 3
//	»» so if range_update is called on [1, 3] to set their elements to say 1, then as soon as the node [1, 3] is reached
//	»» it will set down = 1 and will return without going down to nodes [1, 1] [1, 2] [2, 2] and [3, 3]
//num_leaves stores size of the interval

struct node{
	int val, down, num_leaves;
	void merge(node &a, node &b)	//merge left_child and right_child
	{
		val = a.val+b.val;
		num_leaves = a.num_leaves+b.num_leaves;
		down = INF;
	}
	void split(node &a, node &b)	//when info needs to propagate downwards 
	{
		if(down != INF){
			a.down = down;	a.val = a.num_leaves*down;
			b.down = down;	b.val = b.num_leaves*down;
			down = INF;
		}
	}

}tree[LIMIT];

int idx = 0;										//used for intitialising leaves
int arr[LIMIT] = {0};						//array taken as input
node identity;									

//simple recursive function to create the tree
void build_tree(int root, int left_lmt, int right_lmt)
{
	if(left_lmt == right_lmt){
		tree[root].val = arr[idx++];
		tree[root].num_leaves = 1;
		return ;
	}
	int mid = ((right_lmt-left_lmt)>>1)+left_lmt;
	tree[root].split(tree[root*2], tree[root*2+1]);
	build_tree(root*2, left_lmt, mid);
	build_tree(root*2+1, mid+1, right_lmt);
	tree[root].merge(tree[root*2], tree[root*2+1]);
}

//return a node x such that x.val is the sum of elements in interval [u, v]	, both inclusive
node query(int root, int left_lmt, int right_lmt, int u, int v)
{
	if(left_lmt > v || right_lmt < u)				//if disjoint
		return identity;
	if(left_lmt >= u && right_lmt <= v){		
		return tree[root];
	}
	int mid = ((right_lmt-left_lmt)>>1)+left_lmt;
	//propagating info downwards before we operate with children nodes
	tree[root].split(tree[root*2], tree[root*2+1]);
	node l, r;
	l = (r = identity);
	//querying on left subtree and right subtree respectively
	l = query(root*2, left_lmt, mid, u, v);
	r = query(root*2+1, mid+1, right_lmt, u, v);
	node x;
	x.merge(l, r);
	return x;
}

void update_single_subtree(node &a, int x)
{
	a.val = a.num_leaves*x;
	a.down = x;
}

//set all elements of arr[] to x in interval [u, v] both inclusive
void range_update(int root, int left_lmt, int right_lmt, int u, int v, int x)
{
	if(left_lmt > v || right_lmt < u)
		return ;
	if(left_lmt >= u && right_lmt <= v){
		return update_single_subtree(tree[root], x);	
	}
	int mid = ((right_lmt-left_lmt)>>1)+left_lmt;
	tree[root].split(tree[root*2], tree[root*2+1]);
	range_update(root*2, left_lmt, mid, u, v, x);
	range_update(root*2+1, mid+1, right_lmt, u, v, x);
	tree[root].merge(tree[root*2], tree[root*2+1]);
}

//just a utility function
void print_tree(int n)
{
	for(int i = 1; i < 2*n; i++){
		cout<<i<<": "<<tree[i].val<<" "<<tree[i].num_leaves<<" "<<tree[i].down<<'\n';
	}
}

int main()

{
	identity.val = (identity.num_leaves = 0);
	identity.down = INF;
	int n, q;
	cin>>n;
	Rep(i,n){
		cin>>arr[i];
	}
	build_tree(1, 1, n);
	//Rest is input dependent
	//Consider a sample input:
	//5
	//1 2 3 4 5
	range_update(1, 1, n, 3, 5, 5);
	print_tree(n);
	node x = query(1, 1, n, 1, 4);
	cout<<x.val<<'\n';
	return 0;
}
