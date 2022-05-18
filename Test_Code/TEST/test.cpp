#define  _CRT_SECURE_NO_WARNINGS 1
#include <string>
#include <iostream>
#include <vector>
using namespace std;
int ways(int apples, int plates)
{
	//apples����ȫ��ͬ��ƻ���ŵ�plates����ȫ��ͬ��������
	//�ж����ַ���
	//���ƻ�������� ˵���ڷŽ����� ����һ�ְڷ�
	if (apples == 0) {
		return 1;
	}
	//���plates����0�� apples������0�� ��ô˵��û����������
	//0�ְڷ�
	if (plates == 0) {
		return 0;
	}
	//�������������ƻ���� ��ô����������Ӳ���ʲô�ڷ�һ������
	//��������µİڷ������ڰѶ���������Ӷ������ǵİڷ���
	if (plates > apples) {
		return ways(apples, apples);
	}
	//��ƻ����������������ʱ�� �����ַ���
	//1) ���ǰ����е����Ӷ�ʹ�� ��ô�൱���������������϶���һ��ƻ��
	// ���ַ����ķ���������ways(apples - plates, plates)
	int a = ways(apples - plates, plates);
	//2) ���������Ӳ�ȫ��ʹ�� ��ô������һ������ 
	//ʣ�µ�����ȫ�û�������һ�� �ܿ��ܷ������õݹ�ȥ����
	int b = ways(apples, plates - 1);
	//�����������Ȼ�ǻ���� ������������ֱ�Ӽ�
	return a + b;
}

int _ways1(int apples, int plates, vector<vector<int>>& dp)
{
	if (dp[apples][plates] != -1) {
		return dp[apples][plates];
	}
	int ans = 0;
	if (apples == 0)
	{
		ans = 1;
	}
	else if (plates == 0)
	{
		ans = 0;
	}
	else if (apples < plates)
	{
		ans = _ways1(apples, apples, dp);
	}
	else
	{
		int a = _ways1(apples - plates, plates, dp);
		int b = _ways1(apples, plates - 1, dp);
		ans = a + b;
	}
	dp[apples][plates] = ans;
	return ans;
}

int ways1(int apples, int plates)
{
	//���ǰѱ����ݹ���̼�Ϊ��̬�滮
	//�����ݹ����֮���Ա��� ����Ϊ��ֻ��ͨ��һ��������չ��ȥ����f(x,y)
	//������f(x,y���Ѿ�������� Ϊʲô�������������أ�
	//����Ƕ�̬�滮��˼��
	vector<vector<int>> dp(apples + 1, vector<int>(plates + 1, -1));
	//dp[x][y] ƻ����x�� ������y�� �ڷŷ�����dp[x][y]��
	//��ȫ�����-1˵����ǰ�������ǻ����
	return _ways1(apples, plates, dp);
}

int main()
{
	int begin1 = clock();
	cout << ways1(100, 20) << endl;
	int end1 = clock();
	int begin2 = clock();
	cout << ways(100, 20) << endl;
	int end2 = clock();
	cout << end1 - begin1 << endl;
	cout << end2 - begin2 << endl;
}