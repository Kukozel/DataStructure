//
//  main.cpp
//  前中后序
//
//  Created by 秦源 on 2016/11/14.
//  Copyright © 2016年 Abfahrt. All rights reserved.
//

#include<iostream>
using namespace std;
class BinaryTreeNode{
private:
    char m_data;//储存数据
    BinaryTreeNode * m_leftChild;//左孩子指针域
    BinaryTreeNode * m_rightChild;//右孩子指针域
public:
    BinaryTreeNode(){m_leftChild=m_rightChild=NULL;};
    BinaryTreeNode(const char&data,BinaryTreeNode * leftChild=NULL,BinaryTreeNode * rightChild=NULL){
        m_data=data;
        m_leftChild=leftChild;
        m_rightChild=rightChild;
    };
    char & GetData(){return m_data;};//返回该节点数据
    BinaryTreeNode * GetLeftChild(){return m_leftChild;};//返回该节点左孩子指针
    BinaryTreeNode * GetRightChild(){return m_rightChild;};//返回该节点右孩子指针
    void SetData(const char&data){m_data=data;};//设置该节点的数据
    void SetLeftChild(BinaryTreeNode *leftChild){m_leftChild=leftChild;};//设置该节点左孩子指针域
    void SetRightChild(BinaryTreeNode *rightChild){m_rightChild=rightChild;};//设置该节点右孩子指针域
};

struct stack{
    BinaryTreeNode * base=NULL;
    BinaryTreeNode * top=NULL;
    int size=30;
};
void initStack(stack & e){
    e.base=new BinaryTreeNode[30];
    if(!e.base){
        cout<<"堆栈创建失败"<<endl;
        exit(-1);
    }
    e.top=e.base;
}
void push(stack & e,BinaryTreeNode temp){
    //栈满扩充
    if(e.top-e.base>=e.size){
        long nowSize=e.top-e.base;
        BinaryTreeNode * t=new BinaryTreeNode[e.size+30];
        if(!t){
            cout<<"堆栈扩容失败"<<endl;
            exit(-1);
        }
        e.size+=30;
        for(int i=0;i<nowSize;i++){
            *(t++)=*(e.base+i);
        }
        *(e.top)=*(t+nowSize);
        delete []e.base;
        e.base=t;
    }
    //push
    *(e.top++)=temp;
}
BinaryTreeNode * pop(stack & e){
    if(e.top==e.base){
        cout<<"Empty!"<<endl;
        exit(-1);
    }
    return --e.top;
}
BinaryTreeNode * top(stack & e){
    if(e.top==e.base){
        cout<<"Empty!"<<endl;
        exit(-1);
    }
    return e.top-1;
}
bool empty(stack & e){
    if(e.top==e.base)
        return true;
    return false;
}
/*
 //测试数据
BinaryTreeNode * example(){
    BinaryTreeNode * root=new BinaryTreeNode('-');
    BinaryTreeNode * node2=new BinaryTreeNode('+');
    BinaryTreeNode * node3=new BinaryTreeNode('/');
    BinaryTreeNode * node4=new BinaryTreeNode('a');
    BinaryTreeNode * node5=new BinaryTreeNode('*');
    BinaryTreeNode * node6=new BinaryTreeNode('e');
    BinaryTreeNode * node7=new BinaryTreeNode('f');
    BinaryTreeNode * node8=new BinaryTreeNode('b');
    BinaryTreeNode * node9=new BinaryTreeNode('-');
    BinaryTreeNode * node10=new BinaryTreeNode('c');
    BinaryTreeNode * node11=new BinaryTreeNode('d');
    
    root->SetLeftChild(node2);
    root->SetRightChild(node3);
    
    node2->SetLeftChild(node4);
    node2->SetRightChild(node5);
    
    node3->SetLeftChild(node6);
    node3->SetRightChild(node7);
    
    node5->SetLeftChild(node8);
    node5->SetRightChild(node9);
    
    node9->SetLeftChild(node10);
    node9->SetRightChild(node11);
    
    return root;
}
*/
void enterDataByPreOrderTraverse(BinaryTreeNode * root){
        char c;
        cin>>c;
    if(c=='#'){
        root=NULL;
        return;
    }
        root->SetData(c);
        BinaryTreeNode * node1=new BinaryTreeNode();
        root->SetLeftChild(node1);
        enterDataByPreOrderTraverse(root->GetLeftChild());
        BinaryTreeNode * node2=new BinaryTreeNode();
        root->SetRightChild(node2);
        enterDataByPreOrderTraverse(root->GetRightChild());
    
}
BinaryTreeNode * enterData(){//书上例子
    BinaryTreeNode * root=new BinaryTreeNode();
    cout<<"请按照先序递归输入数据，空位置为 # "<<endl;
  //  cout<<"书上例题应输入 - + a # # * b # # - c # # d # # / e # # f # #"<<endl;
    enterDataByPreOrderTraverse(root);
    return root;
}

void PreOrderTraverse(BinaryTreeNode * root){//先序递归遍历
    if(root!=NULL){
        cout<<root->GetData()<<" ";
        PreOrderTraverse(root->GetLeftChild());
        PreOrderTraverse(root->GetRightChild());
    }
}
void InOrderTraverse(BinaryTreeNode * root){//中序递归遍历
    if(root!=NULL){
        InOrderTraverse(root->GetLeftChild());
        cout<<root->GetData()<<" ";
        InOrderTraverse(root->GetRightChild());
    }
}
void PostOrderTraverse(BinaryTreeNode * root){//后序递归遍历
    if(root!=NULL){
        PostOrderTraverse(root->GetLeftChild());
        PostOrderTraverse(root->GetRightChild());
        cout<<root->GetData()<<" ";
    }
}

void PreOrderTraverse_byStack(BinaryTreeNode * root){//先序非递归遍历
    stack s;
    initStack(s);
    BinaryTreeNode *p=root;
    while(!empty(s)||p!=NULL){
        while(p){
            push(s,*p);
            cout<<p->GetData()<<" ";
            p=p->GetLeftChild();
        }
        p=top(s);
        pop(s);
        p=p->GetRightChild();
    }
}
void InOrderTraverse_byStack(BinaryTreeNode * root){//中序非递归遍历
    stack s;
    initStack(s);
    BinaryTreeNode *p=root;
    while(!empty(s)||p!=NULL){
        while(p){
            push(s,*p);
            p=p->GetLeftChild();
        }
        p=top(s);
        cout<<p->GetData()<<" ";
        pop(s);
        p=p->GetRightChild();
    }
}
void PostOrderTraverse_byStack(BinaryTreeNode * root){//后序非递归遍历
    stack s;
    initStack(s);
    //用于储存结果的堆栈r
    stack r;
    initStack(r);
    BinaryTreeNode *p=root;
    while(!empty(s)||p!=NULL){
        while(p){
            push(s,*p);
            push(r,*p);
            p=p->GetRightChild();
        }
        p=top(s);
        pop(s);
        p=p->GetLeftChild();
    }
    while(!empty(r)){
        BinaryTreeNode *t=pop(r);
        cout<<t->GetData()<<" ";
    
    }
}


int main(int argc, const char * argv[]) {
      //  BinaryTreeNode * root=example();//测试数据
       BinaryTreeNode * root=enterData();
        cout<<"先序递归遍历 :"<<endl;
        PreOrderTraverse(root);//先序递归遍历
        cout<<endl<<"中序递归遍历 :"<<endl;
        InOrderTraverse(root);//中序递归遍历
        cout<<endl<<"后序递归遍历 :"<<endl;
        PostOrderTraverse(root);//后序递归遍历
        
        cout<<endl<<"先序非递归遍历 :"<<endl;
        PreOrderTraverse_byStack(root);//先序非递归遍历
        cout<<endl<<"中序非递归遍历 :"<<endl;
        InOrderTraverse_byStack(root);//中序非递归遍历
        cout<<endl<<"后序非递归遍历 :"<<endl;
        PostOrderTraverse_byStack(root);//后序非递归遍历
        cout<<endl<<"************************************"<<endl;
        return 0;
}
