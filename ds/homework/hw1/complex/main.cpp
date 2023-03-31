#include<iostream>
#include<time.h>
#include"complex.h"
#include"../../../vector/vector.h"
#define ClOCKS_PER_SEC 1000;
using namespace std;
bool mycmp(Complex e1,Complex e2) {//复数实部虚部的相等判断
	if (e1.real == e2.real && e1.imag == e2.imag)
		return true;
	return false;
}
bool mycmp1(Complex e1, Complex e2) {//复数的模的相等判断
	if (e1.modulus > e2.modulus)
		return true;
	return false;
}
bool mycmp2(Complex e1, Complex e2) {
	if (e1.modulus == e2.modulus)
		return true;
	return false;
}
void myprint(Complex x) {
	printf("%.2f+%.2fi ", x.real, x.imag);
}
void myprint1(Complex x) {
	cout << x.modulus << " ";
}
int main() {
	
	Complex pre;
	pre.init(1, 2);
	Vector<Complex> a(50, 7, pre);
	cout << "随机复数" << endl;
	for (int i = 0; i < a.size(); i++)
	{
		a[i].random();
		myprint(a[i]);
	}
	cout << endl;
	//删除
	cout << "删除" << endl;
	a.remove(2);
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}
	cout << endl;
	//插入相同复数
	cout << "插入" << endl;
	
	a.insert(a[0]);
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}
	cout << endl;
	//置乱
	cout << "置乱" << endl;
	a.unsort(0, a.size());
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}
	cout << endl;
	//查找
	cout << "查找" << endl;
	Complex c;
	c.init(2, 5);
	int result = a.find(a[3],0,a.size(),mycmp);
	cout << result<<endl;
	myprint(a[result]);
	cout << endl;

	cout << "唯一化" << endl;
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}cout << endl;
	//唯一化
	a.deduplicate(mycmp);
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}cout << endl;
	//复数的模
	cout << "模" << endl;
	pre.abs(1);
	Vector<Complex> b(5000, 4000, pre);//储存复数b1的乱序向量模
	Vector<Complex> b1(5000, 4000, pre); //新建一个无序向量b1
	Vector<Complex> d(5000, 4000, pre);//储存复数d1的乱序向量模
	Vector<Complex> d1(5000, 4000, pre); //新建一个无序向量d1
	Vector<Complex> f(5000, 4000, pre);//储存复数模的逆序向量模
	Vector<Complex> f1(5000, 4000, pre);//储存复数的逆序向量模
	for (int i = 0; i < b1.size(); i++)
	{
		b1[i].random();
		//myprint(b1[i]);
		b[i].modulus = b1[i].abscomplex();
		//cout << b[i].modulus << endl;
	}//将无序向量b1模存到b中
	
	clock_t start, end;
	double s;

	cout << "乱序：" << endl;
	start = clock();
	b.bubbleSort(0, b.size(),mycmp1);
	end = clock();
	s=(double)(end-start) / ClOCKS_PER_SEC;
	cout << "乱序气泡排序时间：" << s <<"秒" << endl;

	start = clock();
	d.mergeSort(0, b.size(), mycmp1);
	end = clock();
	s=(double)(end-start) / ClOCKS_PER_SEC;
	cout << "乱序归并排序时间：" << s <<"秒" << endl;

	cout << "顺序：" << endl;
	start = clock();
	b.bubbleSort(0, b.size(), mycmp1);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	cout << "顺序气泡排序时间：" << s <<"秒" << endl;

	start = clock();
	d.mergeSort(0, b.size(), mycmp1);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	cout << "顺序归并排序时间：" << s <<"秒" << endl;

	for (int i = 0; i < b.size(); i++) {//将顺序向量和f首尾赋值，使f，f1成逆序向量
		f[i] = b[b.size() - i];
		f1[i] = b[b.size() - i];
	}
	cout << "逆序：" << endl;
	start = clock();
	f.bubbleSort(0, b.size(), mycmp1);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	cout << "逆序气泡排序时间：" << s << "秒" << endl;

	start = clock();
	f1.mergeSort(0, b.size(), mycmp1);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	cout << "逆序归并排序时间：" << s << "秒" << endl;

	cout << "查找算法" << endl;
	//pre.fanwei(2);
	Vector<Complex> g(5000, 4000, pre);//g为储存符合范围的子向量
	Vector<Complex> g1(5000, 2, pre);//g1储存模范围
	g1[0].modulus = 2;
	g1[1].modulus = 5;
	//g[0].modulus = b[b.binSearch(g1[0], 0, b.size(), mycmp1)].modulus;
	//cout << g[0].modulus << endl<< b.binSearch(g1[0], 0, b.size(), mycmp1) <<endl;
	int num = 0;
	int gnum = 0;
	num = b.binSearch(g1[0], 0, b.size(), mycmp1);
	while (num < b.binSearchbe(g1[1], 0, b.size(), mycmp1)) {
		g[gnum].modulus = b[num].modulus;
		num++;
		myprint1(g[gnum]);
		gnum++;
	}
	//cout << b[3998].modulus;
	return 0;
}