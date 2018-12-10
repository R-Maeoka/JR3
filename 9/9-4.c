#include <stdio.h>

struct point { int x, y; };

void bucket_sort(struct point a[], int n){
	int i, c[100] = {};
	struct point b[n];
	for(i=0;i<n;i++){
		b[i] = a[i];
		c[a[i].x]++;
	}
	for(i=1;i<100;i++) c[i] += c[i-1];
	for(i=n-1;i>=0;i--){
		struct point p = b[i];
		c[p.x]--;
		a[c[p.x]] = p;
	}
}

int main(){
	char buf[128];
	struct point p, arr[128];
	int i = 0, n;
	while(fgets(buf,sizeof(buf),stdin)!=NULL && i<128){
		sscanf(buf,"%d %d",&p.x,&p.y);
		arr[i] = p;
		++i;
	}
	n = i;
	bucket_sort(arr, n);
	for(i=0;i<n;i++)
		printf("%d %d\n", arr[i].x, arr[i].y);
	return 0;
}
