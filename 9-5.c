#include <stdio.h>

struct point { int x, y; };

void radix_sort(struct point a[], int n, int r, int dmax){
	int i, d, c_size = 1;

	/*カウンタ配列の要素数(2^r個)を求めて、宣言。*/
	for(i=0;i<r;i++) c_size *= 2;
	int c[c_size];

	/*nの2^r進法での下からrビットを1桁と見たときの、d桁目ごとにバケツソートの処理をする*/
	for(d=0;d<dmax;d++){

		/*各ループごとにカウンタ配列を0に初期化*/
		for(i=0;i<c_size;i++) c[i] = 0;

		/*以下バケツソートの処理。*/
		/*バケツソートの処理において、カウンタ配列の添え字を(n>>(d*r))&((1<<r)-1)*/
		/*すなわちnの2^r進法での下からd桁目として取り出せば、正しい処理が行える。*/
		struct point b[n];
		for(i=0;i<n;i++){
			b[i] = a[i];
			c[((a[i].x >> (d * r)) & ((1 << r) - 1))]++;
		}
		for(i=1;i<c_size;i++) c[i] += c[i-1];
		for(i=n-1;i>=0;i--){
			struct point p = b[i];
			c[((p.x >> (d * r)) & ((1 << r) - 1))]--;
			a[c[((p.x >> (d * r)) & ((1 << r) - 1))]] = p;
		}
		for(i=0;i<n;i++) printf("%d %d\n", a[i].x, a[i].y);
		printf("--\n");

	}
}

int main(){
	char buf[128];
	struct point p, arr[128];
	int i = 0, n, r, dmax;
	scanf("%d %d ", &r, &dmax);

	while(fgets(buf,sizeof(buf),stdin)!=NULL && i<128){
		sscanf(buf,"%d %d",&p.x,&p.y);
		arr[i] = p;
		++i;
	}
	n = i;
	radix_sort(arr, n, r, dmax);
	return 0;
}
