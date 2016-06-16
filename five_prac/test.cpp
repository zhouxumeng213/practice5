#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
//��Ŀһ����������һ�����ֳ��ֵĴ����������鳤�ȵ�һ�룬���ҳ�������֡���������һ������Ϊ
//9������{1��2��3��2��2��2��5��4��2}����������2�������г�����5�Σ��������鳤�ȵ�һ�룬���
//���2��

//˼·һ��������������������ô�����λ�������м������һ�������Ǹ����ִ����������鳤��
//һ������֡��������ÿ��������˼�룬���ѡ��һ�����֣��������м�����Ƚϣ�Ȼ��ݹ顣ʱ��
//���Ӷ�ΪO(n),��ȱ���ǻ�ı�����ԭ��������˳��

//˼·������������һ�����ֳ��ֵĴ����������鳤�ȵ�һ�룬Ҳ����˵�����ֵĴ�����������������
//���ִ����ĺͻ�Ҫ�ࡣ�����������飬����һ�����ֺ�֮ǰ�����������ͬ��������1����ͬ��1����
//������Ϊ0��������һ�����֣����Ѵ�����Ϊ1����Ҫ�ҵ����ֿ϶������һ�ΰѴ�����Ϊ1��Ӧ������
//ʱ�临�Ӷ�ΪO(n)���Ҳ����޸������е�����˳��

//1�����ڿ�������˼��Ľⷨ

//����һ����begin��end֮��������
int RandomInRange(int begin,int end)
{}
//����������
void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
//����һ������������ÿ�������˼�뽫������ķ����ұߣ�����С�ķ������
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
//������õ��Ľ���ǲ��ǳ������鳤�ȵ�һ��
bool CheckIsLegal(int* num, int len, int result)
{
	int time = 0;//�ۼƵõ��Ľ���������г��ֵĴ���
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
			//�ݹ���middle
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

//2�����������ص�Ľⷨ
int MoreThanHalfNum(int *num, int len)
{
	assert(num);
	assert(len);

	int result = num[0];
	int time = 1;
	for (int i = 1; i < len; i++)
	{
		//timeΪ0��������һ��ֵ������time��Ϊ1
		if (time == 0)
		{
			result = num[i];
			time = 1;
		}
		//�����һ�����ֺ͵�ǰ�����������ȣ�time+1
		else if (result == num[i])
			time++;
		//����ȣ�time-1
		else
			time--;
	}
	//�ж��Ƿ��ǺϷ��Ľ��
	if (!CheckIsLegal(num, len, result))
		result = 0;
	return result;
}


//��Ŀ��������n���������ҳ�������С��K��������������4��5��1��6��2��7��3��8��8�����֣�����С
//��4��������1��2��3��4

//˼·һ����n������������ǰk����������С��k�������������ַ�����ʱ�临�Ӷ�ΪO(n*log(n))��
//���Ҳ��ʺϺ������ݵĴ���

//˼·�������ÿ��������˼�룬ʹ��k�����ִ�ķŵ��ұߣ���k������С�ķŵ���ߡ�����֮��λ
//����������ߵ�k�����־�����С��k��������k������һ��������ģ���ʱ�临�Ӷ�ΪO(n)��ȱ����
//�޸�����������˳��

//˼·�������öѻ��ߺ������ʵ�֣�����һ����k��Ԫ�صĴ�ѣ�ÿ��ȡһ�����ֺʹ�ѵĶѶ��Ƚ�
//������ڶѶ�����ȡ��һ�������С�ڶѶ���ɾ���Ѷ�Ԫ�أ����������ȥ��������ѡ��������ú�
//������ʵ�֡�STL�е�set��multiset���ǻ��ں����ʵ�ֵġ�ʱ�临�Ӷ�ΪO(n*log(k))���˷����ʺ�
//�������ݵĴ���

//1�����ڿ�������˼��Ľⷨ
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
//2�����ڶѻ��ߺ�����Ľⷨ
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


//��Ŀ��������һ���������飬������������Ҳ�и�����������һ���������Ķ���������һ��������
//������������͵����ֵ��Ҫ��ʱ�临�Ӷ�ΪO(n)��

//˼·һ����ͷ��β���������ۼӣ���ʼ����Ϊ0������֮����º͡��ͱ������ֵ��

//˼·����Ӧ�ö�̬�滮��˼��

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
		//���浱ǰ�͵����ֵ
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


//��Ŀ�ģ�����һ������n�����1��n��n��������ʮ���Ʊ�ʾ��1���ֵĴ�������������12.��1��12��Щ
//�����а���1��������1,10,11,12��1һ��������5�Ρ�

//˼·һ��һ���ж�1-nÿ������1���ֵĴ������ۼ���������1���ֵ��ܴ�����ʱ�临�Ӷ�ΪO(n*log(n))
//˼·��������1�ڸ���λ�ϳ��ֵĴ�����������1���ֵ��ܴ�����ʱ�临�Ӷ�ΪO(log*n)

//�ⷨ1����ÿ������1�ĸ�����ͨ��%10��/10�����
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
//��1��n�ۼ�ÿ������1�ĸ���
int NumOf1Between1AndN(unsigned int n)
{
	int numOf1 = 0;//����1�ĸ�����
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
//2���ⷨ����
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
	//����str�ǡ�21345��
	//numFristDigit������10000-19999�ĵ�һ��λ�е���Ŀ
	int numFrirstDigit = 0;
	if (first > 1)
		numFrirstDigit = PowerBase10(len - 1);
	else if (first == 1)
		numFrirstDigit = atoi(str + 1) + 1;

	//numOtherDigits��1346-21345���˵�һλ֮�����λ�е���Ŀ
	int numOtherDigits = first*(len - 1)*PowerBase10(len - 2);

	//numRecursive��1-1345�е���Ŀ
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


//��Ŀ�壺����һ�����������飬����������������ƴ�������ų�һ��������ӡ��ƴ�ӳ�������������
//��С��һ����������������{3��32��321}�����ӡ����3���������ųɵ���С����321323.

//˼·������ϣ���ܹ��ҵ�һ�ֹ��򣬰������ֹ������г�����������С������Ҫȷ������Ĺ�����
 //�Ǿͱ���֪����������������������a��b�����ȷ��һ������ʹ�ð��ո�������������ܵõ���С
 //������Ҳ����Ҫ�Ƚ�a��b��ֵ�������ֱȽϲ�����ͨ����ֵ�Ĵ�С��
 //��������a��b�����еĽ��Ϊab��ba�����abС��ba��Ӧ�����ab����a����b��ǰ�棬Ҳ����a<b��
 //��֮�����baС��ab����b����aǰ�棬Ҳ����b<a�����ab����ba����ôa = b��
 //������������ǣ���������a��b�����ƴ�ӵõ�ab����ba��Ȼ��Ƚ����ǵĴ�С�����ֱ������ֵ
 //����ƴ�ӵ�Ȼ�ǿ��Եģ��������ǿ��ǵ�a��b����int�͵ģ����ƴ�Ӻ�õ����ֳ���int�͵ķ�Χ��
 //�½���������ô�죿����Ȼ�����뵽�����ֽ�������ת�����ַ������ͣ�Ȼ�������ӡ�

//ÿ���������10���������
const int MaxDigits = 10;

//str1��str2�ֱ𱣴�Ƚϵ������ַ�������ab��ba
char* str1 = new char[2 * MaxDigits + 1];
char* str2 = new char[2 * MaxDigits + 1];

int comp(const void* a, const void* b)
{
	//ƴ���ַ������õ�ab
	strcpy(str1, *(const char**)a);
	strcat(str1, *(const char**)b);
	//ƴ���ַ������õ�ba
	strcpy(str2, *(const char**)b);
	strcat(str2, *(const char**)a);
	return strcmp(str1, str2);
}
void GetMinNum(int arr[],int len)
{
	if (arr == NULL || len <= 0)
		return;
	//�����µ��ַ�������
	char** strArr = (char**)(new int[len]);
	//ÿ���ַ��������е�Ԫ�ؽ����µ��ַ�����������Ϊnum�е�ֵ��
	for (int i = 0; i < len; i++)
	{
		strArr[i] = new char[MaxDigits + 1];
		sprintf(strArr[i], "%d", arr[i]);//��arr[i]ת��ʮ���Ʊ�ʾ���ַ���
	}
	//qsort:C���Կ⺯���е������������ÿ��������˼�롣
	qsort(arr, len, sizeof(char*), comp);
	//��ӡ�ųɵ���С����
	for (int i = 0; i < len; i++)
	{
		printf("%s", strArr[i]);
	}
	printf("\n");
	//�ͷ��ڴ�
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


//��Ŀ�������ǰ�ֻ��������2��3��5������������(Ugly Number)���󰴴�С�����˳��ĵ�1500������
//����6��8���ǳ�������14���ǣ���Ϊ����������7��ϰ�������ǰ�1������һ��������

//˼·һ��������������2��3��5.������ֻ�ܱ�2��3��5���������һ�����ܱ�2������������������2��
//����ܱ�3������������������3������ܱ�5��������������5��������õ�����1����˵���ǳ�����

//˼·��������Ӧ������һ����������2��3����5�Ľ����1���⣩����˿��Դ���һ�����飬�������
//�����ĺ���ĳ�����ÿһ����������ǰ��ĳ�������2��3����5�õ��ġ�

//1���ⷨһ��
//�ж�һ�����ǲ��ǳ���
bool IsUgly(int num)
{
	//�ܱ�2��3����5�������������1
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
	//UglyNum:Ҫ�ҵĵ�n������
	int UglyNum = 0;
	int index = 0;
	while (index < n)
	{
		++UglyNum;
		//��n������,��index���ж�,index��¼�����ĸ���
		if (IsUgly(UglyNum))
			index++;
	}
	return UglyNum;
}

//2���ⷨ�����ռ任ʱ��
//�ж�����������Сֵ
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
	//����Ҫ���ɵ�n������
	int *UglyNums = new int[n];
	UglyNums[0] = 1;
	int index = 1;
	//����ÿ��������2��3��5��ֵ
	int* multiply2 = UglyNums;
	int* multiply3 = UglyNums;
	int* multiply5 = UglyNums;

	while (index < n)
	{
		//�Ƚ�ÿ��������2��3��5��ֵ���ҳ���Сֵ
		int min = MinNum(*multiply2 * 2, *multiply3 * 3, *multiply5 * 5);
		UglyNums[index] = min;
		//�����ȵ�ǰֵС�ģ��϶���֮ǰ�Ѿ�����
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




//��Ŀ�ߣ����ַ������ҳ���һ��ֻ����һ�ε��ַ���������"abaccdeff"�������'b'��

//˼·һ�����ַ�������һ�飬����һ���ַ�ʱ����������ַ��Ƚϣ����û���־��ǳ���һ�ε��ַ���
//���ַ�����ʱ�临�Ӷ�Ϊ0(n2)��

//˼·�������ù�ϣ���key-value��ʽ�������ַ�������ֵĴ����������ַ��ǳ���Ϊ8���������ͣ�
//����ܹ���256�ֿ��ܡ�����һ������Ϊ256�����飬ÿ����ĸ������ASCII��ֵ��Ϊ������±��Ӧ
//�����һ�����֣��������д洢����ÿ���ַ����ֵĴ�����ʱ�临�Ӷ�ΪO(n).������ɨ���ϣ��

char FirstNotRepeatingChar(char* str)
{
	assert(str);
	const int size = 256;
	//����һ������Ϊ256������
	unsigned int hashTable[size];
	//��ʼ�����飬����Ϊ0
	for (unsigned int i = 0; i < size; i++)
	{
		hashTable[i] = 0;
	}
	//��һ�α������飬�����ַ�������ֵĴ���
	char* pHashKey = str;
	while ((*pHashKey) != '\0')
	{
		hashTable[*(pHashKey++)]++;
	}
	//�ڶ��α������ҳ�����һ�ε��ַ�
	pHashKey = str;
	while ((*pHashKey) != '\0')
	{
		if (hashTable[*pHashKey] == 1)
			return *pHashKey;
		pHashKey++;
	}
	return '\0';
}
//1�������Ŀһ������һ�����������������ַ������ӵ�һ���ַ�����ɾ���ڵڶ����ַ����г��ֹ�����
//���ַ�������һ������ʵ�ֵĹ�ϣ��������ڶ����ַ�������ɨ���һ���ַ���ʱ��������O(1)��ʱ
//��Ϳ����жϳ����ַ��Ƿ��ڵڶ����ַ����С�ʱ�临�Ӷ�ΪO(n)��

//2�������Ŀ��������һ��������ɾ���ַ����������ظ����ֵ��ַ���ɨ��һ���ַ��������������
//ʵ�ֵĹ�ϣ���У�����������Ϊ1������´���ɨ�赽����ַ�ʱ���������Ϊ1����˵����ǰ������

//3�������Ŀ������Ӣ���У�������������г��ֵ���ĸ��ͬ������ÿ����ĸ���ֵĴ���Ҳ��ͬ����ô
//���������ʻ�Ϊ��λ�ʡ������һ���������ж�����������ַ����ǲ��ǻ�Ϊ��λ�ʡ�����һ��������
//ʵ�ֵļ򵥹�ϣ��ɨ���һ���ַ���������Ӧ���ַ��Ĵ�����Ϊ1����ɨ��ڶ����ַ���ʱ��ɨ��
//��ÿ���ַ��������Ӧ�Ĺ�ϣֵ��1.������ɣ������ϣ��������ֵ��Ϊ0����Ϊ��λ�ʡ�
int main()
{
	char* str = "abaccdeff";
	char ch=FirstNotRepeatingChar(str);
	printf("%c\n", ch);
	return 0;
}