#include<iostream>
using namespace std;


//查找数组中从1到n的元素中第k小的元素

int num[100];
int n;               //元素的总数
int k;               //目标元素下标
int Rand_select(int p, int q, int m)        //在p到q的范围内找到第m小的元素下标
{
	//采用快速排序，得到基准点的位置
	int i = p;
	int j = p + 1;
	int key;
	int tmp;
	int ans;              //记录基准点出现的位置
	key = num[p];
	
	while (j <= q)     //j不能越界
	{
		if (num[j] < key)         //找到一个比key小的元素，和i+1的元素交换位置
		{
			tmp = num[j];
			num[j] = num[i + 1];
			num[i + 1] = tmp;
			i += 1;
		}
		j += 1;
	}  
	//最后把i的元素和num[p]交换
	tmp = num[i];
	num[i] = key;
	num[p] = tmp;
	ans = i;

	if (ans == k) return num[ans];
	else if (ans < k) return Rand_select(ans + 1, q, k - ans);
	else if (ans > k) return Rand_select(p, ans - 1, k);
}

int main()
{
	int ans;
	cin >> n >> k;
	for (int i = 1; i <= n; ++i)
		cin >> num[i];
	ans = Rand_select(1, n, k);
	cout << ans;
	return 0;
}