/**
软件工程一班
秦源
ID：1525161007
实验：约瑟夫环
*/

#include <iostream>
using namespace std;
unsigned int m;//报数上限值m
unsigned int n;//人数n
struct LNode{
 int num;//所持密码
 int sq;//人的编码
 struct LNode * next;
};
LNode * s=new LNode;

void ini(){//初始化
//用于初始化报数上限值(m) 人数(n)
cout<<"请输入初始报数上限值："<<"\t";
cin>>m;
cout<<"请输入人数："<<"\t";
cin>>n;
   //获取每个人携带的密码，初始化每个人的编号，并完成单向链表的构建
if(n>0){
 cout<<"请输入第"<<1<<"个人所持的密码："<<"\t";
     cin>>s->num;
     s->sq=1;
//头插法创建链表
	 if(n>1){
  LNode * tail;
  tail=s;
     for(int i=2;i<=n;i++){
   LNode * newOne=new LNode;
   tail->next=newOne;
   tail=tail->next;
   cout<<"请输入第"<<i<<"个人所持的密码："<<"\t";
   cin>>tail->num;
   tail->sq=i;
  }
    tail->next=s;
	 }
}
}


 void achieve(){
 int number =n;
 LNode * p;
 LNode * tail;
 p=s;
 cout<<"出列顺序:  "<<endl;
 while(number>0){
  for(int i=1;i<(m-1)%number;i++)
         p=p->next;

  cout<<"第"<<p->next->sq<<"人"<<"\t";
  m=p->next->num;
  m++;
  tail=p->next;
  p->next=p->next->next;
  delete tail;
     number--;
 }
 }

void main(){
ini();
achieve();
cout<<endl<<"***************************************************"<<endl;
system("pause");
}