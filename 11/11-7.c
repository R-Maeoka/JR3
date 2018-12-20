#include <stdio.h>
#include <stdlib.h>

struct student { int id; char name[32]; int score; };
typedef struct student datatype;
struct node { datatype data; struct node *left, *right; };

void bst_insert(struct node *t, struct student d){

	/*t->leftをダミーとして考える(そうでなければ提出すべきプログラムの形式に合わない)*/
	/*あとはt->leftを基準にして探索を行い、課題5とほぼ同様の形式で挿入を行う*/
	/*NULLポインタを用いないので空の二分探索木を特別扱いしなくていい*/
	struct node *tmp = t, *p = t, *new = (struct node*)malloc(sizeof(struct node));
	new->data = d; new->left = new->right = t->left;
	while(p!=t->left){
		tmp = p; p = (p->data.id > d.id ? p->left : p->right);
	}

	/*挿入手続き(特別扱い無し)*/
	tmp->data.id > d.id ? (tmp->left = new):(tmp->right = new);

}

void print_bst_dummy(struct node *t, struct node *dummy){
	if(t==dummy)
		printf(".\n");
	else {
		printf("%d,%s,%d\n",t->data.id,t->data.name,t->data.score);
		print_bst_dummy(t->left,dummy);
		print_bst_dummy(t->right,dummy);
	}
	return;
}

void print_bst(struct node *t){
	print_bst_dummy(t->right,t->left);
	return;
}

int main(){
	char buf[128];
	struct node *t = (struct node*)malloc(sizeof(struct node)),
		    *dummy = (struct node*)malloc(sizeof(struct node));
	struct student st;
	t->left = t->right = dummy->left = dummy->right = dummy;
	while(fgets(buf,sizeof(buf),stdin)!=NULL){
		sscanf(buf,"%d,%[^,],%d",&st.id,st.name,&st.score);
		bst_insert(t, st);
	}
	print_bst(t);
	return 0;
}
