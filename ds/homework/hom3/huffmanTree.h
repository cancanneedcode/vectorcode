#pragma once
#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
using namespace std;

//���������ڵ���
class hfTNode {
public:
	int weight;//�ڵ��Ȩ��
	int ch;//�洢�ڵ���±�
	hfTNode* leftchild, * rightchild;//�����ý������Һ���ָ��
	hfTNode() ://���������ڵ����ʼ��
		leftchild(nullptr), rightchild(nullptr) {}
	hfTNode(int data) ://���������ڵ����ʼ��
		leftchild(nullptr), rightchild(nullptr), weight(data) {}
	//�������캯��
	hfTNode(const hfTNode& N) {
		ch = N.ch;
		weight = N.weight;
		if (N.leftchild) {
			leftchild = new hfTNode();
			*leftchild = *(N.leftchild);
		}
		else
			leftchild = nullptr;
		if (N.rightchild) {
			rightchild = new hfTNode();
			*rightchild = *(N.rightchild);
		}
		else
			rightchild = nullptr;
	}
	// ����"<"���ţ�����Ϊ��Сֵ����
	bool operator < (const hfTNode& N) const {
		return weight > N.weight;
	}
};

//����������
class Huffman
{
public:
	Huffman(const string& sample);// ���캯��
	~Huffman();// ��������

	bool IsLeaf(hfTNode* Root);//�жϽڵ��Ƿ�ΪҶ�ӽ��
	void GetFreq(vector<int>& des);//��ȡ��ǰ��Ȩ������
	void BuildTree();//����һ�Ź�������
	void BuildCode();//���ݹ����������������
	void GetCodeList();//���������ͱ�����Ӧ�ı���

	//ǰ����������������Ϊ��ȷ��������������״�Ƿ���ȷ
	void PreOrder();
	void InOrder();

	string Expend(const string& des);//��ѹ��
	string Compress(const string& des);//ѹ��


private:
	void _del(hfTNode* root);//ɾ����������
	void _build(hfTNode* root, string str);//����map��key��valueֵ
	void _PreOrder(hfTNode* root);
	void _InOrder(hfTNode* root);
	unordered_map<char, string> map;//keyΪ�������ַ���valueΪ�������ַ���Ӧ�ı�����ʽ���硰101������111��
	vector<int> freq; // Ȩ������
	vector<char> st; // �����

	hfTNode* Root; // �����������ڵ�
};




#endif // !HUFFMANTREE_H
#include "huffmanTree.h"

//�����ַ������ɱ�����Լ�Ȩ������
Huffman::Huffman(const string& sample)
{
	int len = sample.length();
	if (len == 0) { cout << "�����������ַ���" << endl; exit(-1); }
	unordered_map<char, int> mymap;
	for (int i = 0; i < len; ++i) {//���������ַ�����ʼ����ϣ��
		if (mymap.find(sample[i]) == mymap.end())
			mymap[sample[i]] = 1;
		else
			mymap[sample[i]] += 1;
	}
	for (const auto& pair : mymap) {//������ϣ������key��value�ֱ�ѹ��������Ƶ��������
		//unordered_map<char, int>::const_iterator pair
		st.push_back(pair.first);
		freq.push_back(pair.second);
	}
}

//��������
Huffman::~Huffman()
{
	_del(Root);
}
//�жϽڵ��Ƿ�ΪҶ�ӽ��
bool Huffman::IsLeaf(hfTNode* Root)
{
	if (Root == nullptr) return false;
	if (Root->leftchild == nullptr && Root->rightchild == nullptr)
		return true;
	else
		return false;
}

//��ȡ��ǰ��Ȩ������
void Huffman::GetFreq(vector<int>& des)
{
	for (int i = 0; i < freq.size(); i++)
		des.push_back(freq[i]);
}

//����һ�Ź�������
void Huffman::BuildTree()
{
	priority_queue<hfTNode> myqueue;//ʹ����С���ȼ����д洢�ڵ�
	for (int i = 0; i < freq.size(); i++) {//�ڵ��ʼ���������ڵ�ѹ����С���ȼ�������
		hfTNode* temp = new hfTNode(freq[i]);
		temp->ch = i;
		myqueue.push(*temp);
	}
	//�ϲ��ڵ㲢������
	while (myqueue.size() > 1) {
		//�Ӷ�����ȡ��������СԪ����Ϊ�����������Ӻ��Һ���
		hfTNode left = myqueue.top();
		myqueue.pop();
		hfTNode right = myqueue.top();
		myqueue.pop();
		//�����������ĸ��ڵ㣬������ѹ�������
		hfTNode* parent = new hfTNode(left.weight + right.weight);
		parent->ch = -1;//�趨�������ɵĸ�����±�ֵ��-1��ֻ��������
		parent->leftchild = &left;
		parent->rightchild = &right;
		myqueue.push(*parent);
	}
	//���ɹ��������ĸ����
	Root = new hfTNode();
	*Root = myqueue.top();
	myqueue.pop();
}

//���ݹ����������������
void Huffman::BuildCode()
{
	if (Root == nullptr) return;
	//string temp('\0');
	string temp;
	temp.clear();//��ʼ��Ϊ���ַ���
	_build(Root, temp);
}

//���������ͱ�����Ӧ�ı���
void Huffman::GetCodeList()
{
	for (const auto& pair : map)
		cout << pair.first << ": " << pair.second << endl;
}

void Huffman::PreOrder()
{
	if (Root == nullptr) return;
	_PreOrder(Root);
}

void Huffman::InOrder()
{
	if (Root == nullptr) return;
	_InOrder(Root);
}

//��ѹ��
string Huffman::Expend(const string& des)
{
	string res;
	int i(0), n(des.size());
	hfTNode* temp = new hfTNode();
	temp = Root;
	while (i < n) {
		if (des[i] == '0')
		{
			temp = temp->leftchild;
			i++;
			if (IsLeaf(temp)) {
				res += st[temp->ch];
				temp = Root;
				continue;
			}
		}
		if (des[i] == '1')
		{
			temp = temp->rightchild;
			i++;
			if (IsLeaf(temp)) {
				res += st[temp->ch];
				temp = Root;
				continue;
			}
		}
	}
	return res;
}

//ѹ��
string Huffman::Compress(const string& des)
{
	string res;
	for (int i = 0; i < des.length(); ++i) {
		if (des[i] == '\n' || des[i] == ' ')
			continue;
		res += map[des[i]];
	}
	return res;
}

void Huffman::_PreOrder(hfTNode* root)
{
	if (root == nullptr) return;
	cout << root->ch << " :" << root->weight << endl;
	_PreOrder(root->leftchild);
	_PreOrder(root->rightchild);
}


void Huffman::_InOrder(hfTNode* root)
{
	if (root == nullptr) return;
	_InOrder(root->leftchild);
	cout << root->ch << " :" << root->weight << endl;
	_InOrder(root->rightchild);
}

//ɾ����������
void Huffman::_del(hfTNode* root)
{
	if (root == nullptr)
		return;
	if (root->leftchild)
		_del(root->leftchild);
	if (root->rightchild)
		_del(root->rightchild);
}

void Huffman::_build(hfTNode* root, string str)
{
	if (IsLeaf(root) && root->ch >= 0) {
		cout << str << "    ";
		map[st[root->ch]] = str;
		return;
	}
	if (root->leftchild) _build(root->leftchild, str + '0');
	if (root->rightchild) _build(root->rightchild, str + '1');
}