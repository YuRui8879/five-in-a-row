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

int board[15][15];  //���� 

struct point{  //���ӵĽṹ 
	int x;
	int y;
}player,ai;

static int position[15][15] =   //λ�÷�ֵ 
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

point GetPosition(int left,int right,int up,int down,int tree,int depth);  //�õ�����λ�ã�����λ�� 
int GetScore(int x,int y);  //�õ��õ�ķ��������ظ÷��� 
int IsNull(int x,int y);  //�жϸõ��Ƿ������� 
void GetRowArray(int x,int y,int rowarray[],int flag);  //�õ������� 
void GetListArray(int x,int y,int listarray[],int flag);  //�õ������� 
void GetRightFallingArray(int x,int y,int rightfallingarray[],int flag);  //�õ������� 
void GetLeftFallingArray(int x,int y,int leftfallingarray[],int flag);  //�õ�Ʋ���� 
int Max(int row,int list,int rightfalling,int leftfalling);  //�����ĸ����������ֵ������ 
int Match(int array[],int turn);  //ƥ��ģʽ�����ƥ�䵽�ͷ���1��ƥ�䲻���ͷ���0 
int StruggleScore(int rowtype,int listtype,int rightfallingtype,int leftfallingtype);  //�ж���Ϸ��� 
void Invert(int array[]);  //���鵹��
void SetBoard(int x,int y,int flag); //����
int GetMode(int array[],int mode[]); //ƥ��ģʽ
int Judge(void); //�ж�ʤ������
//��-�¼�֦�㷨
int maxmin(int player,int cur_node[15][15],int alpha,int beta,int depth,int left,int right,int up,int down,int x,int y);

int main()
{
	int flag = 0; 
	int temp = 0;
	//�߽���Ϣ��Ϊ�˼��ټ��������ֻ�������������-5λ�õ���������+5λ�õķ����Լ�
	//��������-5��λ������������+5��λ�õķ��� 
	int left = 7;  //��߽� 
	int right = 7;  //�ұ߽� 
	int up = 7;  //�ϱ߽� 
	int down = 7;  //�±߽� 
	int win = 0; //ʤ����־
	int tree = 0; //�Ƿ�ʹ�ò�������־
	int depth = 0; //����������

	const char aipoint = 'o';  //ai���ӷ���
	const char playerpoint = 'X';  //������ӷ���
	
	printf("===============================================\n");
	printf("���㷨��Ϊ���԰�\n");
	printf("���ǽ�ͨ��������������ķ�ʽ����ҽ��ж�ս\n");
	printf("===============================================\n");
	printf("��ѡ���Ƿ�ʹ�ò�����(1.ʹ�� | 0.��ʹ��):");
	scanf("%d",&tree);
	if(tree == 1)
	{
		printf("�����벩���������(0~6):");
		scanf("%d",&depth);
	}
	printf("��ѡ��\n1���������\n2��AI����\n");
	printf("�����루1|2��");
	scanf("%d",&flag);
	
	printf("\n");


	
	while(1)
	{
		//���Դ��� 
		//printf("left:%d\n",left);
		//printf("right:%d\n",right);
		//printf("up:%d\n",up);
		//printf("down:%d\n",down);
		//================================ 

		//��������
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
					printf("  !");  //������
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
			printf("\nAI���ʤ�������ٽ�������");
			break;
		}
		else if(win == PLAYER)
		{
			printf("\n��ϲ�����ѻ��ʤ����");
			break;
		}
		else
		{
			//û���˻��ʤ������������
		}

		switch(flag)
		{
			case PLAYER:
				while(1)
				{
					printf("�����������꣺");
					scanf("%d",&player.x);
					printf("�����������꣺");
					scanf("%d",&player.y);
					if(IsNull(player.x,player.y))
					{
						if(player.x < 0 || player.x > 14 || player.y < 0 || player.y > 14)
						{
							printf("\n��ѡ���λ���������⣬������ѡ��\n");
						}
						else
						{
							SetBoard(player.x,player.y,PLAYER);
							break;
						}
					}
					else
					{
						printf("\n�˴��������ӣ�������ѡ��\n");
					}
				} 
				printf("\n��������Ϊ��(%d,%d)\n",player.x,player.y);
				
				if(player.y - 5 < left)  //���±߽���Ϣ 
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
				if(temp == 0)  //��һ������ 
				{
					ai.x = 7;
					ai.y = 7;
					temp = 1;
					SetBoard(ai.x,ai.y,AI);
				}
				else
				{
					ai = GetPosition(left,right,up,down,tree,depth);  //������� 
					SetBoard(ai.x,ai.y,AI);
				}
				printf("\nAI����Ϊ��(%d,%d)\n",ai.x,ai.y);
				
				if(ai.y - 5 < left)  //���±߽���Ϣ 
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
						//�˵��ֵͣ����� 
					}
				}
				else  //���ò�����
				{
					score = maxmin(AI,board,-1000000,1000000,depth,left,right,up,down,i,j);
					if(max <= score)
					{
						max = score;
						xy.x = i;
						xy.y = j;
					}
					else
					{
						//�˵��ֵͣ����� 
					}
				}
				
				//���Դ���
				//printf("��������(%d,%d):",i,j);
				//("%d\n",score); 
				//======================================
			}
			else
			{
				//�˵��������ӣ������ټ��� 
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

	GetRowArray(x,y,rowarray,ATTACK);  //��������� 
	GetListArray(x,y,listarray,ATTACK);  //��������� 
	GetRightFallingArray(x,y,rightfallingarray,ATTACK);  //��������� 
	GetLeftFallingArray(x,y,leftfallingarray,ATTACK);  //���Ʋ���� 
	
	//���Դ��� 
	/*
	printf("\n�����飺[");
	for(int i = 0; i < 13; i++)
	{
		printf("%d, ",rowarray[i]);
	}
	printf("]\n�����飺[");
	for(int i = 0; i < 13; i++)
	{
		printf("%d, ",listarray[i]);
	}
	printf("]\n�����飺[");
	for(int i = 0; i < 13; i++)
	{
		printf("%d, ",rightfallingarray[i]);
	}
	printf("]\nƲ���飺[");
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

	GetRowArray(x,y,rowarray,DEFENSE);  //��������� 
	GetListArray(x,y,listarray,DEFENSE);  //��������� 
	GetRightFallingArray(x,y,rightfallingarray,DEFENSE);  //��������� 
	GetLeftFallingArray(x,y,leftfallingarray,DEFENSE);  //���Ʋ���� 

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

	//���Դ���
	//printf("attackrowtype:%d\n",attackrowtype);
	//printf("attacklisttype:%d\n",attacklisttype);
	//printf("attackrightfallingtype:%d\n",attackrightfallingtype);
	//printf("attackleftfallingtype:%d\n",attackleftfallingtype);
	//printf("defenserowtype:%d\n",defenserowtype);
	//printf("defenselisttype:%d\n",defenselisttype);
	//printf("defenserightfallingtype:%d\n",defenserightfallingtype);
	//printf("defenseleftfallingtype:%d\n",defenseleftfallingtype);
	//===============================================
	//���Դ���
	//printf("\nrowtype:%d\n",rowtype);
	//printf("listtype:%d\n",listtype);
	//printf("rightfallingtype:%d\n",rightfallingtype);
	//printf("leftfallingtype:%d\n",leftfallingtype);
	//============================================== 
	
	attackscore = StruggleScore(attackrowtype,attacklisttype,attackrightfallingtype,attackleftfallingtype) + position[x][y];  //����λ�÷ֵĽ����÷�

	defensescore = StruggleScore(defenserowtype,defenselisttype,defenserightfallingtype,defenseleftfallingtype) + position[x][y];  //����λ�÷ֵķ����÷�

	return (attackscore + defensescore);
}

int IsNull(int x,int y)  //�ж��Ƿ������� 
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
		if(y+i > 14)  //�ж��Ƿ�Խ�ұ߽� 
		{
			rowarray[6+i] = SIDE;
		}
		else
		{
			rowarray[6+i] = board[x][y+i];
		}
		
		if(y-i < 0)  //�ж��Ƿ�Խ��߽� 
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
		if(x+i > 14)  //�ж��Ƿ�Խ�±߽� 
		{
			listarray[6+i] = SIDE;
		}
		else
		{
			listarray[6+i] = board[x+i][y];
		}
		
		if(x-i < 0)  //�ж��Ƿ�Խ�ϱ߽� 
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
		if(y+i > 14 || x+i > 14)  //�ж��Ƿ񳬹��±߽���ұ߽� 
		{
			rightfallingarray[6+i] = SIDE;
		}
		else
		{
			rightfallingarray[6+i] = board[x+i][y+i];
		}
		
		if(y-i < 0 || x-i < 0)  //�ж��Ƿ񳬹���߽���ϱ߽� 
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
		if(x+i > 14 || y-i < 0)  //�ж��Ƿ񳬹���߽���±߽� 
		{
			leftfallingarray[6-i] = SIDE;
		}
		else
		{
			leftfallingarray[6-i] = board[x+i][y-i];
		}
		
		if(y+i > 14 || x-i < 0)  //�ж��Ƿ񳬹��ұ߽���ϱ߽� 
		{
			leftfallingarray[6+i] = SIDE;
		}
		else
		{
			leftfallingarray[6+i] = board[x-i][y+i];
		}
	}
}

int Max(int row,int list,int rightfalling,int leftfalling)  //�ж��ĸ�ֵ�Ǹ���� 
{
	int max = 0;

	if(row >= list && row >= rightfalling && row >= leftfalling)  //��������������ͬ����᷵�ص�һ���� 
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
		//Ѱ�Ҷ��Լ���������� 
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
		if(GetMode(array,mode[i]))  //ƥ�䵽����һ��ģʽ 
		{
			if(type[i] >= score)
			{
				score = type[i];  // �ҵ��������� 
			}
		}
		else
		{
			//û��ƥ�䵽�κ�һ��ģʽ 
		}

		Invert(array);  //��ת���飬����ƥ�䣬�ٴ�ƥ��ģʽ
		
		if(GetMode(array,mode[i]))  //ƥ�䵽����һ��ģʽ 
		{
			if(type[i] >= score)
			{
				score = type[i];  // �ҵ��������� 
			}
		}
		else
		{
			//û��ƥ�䵽�κ�һ��ģʽ 
		}

		Invert(array);  //�ٴη�ת���飬ʹ�����Ϊԭ���ģ�˳��ƥ��
	}

	return score;
	
}

int GetMode(int array[],int mode[])
{
	int *parray = array;
	int *pmode = mode;
	int temp = 0;  //���˼��� 
	int flag = 0;  //�Ƿ��ҵ�ģʽ�ı�־ 
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
			if(*pmode == SIDE)  //����ģʽ�����β�����ñ�־������ѭ�� 
			{
				flag = 1;
				break;
			}
			if(*parray == *pmode)  //����ȣ���ԭ����ָ���1 
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
					sign = 1;  //����������ѭ��
					break;
				}
			}
			else
			{
                if(temp == 0)
                {
                    //�������κβ���
                }
				else if(temp == 1)  
				{
                    parray--;
					//��������£�ԭ����ָ�벻��Ҫ���� 
					if(*parray == SIDE)
					{
						sign = 1;  //����������ѭ��
					}
				}
				else
				{
					parray = parray - temp + 1;
				}
				break;
			}
		}
		if(flag == 1 || sign == 1)  //�ҵ�ƥ�䣬�˳���ѭ�� 
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
			GetRowArray(i,j,rowarray,JUDGE);  //��������� 
			GetListArray(i,j,listarray,JUDGE);  //��������� 
			GetRightFallingArray(i,j,rightfallingarray,JUDGE);  //��������� 
			GetLeftFallingArray(i,j,leftfallingarray,JUDGE);  //���Ʋ���� 

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

//α���룬Ҫ�޸�

// player = 2 ��ʾ�ֵ�AI�� player = 1 ��ʾ�ֵ����  
// cur_node ��ʾ��ǰ����(���)  
int maxmin(int player,int cur_node[15][15],int alpha,int beta,int depth,int left,int right,int up,int down,int x,int y)  
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

    if(depth == 0)  //�ﵽ�ս���� 
	{
		return GetScore(x,y); //�þ�����Ĺ���ֵ f  
	}

    if(player == AI) // �ֵ�AI��  
	{
		for(int i = left; i <= right; i++)
		{
			for(int j = up; j <= down; j++)
			{
				if(IsNull(i,j))
				{
					next_node[i][j] = AI; // ������ǰ���� cur_node �������Ӿ���  

					if(j - 5 < left)  //���±߽���Ϣ 
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

					val = maxmin(PLAYER, next_node, alpha, beta,depth - 1,left,right,up,down,i,j); // ���²����ľ��潻���Է����Է�����һ���¾���Ĺ���ֵ  
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
    else // �ֵ������  
	{
		for(int i = left; i <= right; i++)
		{
			for(int j = up; j <= down; j++)
			{
				if(IsNull(i,j))
				{
					next_node[i][j] = PLAYER; // ������ǰ���� cur_node �������Ӿ��� 

					if(j - 5 < left)  //���±߽���Ϣ 
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

					val = maxmin(AI, next_node, alpha, beta,depth - 1,left,right,up,down,i,j); // ���²����ľ��潻���Է����Է�����һ���¾���Ĺ���ֵ  
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