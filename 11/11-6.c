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

void print_bst(struct node *t){
	if(t==NULL) printf(".\n");
	else{
		printf("%d,%s,%d\n", t->data.id, t->data.name, t->data.score);
		print_bst(t->left);
		print_bst(t->right);
	}
}

struct node* bst_delete(struct node *t, int id){

	/*tmpはリンク元記憶用*/
	struct node *tmp = t, *p = t;

	/*削除対象の検索*/
	while(p->data.id != id){
		tmp = p; p = (p->data.id > id ? p->left : p->right);
	}

	struct node *n = p;

	/*nとして根が指定された場合、根を削除しなければならないが、根のリンク元は参照できないので条件分岐を設けて、*/
	/*nすなわちtの示す節点を直接つなぎかえる。以下n==tで条件分岐してあるところは全てこの考え方*/
	if(n->right==NULL){

		/*nのところを置き換える*/
		if(n==t) t = n->left;
		else tmp->data.id > id ? (tmp->left = n->left):(tmp->right = n->left);

	}else if(n->right->left==NULL){

		/*nの右の子の節点で、左の子としてnの左の子、右の子としてnの右の子の右の子を持つ部分木*/
		struct node *tmp_n = n->right;
		tmp_n->left = n->left; tmp_n->right = n->right->right;

		/*nのところを置き換える*/
		if(n==t) t = tmp_n;
		else tmp->data.id > id ? (tmp->left = tmp_n):(tmp->right = tmp_n);

	}else{
		struct node *tmp_n1 = n->right; // nの右の子の節点
		struct node *tmp_n2 = tmp_n1; // tmp_n1のリンク元記憶用

		/*n->rightから左の子を葉の直前まで辿る*/
		while(tmp_n1->left!=NULL){
			tmp_n2 = tmp_n1; tmp_n1 = tmp_n1->left;
		}

		/*nのところに置き換えるのは部分木ではなくデータなので挿入用の節点のポインタを用意*/
		/*nとtmp_n1のdataを入れ替えただけの処理だと、nのメモリ領域を開放したときに*/
		/*おかしくなるので、新しく節点のポインタを用意して、ポインタのつなぎ替えを行わなければならない*/
		struct node *new1 = (struct node*)malloc(sizeof(struct node));
		new1->data = tmp_n1->data; new1->left = n->left; new1->right = n->right;

		/*nのところを置き換える*/
		if(n==t) t = new1;
		else tmp->data.id > id ? (tmp->left = new1):(tmp->right = new1);

		/*tmp_n1があったところにその右の子をいれる*/
		/*左を辿っていたのだから左にリンクさせればよい*/
		tmp_n2->left = tmp_n1->right;

	}

	/*不必要なnのメモリ領域を解放*/
	free(n);

	return t;
}

int main(){
	struct node *t = get_tree();
	int id;
	scanf("%d ", &id);
	t = bst_delete(t, id);
	print_bst(t);
	return 0;
}
