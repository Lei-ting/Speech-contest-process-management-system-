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

//����ݽ�������
class SpeechManager
{
public:
	//���캯��
	SpeechManager();

	//��������
	~SpeechManager();

	//չʾ�˵�
	void show_Menu();

	//�˳�ϵͳ
	void exitSystem();

	//��ʼ�����Ժ�����
	void initSpeech();

	//��Ա����
	//����ѡ�� ���� 12��
	vector<int>v1;

	//��һ�ֽ������� 6��
	vector<int>v2;

	//ʤ��ǰ��������
	vector<int>vVictory;

	//��ű�� �Լ���Ӧ�� ����ѡ�� ����
	map<int, Speaker>m_Speaker;

	//��¼��������
	int m_Index;

	//��ʼ������12��ѡ��
	void creatSpeaker();

	//��ʼ����
	void startSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContest();

	//��ʾ�������
	void showScore();

	//�����¼
	void saveRecord();

	//��ȡ��¼
	void loadRecord();

	//�ļ�Ϊ�յı�־
	bool fileIsEmpty;

	//�����¼�������
	map<int, vector<string>>m_Record;

	//��ʾ����÷�
	void showRecord();

	//��ռ�¼
	void clearRecord();
};
