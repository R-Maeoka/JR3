#include <stdio.h>
#include <stdlib.h>
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

	/*リストtable[i]の先頭への、stをdataとするリストの挿入手続き*/
	struct node *tmp = (struct node*)malloc(sizeof(struct node));
	tmp->data = st; tmp->next = table[i]; table[i] = tmp;

}

int main(){
	int i;
	char buf[128];
	struct student st;
	struct node *table[SIZE], *p;
	for(i=0;i<SIZE;++i) table[i] = NULL;
	while(fgets(buf,sizeof(buf),stdin)!=NULL){
		sscanf(buf, "%d,%[^,],%d", &st.id, st.name, &st.score);
		set_data(table, st);
	}
	for(i=0;i<SIZE;++i){
		p = table[i];
		while(p!=NULL){
			st = p->data;
			printf("(%d)%d,%s,%d\n", i, st.id, st.name, st.score);
			p = p->next;
		}
	}
	return 0;
}
