#include <stdio.h>
#include <stdlib.h>
char buf[128];

struct student { int id; char name[32]; int score; };
typedef struct student datatype;
struct rb_node { datatype data; struct rb_node *left, *right; int black; };

struct rb_node* get_rbtree(){
	struct rb_node *t;
	char c;
	if(fgets(buf,sizeof(buf),stdin)==NULL || buf[0]=='.')
		return NULL;
	else {
		t = (struct rb_node*)malloc(sizeof(struct rb_node));
		sscanf(buf,"[%c]%d,%[^,],%d",&c,&t->data.id,t->data.name,&t->data.score);
		t->black = (c=='b');
		t->left = get_rbtree(); t->right = get_rbtree();
		return t;
	}
}

int is_red(struct rb_node *t){
	return (t != NULL && !t->black);
}

//条件2
int is_red_balanced(struct rb_node *t){
	if(t->black == 0){
		if(is_red(t->left)||is_red(t->right)) return 0;
	}
	if(t->left != NULL){
		if(is_red_balanced(t->left)==0) return 0;
	}
	if(t->right != NULL){
		if(is_red_balanced(t->right)==0) return 0;
	}
	return 1;
}

//条件3
int is_count_balanced(struct rb_node *t){
	int l_count = 0, r_count = 0;
	if(t->left != NULL) l_count += is_count_balanced(t->left) + t->left->black;
	if(t->right != NULL) r_count += is_count_balanced(t->right) + t->right->black;
	if(l_count==-1||r_count==-1||l_count!=r_count) return -1;
	else return l_count;
}

int is_rbtree(struct rb_node *t){
	if(is_red_balanced(t) && is_count_balanced(t) != -1) return 1;
	else return 0;
}

int main(){
	struct rb_node *t = get_rbtree();
	if(is_rbtree(t)) printf("Yes.\n");
	else             printf("No.\n");
	return 0;
}
