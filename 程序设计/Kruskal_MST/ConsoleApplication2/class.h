using namespace std;
struct side//三元组结构
{
	int root,peak;
	double value;
};
class MST			//Kruskal MST
{
private:
	int n,m,*flag;//side,peak number ,and flag array
	struct side *a,*ms;//store side,and tree
public:
	MST(int n,int m);//initialize
	int find(int i);//find root
	void un(int i,int j);//union,,,,,similar to union-find
	void sort();//insert sort
	void mst();//build tree
	void display();//show
};