#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 101

struct student { char name[32]; int score; };

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

	/*p->next!=NULLを条件に探索するので先頭からスタート*/
	struct node *p = table[i];

	/*末尾探索*/
	while(p->next != NULL) p = p->next;

	/*末尾への挿入手続き*/
	struct node *tmp = (struct node*)malloc(sizeof(struct node));
	tmp->data = st; p->next = tmp; tmp->next = NULL;

}

void update_score(struct node *table[], struct student st){
	int i = hash(st.name);

	/*先頭の次を指すポインタを用意*/
	struct node *p = table[i]->next;

	/*指定された名前があるかハッシュ表を検索(あったら更新)*/
	while(p!=NULL){
		if(strcmp(p->data.name,st.name)==0){
			p->data.score += st.score; break;
		}
		p = p->next;
	}

	/*ハッシュ表にないなら追加*/
	if(p==NULL) set_data(table, st);

}

int main(){
	int i, v;
	char buf[128], name[32];
	struct student st;
	struct node *table[SIZE], *p;

	/*末尾探索をしょっちゅう行うので頭つきで宣言する*/
	for(i=0;i<SIZE;++i) table[i] = (struct node*)malloc(sizeof(struct node));

	/*入力は10000行以下*/
	i = 0;
	while(fgets(buf,sizeof(buf),stdin)!=NULL && i<10000){
		sscanf(buf,"%[^,],%d", st.name, &st.score);

		/*stがtableにあれば、scoreを足して更新、無ければ出力形式に合うようなハッシュ表への追加を行う*/
		update_score(table, st);

		i++;
	}
	for(i=0;i<SIZE;++i){
		p = table[i]->next;
		while(p!=NULL){
			st = p->data;
			printf("%s,%d\n", st.name, st.score);
			p = p->next;
		}
	}
	return 0;
}
