#include <stdio.h>
#include <stdlib.h>
char buf[128];

typedef int datatype;
struct node { datatype data; struct node *left, *right; };

struct node* get_tree() {
	struct node *t;
	if(fgets(buf,sizeof(buf),stdin)==NULL || buf[0]=='.')
		return NULL;
	else {
		t = (struct node*)malloc(sizeof(struct node));
		sscanf(buf,"%d ",&t->data);
		t->left = get_tree();
		t->right = get_tree();
		return t;
	}
}

void print_tree(struct node *t){
	if(t==NULL){

		/*葉に到達したら"-"を出力*/
		printf("-");

	}else{
		printf("%d(", t->data);

		/*現在の節点の左の節点を根とするような部分木に対して再帰的呼び出し*/
		print_tree(t->left);

		printf(",");

		/*現在の節点の右の節点を根とするような部分木に対して再帰的呼び出し*/
		print_tree(t->right);

		printf(")");
	}		
}

int main(){
	struct node *t = get_tree();
	print_tree(t);
	printf("\n");
	return 0;
}
