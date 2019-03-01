#include "Snake.h"
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <queue>
//#include<vector>
//using namespace std;

MySnake Director1[4] = { { 0,-1 },{ 1,0 },{ 0,1 },{ -1,0 } };//建立方向数组

int Automatic_flag = 0;


Snake::Snake(Console & console, COORD coordinate)
{
	// 创建一个矩形
	SMALL_RECT rect = { coordinate.X, coordinate.Y, coordinate.X + GAME_WIDTH, coordinate.Y + GAME_HIGHT };

	// 初始化这个窗口
	win.Init(console, rect);
}

/// \brief 初始化游戏
/// \param keys 按键
/// \param keyDesc 按键描述
void Snake::InitSnake(int keys[KeyNum], char keyDesc[KeyNum][5])
{
	// 初始化游戏的数据
	memcpy(m_keys, keys, sizeof(m_keys));
	memcpy(m_keyDesc, keyDesc, sizeof(m_keyDesc));
	memcpy(bg, Background, sizeof(bg));

	m_gameover = false;
	m_pause = true;
	m_score = 0;
	m_speed = 0;

	// 方块数据部分置0
	memset(m_data, 0, sizeof(m_data));

	// 设置随机种子
	srand((unsigned)time(NULL));

	// 产生食物
	food.x = (rand() % COLS + 1) * 2;
	food.y = rand() % ROWS + 1;

	//初始化小蛇，蛇头为2，蛇身为1
	head = 1; tail = 0;
	position[head].x = 4;
	position[head].y = 5;
	position[tail].x = 4;
	position[tail].y = 4;
	m_data[position[head].x][position[head].y] = 1;
	m_data[position[tail].x][position[tail].y] = 1;

	m_currentDir = 0;

	COORD coord = { 0, 0 };

	win.Output(bg + 0, coord, COLOR_SCORE, GAME_WIDTH);

	for (int i = 1; i < ROWS; ++i)
	{
		coord = { 0,(SHORT)i };
		win.Output(bg + GAME_WIDTH * i + 0, coord, COLOR_SCORE, 2);
		coord = { 2,(SHORT)i };
		win.Output(bg + GAME_WIDTH * i + 2, coord, COLOR_BLANK, 34);
		coord = { 36, (SHORT)i };
		win.Output(bg + GAME_WIDTH * i + 38, coord, COLOR_SCORE, 2);
	}

	coord = { 0, 20 };
	win.Output(bg + GAME_WIDTH * 20, coord, COLOR_SCORE, GAME_WIDTH);

	for (int i = ROWS; i < 21; ++i)
	{
		coord = { 0,(SHORT)i };
		win.Output(bg + GAME_WIDTH * i + 0, coord, COLOR_SCORE, 38);
	}

	COORD coord1 = { SHORT(position[head].x * 2), SHORT( position[head].y) };
	win.Output("●", coord1, COLOR_MOVE, 2);
	COORD coord2 = { SHORT(position[tail].x * 2), SHORT(position[tail].y) };
	win.Output("●", coord2, COLOR_MOVE, 2);
	// 绘制下一个将要出现的食物
	//Produce_Food();
}

/// \brief 绘制下一个将要出现的食物
void Snake::Produce_Food()
{
	//随机种子
	COORD coord = { 0, 0 };
	srand(unsigned(time(NULL)));
	bool flag = false;
	do {
		food.x = (rand() % COLS+1)*2;
		food.y = rand() % (ROWS-1);
		if (food.x <= (COLS - 2) && food.x >= 2 && food.y <= ROWS - 1 && food.y >= 1 && m_data[food.x/2][food.y] != 1) {
			coord = { SHORT(food.x), SHORT(food.y) };
			win.Output("★", coord, COLOR_FOOD, 2);
			flag = false;
		}
		else flag = true;
	} while (flag == true);
}

/// \brief 获取当前等级
int Snake::GetLevel() const
{
	return m_speed;
}

/// \brief 绘制得分
void Snake::DrawScoreLevel()
{
	char tmp[6];
	COORD coord = { 0, 0 };
	sprintf_s(tmp, "%05d", food.x);
	coord = { 31, 19 };
	win.Output(tmp, coord, COLOR_SCORE, 5);
	sprintf_s(tmp, "%1d", m_speed);
	coord = { 28, 19 };
	win.Output(tmp, coord, COLOR_SCORE, 1);
}

/// \brief 绘制游戏结束界面
void Snake::DrawGameOver()
{
	system("cls");
	system("color 24");
	cout << endl; cout << endl;
	cout << "*************************************" << endl;
	cout << endl; cout << endl; cout << endl; cout << endl;
	cout << "           GAME OVER                " << endl;
	cout << endl; cout << endl;
	cout << "           GO TO STUDY              " << endl;
	cout << endl; cout << endl; cout << endl; cout << endl;
	cout << "*************************************" << endl;
}

/// \brief 蛇头是否合法
/// \prama x x轴坐标
/// \prama y y轴坐标
/// \notice x,y 均指下一步的前进位置并不是当前位置
bool Snake::IsFit(int x, int y)
{
	if (x > COLS  || x<=0 || y>ROWS-1 || y <=0 || m_data[x][y] == 1) {
		return false;
	}
	return true;
}
/// \brief 蛇的移动
void Snake::Move(int x, int y)
{
	COORD coord = { 0,0 };
	if (IsFit(x, y)) {

		//更新蛇尾坐标
		m_data[position[tail].x][position[tail].y] = 0;
		coord = { SHORT(position[tail].x * 2), SHORT(position[tail].y) };
		win.Output("■", coord, COLOR_BLANK, 2);
		tail = (tail + 1) % ((ROWS - 1)*(COLS - 2));

		//跟新蛇头坐标
		head = (head + 1) % ((ROWS - 1)*(COLS - 2));
		position[head].x = x;
		position[head].y = y;
		m_data[position[head].x][position[head].y] = 1;
		coord = { SHORT(position[head].x * 2), SHORT(position[head].y) };
		win.Output("●", coord, COLOR_MOVE, 2);
			
	}
	else { DrawGameOver(); cout << "Game over 1"; }
}

/// \brief 向左转
void Snake::LeftMove()
{
	int x, y;
	x = position[head].x-1;
	y = position[head].y;
	//Eat_Food(x,y);
	if(!Eat_Food(x, y))
		Move(x, y);
	
}

/// \brief 向右转
void Snake::RightMove()
{
	int x, y;
	x = position[head].x + 1;
	y = position[head].y;
	if (!Eat_Food(x, y))
		Move(x, y);
}
/// \brief 向上转
void Snake::UpMove()
{
	int x, y;
	x = position[head].x;
	y = position[head].y-1;
	if (!Eat_Food(x, y))
		Move(x, y);
}
/// \brief 向下转
void Snake::DownMove()
{
	int x, y;
	x = position[head].x ;
	y = position[head].y+1;
	if (!Eat_Food(x, y))
		Move(x, y);
}
/// \brief 获得食物
bool Snake::Eat_Food(int x, int y)
{
	//吃米
	int score;
	COORD coord = { 0,0 };
	if (x*2 == food.x&&y == food.y) {
		//更新蛇头
		head = (head + 1) % ((ROWS - 1)*(COLS - 2));
		position[head].x = x;
		position[head].y = y;
		m_data[position[head].x][position[head].y] = 1;
		coord = { SHORT(position[head].x * 2), SHORT(position[head].y) };
		win.Output("●", coord, COLOR_MOVE, 2);

		// 绘制下一个将要出现的食物
		Produce_Food();

		//更新分数
		score = ONE_FOOD_SCORE;
		m_score += score;
		if (m_score > MAX_SCORE) {
			m_score = MAX_SCORE;
			m_speed = m_score / SPEED_ADD_SCORE;
		}
		DrawScoreLevel();
		return true;
	}
	else return false;
}

/// \brief 是否正在运行游戏
bool Snake::IsRun()
{
	return !m_gameover && !m_pause;
}

/// \brief 消息处理
/// \param key 按键
/// \return 游戏结束返回false
bool Snake::MessageProc(const Cmd cmd)
{
	int const key = m_keys[cmd];
	// 游戏结束
	if (m_gameover)
	{
		// 游戏重新开始
		if (m_keys[GameBegin] == key)
		{
			InitSnake(m_keys, m_keyDesc);
			return true;
		}

		return false;
	}

	// 游戏暂停
	if (m_pause)
	{
		// 游戏重新开始
		if (m_keys[GameBegin] == key)
		{
			m_pause = false;
			Produce_Food();
		//	DownMove();
		}

		return true;
	}

		if (m_keys[GamePause] == key)        // 按下暂停键
		{
			m_pause = true;
		}
		else if (m_keys[Up] == key)            // 按下上行键
		{
			UpMove();
		}
		else if (m_keys[Left] == key)        // 按下方向左键
		{
			LeftMove();
		}
		else if (m_keys[Right] == key)        // 按下方向右键
		{
			RightMove();
		}
		else if (m_keys[Down] == key)        // 按下方向下键
		{
			DownMove();
		}

	return true;
}

/// \brief 模式选择
int Snake::Model_Slect()
{
	int fg = 0;
	system("cls");
	system("color f2");
	cout << endl; cout << endl;
	cout << "*************************************" << endl;
	cout << endl; cout << endl;
	cout << "           Model Slect                " << endl;
	cout << endl;
	cout << "           GO TO Operate              " << endl;
	cout << "           Please Input 1: ";
	cout << endl;
	cout << "           GO TO Automatic              " << endl;
	cout << "           Please Input 2: "; 
    cout << endl; cout << endl;
	cout << "*************************************" << endl;
	cout << " If you don't to slect a Model,";
	cout << "Please close the window.!!! "<<endl;
	cout << "Input: "; cin >> fg;
	return fg;
}

/// \brief 寻找最短路径
/// \param Start 开始点（蛇头）
/// \return End 结束点（食物）
vector<MySnake> Snake::Found_short(int data[ROWS][COLS], MySnake &Start, MySnake &End)
{
	vector<MySnake>Path;
	//标定路线
	MySnake here, nbr; queue<MySnake>Q;
	here.x = Start.x; here.y = Start.y;
	//标定开始的值为s，与0,1区分开来
	data[here.x][here.y] = 2;
	do {
		for (int i = 0; i< 4; i++) {
			if (here.x > 0 && here.y > 0&&here.x<17&&here.y<16) {
				nbr.x = here.x + Director1[i].x;
				nbr.y = here.y + Director1[i].y;
			}
			if (data[nbr.x][nbr.y] == 0) {
				data[nbr.x][nbr.y] = data[here.x][here.y] + 1;
				if (nbr.x == End.x&&nbr.y == End.y)//退出内循环
					break;
				Q.push(nbr);//相邻位置进队
			}
		}
		if (nbr.x == End.x&&nbr.y == End.y)//退出外循环
			break;
		if (Q.empty()) {
			Automatic_flag = 1;
			return Path;
		}

		//出队，将其赋给当前位置
		here = Q.front();		
		Q.pop();

	} while (1);

	//清空队列
	queue<MySnake> empty;
	swap(empty, Q);
	
	//从终点回溯，寻找最短路径
	here.x = End.x;//终点的坐标赋值给当前坐标
	here.y = End.y;
	//将当前坐标存入路线
	Path.push_back(here);
	do {
		for (int i = 0; i < 4; i++) {
			nbr.x = here.x + Director1[i].x;
			nbr.y = here.y + Director1[i].y;
			if (data[nbr.x][nbr.y] == data[here.x][here.y] - 1)
				break;
		}
		here.x = nbr.x;
		here.y = nbr.y;
		//将当前坐标存入路线
		Path.push_back(here);
	} while (here.x != Start.x&&Start.y);
	return Path;
}

/// \brief 自动寻路
/// \param data 路径
/// \param Syart 蛇头的位置
/// \return End 结束点（食物）
void Snake::Automatic_Road(int data[ROWS][COLS], MySnake &Start,MySnake &End)
{
	int x = 0, y = 0;
	MySnake Road1, Road2;
	//将蛇头的值赋给Road1
	Road1 = Start;
	//获取路径
	vector<MySnake>Automatic_Path;
	Automatic_Path = Found_short(data,Start,End);

	while (!Automatic_Path.empty()) {
		//取出路径
		Road2 = Automatic_Path.back();
		Automatic_Path.pop_back();

		//判断运动方向
		x = Road2.x - Road1.x;
		y = Road2.y - Road1.y;
		Sleep(SLEEP_TIME);
		if (x == 1 && y == 0)
			RightMove();
		if (x == -1 && y == 0)
			LeftMove();
		if (x == 0 && y == -1)
			UpMove();
		if (x == 0 && y == 1)
			DownMove();
		Road1 = Road2;
	}
}   

/// \brief 自动运行
void Snake::Automatic_run()
{	
	//产生食物
	
	//if (Automatic_flag != 1) 

		//低昂一开始和结束点
		MySnake Start, End;
		Start.x = position[head].x;
		Start.y = position[head].y;
		End.x = food.x / 2;
		End.y = food.y;
       // cout << End.x <<"gh"<< End.y;
		//复制矩阵，保留原始数据
		int data[ROWS][COLS];
		memcpy(data, m_data, sizeof(data));

		//自动寻路
		Automatic_Road(data, Start, End);
		//Produce_Food();
	
}
