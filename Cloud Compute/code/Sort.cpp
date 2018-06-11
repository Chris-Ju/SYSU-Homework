#include <iostream>
#include <fstream>
#include <string>

//由于结果已知，所以可直接定义总数
#define N 2281

using namespace std;

//声明结构体
struct key
{
  string word;
  int number;
  //赋值运算符重载
  key& operator=(const key& temp) 
  {
    this->word = temp.word;
    this->number = temp.number;
    return *this;
  }
};

int main()
{
  //声明输入输出文件
  ifstream in;
  ofstream out;
  in.open("CHINESEResult");
  out.open("out");

  //声明数组
  key all[N];

  //文件读入
  for (int i = 0; i < N; i++)
  {
    in >> all[i].word >> all[i].number;
  }


  //冒泡排序
  for (int i = 0; i < N; i++)
  {
    for (int j = N - 1; j > i; j--)
    {
      if (all[j].number > all[j - 1].number) {
        key temp = all[j];
        all[j] = all[j - 1];
        all[j - 1] = temp;
      }
    }
  }

  //文件输出
  for (int i = 0; i < N; i++)
  {
    out << all[i].word << " " << all[i].number << "\n";
  }
  
  in.close();
  out.close();
}