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
	printf("最大子段和为：%d\n", maxSum);
	return maxSum;
}

int main(void) {
	int n;
	printf("请输入数组长度: ");
	scanf("%d", &n);
	int arr[10000];
	printf("请输入数组元素，以空格分隔: ");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	Func(n, arr);
	return 0;
}
