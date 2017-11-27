//
//  main.cpp
//  06赫夫曼编码
//
//  Created by 秦源 on 2016/11/21.
//  Copyright © 2016年 Abfahrt. All rights reserved.
//

#include <iostream>
using namespace std;

//--赫夫曼树和赫夫曼编码表的存储表示--
typedef struct{
    unsigned int weight;
    unsigned int parent,lchild,rchild;
}HTNode,* HuffmanTree;//动态分配数组存储赫夫曼树
typedef char ** HuffmanCode;//动态分配数组存储赫夫曼编码表
//--Select 算法--
int * Select(HuffmanTree HT,int t){
    int *s=new int[5];
    s[0]=s[1]=1000;//储存序号
    s[2]=s[3]=1000;//储存权值用于比较

    for(int i=1;i<=t;i++){
        if(HT[i].parent!=0)
            continue;
        
            if(HT[i].weight<s[2]){
                
                s[3]=s[2];
                s[2]=HT[i].weight;
                
                s[1]=s[0];
                s[0]=i;
                
                continue;
            }
        
        if(HT[i].weight<s[3]){
            s[3]=HT[i].weight;
            s[1]=i;
        }
    }
    
    if(s[0]>s[1]){
        int temp=s[0];
        s[0]=s[1];
        s[1]=temp;
    }

    return s;
}
//--HuffmanCoding--
void HuffmanCoding(HuffmanTree & HT,HuffmanCode & HC,int * w,int n){
    //w 存放n个字符的权值(均>0)，构造赫夫曼树HT，并求出n个字符的赫夫曼编码表HC。
    if(n<=1)
        return;
    int m=2*n-1;//表的列数
    HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));//0号单元未用
    HTNode *p;
    int i;
    for(p=HT+1,i=1;i<=n;++i,++p,++w)
        *p={(unsigned)*w,0,0,0};
    for(;i<=m;++i,++p)
        *p={0,0,0,0};

    for(i=n+1;i<=m;++i){//建赫夫曼树
        //在HT[1..i-1]选择parent为0且weight最小的两个节点，其序号分别为s1和s2。
        int *s=Select(HT,i-1);
        int s1=s[0];
        int s2=s[1];
        HT[s1].parent=i;
        HT[s2].parent=i;
        HT[i].lchild=s1;
        HT[i].rchild=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }
 /*
    cout<<"打印HT的终态 ： "<<endl;
    for(int k=1;k<=m;k++){
        cout<<HT[k].weight<<"\t"<<HT[k].parent<<"\t"<<HT[k].lchild<<"\t"<<HT[k].rchild<<endl;
    }
  */
    
    //--从叶子的根逆向求每个字符的赫夫曼编码--
    HC=(HuffmanCode)malloc((n+1)*sizeof(char *));//分配n个字符编码的头指针向量
    char * cd=(char*)malloc(n*sizeof(char));//分配求编码的工作空间
    cd[n-1]='\0';//编码结束符
   
    for(i=1;i<=n;++i){//逐个字符求赫夫曼编码
        int start=n-1;
         int c,f;
        for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent){//从叶子到根逆向求编码
            if(HT[f].lchild==c){
                cd[--start]='0';
            }else{
                cd[--start]='1';
            }
        }

        HC[i]=(char*)malloc((n-start)*sizeof(char));
        strcpy(HC[i], &cd[start]);
    }
    free(cd);
    
}//HuffmanCoding

void print_HC(HuffmanCode & HC,int n){
    int i=0;
    while(HC[n][i]!='\0'){
        cout<<HC[n][i];
        i++;
    }
    cout<<endl;
}

HuffmanTree  HT;
HuffmanCode  HC;

void Initialization(){
    cout<<"请输入字符种类"<<endl;
    int n;
    cin>>n;
    int * w=new int[n];
    for(int i=0;i<n;i++){
        cout<<"请输入第"<<i+1<<"个字符的权值:";
        cin>>w[i];
    }
    /*}
    w[0]=5;w[1]=29;w[2]=7;w[3]=8;
    w[4]=14;w[5]=23;w[6]=3;w[7]=11;
    int n=8;
     */
    HuffmanCoding(HT,HC, w, n);
    
}

void Print(){
    cout <<"HC 表:"<<endl;
    for(int i=1;i<=8;i++){
        cout<<"第"<<i<<"个字符对应的编码为： ";
        print_HC(HC, i);
    }
}

int main(int argc, const char * argv[]) {
    Initialization();
    Print();
    return 0;
}
