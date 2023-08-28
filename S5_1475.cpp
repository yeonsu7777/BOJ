#include <iostream>

int min(int a, int b)
{
	if (a > b)
		return b;
	return a;
}

int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

int main()
{
	int roomNum;
	scanf("%d", &roomNum);

	int nums[10] = {};

	while (roomNum)
	{
		nums[roomNum % 10]++;
		roomNum /= 10;
	}

	int sixNine = abs(nums[6] - nums[9]);
	if (sixNine % 2)
		sixNine++;
	nums[6] = min(nums[6], nums[9]) + sixNine / 2;
	nums[9] = 0;

	int result = 0;
	for (int i = 0; i < 10; i++)
	{
		result = max(result, nums[i]);
	}

	printf("%d", result);

	return 0;
}