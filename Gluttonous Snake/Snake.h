//--------------------------------------------------------------------
// �ļ���:        Snake.h
// ��  ��:        �ߵĶ����ļ�
// ˵  ��:        �����ߵĲ������ƶ�
// ��������:      2018��6��10��
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
	void InitSnake(int keys[KeyNum], char keyDesc[KeyNum][5]);//��ʼ����
	int GetLevel() const;//�����Ϸ�ȼ�
	bool MessageProc(const Cmd cmd);//��Ϣ����
	void DrawScoreLevel();//���Ƶ÷�
	void DrawGameOver();//������Ϸ��������
	bool IsFit(int x, int y);//��ͷ�Ƿ�Ϸ�
	bool IsRun();
	void Move(int x, int y);//�ߵ��ƶ�
	void LeftMove();//����
	void RightMove();//����
	void DownMove();//����
	void UpMove();//����
	void Produce_Food();//����ʳ��
	bool Eat_Food(int x, int y);//��ʳ��
	int Model_Slect();//ģʽѡ��
	void Automatic_Road(int data[ROWS][COLS], MySnake &Start, MySnake &End);//�Զ�Ѱ·
	void Automatic_run();//�Զ�����
	vector<MySnake>  Found_short(int data[ROWS][COLS], MySnake &Start, MySnake &End);//Ѱ�����·��

private:
	char bg[GAME_HIGHT * GAME_WIDTH + 1];

	// ����ʱ��
	DWORD m_voiceDuration;

	// ���ư���
	int m_keys[KeyNum];

	// ���ư���������
	char m_keyDesc[KeyNum][5];

	// ��Ϸ�Ƿ����
	bool m_gameover;

	// ��Ϸ��ͣ
	bool m_pause;

	// ��Ϸ�÷�
	int m_score;

	// ��Ϸ�ٶ�
	int m_speed;

	// ��Ϸ����(����Ĵ������)
	int m_data[ROWS][COLS];

	//ʳ�������
	MySnake food;

	//�ߵ�λ��
	MySnake position[ROWS*COLS];
	//��ͷ������
	int head;
	//��β������
	int tail;

	// ��ǰ����
	int m_currentDir;

	// ����
	Window win;
};
