#include <stdio.h>
#include <stdlib.h>
char buf[128];

struct student { int id; char name[32]; int score; };
typedef struct student datatype;
struct node { datatype data; struct node *left, *right; };

struct node* get_tree(){
	struct node *t;
	if(fgets(buf,sizeof(buf),stdin)==NULL || buf[0]=='.')
		return NULL;
	else{
		t = (struct node*)malloc(sizeof(struct node));
		sscanf(buf,"%d,%[^,],%d",&t->data.id,t->data.name,&t->data.score);
		t->left = get_tree();
		t->right = get_tree();
		return t;
	}
}

struct node* bst_insert(struct node *t, struct student d){

	/*newは挿入する節点のポインタ*/
	struct node *tmp = t, *p = t, *new = (struct node*)malloc(sizeof(struct node));
	new->data = d; new->left = new->right = NULL;

	/*二分探索木の条件を満たすようなたどり方を、葉に到達するまでやる*/
	/*葉をノードに置き換えるためにtmpでひとつ前の節点のアドレスを保存している*/
	while(p!=NULL){
		tmp = p; p = (p->data.id > d.id ? p->left : p->right);
	}

	/*挿入手続き(空の二分探索木は特別扱い)*/
	if(tmp==NULL) t = new;
	else tmp->data.id > d.id ? (tmp->left = new):(tmp->right = new);

	return t;

}

void print_bst(struct node *t){
	if(t==NULL) printf(".\n");
	else{
		printf("%d,%s,%d\n", t->data.id, t->data.name, t->data.score);
		print_bst(t->left);
		print_bst(t->right);
	}
}

int main(){
	struct node *t = get_tree();
	struct student d;
	scanf("%d,%[^,],%d ", &d.id, d.name, &d.score);
	t = bst_insert(t, d);
	print_bst(t);
	return 0;
}
