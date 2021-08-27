#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include"speaker.h"
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<string>
#include<fstream>
using namespace std;

//设计演讲管理类
class SpeechManager
{
public:
	//构造函数
	SpeechManager();

	//析构函数
	~SpeechManager();

	//展示菜单
	void show_Menu();

	//退出系统
	void exitSystem();

	//初始化属性和容器
	void initSpeech();

	//成员属性
	//比赛选手 容器 12人
	vector<int>v1;

	//第一轮晋级容器 6人
	vector<int>v2;

	//胜利前三名容器
	vector<int>vVictory;

	//存放编号 以及对应的 具体选手 容器
	map<int, Speaker>m_Speaker;

	//记录比赛轮数
	int m_Index;

	//初始化创建12名选手
	void creatSpeaker();

	//开始比赛
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();

	//显示比赛结果
	void showScore();

	//保存记录
	void saveRecord();

	//读取记录
	void loadRecord();

	//文件为空的标志
	bool fileIsEmpty;

	//往届记录存放容器
	map<int, vector<string>>m_Record;

	//显示往届得分
	void showRecord();

	//清空记录
	void clearRecord();
};
