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



int partition(struct point a[], int m, int n){

	struct point pivot = a[m];

	int l = m+1, r = n;

	while(1){

		while(l < n && compare(a[l], pivot)==-1) l++;

		while(m < r && compare(a[r], pivot)==1) r--;

		if(l < r){

			struct point tmp = a[l];

			a[l] = a[r];

			a[r] = tmp;

		}else break;

		l++; r--;

	}

	a[m] = a[r]; a[r] = pivot;

	return r;

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

	printf("%d\n", partition(arr, 0, n-1));

	for(i=0;i<n;i++)

		printf("%d %d\n", arr[i].x, arr[i].y);

	return 0;

}
