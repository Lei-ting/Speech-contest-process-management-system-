#include<iostream>
using namespace std;
#include"speechManager.h"

int main()
{
	//���������
	srand((unsigned int)time(NULL));
	//�����������
	SpeechManager sm;

	//����12��ѡ�ֵĴ���
	/*for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << it->first << "������" << it->second.m_Name << "������" << it->second.m_Score[0] << endl;
	}*/

	int choice = 0;//�����洢�û���ѡ��

	while(true)
	{
		sm.show_Menu();
		cout << "����������ѡ��" << endl;
		cin >> choice;//�����û���ѡ��

		switch (choice)
		{
		case 1://��ʼ����
			sm.startSpeech();
			break;
		case 2://�鿴��¼
			sm.showRecord();
			break;
		case 3://��ռ�¼
			sm.clearRecord();
			break;
		case 0://�˳�ϵͳ
			sm.exitSystem();
			break;
		default:
			system("cls");//����
			break;
		}
	}
	system("pause");
	return 0;
}