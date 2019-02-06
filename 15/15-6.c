#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SETMAX 10600
char buf[256];

struct station { int eki; char name[64], rosen[64]; };

int main(){
	int i=0, ekisize, l, r, m;
	struct station *ekidata[SETMAX], *st;
	char ekiname[64];
	FILE *fp = fopen("./ekisen.txt", "r");
	while(fgets(buf,sizeof(buf),fp)!=NULL && i<SETMAX){
		st = (struct station*)malloc(sizeof(struct station));
		sscanf(buf, "%[^:]:%d:%[^\n]*c", st->name, &st->eki, st->rosen);
		ekidata[i] = st;
		++i;
	}
	fclose(fp);
	ekisize = i;
	scanf("%[^\n]%*c",ekiname);
	l=0; r=ekisize-1;
	while(l<=r){
		m=(l+r)/2;
		if(strcmp(ekiname, ekidata[m]->name)==0) break;
		else if(strcmp(ekiname, ekidata[m]->name)>0) l = m+1;
		else r = m-1;
	}
	if(r<l){
		fprintf(stderr, "%s: 駅名がありません\n", ekiname); exit(1);
	}else{
		while(m>0 && m<ekisize && strcmp(ekiname, ekidata[m]->name)==0){
			if(strcmp(ekiname, ekidata[m-1]->name)==0) m = m-1;
			else break;
		}
		while(strcmp(ekiname, ekidata[m]->name)==0){
			printf("%d:%s\n", ekidata[m]->eki, ekidata[m]->rosen);
			m++;
		}
	}
	return 0;
}
