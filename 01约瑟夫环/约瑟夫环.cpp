/**
�������һ��
��Դ
ID��1525161007
ʵ�飺Լɪ��
*/

#include <iostream>
using namespace std;
unsigned int m;//��������ֵm
unsigned int n;//����n
struct LNode{
 int num;//��������
 int sq;//�˵ı���
 struct LNode * next;
};
LNode * s=new LNode;

void ini(){//��ʼ��
//���ڳ�ʼ����������ֵ(m) ����(n)
cout<<"�������ʼ��������ֵ��"<<"\t";
cin>>m;
cout<<"������������"<<"\t";
cin>>n;
   //��ȡÿ����Я�������룬��ʼ��ÿ���˵ı�ţ�����ɵ�������Ĺ���
if(n>0){
 cout<<"�������"<<1<<"�������ֵ����룺"<<"\t";
     cin>>s->num;
     s->sq=1;
//ͷ�巨��������
	 if(n>1){
  LNode * tail;
  tail=s;
     for(int i=2;i<=n;i++){
   LNode * newOne=new LNode;
   tail->next=newOne;
   tail=tail->next;
   cout<<"�������"<<i<<"�������ֵ����룺"<<"\t";
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
 cout<<"����˳��:  "<<endl;
 while(number>0){
  for(int i=1;i<(m-1)%number;i++)
         p=p->next;

  cout<<"��"<<p->next->sq<<"��"<<"\t";
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