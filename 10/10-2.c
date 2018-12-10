#include <stdio.h>

int count = 0;

struct student { int id; char name[32]; int score; };

int binary_search(struct student st[], int id, int l, int r){
	++count;
	if(r < l) return -1;
	else{
		int m = (l + r) / 2;
		if(st[m].id == id) return m;
		else{ return st[m].id<id ? 
			binary_search(st,id,m+1,r) : binary_search(st,id,l,m-1);}
	}
}

int main(){
	int i = 0, n, v;
	char buf[128], c;
	struct student st[1024];
	while(fgets(buf,sizeof(buf),stdin)!=NULL && i<1024){
		sscanf(buf, "%d%c", &v, &c);
		if(c==','){
			st[i].id = v;
			sscanf(buf, "%*d,%[^,],%d", st[i].name, &st[i].score);
			++i;
		}
	}
	n = i;
	i = binary_search(st, v, 0, n-1);
	if(i < 0) printf("Not found.\n");
	else	  printf("%s,%d\n",st[i].name,st[i].score);
	printf("%d\n", count);
	return 0;
}
