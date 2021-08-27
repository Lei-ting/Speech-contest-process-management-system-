#include"speechManager.h"
//���캯��
SpeechManager::SpeechManager()
{
	//��ʼ������������
	this->initSpeech();

	//����12��ѡ��
	this->creatSpeaker();

	//��ȡ�����¼
	this->loadRecord();
}
//�˵�
void SpeechManager::show_Menu()
{
	cout << "**************************************" << endl;
	cout << "***********  ��ӭ�μ��ݽ����� ********" << endl;
	cout << "***********  1.��ʼ�ݽ�����   ********" << endl;
	cout << "***********  2.�鿴�����¼   ********" << endl;
	cout << "***********  3.��ձ�����¼   ********" << endl;
	cout << "***********  0.�˳�����ϵͳ   ********" << endl;
	cout << "**************************************" << endl;
	cout << endl;
}

//�˳�ϵͳ
void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech()
{
	//������Ҫ��
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	
	//��ʼ����������
	this->m_Index = 1;
	//��ʼ����¼����
	this->m_Record.clear();
}

void SpeechManager::creatSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2; i++)
		{
			sp.m_Score[i] = 0;
		}
		//����ѡ�ֱ�Ų�����v1������
		this->v1.push_back(i + 10001);

		//��Ӧѡ�ֱ���Լ���Ӧѡ�� ����map������
		this->m_Speaker.insert(make_pair(i + 10001,sp));
	}
}

//��ʼ����
void SpeechManager::startSpeech()
{
	//��һ�ֱ���
	//1����ǩ
	this->speechDraw();
	//2������
	this->speechContest();
	//3����ʾ�������
	this->showScore();
	//�ڶ��ֱ���
	this->m_Index++;
	//1����ǩ
	this->speechDraw();
	//2������
	this->speechContest();
	//3����ʾ�������
	this->showScore();
	//4���������
	this->saveRecord();
	//���ñ���
	//��ʼ������
	this->initSpeech();

	//����ѡ��
	this->creatSpeaker();

	//��ȡ�����¼
	this->loadRecord();

	cout << "����������!" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::speechDraw()
{
	cout << "��<<" << this->m_Index << ">>�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->m_Index == 1)
	{
		//��һ�ֱ���
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//�ڶ��ֱ���
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << "";
		}
		cout << endl;
	}
	cout << "---------------------" << endl;
	system("pause");
	cout << endl;
}

//����
void SpeechManager::speechContest()
{
	cout << "----------��" << this->m_Index << "�ֱ�����ʽ��ʼ��-------------" << endl;
	multimap<double, int, greater<double>>groupScore;//��ʱ����������key����valueѡ�ֱ��
	int num = 0;//��¼��Ա����6��Ϊ1��
	
	vector<int>v_Src;//��������Ա����
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	//�������в���ѡ��
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//��ί���
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand()% 401 + 600) / 10.f;//600~1000
			//cout<<score<< " ";
			d.push_back(score);

		}
		//cout << endl;
		sort(d.begin(),d.end(), greater<double>());//����
		d.pop_front();//ȥ����߶�
		d.pop_back();//ȥ����ͷ�


		double sum = accumulate(d.begin(), d.end(), 0.0f);//�ܷ�
		double avg = sum / (double)d.size();//ƽ����

		//��ӡƽ����
		//cout << " ��ţ� " << *it << "������ " << this->m_Speaker[*it].m_Name << " ��ȡƽ���֣� " <<avg<< endl;
		//��ƽ���ַŵ�map������
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//6����һ�飬����ʱ��������
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "��ţ�" << it->second << "������" << this->m_Speaker[it->second].m_Name << "�ɼ���" << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			int count = 0;
			//ȡǰ����
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear();//С���������
			cout << endl;
		}

	}
	cout << "-------------��" << this->m_Index << "�ֱ������-------------" << endl;
	system("pause");
}

//��ʵ�������
void SpeechManager::showScore()
{
	cout << "----------------��" << this->m_Index << "�ֽ���ѡ����Ϣ���£�-------" << endl;
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << "������" << m_Speaker[*it].m_Name << " �÷� " << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();
}

//�������
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//������ķ�ʽ���ļ�--д�ļ�

	//��ÿ���˵�����д���ļ���
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << ","
			<< m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	//�ر��ļ�
	ofs.close();

	cout << "��¼�Ѿ�����" << endl;

	//�м�¼�ˣ��ļ���Ϊ��
	this->fileIsEmpty = false;
}
//��ȡ��¼
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);//���������� ��ȡ�ļ�

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ�գ�" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->fileIsEmpty = false;

	ifs.putback(ch);//��ȡ�ĵ����ַ��Ż�ȥ

	string data;
	int index = 0;
	while (ifs >> data)
	{
		//cout<<data<<endl;
		vector<string>v;

		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(" ,", start);//��0��ʼ���ҡ�����
			if (pos == -1)
			{
				break;//�Ҳ���break����
			}
			string tmp = data.substr(start, pos - start);//�ҵ��˽��зָ����1��ʼλ�ã�����2��ȡ����
			v.push_back(tmp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
	//for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
	//{
		//cout << it->first << "�ھ����" << it->second[0] << "������" << it->second[1] << endl;
	//}

}

//��ʾ����÷�
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ������ڣ����¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "��" << i + 1 << "��" <<
				"�ھ���ţ�" << this->m_Record[i][0] << "�÷֣�" << this->m_Record[i][1] << " "
				"�Ǿ���ţ�" << this->m_Record[i][0] << "�÷֣�" << this->m_Record[i][1] << " "
				"������ţ�" << this->m_Record[i][0] << "�÷֣�" << this->m_Record[i][1] << endl;
		}
	}
	system("pause");
	system("cls");
}

//��ռ�¼
void SpeechManager::clearRecord()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//��ģʽ ios::trunc�������ɾ���ļ������´���
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//��ʼ������
		this->initSpeech();

		//����ѡ��
		this->creatSpeaker();

		//��ȡ�����¼
		this->loadRecord();

		cout << "��ճɹ���" << endl;
	}

	system("pause");
	system("cls");
}	


//��������
SpeechManager::~SpeechManager()
{

}