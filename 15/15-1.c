#include <stdio.h>
#define SETMAX 10600

struct set { int elements[SETMAX]; int size; };

void init_set(struct set *p, int n, int e){
	int count=0, i=0;
	p->size = n-1;
	while(count < n){
		if(count==e){
			count++; continue;
		}else{
			p->elements[i] = count;
			i++; count++;
		}
	}
}

void print_set(struct set *p){
	int i;
	printf("{");
	for(i=0;i<p->size;++i) printf(" %d", p->elements[i]);
	printf(" }\n");
}

int main(){
	int n, e;
	struct set s;
	scanf("%d %d ", &n, &e);
	init_set(&s, n, e);
	print_set(&s);
	return 0;
}
