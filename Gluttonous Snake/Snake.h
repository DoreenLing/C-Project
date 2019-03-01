//--------------------------------------------------------------------
// 文件名:        Snake.h
// 内  容:        蛇的定义文件
// 说  明:        定义蛇的产生和移动
// 创建日期:      2018年6月10日
//--------------------------------------------------------------------
#include <vector>
#include "Console.h"
#include "Window.h"
#include "GameDefine.h"
using namespace std;

struct MySnake
{
	int x, y;
};



class Snake
{
public:
	Snake(Console & console, COORD coordinate);
	void InitSnake(int keys[KeyNum], char keyDesc[KeyNum][5]);//初始化蛇
	int GetLevel() const;//获得游戏等级
	bool MessageProc(const Cmd cmd);//消息处理
	void DrawScoreLevel();//绘制得分
	void DrawGameOver();//绘制游戏结束界面
	bool IsFit(int x, int y);//蛇头是否合法
	bool IsRun();
	void Move(int x, int y);//蛇的移动
	void LeftMove();//左移
	void RightMove();//右移
	void DownMove();//下移
	void UpMove();//上移
	void Produce_Food();//产生食物
	bool Eat_Food(int x, int y);//吃食物
	int Model_Slect();//模式选择
	void Automatic_Road(int data[ROWS][COLS], MySnake &Start, MySnake &End);//自动寻路
	void Automatic_run();//自动运行
	vector<MySnake>  Found_short(int data[ROWS][COLS], MySnake &Start, MySnake &End);//寻找最短路径

private:
	char bg[GAME_HIGHT * GAME_WIDTH + 1];

	// 延续时间
	DWORD m_voiceDuration;

	// 控制按键
	int m_keys[KeyNum];

	// 控制按键的描述
	char m_keyDesc[KeyNum][5];

	// 游戏是否结束
	bool m_gameover;

	// 游戏暂停
	bool m_pause;

	// 游戏得分
	int m_score;

	// 游戏速度
	int m_speed;

	// 游戏数据(蛇身的存放数据)
	int m_data[ROWS][COLS];

	//食物的坐标
	MySnake food;

	//蛇的位置
	MySnake position[ROWS*COLS];
	//蛇头的坐标
	int head;
	//蛇尾的坐标
	int tail;

	// 当前方向
	int m_currentDir;

	// 窗口
	Window win;
};
