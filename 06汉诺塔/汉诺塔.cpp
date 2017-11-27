#include <iostream>
using namespace std;
//定义盘子数量
int Disks ;

//移动的步骤
void Move(int n,char x,char y){
	cout << " Move " << n << " From " << x << " To " << y << endl;
}
//递归方法
void Hannoi(int n, char a, char b,char c){
	if (n == 1)
		Move(1, a, c);
	else{
		Hannoi(n - 1, a, c, b);1
		Move(n, a, c);
		Hannoi(n - 1, b, a, c);
	} 

}

void main(){
	cout << "汉诺塔：将A柱子上的盘子移动到C柱子上" << endl;
	cout << "请输入盘子数量：" << endl;
	cin >> Disks;
	cout << "移动过程："  << endl;
	Hannoi(Disks, 'A', 'B', 'C');

	system("pause");
}