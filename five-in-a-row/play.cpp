#include<stdio.h>
#include<stdlib.h>

#define SIDE -1 
#define ARRAYSIDE -2

#define PLAYER 1
#define AI 2

#define ATTACK 1
#define DEFENSE 2
#define JUDGE 3

#define LONGFIVE 10
#define LIVEFOUR 9
#define CLASHFOUR 8
#define LIVETHREE 7
#define SLEEPTHREE 6
#define LIVETWO 5
#define SLEEPTWO 4
#define DEAFFOUR 3
#define DEAFTHREE 2
#define DEAFTWO 1

#define DULLIVETHREE 11
#define LIVETHREEANDSLEEPTHREE 12
#define DULLIVETWO 13
#define LIVETWOANDSLEEPTWO 14

int board[15][15];  //棋盘 

struct point{  //落子的结构 
	int x;
	int y;
}player,ai;

static int position[15][15] =   //位置分值 
{   
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
	{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
	{ 0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0 },
	{ 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0 },
	{ 0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0 },
	{ 0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0 },
	{ 0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0 },
	{ 0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0 },
	{ 0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0 },
	{ 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0 },
	{ 0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0 },
	{ 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
	{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

point GetPosition(int left,int right,int up,int down,int tree,int depth);  //得到落子位置，返回位置 
int GetScore(int x,int y);  //得到该点的分数并返回该分数 
int IsNull(int x,int y);  //判断该点是否有棋子 
void GetRowArray(int x,int y,int rowarray[],int flag);  //得到行数组 
void GetListArray(int x,int y,int listarray[],int flag);  //得到列数组 
void GetRightFallingArray(int x,int y,int rightfallingarray[],int flag);  //得到捺数组 
void GetLeftFallingArray(int x,int y,int leftfallingarray[],int flag);  //得到撇数组 
int Max(int row,int list,int rightfalling,int leftfalling);  //计算四个参数的最大值并返回 
int Match(int array[],int turn);  //匹配模式，如果匹配到就返回1，匹配不到就返回0 
int StruggleScore(int rowtype,int listtype,int rightfallingtype,int leftfallingtype);  //判断组合分数 
void Invert(int array[]);  //数组倒序
void SetBoard(int x,int y,int flag); //落子
int GetMode(int array[],int mode[]); //匹配模式
int Judge(void); //判断胜利函数
//α-β剪枝算法
int Maxmin(int player,int cur_node[15][15],int alpha,int beta,int depth,int left,int right,int up,int down,int x,int y);

int main()
{
	int flag = 0; 
	int temp = 0;
	//边界信息，为了减少计算次数，只计算最左的棋子-5位置到最右棋子+5位置的分数以及
	//最上棋子-5的位置与最下棋子+5的位置的分数 
	int left = 7;  //左边界 
	int right = 7;  //右边界 
	int up = 7;  //上边界 
	int down = 7;  //下边界 
	int win = 0; //胜利标志
	int tree = 0; //是否使用博弈树标志
	int depth = 0; //博弈树参数

	const char aipoint = 'o';  //ai棋子符号
	const char playerpoint = 'X';  //玩家棋子符号
	
	printf("===============================================\n");
	printf("本算法仅为测试版\n");
	printf("我们将通过输入和输出坐标的方式与玩家进行对战\n");
	printf("===============================================\n");
	printf("请选择是否使用博弈树(1.使用 | 0.不使用):");
	scanf("%d",&tree);
	if(tree == 1)
	{
		printf("请输入博弈树的深度(0~6):");
		scanf("%d",&depth);
	}
	printf("请选择：\n1、玩家先手\n2、AI先手\n");
	printf("请输入（1|2）");
	scanf("%d",&flag);
	
	printf("\n");


	
	while(1)
	{
		//测试代码 
		//printf("left:%d\n",left);
		//printf("right:%d\n",right);
		//printf("up:%d\n",up);
		//printf("down:%d\n",down);
		//================================ 

		//绘制棋盘
		printf("\n     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14  \n");
		printf("  -------------------------------------------------\n");
		for(int i = 0; i < 15; i++)
		{
			printf("%2d|",i);
			for(int j = 0; j < 15; j++)
			{
				if(board[i][j] == PLAYER)
				{
					printf("  %c",playerpoint);
				}
				else if(board[i][j] == AI)
				{
					printf("  %c",aipoint);
				}
				else if(board[i][j] == 0)
				{
					printf("  +");
				}
				else
				{
					printf("  !");  //差错控制
				}
				if(j == 14)
				{
					printf("  |\n");
				}
			}
		}
		printf("  -------------------------------------------------\n");
		//=================================================================

		win = Judge();
		if(win == AI)
		{
			printf("\nAI获得胜利。请再接再厉！");
			break;
		}
		else if(win == PLAYER)
		{
			printf("\n恭喜！您已获得胜利！");
			break;
		}
		else
		{
			//没有人获得胜利，比赛继续
		}

		switch(flag)
		{
			case PLAYER:
				while(1)
				{
					printf("请输入行坐标：");
					scanf("%d",&player.x);
					printf("请输入纵坐标：");
					scanf("%d",&player.y);
					if(IsNull(player.x,player.y))
					{
						if(player.x < 0 || player.x > 14 || player.y < 0 || player.y > 14)
						{
							printf("\n您选择的位置在棋盘外，请重新选择\n");
						}
						else
						{
							SetBoard(player.x,player.y,PLAYER);
							temp = 1;
							break;
						}
					}
					else
					{
						printf("\n此处已有棋子，请重新选择\n");
					}
				} 
				printf("\n您的落子为：(%d,%d)\n",player.x,player.y);
				
				if(player.y - 5 < left)  //更新边界信息 
				{
					left = player.y - 5;
				}
				if(player.y + 5 > right)
				{
					right = player.y + 5;
				}
				if(player.x - 5 < up)
				{
					up = player.x - 5;
				}
				if(player.x + 5 > down)
				{
					down = player.x + 5;
				}
				
				if(left < 0)
				{
					left = 0;
				}
				if(right > 14)
				{
					right = 14;
				}
				if(up < 0)
				{
					up = 0;
				}
				if(down > 14)
				{
					down = 14;
				}

				flag = AI;
				break;
			case AI:
				if(temp == 0)  //第一次落子 
				{
					ai.x = 7;
					ai.y = 7;
					temp = 1;
					SetBoard(ai.x,ai.y,AI);
				}
				else
				{
					ai = GetPosition(left,right,up,down,tree,depth);  //计算落点 
					SetBoard(ai.x,ai.y,AI);
				}
				printf("\nAI落子为：(%d,%d)\n",ai.x,ai.y);
				
				if(ai.y - 5 < left)  //更新边界信息 
				{
					left = ai.y - 5;
				}
				if(ai.y + 5 > right)
				{
					right = ai.y + 5;
				}
				if(ai.x - 5 < up)
				{
					up = ai.x -5;
				}
				if(ai.x + 5 > down)
				{
					down = ai.x + 5;
				}
				
				if(left < 0)
				{
					left = 0;
				}
				if(right > 14)
				{
					right = 14;
				}
				if(up < 0)
				{
					up = 0;
				}
				if(down > 14)
				{
					down = 14;
				}
				
				flag = PLAYER;
				break;
		}

	}
	
	system("PAUSE");

	return 0;
}

point GetPosition(int left,int right,int up,int down,int tree,int depth)
{
	int max = 0;
	point xy;
	int score = 0;
	
	for(int i = left; i <= right; i++)
	{
		for(int j = up; j <= down; j++)
		{
			if(IsNull(i,j))
			{
				if(tree == 0)
				{
					score = GetScore(i,j);
					if(max <= score)
					{
						max = score;
						xy.x = i;
						xy.y = j;
					}
					else
					{
						//此点打分低，舍弃 
					}
				}
				else  //启用博弈树
				{
					score = Maxmin(AI,board,-1000000,1000000,depth,left,right,up,down,i,j);
					if(max <= score)
					{
						max = score;
						xy.x = i;
						xy.y = j;
					}
					else
					{
						//此点打分低，舍弃 
					}
				}
				
				//测试代码
				//printf("打分情况：(%d,%d):",i,j);
				//("%d\n",score); 
				//======================================
			}
			else
			{
				//此点已有棋子，无需再计算 
			}
		}
	}
	
	return xy;
}

int GetScore(int x,int y)
{
	int rowarray[13] = {SIDE,0,0,0,0,0,0,0,0,0,0,0,SIDE};
	int listarray[13] = {SIDE,0,0,0,0,0,0,0,0,0,0,0,SIDE};
	int rightfallingarray[13] = {SIDE,0,0,0,0,0,0,0,0,0,0,0,SIDE};
	int leftfallingarray[13] = {SIDE,0,0,0,0,0,0,0,0,0,0,0,SIDE};
	int attackrowtype = 0;
	int attacklisttype = 0;
	int attackrightfallingtype = 0;
	int attackleftfallingtype = 0;
	int defenserowtype = 0;
	int defenselisttype = 0;
	int defenserightfallingtype = 0;
	int defenseleftfallingtype = 0;
	int attackscore = 0;
	int defensescore = 0;

	GetRowArray(x,y,rowarray,ATTACK);  //获得行数组 
	GetListArray(x,y,listarray,ATTACK);  //获得列数组 
	GetRightFallingArray(x,y,rightfallingarray,ATTACK);  //获得捺数组 
	GetLeftFallingArray(x,y,leftfallingarray,ATTACK);  //获得撇数组 
	
	//测试代码 
	/*
	printf("\n行数组：[");
	for(int i = 0; i < 13; i++)
	{
		printf("%d, ",rowarray[i]);
	}
	printf("]\n列数组：[");
	for(int i = 0; i < 13; i++)
	{
		printf("%d, ",listarray[i]);
	}
	printf("]\n捺数组：[");
	for(int i = 0; i < 13; i++)
	{
		printf("%d, ",rightfallingarray[i]);
	}
	printf("]\n撇数组：[");
	for(int i = 0; i < 13; i++)
	{
		printf("%d, ",leftfallingarray[i]);
	}
	printf("]\n");
	*/
	//===============================================
	
	attackrowtype = Match(rowarray,ATTACK);
	attacklisttype = Match(listarray,ATTACK);
	attackrightfallingtype = Match(rightfallingarray,ATTACK);
	attackleftfallingtype = Match(leftfallingarray,ATTACK);

	GetRowArray(x,y,rowarray,DEFENSE);  //获得行数组 
	GetListArray(x,y,listarray,DEFENSE);  //获得列数组 
	GetRightFallingArray(x,y,rightfallingarray,DEFENSE);  //获得捺数组 
	GetLeftFallingArray(x,y,leftfallingarray,DEFENSE);  //获得撇数组 

	defenserowtype = Match(rowarray,DEFENSE);
	defenselisttype = Match(listarray,DEFENSE);
	defenseleftfallingtype = Match(leftfallingarray,DEFENSE);
	defenserightfallingtype = Match(rightfallingarray,DEFENSE);

	/*
	if((attackrowtype == LONGFIVE && defenserowtype != DEAFFOUR ) || (attacklisttype == LONGFIVE && defenselisttype != DEAFFOUR) || 
		(attackleftfallingtype == LONGFIVE && defenseleftfallingtype != DEAFFOUR )|| (attackrightfallingtype == LONGFIVE && defenserightfallingtype != DEAFFOUR))
	{
		win = AI;
	}

	if((defenserowtype == LONGFIVE && attackrowtype != DEAFFOUR) || (defenselisttype == LONGFIVE && attacklisttype != DEAFFOUR) || 
		(defenseleftfallingtype == LONGFIVE && attackleftfallingtype != DEAFFOUR) || (defenserightfallingtype == LONGFIVE && attackrightfallingtype != DEAFFOUR))
	{
		win = PLAYER;
	}
	*/

	//测试代码
	//printf("attackrowtype:%d\n",attackrowtype);
	//printf("attacklisttype:%d\n",attacklisttype);
	//printf("attackrightfallingtype:%d\n",attackrightfallingtype);
	//printf("attackleftfallingtype:%d\n",attackleftfallingtype);
	//printf("defenserowtype:%d\n",defenserowtype);
	//printf("defenselisttype:%d\n",defenselisttype);
	//printf("defenserightfallingtype:%d\n",defenserightfallingtype);
	//printf("defenseleftfallingtype:%d\n",defenseleftfallingtype);
	//===============================================
	//测试代码
	//printf("\nrowtype:%d\n",rowtype);
	//printf("listtype:%d\n",listtype);
	//printf("rightfallingtype:%d\n",rightfallingtype);
	//printf("leftfallingtype:%d\n",leftfallingtype);
	//============================================== 
	
	attackscore = StruggleScore(attackrowtype,attacklisttype,attackrightfallingtype,attackleftfallingtype) + position[x][y];  //加上位置分的进攻得分

	defensescore = StruggleScore(defenserowtype,defenselisttype,defenserightfallingtype,defenseleftfallingtype) + position[x][y];  //加上位置分的防御得分

	return (attackscore + defensescore);
}

int IsNull(int x,int y)  //判断是否有棋子 
{
	if(board[x][y] == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
} 

void GetRowArray(int x,int y,int rowarray[],int flag)
{
	if(flag == ATTACK)
	{
		rowarray[6] = AI;
	}
	else if(flag == DEFENSE)
	{
		rowarray[6] = PLAYER;
	}
	else if(flag == JUDGE)
	{
		rowarray[6] = board[x][y];
	}

	for(int i = 1; i < 6; i++)
	{
		if(y+i > 14)  //判断是否超越右边界 
		{
			rowarray[6+i] = SIDE;
		}
		else
		{
			rowarray[6+i] = board[x][y+i];
		}
		
		if(y-i < 0)  //判断是否超越左边界 
		{
			rowarray[6-i] = SIDE;
		}
		else
		{
			rowarray[6-i] = board[x][y-i];
		}
	}
}

void GetListArray(int x,int y,int listarray[],int flag)
{
	if(flag == ATTACK)
	{
		listarray[6] = AI;
	}
	else if(flag == DEFENSE)
	{
		listarray[6] = PLAYER;
	}
	else if(flag == JUDGE)
	{
		listarray[6] = board[x][y];
	}

	for(int i = 1; i < 6; i++)
	{
		if(x+i > 14)  //判断是否超越下边界 
		{
			listarray[6+i] = SIDE;
		}
		else
		{
			listarray[6+i] = board[x+i][y];
		}
		
		if(x-i < 0)  //判断是否超越上边界 
		{
			listarray[6-i] = SIDE;
		}
		else
		{
			listarray[6-i] = board[x-i][y];
		}
	}
}

void GetRightFallingArray(int x,int y,int rightfallingarray[],int flag)
{
	if(flag == ATTACK)
	{
		rightfallingarray[6] = AI;
	}
	else if(flag == DEFENSE)
	{
		rightfallingarray[6] = PLAYER;
	}
	else if(flag == JUDGE)
	{
		rightfallingarray[6] = board[x][y];
	}

	for(int i = 1; i < 6; i++)
	{
		if(y+i > 14 || x+i > 14)  //判断是否超过下边界和右边界 
		{
			rightfallingarray[6+i] = SIDE;
		}
		else
		{
			rightfallingarray[6+i] = board[x+i][y+i];
		}
		
		if(y-i < 0 || x-i < 0)  //判断是否超过左边界和上边界 
		{
			rightfallingarray[6-i] = SIDE;
		}
		else
		{
			rightfallingarray[6-i] = board[x-i][y-i];
		}
	}
}

void GetLeftFallingArray(int x,int y,int leftfallingarray[],int flag)
{
	if(flag == ATTACK)
	{
		leftfallingarray[6] = AI;
	}
	else if(flag == DEFENSE)
	{
		leftfallingarray[6] = PLAYER;
	}
	else if(flag == JUDGE)
	{
		leftfallingarray[6] = board[x][y];
	}

	for(int i = 1; i < 6; i++)
	{
		if(x+i > 14 || y-i < 0)  //判断是否超过左边界和下边界 
		{
			leftfallingarray[6-i] = SIDE;
		}
		else
		{
			leftfallingarray[6-i] = board[x+i][y-i];
		}
		
		if(y+i > 14 || x-i < 0)  //判断是否超过右边界和上边界 
		{
			leftfallingarray[6+i] = SIDE;
		}
		else
		{
			leftfallingarray[6+i] = board[x-i][y+i];
		}
	}
}

int Max(int row,int list,int rightfalling,int leftfalling)  //判断四个值那个最大 
{
	int max = 0;

	if(row >= list && row >= rightfalling && row >= leftfalling)  //若出现两个数相同，则会返回第一个数 
	{
		max = row;
	}
	if(list >= row && list >= rightfalling && list >= leftfalling)
	{
		max = list;
	}
	if(leftfalling >= row && leftfalling >= list && leftfalling >= rightfalling)
	{
		max = leftfalling;
	}
	if(rightfalling >= row && rightfalling >= list && rightfalling >= leftfalling)
	{
		max = rightfalling;
	}
	
	return max;
}

int Match(int array[],int turn)
{
	int type[] = {LONGFIVE,LIVEFOUR,CLASHFOUR,CLASHFOUR,CLASHFOUR,LIVETHREE,LIVETHREE,SLEEPTHREE,SLEEPTHREE,SLEEPTHREE,SLEEPTHREE
		,SLEEPTHREE,SLEEPTHREE,LIVETWO,LIVETWO,LIVETWO,SLEEPTWO,SLEEPTWO,SLEEPTWO,SLEEPTWO,SLEEPTWO,SLEEPTWO,DEAFFOUR,DEAFTHREE,DEAFTWO};
	int score = 0; 
	int playerscore = 0;
	int aiscore = 0;
	if(turn == ATTACK)
	{
		//寻找对自己有利的情况 
		playerscore = 2;
		aiscore = 1;
	}
	else if(turn == DEFENSE)
	{
		playerscore = 1;
		aiscore = 2;
	}
	
	int situation1[] = {playerscore,playerscore,playerscore,playerscore,playerscore,SIDE,ARRAYSIDE};
	int situation2[] = {0,playerscore,playerscore,playerscore,playerscore,0,SIDE,ARRAYSIDE};
	int situation3[] = {0,playerscore,playerscore,playerscore,playerscore,aiscore,SIDE,ARRAYSIDE};
	int situation4[] = {0,playerscore,0,playerscore,playerscore,playerscore,0,SIDE,ARRAYSIDE};
	int situation5[] = {0,playerscore,playerscore,0,playerscore,playerscore,0,SIDE,ARRAYSIDE};
	int situation6[] = {0,playerscore,playerscore,playerscore,0,SIDE,ARRAYSIDE};
	int situation7[] = {0,playerscore,0,playerscore,playerscore,0,SIDE,ARRAYSIDE};
	int situation8[] = {0,0,playerscore,playerscore,playerscore,aiscore,SIDE,ARRAYSIDE};
	int situation9[] = {0,playerscore,0,playerscore,playerscore,aiscore,SIDE,ARRAYSIDE};
	int situation10[] = {0,playerscore,playerscore,0,playerscore,aiscore,SIDE,ARRAYSIDE};
	int situation11[] = {playerscore,0,0,playerscore,playerscore,SIDE,ARRAYSIDE};
	int situation12[] = {playerscore,0,playerscore,0,playerscore,SIDE,ARRAYSIDE};
	int situation13[] = {aiscore,0,playerscore,playerscore,playerscore,0,aiscore,SIDE,ARRAYSIDE};
	int situation14[] = {0,0,playerscore,playerscore,0,SIDE,ARRAYSIDE};
	int situation15[] = {0,playerscore,0,playerscore,0,SIDE,ARRAYSIDE};
	int situation16[] = {0,playerscore,0,0,playerscore,0,SIDE,ARRAYSIDE};
	int situation17[] = {0,0,0,playerscore,playerscore,aiscore,SIDE,ARRAYSIDE};
	int situation18[] = {0,0,playerscore,0,playerscore,aiscore,SIDE,ARRAYSIDE};
	int situation19[] = {0,playerscore,0,0,playerscore,aiscore,SIDE,ARRAYSIDE};
	int situation20[] = {playerscore,0,0,0,playerscore,SIDE,ARRAYSIDE};
	int situation21[] = {aiscore,0,playerscore,0,playerscore,0,aiscore,SIDE,ARRAYSIDE};
	int situation22[] = {aiscore,0,playerscore,playerscore,0,0,aiscore,SIDE,ARRAYSIDE};
	int situation23[] = {aiscore,playerscore,playerscore,playerscore,playerscore,aiscore,SIDE,ARRAYSIDE};
	int situation24[] = {aiscore,playerscore,playerscore,playerscore,aiscore,SIDE,ARRAYSIDE};
	int situation25[] = {aiscore,playerscore,playerscore,aiscore,SIDE,ARRAYSIDE};
	
	int *mode[] = {situation1,situation2,situation3,situation4,situation5,situation6,situation7,situation8,situation9,situation10,situation11
		,situation12,situation13,situation14,situation15,situation16,situation17,situation18,situation19,situation20,situation21,situation22
		,situation23,situation24,situation25};
	
	for(int i = 0; i < 25; i++)
	{
		if(GetMode(array,mode[i]))  //匹配到其中一种模式 
		{
			if(type[i] >= score)
			{
				score = type[i];  // 找到分数最大的 
			}
		}
		else
		{
			//没有匹配到任何一种模式 
		}

		Invert(array);  //翻转数组，逆序匹配，再次匹配模式
		
		if(GetMode(array,mode[i]))  //匹配到其中一种模式 
		{
			if(type[i] >= score)
			{
				score = type[i];  // 找到分数最大的 
			}
		}
		else
		{
			//没有匹配到任何一种模式 
		}

		Invert(array);  //再次翻转数组，使数组变为原来的，顺序匹配
	}

	return score;
	
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

int StruggleScore(int rowtype,int listtype,int rightfallingtype,int leftfallingtype)
{
	int max = 0;
	int returnscore = 0;
	
	max = Max(rowtype,listtype,rightfallingtype,leftfallingtype);
	
	if(rowtype == CLASHFOUR)
	{
		if(listtype == CLASHFOUR || rightfallingtype == CLASHFOUR || leftfallingtype == CLASHFOUR)
		{
			max = LIVEFOUR;
		}
		if(listtype == LIVETHREE || rightfallingtype == LIVETHREE || leftfallingtype == LIVETHREE)
		{
			max = LIVEFOUR;
		}
	}
	if(listtype == CLASHFOUR)
	{
		if(rowtype == CLASHFOUR || rightfallingtype == CLASHFOUR || leftfallingtype == CLASHFOUR)
		{
			max = LIVEFOUR;
		}
		if(rowtype == LIVETHREE || rightfallingtype == LIVETHREE || leftfallingtype == LIVETHREE)
		{
			max = LIVEFOUR;
		}
	}
	if(rightfallingtype == CLASHFOUR)
	{
		if(listtype == CLASHFOUR || rowtype == CLASHFOUR || leftfallingtype == CLASHFOUR)
		{
			max = LIVEFOUR;
		}
		if(listtype == LIVETHREE || rowtype == LIVETHREE || leftfallingtype == LIVETHREE)
		{
			max = LIVEFOUR;
		}
	}
	if(leftfallingtype == CLASHFOUR)
	{
		if(listtype == CLASHFOUR || rightfallingtype == CLASHFOUR || rowtype == CLASHFOUR)
		{
			max = LIVEFOUR;
		}
		if(listtype == LIVETHREE || rightfallingtype == LIVETHREE || rowtype == LIVETHREE)
		{
			max = LIVEFOUR;
		}
	}
	
	if(rowtype == LIVETHREE)
	{
		if(listtype == LIVETHREE || rightfallingtype == LIVETHREE || leftfallingtype == LIVETHREE)
		{
			max = DULLIVETHREE;
		}
		if(listtype == SLEEPTHREE || rightfallingtype == SLEEPTHREE || leftfallingtype == SLEEPTHREE)
		{
			max = LIVETHREEANDSLEEPTHREE;
		}
	}
	if(listtype == LIVETHREE)
	{
		if(rowtype == LIVETHREE || rightfallingtype == LIVETHREE || leftfallingtype == LIVETHREE)
		{
			max = DULLIVETHREE;
		}
		if(rowtype == SLEEPTHREE || rightfallingtype == SLEEPTHREE || leftfallingtype == SLEEPTHREE)
		{
			max = LIVETHREEANDSLEEPTHREE;
		}
	}
	if(rightfallingtype == LIVETHREE)
	{
		if(listtype == LIVETHREE || rowtype == LIVETHREE || leftfallingtype == LIVETHREE)
		{
			max = DULLIVETHREE;
		}
		if(listtype == SLEEPTHREE || rowtype == SLEEPTHREE || leftfallingtype == SLEEPTHREE)
		{
			max = LIVETHREEANDSLEEPTHREE;
		}
	}
	if(leftfallingtype == LIVETHREE)
	{
		if(listtype == LIVETHREE || rightfallingtype == LIVETHREE || rowtype == LIVETHREE)
		{
			max = DULLIVETHREE;
		}
		if(listtype == SLEEPTHREE || rightfallingtype == SLEEPTHREE || rowtype == SLEEPTHREE)
		{
			max = LIVETHREEANDSLEEPTHREE;
		}
	}
	
	if(rowtype == LIVETWO)
	{
		if(listtype == LIVETWO || rightfallingtype == LIVETWO || leftfallingtype == LIVETWO)
		{
			max = DULLIVETWO;
		}
		if(listtype == SLEEPTWO || rightfallingtype == SLEEPTWO || leftfallingtype == SLEEPTWO)
		{
			max = LIVETWOANDSLEEPTWO;
		}
	}
	if(listtype == LIVETWO)
	{
		if(rowtype == LIVETWO || rightfallingtype == LIVETWO || leftfallingtype == LIVETWO)
		{
			max = DULLIVETWO;
		}
		if(rowtype == SLEEPTWO || rightfallingtype == SLEEPTWO || leftfallingtype == SLEEPTWO)
		{
			max = LIVETWOANDSLEEPTWO;
		}
	}
	if(rightfallingtype == LIVETWO)
	{
		if(listtype == LIVETWO || rowtype == LIVETWO || leftfallingtype == LIVETWO)
		{
			max = DULLIVETWO;
		}
		if(listtype == SLEEPTWO || rowtype == SLEEPTWO || leftfallingtype == SLEEPTWO)
		{
			max = LIVETWOANDSLEEPTWO;
		}
	}
	if(leftfallingtype == LIVETWO)
	{
		if(listtype == LIVETWO || rightfallingtype == LIVETWO || rowtype == LIVETWO)
		{
			max = DULLIVETWO;
		}
		if(listtype == SLEEPTWO || rightfallingtype == SLEEPTWO || rowtype == SLEEPTWO)
		{
			max = LIVETWOANDSLEEPTWO;
		}
	}
	
	switch(max)
	{
		case DEAFTWO:
			returnscore = -5;
			break;
		case DEAFTHREE:
			returnscore = -5;
			break;
		case DEAFFOUR:
			returnscore = -5;
			break;
		case SLEEPTWO:
			returnscore = 3;
			break;
		case LIVETWO:
			returnscore = 5;
			break;
		case LIVETWOANDSLEEPTWO:
			returnscore = 10;
			break;
		case SLEEPTHREE:
			returnscore = 50;
			break;
		case DULLIVETWO:
			returnscore = 100;
			break;
		case LIVETHREE:
			returnscore = 200;
			break;
		case LIVETHREEANDSLEEPTHREE:
			returnscore = 1000;
			break;
		case DULLIVETHREE:
			returnscore = 5000;
			break;
		case LIVEFOUR:
			returnscore = 10000;
			break;
		case CLASHFOUR:
			returnscore = 500;
			break;
		case LONGFIVE:
			returnscore = 100000;
			break;
		case 0:
			returnscore = 0;
			break;
	}

	return returnscore;
	
}

void Invert(int array[])
{
	int temp[13];

	for(int i = 0; i < 13; i++)
	{
		temp[i] = array[12 - i];
	}
	for(int i = 0; i < 13; i++)
	{
		array[i] = temp[i];
	}
}

void SetBoard(int x,int y,int flag)
{
	board[x][y] = flag;
}

int Judge(void)
{
	int rowarray[13] = {SIDE,0,0,0,0,0,0,0,0,0,0,0,SIDE};
	int listarray[13] = {SIDE,0,0,0,0,0,0,0,0,0,0,0,SIDE};
	int rightfallingarray[13] = {SIDE,0,0,0,0,0,0,0,0,0,0,0,SIDE};
	int leftfallingarray[13] = {SIDE,0,0,0,0,0,0,0,0,0,0,0,SIDE};
	int judgeaiwin[] = {2,2,2,2,2,SIDE,ARRAYSIDE};
	int judgeplayerwin[] = {1,1,1,1,1,SIDE,ARRAYSIDE};
	int win = 0;
	int rowflag = 0;
	int listflag = 0;
	int rightflag = 0;
	int leftflag = 0;

	for(int i = 0; i < 15; i++)
	{
		for(int j = 0; j < 15; j++)
		{
			GetRowArray(i,j,rowarray,JUDGE);  //获得行数组 
			GetListArray(i,j,listarray,JUDGE);  //获得列数组 
			GetRightFallingArray(i,j,rightfallingarray,JUDGE);  //获得捺数组 
			GetLeftFallingArray(i,j,leftfallingarray,JUDGE);  //获得撇数组 

			rowflag = GetMode(rowarray,judgeplayerwin);
			listflag = GetMode(listarray,judgeplayerwin);
			leftflag = GetMode(leftfallingarray,judgeplayerwin);
			rightflag = GetMode(rightfallingarray,judgeplayerwin);

			if(rowflag || listflag || leftflag || rightflag)
			{
				win = PLAYER;
			}

			rowflag = GetMode(rowarray,judgeaiwin);
			listflag = GetMode(listarray,judgeaiwin);
			leftflag = GetMode(leftfallingarray,judgeaiwin);
			rightflag = GetMode(rightfallingarray,judgeaiwin);

			if(rowflag || listflag || leftflag || rightflag)
			{
				win = AI;
			}
		}
	}

	return win;
}

//伪代码，要修改

// player = 2 表示轮到AI， player = 1 表示轮到玩家  
// cur_node 表示当前局面(结点)  
int Maxmin(int player,int cur_node[15][15],int alpha,int beta,int depth,int left,int right,int up,int down,int x,int y)  
{  
	int val = 0;
	int next_node[15][15];

	for(int i = 0; i < 15; i++)
	{
		for(int j = 0; j < 15; j++)
		{
			next_node[i][j] = cur_node[i][j];
		}
	}

    if(depth == 0)  //达到终结局面 
	{
		return GetScore(x,y); //该局面结点的估价值 f  
	}

    if(player == AI) // 轮到AI走  
	{
		for(int i = left; i <= right; i++)
		{
			for(int j = up; j <= down; j++)
			{
				if(IsNull(i,j))
				{
					next_node[i][j] = AI; // 遍历当前局面 cur_node 的所有子局面  

					if(j - 5 < left)  //更新边界信息 
					{
						left = j - 5;
					}
					if(j + 5 > right)
					{
						right = j + 5;
					}
					if(i - 5 < up)
					{
						up = i - 5;
					}
					if(i + 5 > down)
					{
						down = i + 5;
					}
					
					if(left < 0)
					{
						left = 0;
					}
					if(right > 14)
					{
						right = 14;
					}
					if(up < 0)
					{
						up = 0;
					}
					if(down > 14)
					{
						down = 14;
					}

					val = Maxmin(PLAYER, next_node, alpha, beta,depth - 1,left,right,up,down,i,j); // 把新产生的局面交给对方，对方返回一个新局面的估价值  
					if(val > alpha)
					{
						alpha = val;  
					} 
					if(alpha > beta)
					{
						return alpha;
					}
				}
			}
		}
		return alpha; 
	}
    else // 轮到玩家走  
	{
		for(int i = left; i <= right; i++)
		{
			for(int j = up; j <= down; j++)
			{
				if(IsNull(i,j))
				{
					next_node[i][j] = PLAYER; // 遍历当前局面 cur_node 的所有子局面 

					if(j - 5 < left)  //更新边界信息 
					{
						left = j - 5;
					}
					if(j + 5 > right)
					{
						right = j + 5;
					}
					if(i - 5 < up)
					{
						up = i - 5;
					}
					if(i + 5 > down)
					{
						down = i + 5;
					}
					
					if(left < 0)
					{
						left = 0;
					}
					if(right > 14)
					{
						right = 14;
					}
					if(up < 0)
					{
						up = 0;
					}
					if(down > 14)
					{
						down = 14;
					}

					val = Maxmin(AI, next_node, alpha, beta,depth - 1,left,right,up,down,i,j); // 把新产生的局面交给对方，对方返回一个新局面的估价值  
					if(val < beta)
					{
						beta = val;
					}   
					if(alpha > beta) 
					{
						return beta;  
					}
				}
			}
		}  
        return beta; 
	}
}  