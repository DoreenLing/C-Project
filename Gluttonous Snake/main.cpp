#include "Console.h"
#include "Window.h"
#include "GameDefine.h"
#include "Snake.h"
#include <WinUser.h>
#include <conio.h>

DWORD oldTime = 0;
Cmd CMD_Present = CMD_DOWN;//当前命令
int gg=0;
// 得到按键命令
Cmd GetCmd(Snake& snake, Console& console)
{
	while (true)
	{
		// 延时，减少CPU占用率
		Sleep(SLEEP_TIME);

		DWORD newTime = GetTickCount();

		// 超时下落
		if (newTime - oldTime > TIME_OUT)
		{
			oldTime = newTime;
			return CMD_Present;
		}

		// 有按键
		if (_kbhit())
		{
			switch (_getch())
			{
			case KEY_ENTER:
			{
				return CMD_BEGIN; 
			}
			case KEY_INTER:
				return CMD_PAUSE;
			case KEY_ESC:
				return CMD_QUIT;

			case 0:
			case 0xE0:
				switch (_getch())
				{
				case KEY_UP: {
					CMD_Present = CMD_UP;
					return CMD_Present;
				}
				case KEY_LEFT: {
					CMD_Present = CMD_LEFT;
					return CMD_Present;
				}
				case KEY_RIGHT: {
					CMD_Present = CMD_RIGHT;
					return CMD_Present;
				}
				case KEY_DOWN: {
					CMD_Present = CMD_DOWN;
					return CMD_Present;
				}
				}

			}
		}

		if (snake.IsRun()&&snake.GetLevel() <= 10)
		{
			return CMD_Present;
		}
	}
}

// 分发按键命令处理
void DispatchCmd(Snake& Snake, Console& console, Cmd cmd)
{
	switch (cmd)
	{
	case CMD_QUIT:
		exit(0);
		break;
	default:
		Snake.MessageProc(cmd);
		break;

	}
}

void main()
{
	// 创建一个控制台
	Console console;
	// 创建一个坐标
	COORD coordinate = { GameStartX, GameStartY };

	const char* strGameName = "Gluttonous ---- By Chen";
	console.Init(strGameName, coordinate);

	int keys[KeyNum] = { KEY_ENTER, KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_DOWN, KEY_INTER };
	char decs[KeyNum][5] = { "回车", "↑", "←", "→", "↓", "空格" };

	COORD coord = { 0, 0 };
	Snake snake(console, coord);
	
	gg=snake.Model_Slect();

	snake.InitSnake(keys, decs);
	snake.Produce_Food();
	Cmd cmd;
	while (true)
	{
		if (gg == 1) {
			cmd = GetCmd(snake, console);
			DispatchCmd(snake, console, cmd);
		}
		else 
		snake.Automatic_run();
	}

}