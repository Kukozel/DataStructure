#include <iostream>
using namespace std;
//������������
int Disks ;

//�ƶ��Ĳ���
void Move(int n,char x,char y){
	cout << " Move " << n << " From " << x << " To " << y << endl;
}
//�ݹ鷽��
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
	cout << "��ŵ������A�����ϵ������ƶ���C������" << endl;
	cout << "����������������" << endl;
	cin >> Disks;
	cout << "�ƶ����̣�"  << endl;
	Hannoi(Disks, 'A', 'B', 'C');

	system("pause");
}