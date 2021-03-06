//
//  main.cpp
//  Maze
//
//  Created by 秦源 on 2016/10/22.
//  Copyright © 2016年 Abfahrt. All rights reserved.
//

#include <iostream>
using namespace std;
const int STACK_INIT_SIZE=64 ;//定义堆栈的初始大小
const int STACKINCREMENT=32;//栈满后扩充大小

struct PosType{	//定义点的坐标
    int x;//点的横坐标
    int y;//点的纵坐标
};

struct SElemType{
    int ord;    //通道块在路径上的“序号”
    PosType seat;//通道块在迷宫中的“坐标位置”
    int di;//从此通道块走向下一通道块的“方向”
};

struct MazeType{//定义储存迷宫的数组（最外侧需要封闭上）
    int L_x;//实际迷宫横为8
    int L_y;//实际迷宫纵为9
    int map[10][11];//将迷宫包围后横为10，纵为11
};
MazeType InitMazeMap(){//初始化迷宫
    MazeType M;
    M.L_x=8;
	M.L_y=9;
	for(int x=0;x<10;x++)
		for(int y=0;y<11;y++)
			M.map[x][y]=0;
	//包围迷宫外侧
    for(int x=0;x<10;x++){
        M.map[x][0]=1;
        M.map[x][10]=1;
    }
    for(int y=1;y<11;y++){
        M.map[0][y]=1;
        M.map[9][y]=1;
    }
	//绘制迷宫
        M.map[3][1]=1;
        M.map[7][1]=1;
        M.map[3][2]=1;
        M.map[7][2]=1;
        M.map[5][3]=1;
        M.map[6][3]=1;
        M.map[8][3]=1;
        M.map[2][4]=1;
        M.map[3][4]=1;
        M.map[4][4]=1;
        M.map[7][4]=1;
        M.map[4][5]=1;
        M.map[2][6]=1;
        M.map[6][6]=1;
        M.map[8][6]=1;
        M.map[2][7]=1;
        M.map[3][7]=1;
        M.map[4][7]=1;
        M.map[5][7]=1;
        M.map[8][7]=1;
        M.map[1][8]=1;
        M.map[2][8]=1;
        M.map[6][8]=1;
        M.map[8][8]=1;
        M.map[1][9]=1;
        M.map[2][9]=1;
	//输出迷宫
    cout<<"迷宫实例："<<endl;
	for(int y=0;y<11;y++){
        for(int x=0;x<10;x++){
         cout<< M.map[x][y]<<" ";
        }
        cout<<endl;
    }
    return M;
}

struct SqStack{	//	定义顺序栈结构体
    SElemType * base;
    SElemType * top;
    int stacksize;
};

SqStack InitStack(){//	初始化顺序栈
    SqStack S;
    S.base=new SElemType[STACK_INIT_SIZE];
    if(!S.base)
        exit(1);
    S.top=S.base;
    S.stacksize=STACK_INIT_SIZE;
    return S;
}

void Push(SqStack & S,SElemType &e){//入栈
   //栈满情况下扩充栈的大小
	if(S.top-S.base>=S.stacksize){
        SElemType * temp;
        temp=new SElemType[S.stacksize+STACKINCREMENT];
        if(!temp)
            exit(1);
        for(int i=0;i<S.stacksize;i++)
            temp[i]=S.base[i];
        delete []S.base;
        S.base=temp;
        S.top=S.base+S.stacksize;
        S.stacksize+=STACKINCREMENT;
    }
	//入栈
    *S.top++=e;
}
bool StackEmpty(SqStack &S){//判断栈是否为空
if(S.base==S.top)
    return true;
    return false;
}
SElemType Pop(SqStack & S){//出栈
    //判断是否栈为空
	if(S.base==S.top)
        exit(1);
	//出栈
    SElemType e;
    e=*--S.top;
    return e;
}
bool Pass(MazeType & maze,PosType pos){	//判断当前点是否可通
    if(maze.map[pos.x][pos.y]==0)
    return true;
    return false;
}

PosType NextPos(PosType now,int w){	//根据上一个点的信息，定义下一个点的位置
    PosType next;
    switch(w){
        case 1:next.x=now.x;next.y=now.y-1;break;
        case 2:next.x=now.x+1;next.y=now.y;break;
        case 3:next.x=now.x;next.y=now.y+1;break;
        case 4:next.x=now.x-1;next.y=now.y;break;
        default:cout<<"Error!";break;  
    }
    return next;
}
void printPos(PosType e){//输出点坐标
    cout<<"("<<e.x<<","<<e.y<<")"<<endl;
}
void printStack(SqStack s1){//输出结果路径
	cout<<"已找到路径："<<endl;
	//将栈转置
	SqStack s2=InitStack();
	while(!StackEmpty(s1)){
	SElemType e1= Pop(s1);
	Push(s2,e1);
	}
	//输出结果
    while(!StackEmpty(s2)){
    SElemType e2= Pop(s2);
	cout<<"第";
	printf("%3d",e2.ord);
	cout<<" 步"<<"：";
	printPos(e2.seat); 
    }  
}
bool MazePath(MazeType &maze,PosType start,PosType end){//迷宫解法
    SqStack S=InitStack();
    PosType curPos=start;//设”当前位置“为”入口位置“
    int curstep=1;//探索第一步
    do{
        if(Pass(maze,curPos)){//当前位置可以通过
            SElemType e;
            e.ord=curstep;
            e.seat=curPos;
            e.di=1;
            Push(S, e);
            maze.map[curPos.x][curPos.y]=1;//将走过的点标记为不可通
            if(curPos.x==end.x&&curPos.y==end.y){//找到出路
                printStack(S);
                return true;
            }
            curPos=NextPos(curPos,e.di);
            curstep++;
        }else{
            if(!StackEmpty(S)){
               SElemType e= Pop(S);
			   curstep--;
                while(e.di==4&&!StackEmpty(S)){	//遇到死胡同时将当前点提到可以改变方向的通点
                    e= Pop(S);
					curstep--;
                }
                if(e.di<4){//当下个点不可通时，改变方向寻找其他通路
                    e.di++;
                    Push(S, e);
					curstep++;
                 curPos=NextPos(e.seat, e.di);
                }  
            }
        }
    }while(!StackEmpty(S));
    return false;
}

int main(int argc, const char * argv[]) {
   //实例化堆栈
	MazeType M;
    M=InitMazeMap();
   //确认迷宫入口 
    PosType start;
    start.x=1;
    start.y=1;
	//确认迷宫出口
    PosType end;
    end.x=8;
    end.y=9;
	//迷宫求解计算
    MazePath(M, start, end);
	system("pause");
    return 0;
}
