#include <stdio.h>
#pragma warning(disable:4996)
int maxSubarraySum(int arr[], int n) {
	int maxSum = 0, maxEndingHere = 0;
	for (int i = 0; i < n; i++) {
		maxEndingHere = (maxEndingHere + arr[i] > 0) ? maxEndingHere + arr[i] : 0;
		maxSum = (maxEndingHere > maxSum) ? maxEndingHere : maxSum;
	}
	return maxSum;
}
int Func(int n, int* arr) {
	int maxSum = maxSubarraySum(arr, n);
	printf("����Ӷκ�Ϊ��%d\n", maxSum);
	return maxSum;
}

int main(void) {
	int n;
	printf("���������鳤��: ");
	scanf("%d", &n);
	int arr[10000];
	printf("����������Ԫ�أ��Կո�ָ�: ");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	Func(n, arr);
	return 0;
}
