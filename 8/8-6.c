#include <stdio.h>
#include <stdlib.h>

int count = 0;
char kijun;

struct point { int x, y; };
typedef struct point elementtype;

struct node { elementtype element; struct node *next; };
typedef struct node* list;

int compare(struct point p1, struct point p2){
	++count;
	if(kijun=='X'){
		if(p1.x==p2.x){
			if(p1.y==p2.y) return 0;
			else return p1.y>p2.y ? 1 : -1;
		}else{
			return p1.x>p2.x ? 1 : -1;
		}
	}else if(kijun=='Y'){
		if(p1.y==p2.y){
			if(p1.x==p2.x) return 0;
			else return p1.x>p2.x ? 1 : -1;
		}else{
			return p1.y>p2.y ? 1 : -1;
		}
	}else if(kijun=='D'){
		if(p1.x*p1.x+p1.y*p1.y==p2.x*p2.x+p2.y*p2.y){
			if(p1.x==p2.x){
				if(p1.y==p2.y) return 0;
				else return p1.y>p2.y ? 1 : -1;
			}else{
				return p1.x>p2.x ? 1 : -1;
			}
		}else return p1.x*p1.x+p1.y*p1.y>p2.x*p2.x+p2.y*p2.y ? 1 : -1;
	}else{
		return 0;
	}	
}

void split(list l1, list l2){
	list p1 = l1->next, p2 = l1->next;
	while(p2->next != NULL && p2->next->next != NULL){
		p2 = p2->next->next; p1 = p1->next;
	}
	l2->next = p1->next; p1->next = NULL;
}

void merge(list l1, list l2){
	l2 = l2->next;
	while(l2 != NULL){

		/*compare(l->next->element, l2->element)==-1を条件にすると安定ソートにならないことに注意*/
		/*l1->next->elementで比較を行うことにより、比較しているl1の要素の直前に挿入できる*/
		while(l1->next!=NULL && compare(l1->next->element, l2->element)<=0) l1 = l1->next;

		/*l2の要素をelementとするリストをl1に挿入*/
		list tmp = (list)malloc(sizeof(struct node));
		tmp->element = l2->element;
		tmp->next = l1->next; l1->next = tmp;

		/*比較した分、リストを進める。*/
		l2 = l2->next; l1 = l1->next;

	}
}

void merge_sort(list l){

	/*要素が1つになるまで分割し続けるための場合わけ*/
	if(l->next->next != NULL){

		/*分割用リスト*/
		list l2 = (list)malloc(sizeof(struct node));

		/*分割して*/
		split(l, l2);

		/*分割後のそれぞれのリストに対してmerge_sortで昇順に整列*/
		merge_sort(l); merge_sort(l2);

		/*昇順に整列してあるl,l2をmerge*/
		merge(l, l2);

	}
}

int main(){
	char buf[128];
	struct point p;
	list l, last;
	scanf("%c ",&kijun);

	last = l = (list)malloc(sizeof(struct node));
	while(fgets(buf,sizeof(buf),stdin)!=NULL){
		sscanf(buf,"%d %d",&p.x,&p.y);
		last = last->next = (list)malloc(sizeof(struct node));
		last->element = p;
	}
	last->next = NULL;

	merge_sort(l);

	printf("%d\n", count);
	while((l=l->next) != NULL){
		p = l->element;
		printf("%d %d\n", p.x, p.y);
	}
	return 0;
}
