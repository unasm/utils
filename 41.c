/*************************************************************************
  * File Name :  41.c
  * Author  :      unasm
  * Mail :         unasm@sina.cn
  * Last_Modified: 2015-08-20 18:18:25
 ************************************************************************/

#include<stdio.h>
int hash[10000];
void disp(int size,int *nums) {
	for (int i = 0;i < size; i++) {
		printf("%d\t", nums[i]);
	}
	printf("\n");
}
int swap(int pos, int min, int max, int* nums) {
	int tmp, res = pos, target = nums[pos];
	while(min < max) {
		while(min < max)	 {
			if (nums[min] >= target) {
				break;
			} else {
				min++;
			}
		}
		while(min < max)	 {
			if (nums[max] <= target) {
				break;
			} else {
				max--;
			}
		}
		if(min != max && nums[min] >= target && nums[max] <= target) {
			if(nums[min] == target && nums[max] == target) {
				//min+=1;
				max --;
				printf("same\n");
				continue;
				//printf("repeat\n");
			}
			tmp = nums[max]	;
			nums[max] = nums[min];
			nums[min] = tmp;
			if (nums[min] != target) {
				min++;
			} else {
				res = min;
			}
			if (nums[max] != target) {
				max--;
			} else {
				res = max;
			}
			
		} 
		/*else {
			printf("%d \t %d\n", nums[max], nums[min]);
			break;
		}
		*/
	}
	//nums[min+1] = target;
	return  res;
}
int firstMissingPositive(int* nums, int numsSize) {
	for (int i = 0;i <= numsSize;i++) {
		hash[i] = -1;
	}
	for (int i = 0;i < numsSize;i++) {
		if (nums[i] >= 0) {
			hash[nums[i]] = 1;
		}
	}
	int cnt = 0;
	for (int i = 0;i <= numsSize;i++) {
		if (hash[i] !=  -1) {
			nums[cnt++] = i;
		}
	}
	numsSize = cnt;
	int one = -1, maxVal = -1;
	for (int i = 0;i < numsSize;i++) {
		if (nums[i] == 1) {
			one = i;
			break;
		}
		if (nums[i] > maxVal) {
			maxVal = nums[i];
		}
	}
	//printf("one %d\n", one);
	if (one == -1) {
		return 1;
	}
	int min = swap(one, 0, numsSize - 1, nums), max = numsSize - 1;
	//disp(numsSize, nums);
	while(max > min) {
		int mid = (min+max)	/ 2;
		mid = swap(mid, min,max, nums);
		//printf("mid is %d\n", nums[mid]);
		//disp(numsSize, nums);
		if((nums[mid] - nums[min]) > mid - min) {
			max = mid;
		} else {
			if (min == mid) {
				if((nums[max] - nums[min]) == max - min) {
					return nums[max] + 1;
				} else {
					return nums[min] + 1;
				}
			}
			min = mid;
		}
	}
	//printf("%d\n", nums[min]);
	return nums[min]+1;
}

int main(int argc, const char *argv[])
{
	//int nums[] = {-1,3,1,4}, size = 4, exp = 2;
	//int nums[] = {3, 4 ,1, -1}, size = 4, exp = 2;
	//int nums[] = {3,3,1,4,0}, size = 5, exp = 2;
	int nums[] = {0,2,2,4,0,1,0,1,3}, size = 9, exp = 5;
	// 0 0 0 1 1 2 2 3 4
	//int nums[] = {3,4, -1,1}, size = 4, exp = 2;
	//int nums[] = {-1,3,2,1,4}, size = 5, exp = 5;
	int got = firstMissingPositive(nums, size)	;
	printf("got %d\n", got);
	return 0;
}
