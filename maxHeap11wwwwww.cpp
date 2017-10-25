
	for (int i = (size >> 1); i >= 1; --i)
		maintenance(a, i, size);
}
void heapSort(int *a, int size)
{
	build(a, size);
	for (int i = size-1; i >= 1;--i)
	{
		a[i] ^= a[0];
		a[0] ^= a[i];
		a[i] ^= a[0];//交换堆顶和最后一个元素
		--size;
		maintenance(a, 1, size);
	}
}
int main()
{
	uniform_int_distribution<int>u(-100, 100);
	default_random_engine e;
	int a[100] = { 0 };
	for (int i = 0; i < 100; ++i)
		a[i] = u(e);
	int size = sizeof a / sizeof (int);
	heapSort(a, size);
	for (auto &i : a)
		cout << i << " ";
	cout << endl;
	getchar();
	getchar();
	return 0;
}