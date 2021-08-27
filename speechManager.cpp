#include"speechManager.h"
//构造函数
SpeechManager::SpeechManager()
{
	//初始化容器和属性
	this->initSpeech();

	//创建12名选手
	this->creatSpeaker();

	//获取往届记录
	this->loadRecord();
}
//菜单
void SpeechManager::show_Menu()
{
	cout << "**************************************" << endl;
	cout << "***********  欢迎参加演讲比赛 ********" << endl;
	cout << "***********  1.开始演讲比赛   ********" << endl;
	cout << "***********  2.查看往届记录   ********" << endl;
	cout << "***********  3.清空比赛记录   ********" << endl;
	cout << "***********  0.退出比赛系统   ********" << endl;
	cout << "**************************************" << endl;
	cout << endl;
}

//退出系统
void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech()
{
	//容器都要空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	
	//初始化比赛轮数
	this->m_Index = 1;
	//初始化记录容器
	this->m_Record.clear();
}

void SpeechManager::creatSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2; i++)
		{
			sp.m_Score[i] = 0;
		}
		//创建选手编号并放在v1容器中
		this->v1.push_back(i + 10001);

		//对应选手编号以及对应选手 放入map容器中
		this->m_Speaker.insert(make_pair(i + 10001,sp));
	}
}

//开始比赛
void SpeechManager::startSpeech()
{
	//第一轮比赛
	//1、抽签
	this->speechDraw();
	//2、比赛
	this->speechContest();
	//3、显示晋级结果
	this->showScore();
	//第二轮比赛
	this->m_Index++;
	//1、抽签
	this->speechDraw();
	//2、比赛
	this->speechContest();
	//3、显示晋级结果
	this->showScore();
	//4、保存分数
	this->saveRecord();
	//重置比赛
	//初始化属性
	this->initSpeech();

	//创建选手
	this->creatSpeaker();

	//获取往届记录
	this->loadRecord();

	cout << "本届比赛完毕!" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::speechDraw()
{
	cout << "第<<" << this->m_Index << ">>轮比赛选手正在抽签" << endl;
	cout << "------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (this->m_Index == 1)
	{
		//第一轮比赛
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//第二轮比赛
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

//比赛
void SpeechManager::speechContest()
{
	cout << "----------第" << this->m_Index << "轮比赛正式开始：-------------" << endl;
	multimap<double, int, greater<double>>groupScore;//临时容器，保存key分数value选手编号
	int num = 0;//记录人员数，6个为1组
	
	vector<int>v_Src;//比赛的人员容器
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	//遍历所有参赛选手
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//评委打分
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand()% 401 + 600) / 10.f;//600~1000
			//cout<<score<< " ";
			d.push_back(score);

		}
		//cout << endl;
		sort(d.begin(),d.end(), greater<double>());//排序
		d.pop_front();//去掉最高恩
		d.pop_back();//去掉最低分


		double sum = accumulate(d.begin(), d.end(), 0.0f);//总分
		double avg = sum / (double)d.size();//平均分

		//打印平均分
		//cout << " 编号： " << *it << "姓名： " << this->m_Speaker[*it].m_Name << " 获取平均分： " <<avg<< endl;
		//将平均分放到map容器中
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//6个人一组，用临时容器保存
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second << "姓名：" << this->m_Speaker[it->second].m_Name << "成绩：" << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			int count = 0;
			//取前三名
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
			groupScore.clear();//小组容器清空
			cout << endl;
		}

	}
	cout << "-------------第" << this->m_Index << "轮比赛完毕-------------" << endl;
	system("pause");
}

//现实比赛结果
void SpeechManager::showScore()
{
	cout << "----------------第" << this->m_Index << "轮晋级选手信息如下：-------" << endl;
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
		cout << "选手编号：" << "姓名：" << m_Speaker[*it].m_Name << " 得分 " << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();
}

//保存分数
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//用输出的方式打开文件--写文件

	//将每个人的数据写到文件中
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << ","
			<< m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	//关闭文件
	ofs.close();

	cout << "记录已经保存" << endl;

	//有记录了，文件不为空
	this->fileIsEmpty = false;
}
//读取记录
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);//输入流对象 读取文件

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空！" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->fileIsEmpty = false;

	ifs.putback(ch);//读取的单个字符放回去

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
			pos = data.find(" ,", start);//从0开始查找‘，’
			if (pos == -1)
			{
				break;//找不到break返回
			}
			string tmp = data.substr(start, pos - start);//找到了进行分割，参数1起始位置，参数2截取长度
			v.push_back(tmp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
	//for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
	//{
		//cout << it->first << "冠军编号" << it->second[0] << "分数：" << it->second[1] << endl;
	//}

}

//显示往届得分
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在，或记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "第" << i + 1 << "届" <<
				"冠军编号：" << this->m_Record[i][0] << "得分：" << this->m_Record[i][1] << " "
				"亚军编号：" << this->m_Record[i][0] << "得分：" << this->m_Record[i][1] << " "
				"季军编号：" << this->m_Record[i][0] << "得分：" << this->m_Record[i][1] << endl;
		}
	}
	system("pause");
	system("cls");
}

//清空记录
void SpeechManager::clearRecord()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//打开模式 ios::trunc如果存在删除文件并重新创建
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//初始化属性
		this->initSpeech();

		//创建选手
		this->creatSpeaker();

		//获取往届记录
		this->loadRecord();

		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");
}	


//析构函数
SpeechManager::~SpeechManager()
{

}