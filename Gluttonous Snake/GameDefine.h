//--------------------------------------------------------------------
// 文件名:        GameDefine.h
// 内  容:        游戏定义文件
// 说  明:        定义游戏的一些常量，比如窗口大小等
// 创建日期:      2018年6月7日
//--------------------------------------------------------------------

#pragma once
#include <windows.h>

// 高度
const SHORT GAME_HIGHT = 21;

// 宽度
const SHORT GAME_WIDTH = 38;

// 方块的行数
const SHORT ROWS = 16;

// 方块的列数
const SHORT COLS = 17;

// 运动中的颜色
const WORD COLOR_MOVE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

// 食物的颜色
const WORD COLOR_FOOD = FOREGROUND_GREEN;

// 分数的颜色
const WORD COLOR_SCORE = FOREGROUND_RED| FOREGROUND_BLUE;

// 空白处的颜色
const WORD COLOR_BLANK = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

// 吃一个食物的得分
const int ONE_FOOD_SCORE = 100;

// 最大分值
const int MAX_SCORE = 99999;

// 得分满，加一个速度
const int SPEED_ADD_SCORE = 10000;

// 休眠间隔时间(毫秒)
const int SLEEP_TIME = 300;

const int TIME_OUT = 1000;
// 游戏按键对应的索引
enum KeyIndex
{
	GameBegin = 0,    // 游戏开始
	GamePause,        // 游戏暂停
	Up,                // 方向键-上
	Left,            // 方向键-左
	Right,            // 方向键-右
	Down,            // 方向键-下
	Esc,
	KeyNum,            // 按键总数
};


// 对应的键值(这个需要查表或者自己实验所得)
enum KeyMap
{
	KEY_ENTER = 13,
	KEY_UP = 72,
	KEY_LEFT = 75,
	KEY_RIGHT = 77,
	KEY_DOWN = 80,
	KEY_INTER = 8,
	KEY_ESC = 27,
};

// 游戏操作定义
enum Cmd
{
	CMD_BEGIN,        // 游戏开始
	CMD_PAUSE,        // 游戏暂停
	CMD_UP,          // 方块上移
	CMD_LEFT,        // 方块左移
	CMD_RIGHT,        // 方块右移
	CMD_DOWN,        // 方块下移
	CMD_QUIT,        // 游戏退出
};


// 游戏背景
const char Background[GAME_HIGHT * GAME_WIDTH + 1] =
"┏━━━━━━━━━━━━━━━━━┓"
"┃■■■■■■■■■■■■■■■■■┃"
"┃■■■■■■■■■■■■■■■■■┃"
"┃■■■■■■■■■■■■■■■■■┃"
"┃■■■■■■■■■■■■■■■■■┃"
"┃■■■■■■■■■■■■■■■■■┃"
"┃■■■■■■■■■■■■■■■■■┃"
"┃■■■■■■■■■■■■■■■■■┃"
"┃■■■■■■■■■■■■■■■■■┃"
"┃■■■■■■■■■■■■■■■■■┃"
"┃■■■■■■■■■■■■■■■■■┃"
"┃■■■■■■■■■■■■■■■■■┃"
"┃■■■■■■■■■■■■■■■■■┃"
"┃■■■■■■■■■■■■■■■■■┃"
"┃■■■■■■■■■■■■■■■■■┃"
"┃■■■■■■■■■■■■■■■■■┃"
"┃━━━━━━━━━━━━━━━━━┃"
"┃开始 = 回车 退出 = ESC┃ 速度 得分┃"
"┃上移 =  ↑  下移 = ↓ ┃┏━━━━┓"
"┃左移 =  ←  右移 = → ┃┃0  00000┃"
"┗━━━━━━━━━━━┛┗━━━━┛";


// 游戏开始时的X坐标
const unsigned int GameStartX = 38;

// 游戏开始时的Y坐标
const unsigned int GameStartY = 21;


