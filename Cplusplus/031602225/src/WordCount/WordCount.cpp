
#include "stdafx.h"
#include<iostream>
#include<string>
#include<queue>
#include<stdio.h>
#include<fstream>


using namespace std;

int characters = 0;
int words = 0;
int lines = 0;



typedef struct {
	char word[50];
	int count;
}wo;


//自定义优先队列
bool operator< (wo a, wo b)
{
	if (a.count == b.count)
		return a.word[0] > b.word[0];
	else return a.count < b.count;

}

int main() {

	string url;
	cin >> url;

	wo *danci = new wo[9999999];//动态分配
	wo temp_danci;

	int k, i, j, n = 0, flag, x = 0;


	char ch;

	ifstream fin;
	fin.open(url);//打开文件

	if (!fin)
	{
		cout << "can not open file" << endl;
	}

	while (!fin.eof())
	{
		ch = fin.get();
		characters++;


		//判断单词
		if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z'))
		{
			k = 0;
			flag = 0;
			temp_danci.count = 1;

			while ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9'))
			{
				if (ch >= 'A'&&ch <= 'Z')
					ch += 32;

				temp_danci.word[k++] = ch;
				ch = fin.get();
				if (!fin.eof())
					characters++;
			}
			temp_danci.word[k++] = '\0';


			for (i = 0; i < 4; i++)
			{
				if ((temp_danci.word[i] >= '0'&&temp_danci.word[i] <= '9') || temp_danci.word[i] == '\0')
				{
					flag = 1;//判断是否符合单词规范
					break;
				}
			}


			if (flag == 0)
			{
				words++;
				j = n;


				for (i = 0; i<j; i++)
				{
					if (strcmp(temp_danci.word, danci[i].word) == 0)

					{
						danci[i].count++;

						break;
					}


				}


				if (n == 0 || i == j)

				{
					danci[n] = temp_danci;

					n++;
				}

			}

		}

		else continue;



	}
	fin.close();


	//重新行遍历一遍，计算行数
	fin.open(url);

	string s;
	while (getline(fin, s))lines++;

	fin.close();


	//优先队列排序
	priority_queue<wo> tmp;


	for (i = 0; i < n; i++)
	{
		tmp.push(danci[i]);
	}


	//输出到文件
	ofstream outf;
	outf.open("result.txt");

	outf << "characters: " << characters << endl;
	outf << "words: " << words << endl;
	outf << "lines: " << lines << endl;
	while (!tmp.empty() && x<10)
	{
		outf << "<" << tmp.top().word << ">: " << tmp.top().count << endl;
		tmp.pop();
		x++;
	}
	outf.close();

}