#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
//题目一：数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例如输入一个长度为
//9的数组{1，2，3，2，2，2，5，4，2}。由于数字2在数组中出现了5次，超过数组长度的一半，因此
//输出2。

//思路一：如果把这个数组排序，那么排序后位于数组中间的数字一定就是那个出现次数超过数组长度
//一半的数字。可以利用快速排序的思想，随机选择一个数字，和数组中间的数比较，然后递归。时间
//复杂度为O(n),但缺点是会改变数组原本的数字顺序。

//思路二：数组中有一个数字出现的次数超过数组长度的一半，也就是说它出现的次数比其它所有数字
//出现次数的和还要多。遍历整个数组，当下一个数字和之前保存的数字相同，次数加1，不同减1。如
//果次数为0，保存下一个数字，并把次数设为1。故要找的数字肯定是最后一次把次数设为1对应的数字
//时间复杂度为O(n)，且不会修改数组中的数字顺序

//1、基于快速排序思想的解法

//生成一个在begin和end之间的随机数
int RandomInRange(int begin,int end)
{}
//交换两个数
void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
//生成一个随机数，利用快速排序思想将比它大的放在右边，比它小的放在左边
int Partition(int data[], int len, int begin, int end)
{
	assert(data);
	if (len <= 0 || begin < 0 || end >= len)
		return -1;

	int index = RandomInRange(begin, end);
	Swap(&data[index], &data[end]);
	int small = begin - 1;
	for (int index = begin; index < end; index++)
	{
		if (data[index] < data[end])
		{
			++small;
			if (small != index)
				Swap(&data[index], &data[small]);
		}
	}
	++small;
	Swap(&data[small], &data[end]);
	return small;
}
//检查最后得到的结果是不是超过数组长度的一半
bool CheckIsLegal(int* num, int len, int result)
{
	int time = 0;//累计得到的结果在数组中出现的次数
	for (int i = 0; i < len; i++)
	{
		if (num[i] == result)
			time++;
	}
	bool isMoreHalf = true;
	if (time * 2 <= len)
	{
		isMoreHalf = false;
	}
	return isMoreHalf;
}
int MoreThanHalfNum(int *num, int len)
{
	assert(num);
	assert(len);

	int middle = len >> 1;
	int begin = 0;
	int end = len - 1;
	int index = Partition(num, len,begin, end);
	while (index != middle)
	{
		if (index > middle)
		{
			end = index - 1;
			//递归找middle
			index = Partition(num, len, begin, end);
		}
		else
		{
			begin = index + 1;
			index = Partition(num, len, begin, end);
		}
	}
	int result = num[middle];
	if (!CheckIsLegal(num, len, result))
	{
		result = 0;
	}
	return result;
}

//2、基于数组特点的解法
int MoreThanHalfNum(int *num, int len)
{
	assert(num);
	assert(len);

	int result = num[0];
	int time = 1;
	for (int i = 1; i < len; i++)
	{
		//time为0，保存下一个值，并把time设为1
		if (time == 0)
		{
			result = num[i];
			time = 1;
		}
		//如果下一个数字和当前保存的数字相等，time+1
		else if (result == num[i])
			time++;
		//不想等，time-1
		else
			time--;
	}
	//判断是否是合法的结果
	if (!CheckIsLegal(num, len, result))
		result = 0;
	return result;
}


//题目二：输入n个整数，找出其中最小的K个数。例如输入4，5，1，6，2，7，3，8这8个数字，则最小
//的4个数字是1，2，3，4

//思路一：将n个整数排序，则前k个数就是最小的k个数。但是这种方法的时间复杂度为O(n*log(n))。
//而且不适合海量数据的处理

//思路二：利用快速排序的思想，使比k个数字大的放到右边，比k个数字小的放到左边。调整之后，位
//于数组中左边的k个数字就是最小的k个数（这k个数不一定是排序的），时间复杂度为O(n)，缺点是
//修改数组中数字顺序

//思路三：利用堆或者红黑树来实现，建立一个有k个元素的大堆，每次取一个数字和大堆的堆顶比较
//如果大于堆顶，读取下一个，如果小于堆顶，删除堆顶元素，将此数插进去，调整大堆。或者利用红
//黑树来实现。STL中的set和multiset都是基于红黑树实现的。时间复杂度为O(n*log(k))。此方法适合
//海量数据的处理。

//1、基于快速排序思想的解法
void GetKNums(int* input, int len, int* output, int k)
{
	assert(input);
	assert(output);
	if (len <= 0 || k > len || k <= 0)
	{
		return;
	}
	int begin = 0;
	int end = len - 1;
	int index = Partition(input, len, begin, end);
	while (index != k - 1)
	{
		if (index > k - 1)
		{
			end = index - 1;
			index = Partition(input, len, begin, end);
		}
		else
		{
			begin = index + 1;
			index = Partition(input, len, begin, end);
		}
	}
	for (int i = 0; i < k; i++)
	{
		output[i] = input[i];
	}
}

#include<vector>
//2、基于堆或者红黑树的解法
typedef multiset<int, greater<int> > intSet;
typedef multiset<int, greater<int> >::iterator setIterator;
void GetKNum(const std::vector<int> &data, intSet& leastNumbers, int k)
{
	leastNumbers.clear();
	if (k < 1 || data.size() < k)
		return;
	vector<int>::const_iterator iter = data.begin();
	for (; iter != data.end(); ++iter)
	{
		if ((leastNumbers.size()) < k)
			leastNumbers.insert(*iter);
		else
		{
			setIterator iterGreatest = leastNumbers.begin();
			if (*iter < *(leastNumbers.begin()))
			{
				leastNumbers.erase(iterGreatest);
				leastNumbers.insert(*iter);
			}
		}
	}
}


//题目三：输入一个整形数组，数组里有正数也有负数。数组中一个或连续的多个整数组成一个子数组
//求所有子数组和的最大值。要求时间复杂度为O(n)。

//思路一：从头到尾依次往后累加，初始化和为0，加了之后更新和。和保存最大值。

//思路二：应用动态规划的思想

int MaxChildArray(int array[], int len)
{
	assert(array);
	if (len <= 0)
		return -1;
	int CurrentSum = 0;
	int sum = 0;
	for (int i = 0; i < len; i++)
	{
		if (CurrentSum <= 0)
			CurrentSum = array[i];
		else
			CurrentSum += array[i];
		//保存当前和的最大值
		if (CurrentSum>sum)
			sum = CurrentSum;
	}
	return sum;
}
int main()
{
	int array[] = { 1, -2, 3, 10, -4, 7, 2, -5 };
	int sum = MaxChildArray(array, 8);
	printf("%d\n", sum);
	return 0;
}


//题目四：输入一个整数n，求从1到n这n个整数的十进制表示中1出现的次数。例如输入12.从1到12这些
//整数中包含1的数字有1,10,11,12。1一共出现了5次。

//思路一：一次判断1-n每个数中1出现的次数，累加起来就是1出现的总次数。时间复杂度为O(n*log(n))
//思路二：计算1在各个位上出现的次数，来计算1出现的总次数。时间复杂度为O(log*n)

//解法1、求每个数中1的个数，通过%10，/10来求解
int NumOf1(unsigned int n)
{
	int num = 0;
	while (n)
	{
		if (n % 10 == 1)
			num++;
		n = n / 10;
	}
	return num;
}
//从1到n累加每个数中1的个数
int NumOf1Between1AndN(unsigned int n)
{
	int numOf1 = 0;//保存1的个数和
	for (unsigned int i =0; i <= n; i++)
	{
		numOf1 += NumOf1(i);
	}
	return numOf1;
}
int main()
{
	int ret = NumOf1Between1AndN(12);
	printf("%d\n", ret);
	return 0;
}
//2、解法二：
int PowerBase10(unsigned int n)
{
	int result = 1;
	for (unsigned int i = 0; i < n; i++)
	{
		result *= 10;
	}
	return result;
}
int NumOf1(const char* str)
{
	if (!str || *str<'0' || *str>'9' || *str == '\0')
		return 0;
	int first = *str - '0';
	unsigned int len = static_cast<unsigned int>(strlen(str));
	if (len == 1 && first == 0)
		return 0;
	if (len == 1 && first > 0)
		return 1;
	//假设str是“21345”
	//numFristDigit是数字10000-19999的第一个位中的数目
	int numFrirstDigit = 0;
	if (first > 1)
		numFrirstDigit = PowerBase10(len - 1);
	else if (first == 1)
		numFrirstDigit = atoi(str + 1) + 1;

	//numOtherDigits是1346-21345除了第一位之外的数位中的数目
	int numOtherDigits = first*(len - 1)*PowerBase10(len - 2);

	//numRecursive是1-1345中的数目
	int numRecursive = NumOf1(str + 1);
	return numFrirstDigit + numOtherDigits + numRecursive;
}
int NumOf1Between1AndN(int n)
{
	if (n <= 0)
		return 0;
	char str[50];
	sprintf(str, "%d", n);
	return NumOf1(str);
}


//题目五：输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中
//最小的一个。例如输入数组{3，32，321}，则打印出这3个数字能排成的最小数字321323.

//思路：我们希望能够找到一种规则，按照这种规则排列出来的数是最小的数。要确定排序的规则，我
 //们就必须知道，对于任意两个正整数a和b，如果确定一个规则，使得按照该问题进行排序能得到最小
 //的数，也就是要比较a和b的值，而这种比较不是普通的数值的大小。
 //对于数字a和b，排列的结果为ab和ba，如果ab小于ba，应该输出ab，即a排在b的前面，也就是a<b。
 //反之，如果ba小于ab，即b排在a前面，也就是b<a。如果ab等于ba，那么a = b。
 //接下里的问题是：给出数字a和b，如果拼接得到ab或者ba，然后比较他们的大小？如果直接用数值
 //进行拼接当然是可以的，但是我们考虑到a和b都是int型的，如果拼接后得到数字超出int型的范围导
 //致结果溢出该怎么办？很自然我们想到可以现将整数都转换成字符串类型，然后在连接。

//每个整数最长有10个整数组成
const int MaxDigits = 10;

//str1和str2分别保存比较的两个字符串，即ab和ba
char* str1 = new char[2 * MaxDigits + 1];
char* str2 = new char[2 * MaxDigits + 1];

int comp(const void* a, const void* b)
{
	//拼接字符串，得到ab
	strcpy(str1, *(const char**)a);
	strcat(str1, *(const char**)b);
	//拼接字符串，得到ba
	strcpy(str2, *(const char**)b);
	strcat(str2, *(const char**)a);
	return strcmp(str1, str2);
}
void GetMinNum(int arr[],int len)
{
	if (arr == NULL || len <= 0)
		return;
	//建立新的字符串数组
	char** strArr = (char**)(new int[len]);
	//每个字符串数组中的元素建立新的字符串，并复制为num中的值。
	for (int i = 0; i < len; i++)
	{
		strArr[i] = new char[MaxDigits + 1];
		sprintf(strArr[i], "%d", arr[i]);//将arr[i]转成十进制表示的字符串
	}
	//qsort:C语言库函数中的排序函数，利用快速排序的思想。
	qsort(arr, len, sizeof(char*), comp);
	//打印排成的最小数字
	for (int i = 0; i < len; i++)
	{
		printf("%s", strArr[i]);
	}
	printf("\n");
	//释放内存
	for (int i = 0; i < len; i++)
	{
		delete[] strArr[i];
	}
	delete[] strArr;
}
int main()
{
	int arr[] = { 3, 32, 321 };
	GetMinNum(arr,3);
	return 0;
}


//题目六：我们把只包含因子2、3和5的数称作丑数(Ugly Number)。求按从小到大的顺序的第1500个丑数
//例如6、8都是丑数，但14不是，因为它包含因子7。习惯上我们把1当作第一个丑数。

//思路一：丑数包含因子2、3、5.即丑数只能被2、3、5整除。如果一个数能被2整除，就让它连续除2；
//如果能被3整除，就让它连续除3；如果能被5整除，就连续除5。如果最后得到的是1，就说明是丑数。

//思路二：丑数应该是另一个丑数乘以2、3或者5的结果（1除外）。因此可以创建一个数组，里面的数
//字是拍好序的丑数，每一个丑数都是前面的丑数乘以2、3或者5得到的。

//1、解法一：
//判断一个数是不是丑数
bool IsUgly(int num)
{
	//能被2、3或者5整除，最后结果是1
	while (num % 2 == 0)
		num /= 2;
	while (num % 3 == 0)
		num /= 3;
	while (num % 5 == 0)
		num /= 5;
	return (num == 1) ? true : false;
}
int GetUgly(int n)
{
	if (n <= 0)
		return 0;
	//UglyNum:要找的第n个丑数
	int UglyNum = 0;
	int index = 0;
	while (index < n)
	{
		++UglyNum;
		//找n个丑数,用index来判断,index记录丑数的个数
		if (IsUgly(UglyNum))
			index++;
	}
	return UglyNum;
}

//2、解法二：空间换时间
//判断三个数的最小值
int MinNum(int num1, int num2, int num3)
{
	int min = (num1 < num2) ? num1 : num2;
	min = (min < num3) ? min : num3;
	return min;
}
int GetUgly(int n)
{
	if (n <= 0)
		return 0;
	//保存要生成的n个丑数
	int *UglyNums = new int[n];
	UglyNums[0] = 1;
	int index = 1;
	//保存每个丑数乘2、3、5的值
	int* multiply2 = UglyNums;
	int* multiply3 = UglyNums;
	int* multiply5 = UglyNums;

	while (index < n)
	{
		//比较每个丑数乘2、3、5的值，找出最小值
		int min = MinNum(*multiply2 * 2, *multiply3 * 3, *multiply5 * 5);
		UglyNums[index] = min;
		//放弃比当前值小的，肯定在之前已经出现
		while (*multiply2 * 2 <= UglyNums[index])
			++multiply2;
		while (*multiply3 * 3 <= UglyNums[index])
			++multiply3;
		while (*multiply5 * 5 <= UglyNums[index])
			++multiply5;
		++index;
	}
	int ugly = UglyNums[index - 1];
	delete[] UglyNums;
	return ugly;
}




//题目七：在字符串中找出第一个只出现一次的字符。如输入"abaccdeff"，则输出'b'。

//思路一：将字符串遍历一遍，遍历一个字符时与后面所有字符比较，如果没出现就是出现一次的字符，
//这种方法的时间复杂度为0(n2)。

//思路二：利用哈希表的key-value形式来保存字符和其出现的次数。由于字符是长度为8的数据类型，
//因此总共有256种可能。创建一个长度为256的数组，每个字母根据其ASCII码值作为数组的下标对应
//数组的一个数字，而数组中存储的是每个字符出现的次数。时间复杂度为O(n).须两次扫描哈希表。

char FirstNotRepeatingChar(char* str)
{
	assert(str);
	const int size = 256;
	//创建一个长度为256的数组
	unsigned int hashTable[size];
	//初始化数组，次数为0
	for (unsigned int i = 0; i < size; i++)
	{
		hashTable[i] = 0;
	}
	//第一次遍历数组，保存字符及其出现的次数
	char* pHashKey = str;
	while ((*pHashKey) != '\0')
	{
		hashTable[*(pHashKey++)]++;
	}
	//第二次遍历，找出出现一次的字符
	pHashKey = str;
	while ((*pHashKey) != '\0')
	{
		if (hashTable[*pHashKey] == 1)
			return *pHashKey;
		pHashKey++;
	}
	return '\0';
}
//1、相关题目一：定义一个函数，输入两个字符串，从第一个字符串中删除在第二个字符串中出现过的所
//有字符。创建一个数组实现的哈希表来保存第二个字符串，在扫描第一个字符串时，可以在O(1)的时
//间就可以判断出该字符是否在第二个字符串中。时间复杂度为O(n)。

//2、相关题目二：定义一个函数，删除字符串中所有重复出现的字符。扫描一个字符，将其存在数组
//实现的哈希表中，并将次数设为1。如果下次再扫描到这个字符时，如果次数为1，则说明以前出过。

//3、相关题目三：在英语中，如果两个单词中出现的字母相同，并且每个字母出现的次数也相同，那么
//这两个单词互为变位词。请完成一个函数，判断输入的两个字符串是不是互为变位词。创建一个用数组
//实现的简单哈希表，扫描第一个字符串，将对应的字符的次数设为1，当扫描第二个字符串时，扫描
//到每个字符，将其对应的哈希值减1.遍历完成，如果哈希表中所有值都为0，则互为变位词。
int main()
{
	char* str = "abaccdeff";
	char ch=FirstNotRepeatingChar(str);
	printf("%c\n", ch);
	return 0;
}