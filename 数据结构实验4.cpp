#include<iostream>
#include<stdlib.h>
using namespace std;
#include<limits.h>   //����int�����͵���ֵ�������㲻��ͨ�����������ȨֵΪINT_MAX
struct graph {
	char vertlist[100];   //�ڵ����ƣ���A B C...��
	int edgelist[100][100];   //�ڽӾ���
	int n, e;   // n Ϊnodes' count, e Ϊedges' count
};
struct table {   //��ǵ�ǰ����״̬
	bool visited;   //��ǵ�ǰ�����Ƿ��ѱ�����
	int distance, path;   //��ǰ����������������С���루distance���;����Ķ���
};
void CreateGraph(graph*& g) {
	g = new graph;
	cin >> g->n;   //���붥�����
	for (int i = 1; i <= g->n; i++) {
		cin >> g->vertlist[i];   //���붥�����ƣ���A B C...��
		for (int j = 1; j <= g->n; j++) {   //��ʼ���ڽӾ���
			if (i != j) g->edgelist[i][j] = INT_MAX;
			else g->edgelist[i][j] = 0;
		}
	}
	cin >> g->e;   //����߸���
	char temp1, temp2;
	int weight, adj1, adj2;
	for (int i = 1; i <= g->e; i++) {   //���������ϢתΪ�ڽӾ��󴢴�
		cin >> temp1 >> temp2 >> weight;
		for (int j = 1; j <= g->n; j++) {
			if (g->vertlist[j] == temp1) adj1 = j;
			if (g->vertlist[j] == temp2) adj2 = j;
		}
		g->edgelist[adj1][adj2] = weight;
		g->edgelist[adj2][adj1] = weight;   //����ͼ�轻���ڽӵ��ٴ�¼�����Ϣ
	}
}
int Findmin(graph* g, table* t) {   //�ҵ���������Ķ���
	int min = INT_MAX, adjmin;
	for (int i = 1; i <= g->n; i++)
		if (!t[i].visited && t[i].distance < min) {
			min = t[i].distance;
			adjmin = i;
		}
	return adjmin;
}
void Dijkstra(graph* g, table* t, int flag) {   //��flag����������󵽸�������ľ���distance��Dijkstra�㷨��
	for (int i = 1; i <= g->n; i++) {
		t[i].distance = g->edgelist[flag][i];
		t[i].visited = false;
		t[i].path = flag;
	}
	t[flag].visited = true;
	int sum, adjmin;
	for (int i = 1; i < g->n; i++) {   //��Ϊflag�����ѱ�ѡ������˻���ѡ��n-1������
		adjmin = Findmin(g, t);
		t[adjmin].visited = true;
		for (int j = 1; j <= g->n; j++)
			if (!t[j].visited && g->edgelist[adjmin][j] < INT_MAX) {   //ע������ͼһ��Ҫ�ж� g->edgelist[adjmin][j]<INT_MAX
				sum = t[adjmin].distance + g->edgelist[adjmin][j];
				if (sum < t[j].distance) {
					t[j].distance = sum;
					t[j].path = adjmin;
				}
			}
	}
}
int main() {
	graph* g;
	CreateGraph(g);
	table t[100][100];
	for (int i = 1; i <= g->n; i++)
		Dijkstra(g, t[i], i);   //��i����������󵽸�������ľ���distance���洢��t[i]��
	int farthest[100],tempfar;   //farthest[i]Ϊ����ӵ�i�����������Զ�������̾���
	for (int i = 1; i <= g->n; i++) {
		tempfar = 0;
		for (int j = 1; j <= g->n; j++)
			if (tempfar < t[i][j].distance)
				tempfar = t[i][j].distance;
		farthest[i] = tempfar;
	}
	int min = INT_MAX, adjmin;   //adjminΪ��Сֵ���±�
	for(int i=1;i<=g->n;i++)
		if (min > farthest[i]) {
			min = farthest[i];
			adjmin = i;   //adjminΪ����Զ�������̾������Сֵ�ĳ��������±�
		}
	cout << g->vertlist[adjmin] << endl;   //�����һ����Ľ�
	int sum[100] = { 0 };   //��i����������󵽸����������̾���֮��
	for (int i = 1; i <= g->n; i++)
		for (int j = 1; j <= g->n; j++)
			sum[i] += t[i][j].distance;
	min = INT_MAX;   //min����Ϊ�ܴ����
	for (int i = 1; i <= g->n; i++)   //�ҵ���adjmin�������·���ܺ����
		if (min > sum[i]) {
			min = sum[i];
			adjmin = i;
		}
	cout << g->vertlist[adjmin] << endl;   //����ڶ�����Ľ�
	system("pause");
	return 0;
}