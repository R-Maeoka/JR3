#include <stdio.h>
#include <stdlib.h>
char buf[128];

typedef char datatype;
struct node { datatype data; struct node *left, *right; };

struct node* get_tree() {
	struct node *t;
	if(fgets(buf,sizeof(buf),stdin)==NULL || buf[0]=='.')
		return NULL;
	else {
		t = (struct node*)malloc(sizeof(struct node));
		sscanf(buf,"%c ",&t->data);
		t->left = get_tree();
		t->right = get_tree();
		return t;
	}
}

/*それぞれのなぞり方の定義をそのまま書き起こしただけ*/

void print_preorder(struct node *t){
	if(t==NULL) return;
	else{
		printf("%c", t->data);
		print_preorder(t->left);
		print_preorder(t->right);
	}
}

void print_inorder(struct node *t){
	if(t==NULL) return;
	else{
		print_inorder(t->left);
		printf("%c", t->data);
		print_inorder(t->right);
	}
}

void print_postorder(struct node *t){
	if(t==NULL) return;
	else{
		print_postorder(t->left);
		print_postorder(t->right);
		printf("%c", t->data);
	}
}

int main(){
	struct node *t = get_tree();
	print_preorder(t);  printf("\n");
	print_inorder(t);   printf("\n");
	print_postorder(t); printf("\n");
	return 0;
}
