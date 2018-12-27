#include<stdio.h>

#define SIDE -1
#define ARRAYSIDE -2

int GetMode(int array[],int mode[]);

int main()
{
    int modescore;
    int array[] = {-1,-1,-1,-1,0,0,0,1,1,1,1,2,-1};
    int mode[] = {0,1,1,1,1,2,-1,-2};

    modescore = GetMode(array,mode);

    printf("%d",modescore);

    return 0;
    
}

int GetMode(int array[],int mode[])
{
	int *parray = array;
	int *pmode = mode;
	int temp = 0;  //回退计数 
	int flag = 0;  //是否找到模式的标志 
	int sign = 0;
	
	for(;*(parray)==SIDE;parray++);

	for(;*(parray)!=SIDE;parray++)
	{
		flag = 0;
		temp = 0;
		sign = 0;
		pmode = mode;
		for(; *pmode!=ARRAYSIDE; pmode++)
		{
			if(*pmode == SIDE)  //到达模式数组结尾，设置标志，跳出循环 
			{
				flag = 1;
				break;
			}
			if(*parray == *pmode)  //若相等，则原数组指针加1 
			{
				temp++;
				parray++;
				if(*parray == SIDE)
				{
					pmode++;
					if(*pmode == SIDE)
					{
						flag = 1;
					}
					pmode--;
					sign = 1;  //非正常结束循环
					break;
				}
			}
			else
			{
                if(temp == 0)
                {
                    //无需做任何操作
                }
				else if(temp == 1)  
				{
                    parray--;
					//这种情况下，原数组指针不需要回退 
					if(*parray == SIDE)
					{
						sign = 1;  //非正常结束循环
					}
				}
				else
				{
					parray = parray - temp + 1;
				}
				break;
			}
		}
		if(flag == 1 || sign == 1)  //找到匹配，退出外循环 
		{
			break;
		}
		
	}
	
	if(flag)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}