#include <stdlib.h>   
#include <time.h>     
#include <conio.h>    
#include <windows.h>  
#include <stdio.h>



#define WIDTH 10	
#define HEIGHT 20   

#define BOARD_X 4
#define BOARD_Y 2

#define DELAY 100
	int u, b;

enum ControlKeys
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32
};

static int score = 0;
static int level = 1;
static int speed = 180;
static bool collision = false;
static int next;
static COORD shadowArr = { 0,0 };
static COORD temp;
int board[HEIGHT + 1][WIDTH + 2] = { 0, };


int blocks[28][4][4] =  // 4*4 가 7개
{
	// ㅣ
	{
{ 0, 1, 0, 0 },
{ 0, 1, 0, 0 },
{ 0, 1, 0, 0 },
{ 0, 1, 0, 0 }
	},
	{
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 1, 1, 1, 1 },
{ 0, 0, 0, 0 }
	},
	{
{ 0, 1, 0, 0 },
{ 0, 1, 0, 0 },
{ 0, 1, 0, 0 },
{ 0, 1, 0, 0 }
	},
	{
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 1, 1, 1, 1 },
{ 0, 0, 0, 0 }
	},
	//ㅁ
	{
{ 1, 1, 0, 0 },
{ 1, 1, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 }
	},
	{
{ 1, 1, 0, 0 },
{ 1, 1, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 }
	},
	{
{ 1, 1, 0, 0 },
{ 1, 1, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 }
	},
	{
{ 1, 1, 0, 0 },
{ 1, 1, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 }
	},

	// ㅗ
	{
{ 0, 0, 0, 0 },
{ 0, 1, 0, 0 },
{ 1, 1, 1, 0 },
{ 0, 0, 0, 0 }
	},
	{
{ 0, 0, 0, 0 },
{ 0, 1, 0, 0 },
{ 1, 1, 0, 0 },
{ 0, 1, 0, 0 }
	},
	{
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 1, 1, 1, 0 },
{ 0, 1, 0, 0 }
	},
	{
{ 0, 0, 0, 0 },
{ 0, 1, 0, 0 },
{ 0, 1, 1, 0 },
{ 0, 1, 0, 0 }
	},

//니은 역반향
	{
{ 0, 0, 0, 0 },
{ 0, 0, 1, 0 },
{ 1, 1, 1, 0 },
{ 0, 0, 0, 0 }
	},
	{
{ 0, 1, 1, 0 },
{ 0, 0, 1, 0 },
{ 0, 0, 1, 0 },
{ 0, 0, 0, 0 }
	},
	{
{ 1, 1, 1, 0 },
{ 1, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 }
	},
	{
{ 1, 0, 0, 0 },
{ 1, 0, 0, 0 },
{ 1, 1, 0, 0 },
{ 0, 0, 0, 0 }
	},

//ㄴ
		{
{ 0, 0, 0, 0 },
{ 1, 0, 0, 0 },
{ 1, 1, 1, 0 },
{ 0, 0, 0, 0 }
		},
		{
{ 0, 0, 1, 0 },
{ 0, 0, 1, 0 },
{ 0, 1, 1, 0 },
{ 0, 0, 0, 0 }
		},
		{
{ 1, 1, 1, 0 },
{ 0, 0, 1, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 }
		},
		{
{ 1, 1, 0, 0 },
{ 1, 0, 0, 0 },
{ 1, 0, 0, 0 },
{ 0, 0, 0, 0 }
		},

//N
		{
{ 0, 0, 0, 0 },
{ 0, 1, 1, 0 },
{ 1, 1, 0, 0 },
{ 0, 0, 0, 0 }
		},
		{
{ 0, 1, 0, 0 },
{ 0, 1, 1, 0 },
{ 0, 0, 1, 0 },
{ 0, 0, 0, 0 }
		},
		{
{ 0, 0, 0, 0 },
{ 0, 1, 1, 0 },
{ 1, 1, 0, 0 },
{ 0, 0, 0, 0 }
		},
		{
{ 0, 1, 0, 0 },
{ 0, 1, 1, 0 },
{ 0, 0, 1, 0 },
{ 0, 0, 0, 0 }
		},

//Z
		{
{ 0, 0, 0, 0 },
{ 1, 1, 0, 0 },
{ 0, 1, 1, 0 },
{ 0, 0, 0, 0 }
		},
		{
{ 0, 0, 1, 0 },
{ 0, 1, 1, 0 },
{ 0, 1, 0, 0 },
{ 0, 0, 0, 0 }
		},
		{
{ 0, 0, 0, 0 },
{ 1, 1, 0, 0 },
{ 0, 1, 1, 0 },
{ 0, 0, 0, 0 }
		},
		{
{ 0, 0, 1, 0 },
{ 0, 1, 1, 0 },
{ 0, 1, 0, 0 },
{ 0, 0, 0, 0 }
		},
};
//int ***tempBlock = *blocks[];

   
void NoCursor(bool blnCursorVisible); // 커서 없애줌
void SetCursor(int cursorLeft, int cursorTop); //커서 정해줌
COORD GetCur(void); // 커서 어딨는지 보여줌
void Box(void); //틀딱
bool CanPositionedAt(int rotation, int move1, int move2); //벽하고 충돌체크
void WriteBlock(int rotation);// 블록 생성
void BoardInit(int n, int move1, int move2); // 불록 쌓아올릴때 충돌
void MoveBlock(int column); // 선이 지워졌을시 한칸 밑으로 이동
void ScoreUpdate(void); //점수
void RemoveLine(void);//줄한칸이 다 지워졌는지 확인하고 그 다음에 선을 지우고 내려줌
void ClearBlock(int rotation, int move1, int move2); //블록을 지워주고 다시 만듬 // 블록을 움직여줌
void update(void);//게임돌아감
void NextBlock();//
void Shadow(int rotation);
bool ShadowCheck(int rotation, int move1, int move2, COORD cursor);
void Board();

void EndGame();//끝

int main()
{

	NoCursor(false);


	ScoreUpdate();

	update();


	EndGame();

}

bool CanPositionedAt(int rotation, int move1, int move2) 
{
	int x, y;
	int arrX, arrY; 
	COORD pos = GetCur();

	arrX = pos.X + move1;
	arrY = pos.Y + move2;

	arrX = (arrX / 2) - 2;
	arrY = arrY - BOARD_Y;

	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			if ((blocks[rotation][y][x] == 1) && board[arrY + y][arrX + x] == 1)
				return false;  
		}
	}
	return true;  
}


void WriteBlock(int rotation) 
{
	int i, j;
	COORD cursor = GetCur();
	
	if (CanPositionedAt(rotation, 0, 0) == true)
	{
		for (i = 0; i < 4; i++)        
		{
			for (j = 0; j < 4; j++)    
			{
				SetCursor(cursor.X + (j * 2), cursor.Y + i);
				if (blocks[rotation][i][j] == 1)
				{
					printf("■");
				}
			}
		}
		SetCursor(cursor.X, cursor.Y);
	}
}


void BoardInit(int n, int move1, int move2)
{
	COORD pos = GetCur();
	
	int arrX = pos.X + move1;  
	int arrY = pos.Y + move2;  
	int x, y;
	
	
	arrX = arrX / 2 - 2; 
	arrY = arrY - 2;     
	
	
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			if (blocks[n][y][x] == 1)
			{
				board[arrY + y][arrX + x] = 1;
				//Board();
				collision = true;
			}
		}
	}
}


void MoveBlock(int column) 
{
	int y, x;


	for (y = column; y >= 0; y--)
	{
		for (x = 1; x <= 10; x++)
		{
			board[y][x] = board[y - 1][x];
		}
	}

	for (x = 1; x <= 10; x++)
		board[0][x] = 0;


	for (y = 1; y <= 19; y++)
	{
		for (x = 1; x <= 10; x++)
		{
			SetCursor((BOARD_X)+x * 2 + 1, y + BOARD_Y);
			if (board[y][x] == 1)
				printf("■");
			else
				printf("  ");
		}
	}
}


void RemoveLine(void)
{
	int i;
	int x, y;
	int z = 0;

	for (y = 19; y >= 1; y--)
	{
		for (z = 0; z < 4; z++)
		{
			i = 0;
			for (x = 1; x < 11; x++)
			{
				if (board[y][x] == 1)
				{
					i++;
					if (i == 10)
					{
						for (x = 1; x < 11; x++)
						{
							SetCursor((x + 2) * 2, y + 2);
							printf("  ");
						}
					
						ScoreUpdate();
						MoveBlock(y);
					}
				}
			}
		}
	}
}


void ClearBlock(int rotation, int move1, int move2) 
{
	int x, y;
	
	COORD cursor = GetCur();
	
	if (CanPositionedAt(rotation, move1, move2) == true)
	{
		for (y = 0; y < 4; y++)
		{
			for (x = 0; x < 4; x++)
			{
				SetCursor(cursor.X + (x * 2), cursor.Y + y);
				if (blocks[rotation][y][x] == 1)
					printf(" ");
			}
		}
		SetCursor(cursor.X + move1, cursor.Y + move2);
	}
}


void update(void)
{

	int n;
	int kb;
	int c = 2;
	for (n = 0; n < 28; n++)
		srand((unsigned)time(0));

	n = rand() % 7;

	n = n * 4;
	NextBlock();

	while (1)
	{
		if (collision)
		{
			collision = false;
			n = next;
			NextBlock();

			SetCursor(temp.X, temp.Y);
		}

		SetCursor(13, 2);
		if (CanPositionedAt(n, 0, 0) == false)
			break;                
		while (1)
		{
			int ww = 0;
			int k = 0;
			
			Box();
			COORD temp = GetCur();
			Board();
			SetCursor(temp.X, temp.Y);
			Shadow(n);
		
			while (!_kbhit())
			{
				
			
				WriteBlock(n);
		
				Sleep(DELAY + speed);
				if (CanPositionedAt(n, 0, 1) == false)
				{
					ww = 1;
					BoardInit(n, 0, 0);
					RemoveLine();
					

					break;
				}
				ClearBlock(n, 0, 1);  
			}
			
			if (ww == 1)
				break;

			kb = _getch();

		
			switch (kb)
			{
			case LEFT:
				ClearBlock(n, -2, 0);
				WriteBlock(n);
				Shadow(n);
				break;
			case RIGHT:
				ClearBlock(n, 2, 0);
				WriteBlock(n);
				Shadow(n);
				break;
			case UP:
				k = n / 4;
				k *= 4;

				if ((n + 1) <= (k + 3))
				{
					k = n + 1;
				}

				if (CanPositionedAt(k, 0, 0) == true)
				{
					ClearBlock(n, 0, 0);
					n = k;
					break;
				}
				Shadow(n);
				break;
			case DOWN:
				ClearBlock(n, 0, 2);
				//Shadow(n);

				break;
			case SPACE:
				while (1)
				{
					ClearBlock(n, 0, 1);
					if (CanPositionedAt(n, 0, 1) == false)
					{
						WriteBlock(n);
						BoardInit(n, 0, 0);
						break;
					}
				}

			default: break;
			}

		}
	}
}


void NoCursor(bool blnCursorVisible)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = blnCursorVisible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

//[2] 현재 콘솔 내의 커서 위치를 설정
void SetCursor(int cursorLeft, int cursorTop)
{
	int posX = cursorLeft;
	int posY = cursorTop;

	COORD pos = { posX, posY };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//[3] 커서의 현재 위치 정보 얻기
COORD GetCur(void)
{
	COORD cursor;
	CONSOLE_SCREEN_BUFFER_INFO cursorInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursor.X = cursorInfo.dwCursorPosition.X;
	cursor.Y = cursorInfo.dwCursorPosition.Y;
	return cursor;
}

void Box(void)
{
	int x, y;
	COORD cursor = GetCur();
	for (x = 1; x <= WIDTH + 1; x++)
	{
		board[HEIGHT][x] = 1; 
		SetCursor((BOARD_X)+x * 2, BOARD_Y + HEIGHT);  
		printf("■");
	}

	for (y = 0; y < HEIGHT + 1; y++)
	{
		board[y][0] = 1; 
		SetCursor(BOARD_X, BOARD_Y + y);
		printf("■");

	}

	for (y = 0; y < HEIGHT + 1; y++)
	{
		board[y][WIDTH + 1] = 1; 
		SetCursor(BOARD_X + (WIDTH + 2) * 2, BOARD_Y + y);
		printf("■");

	}
	SetCursor(cursor.X, cursor.Y);
}

void ScoreUpdate(void)
{
	score += 10;
	if (score % 30 == 0)
	{
		level += 1;
		speed -= 30; // 가속
	}

	SetCursor(40, 5);
	printf("Lv: %d\n", level);
	SetCursor(40, 7);
	printf("Score: %d\n", score);

	if (level == 10)
	{
		SetCursor(40, 15);
		printf("게임 클리어");
		getchar();
		exit(1);
	}
}

void EndGame()
{
	SetCursor(10, 8);
	printf("게임 종료");
	getchar();
	system("cls");
	Sleep(1000);
	exit(1);
}

void  NextBlock()
{

	int n;
	for (n = 0; n < 28; n++)
		srand((unsigned)time(0));

	COORD Boxcursor = { 40,10 };
	for (int i = 0; i < 8; i++)        
	{
		for (int j = 0; j < 8; j++)    
		{
			SetCursor(Boxcursor.X + (j * 2), Boxcursor.Y + i);
			if (i == 0 || i == 7 || j == 0 || j==7 )
			printf("■");
		}
	}
	COORD cursor = {45,12};
	

	n = rand() % 7;

	n = n * 4;
	int i, j;
	for (i = 0; i < 4; i++)        
	{
		for (j = 0; j < 4; j++)    
		{
			SetCursor(cursor.X + (j * 2), cursor.Y + i);

				printf("  ");
			
		}
	}
	for (i = 0; i < 4; i++)        
	{
		for (j = 0; j < 4; j++)    
		{
			SetCursor(cursor.X + (j * 2), cursor.Y + i);
			if (blocks[n][i][j] == 1)
			{
				printf("■");
			}
		}
	}
	next = n;
}

void Shadow(int rotation)
{
	int i, j;

	COORD Mycursor = GetCur();
	COORD cursor = GetCur();
	for (int j = 0; j < HEIGHT; j++)
	{
		
		
		if (ShadowCheck(rotation, 0, j, Mycursor) == false)
		{
			Mycursor.Y += j - 1;
			
			break;
		}
		

	}
	for (i = 0; i < 4; i++)       
	{
		for (j = 0; j < 4; j++)    
		{
			SetCursor(shadowArr.X + (j * 2), shadowArr.Y + i);
			if (shadowArr.X == cursor.X && shadowArr.Y == cursor.Y)
			{
				
			}
			else
			{
				if (blocks[rotation][i][j] == 1)
				{
					printf(" ");
				}


			}
		}
	}


		for (i = 0; i < 4; i++)        
		{
			for (j = 0; j < 4; j++)    
			{
				SetCursor(Mycursor.X + (j * 2), Mycursor.Y + i);
				if (blocks[rotation][i][j] == 1)
				{
					printf("O");
				}

				
			}
		}
		shadowArr = Mycursor;
		SetCursor(cursor.X, cursor.Y);
	
}


bool ShadowCheck(int rotation, int move1, int move2, COORD cursor)
{
	int x, y;
	int arrX, arrY; 
	COORD pos = cursor;

	arrX = pos.X + move1;
	arrY = pos.Y + move2;

	arrX = (arrX / 2) - 2;
	arrY = arrY - BOARD_Y;

	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			if ((blocks[rotation][y][x] == 1) && board[arrY + y][arrX + x] == 1)
			{
				arrY = arrY;
				arrX = arrX;
				temp = pos;
				return false;  
			}
		}
	}
	return true;  
}

void Board()
{
	COORD temp = GetCur();
	for (int y = 1; y <= 19; y++)
	{
		for (int x = 1; x <= 10; x++)
		{
			SetCursor((BOARD_X)+x * 2 + 1, y + BOARD_Y);
			if (board[y][x] == 1)
				printf("■");
			else
				printf("  ");
		}
	}
	SetCursor(temp.X, temp.Y);
}