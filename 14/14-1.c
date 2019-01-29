#include <stdio.h>
#include <stdlib.h>
char buf[128];

struct node { int eki, rosen; float kyori; struct node *next; };

void add_edge(struct node *adjlist[], int eki1, int eki2, int rosen, float kyori){

	//eki1からeki2への辺が追加されるなら、その逆も然りなので、同様の操作を2回行うことになる

	//追加する辺の情報１
	struct node *new1 = (struct node*)malloc(sizeof(struct node));
	new1->eki = eki1; new1->rosen = rosen; new1->kyori = kyori;
	new1->next = adjlist[eki2]; adjlist[eki2] = new1;

	//追加する辺の情報２	
	struct node *new2 = (struct node*)malloc(sizeof(struct node));
	new2->eki = eki2; new2->rosen = rosen; new2->kyori = kyori;
	new2->next = adjlist[eki1]; adjlist[eki1] = new2;

	return;
}

void print_adjlist(struct node *adjlist[], int n){
	int i;
	struct node *p;
	for(i=0;i<n;++i){
		printf("%d:", i);
		p = adjlist[i];
		while(p!=NULL){
			printf(" (%d,%d,%.3f)", p->eki, p->rosen, p->kyori);
			p = p->next;
		}
		printf("\n");
	}
	return;
}

int main(){
	int eki1, eki2, rosen, ekisu, i;
	float kyori;
	scanf("%d ", &ekisu);
	struct node *adjlist[ekisu];
	for(i=0;i<ekisu;++i) adjlist[i] = NULL;
	while(fgets(buf,sizeof(buf),stdin)!=NULL){
		sscanf(buf, "%d:%d:%d:%f ", &eki1, &eki2, &rosen, &kyori);
		add_edge(adjlist, eki1, eki2, rosen, kyori);
	}
	print_adjlist(adjlist, ekisu);
	return 0;
}
