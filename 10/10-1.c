#include <stdio.h>

struct student { int id; char name[32]; int score; };

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
	struct student dum = {0, "dum", v};
	st[n] = dum;
	for(i=0;;i++){
		if(st[i].score == st[n].score) break;
	}
	if(i==n){ printf("Not found.\n"); }
	else{ printf("%d,%s\n",st[i].id,st[i].name); }
	return 0;
}
