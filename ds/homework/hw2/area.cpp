#include<iostream>
#include"../../queue/queue.h"
//#include<queue>
using namespace std;
int main(){
	int n,a,b,shu[150],min,min1,max,max1,minmost,area[150],maxarea=0,count;
	//Queue<int> myqueue;
	//Queue<int> myqueue1;
	//scanf("%d",&b);
	for(int i=0;i<10;i++){
		for(int k=0;k<b;k++){
			b=rand()%150+1;
			a=rand()%150+1;
			shu[k]=a;
			//myqueue.enqueue(a);
			//myqueue1.enqueue(a);
		}
		for (int k=0;k<b;k++){
			for(int j=k;j>=0;j--){
				if(shu[j]<shu[k]){
					min=shu[j];
					min1=j;
					break;
				}
			}
			for(int j=k;j<b;j++){
				if(shu[j]<shu[k]){
					max=shu[j];
					max1=j;
					break;
				}
			}
			if(min<max){
				minmost=min;
			}
			else{
				minmost=max;
			}
			count=max1-min1+1;
			area[k]=count*minmost;
			if(maxarea<area[k]){
				maxarea=area[k];
			}
		}
		cout<<maxarea<<endl;
	}
	return 0;
}
