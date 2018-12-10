#include <stdio.h>

int count = 0;
char kijun;

struct point { int x, y; };

int compare(struct point p1, struct point p2){
	++count;
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

void merge(struct point a[], int m, int n, int h){

	/*添え字をnumとする別の配列を用意*/
	struct point arr[n-m+1];
	int i = m, j = h+1, num = 0;

	while(num < n-m+1 && i <= h && j <= n){

		/*aの前半と後半を比べる*/
		switch(compare(a[i], a[j])){
			case 1:
				arr[num] = a[j];
				num++; j++; break;
			case -1:
				arr[num] = a[i];
				num++; i++; break;

			/*等しいときは安定性の観点から添え字の小さい方から別の配列にいれる*/
			case 0:
				arr[num] = a[i];
				num++; i++; break;
			default:
				break;

		}
	}
	int k;

	/*前半でも後半でも、残った要素は別の配列にそのまま移す。*/
	for(k = num; k <= n; k++){
		if(i > h && j <= n){
			arr[k] = a[j]; j++;
		}else if(i <= h && j > n){
			arr[k] = a[i]; i++;
		}else{
			break;
		}
	}

	/*aの前半と後半のmerge後である別の配列を、添字に注意してaにコピー*/
	for(k = m; k <= n; k++) a[k] = arr[k-m];
}

void merge_sort(struct point a[], int m, int n){
	if(m < n){
		int h = (m+n)/2;
		merge_sort(a, m, h);
		merge_sort(a, h+1, n);
		merge(a, m, n, h);
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
	merge_sort(arr, 0, n-1);
	printf("%d\n", count);
	for(i=0;i<n;++i)
		printf("%d %d\n", arr[i].x, arr[i].y);
	return 0;
}
