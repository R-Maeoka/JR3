#include <stdio.h>

int count = 0;
char kijun;
struct point { int x, y; };

int compare(struct point p1, struct point p2){
	count++;
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

void pushdown(struct point a[], int m, int n){
	int i;
	if(2*m+2 <= n){
		switch(compare(a[2*m+1],a[2*m+2])){
			case 1:
				i = 2*m+1; break;
			default:
				i = 2*m+2; break;
		}
		if(compare(a[i],a[m])>0){
			struct point tmp = a[i];
			a[i] = a[m];
			a[m] = tmp;
			pushdown(a, i, n);
		}
	}else if(2*m+1 == n){
		if(compare(a[2*m+1],a[m])>0){
			struct point tmp = a[2*m+1];
			a[2*m+1] = a[m];
			a[m] = tmp;
		}
	}
}

void heap_sort(struct point a[], int n){
	int k = n/2-1;
	while(k >= 0){
		pushdown(a,k,n-1);
		k--;
	}
	for(k=n-1;k>=1;k--){
		struct point tmp = a[0];
		a[0] = a[k];
		a[k] = tmp;
		pushdown(a,0,k-1);
	}
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
	heap_sort(arr, n);
	printf("%d\n",count);
	for(i=0;i<n;++i)
		printf("%d %d\n", arr[i].x, arr[i].y);
	return 0;
}
