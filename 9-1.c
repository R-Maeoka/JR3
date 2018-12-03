#include <stdio.h>

char kijun;
struct point { int x, y; };

int compare(struct point p1, struct point p2){
	if(kijun=='X'){
		if(p1.x==p2.x){
			if(p1.y==p2.y) return 0;
			else return p1.y>p2.y ? 1 : -1;
		}else{
			return p1.x>p2.x ? 1 : -1;
		}
	}else if(kijun=='Y'){
		if(p1.y==p2.y){
			if(p1.x==p2.x) return 0;
			else return p1.x>p2.x ? 1 : -1;
		}else{
			return p1.y>p2.y ? 1 : -1;
		}
	}else if(kijun=='D'){
		if(p1.x*p1.x+p1.y*p1.y==p2.x*p2.x+p2.y*p2.y){
			if(p1.x==p2.x){
				if(p1.y==p2.y) return 0;
				else return p1.y>p2.y ? 1 : -1;
			}else{
				return p1.x>p2.x ? 1 : -1;
			}
		}else return p1.x*p1.x+p1.y*p1.y>p2.x*p2.x+p2.y*p2.y ? 1 : -1;
	}else{
		return 0;
	}	
}

int is_heap(struct point a[], int n){
	int i, result = 1;
	for(i=0;i<n;i++){
		if(2*i+1<n){
			if(compare(a[i],a[2*i+1])<0) result = 0;
		}
		if(2*i+2<n){
			if(compare(a[i],a[2*i+1])<0) result = 0;
		}
	}
	return result;
}

int main(){
	char buf[128];
	struct point p, arr[128];
	int i = 0, n;
	scanf("%c ",&kijun);
	while(fgets(buf,sizeof(buf),stdin)!=NULL && i<128){
		sscanf(buf,"%d %d",&p.x,&p.y);
		arr[i] = p;
		++i;
	}
	n = i;
	if(is_heap(arr,n)) printf("Yes.\n");
	else printf("No.\n");
	return 0;
}
