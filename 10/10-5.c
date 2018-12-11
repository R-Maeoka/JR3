#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 101

struct student { int id; char name[32]; int score; };

struct node { struct student data; struct node *next; };

int hash(char *s){
	int i;
	int sum_mod = (int)*s%SIZE;
	for(i=1;*(s+i)!='\0';i++){
		sum_mod = ((sum_mod%SIZE) * 128 + (int)*(s+i))%SIZE;
	}
	return sum_mod;
}

void set_data(struct node *table[], struct student st){
	int i = hash(st.name);
	struct node *tmp = (struct node*)malloc(sizeof(struct node));
	tmp->data = st; tmp->next = table[i]; table[i] = tmp;
}

int find_score(struct node *table[], char *s){
	int i = hash(s);
	while(table[i]!=NULL){

		/*名前があったらbreak*/
		if(strcmp(table[i]->data.name,s)==0) break;

		table[i] = table[i]->next;
	}

	/*最初からtable[i]がNULL、または探索後にNULLということは、目的のdataが見つからなかったということ。*/
	return table[i]==NULL ? -1 : table[i]->data.score;

}

int main(){
	int i, v;
	char buf[128], name[32];
	struct student st;
	struct node *table[SIZE];

	for(i=0;i<SIZE;++i) table[i] = NULL;
	while(fgets(buf,sizeof(buf),stdin)!=NULL){
		sscanf(buf,"%d,",&v);
		if(v > 0){
			sscanf(buf,"%d,%[^,],%d",&st.id,st.name,&st.score);
			set_data(table, st);
		}else
			sscanf(buf,"0,%[^,\n]",name);
	}
	v = find_score(table, name);
	if(v < 0) printf("Not found.\n");
	else	  printf("%d\n", v);
	return 0;
}
