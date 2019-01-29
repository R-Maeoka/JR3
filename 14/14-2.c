#include <stdio.h>
#include <stdlib.h>
char buf[128];

struct node { int eki, rosen; float kyori; struct node *next; };

void add_edge(struct node *adjlist[], int eki1, int eki2, int rosen, float kyori){
	struct node *new1 = (struct node*)malloc(sizeof(struct node));
	new1->eki = eki1; new1->rosen = rosen; new1->kyori = kyori;
	new1->next = adjlist[eki2]; adjlist[eki2] = new1;	
	struct node *new2 = (struct node*)malloc(sizeof(struct node));
	new2->eki = eki2; new2->rosen = rosen; new2->kyori = kyori;
	new2->next = adjlist[eki1]; adjlist[eki1] = new2;
	return;
}

float two_hop_kyori(struct node *adjlist[], int eki){

	//求める最大値
	float max = 0.000;

	struct node *p1 = adjlist[eki];
	while(p1!=NULL){

		//p1で参照しているポインタのekiにadjlistの添字が対応するポインタを持ってくる
		struct node *p2 = adjlist[p1->eki];

		//p1->kyoriと合わせて最大値探索
		while(p2!=NULL){

			//p2->ekiがekiと同じなら、ただの往復なので除外
			if(p2->eki != eki && p1->kyori + p2->kyori >= max) max = p1->kyori + p2->kyori;

			p2 = p2->next;
		}

		p1 = p1->next;
	}

	return max;
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
	for(i=0;i<ekisu;++i)
		printf("%d: %.3f\n", i, two_hop_kyori(adjlist, i));
	return 0;
}
