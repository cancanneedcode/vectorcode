#include<iostream>
#include<time.h>
#include"complex.h"
#include"../../../vector/vector.h"
#define ClOCKS_PER_SEC 1000;
using namespace std;
bool mycmp(Complex e1,Complex e2) {//����ʵ���鲿������ж�
	if (e1.real == e2.real && e1.imag == e2.imag)
		return true;
	return false;
}
bool mycmp1(Complex e1, Complex e2) {//������ģ������ж�
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
	cout << "�������" << endl;
	for (int i = 0; i < a.size(); i++)
	{
		a[i].random();
		myprint(a[i]);
	}
	cout << endl;
	//ɾ��
	cout << "ɾ��" << endl;
	a.remove(2);
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}
	cout << endl;
	//������ͬ����
	cout << "����" << endl;
	
	a.insert(a[0]);
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}
	cout << endl;
	//����
	cout << "����" << endl;
	a.unsort(0, a.size());
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}
	cout << endl;
	//����
	cout << "����" << endl;
	Complex c;
	c.init(2, 5);
	int result = a.find(a[3],0,a.size(),mycmp);
	cout << result<<endl;
	myprint(a[result]);
	cout << endl;

	cout << "Ψһ��" << endl;
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}cout << endl;
	//Ψһ��
	a.deduplicate(mycmp);
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}cout << endl;
	//������ģ
	cout << "ģ" << endl;
	pre.abs(1);
	Vector<Complex> b(5000, 4000, pre);//���渴��b1����������ģ
	Vector<Complex> b1(5000, 4000, pre); //�½�һ����������b1
	Vector<Complex> d(5000, 4000, pre);//���渴��d1����������ģ
	Vector<Complex> d1(5000, 4000, pre); //�½�һ����������d1
	Vector<Complex> f(5000, 4000, pre);//���渴��ģ����������ģ
	Vector<Complex> f1(5000, 4000, pre);//���渴������������ģ
	for (int i = 0; i < b1.size(); i++)
	{
		b1[i].random();
		//myprint(b1[i]);
		b[i].modulus = b1[i].abscomplex();
		//cout << b[i].modulus << endl;
	}//����������b1ģ�浽b��
	
	clock_t start, end;
	double s;

	cout << "����" << endl;
	start = clock();
	b.bubbleSort(0, b.size(),mycmp1);
	end = clock();
	s=(double)(end-start) / ClOCKS_PER_SEC;
	cout << "������������ʱ�䣺" << s <<"��" << endl;

	start = clock();
	d.mergeSort(0, b.size(), mycmp1);
	end = clock();
	s=(double)(end-start) / ClOCKS_PER_SEC;
	cout << "����鲢����ʱ�䣺" << s <<"��" << endl;

	cout << "˳��" << endl;
	start = clock();
	b.bubbleSort(0, b.size(), mycmp1);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	cout << "˳����������ʱ�䣺" << s <<"��" << endl;

	start = clock();
	d.mergeSort(0, b.size(), mycmp1);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	cout << "˳��鲢����ʱ�䣺" << s <<"��" << endl;

	for (int i = 0; i < b.size(); i++) {//��˳��������f��β��ֵ��ʹf��f1����������
		f[i] = b[b.size() - i];
		f1[i] = b[b.size() - i];
	}
	cout << "����" << endl;
	start = clock();
	f.bubbleSort(0, b.size(), mycmp1);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	cout << "������������ʱ�䣺" << s << "��" << endl;

	start = clock();
	f1.mergeSort(0, b.size(), mycmp1);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	cout << "����鲢����ʱ�䣺" << s << "��" << endl;

	cout << "�����㷨" << endl;
	//pre.fanwei(2);
	Vector<Complex> g(5000, 4000, pre);//gΪ������Ϸ�Χ��������
	Vector<Complex> g1(5000, 2, pre);//g1����ģ��Χ
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