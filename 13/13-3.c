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

int is_red(struct rb_node *t){ return t != NULL && !t->black; }

void print_rbtree(struct rb_node *t){
	if(t==NULL) printf(".\n");
	else {
		printf("[%c]%d,%s,%d\n",t->black?'b':'r',t->data.id,t->data.name,t->data.score);
		print_rbtree(t->left); print_rbtree(t->right);
	}
}

struct rb_node* rotate_right(struct rb_node *t){
	if(t==NULL || t->left==NULL) return t;
	struct rb_node *tmp = t->left;
	t->left = tmp->right;
	tmp->right = t;
	return tmp;
}

struct rb_node* rotate_left(struct rb_node *t){
	if(t==NULL || t->right==NULL) return t;
	struct rb_node *tmp = t->right;
	t->right = tmp->left;
	tmp->left = t;
	return tmp;
}

struct rb_node* resolve_red_pair(struct rb_node *t){

	// Case 1
	if(is_red(t->left)&&is_red(t->left->left)){
		if(is_red(t->right)){
			t->right->black = 1;
			t->black = 0;
			t->left->black = 1;
		}else if(!is_red(t->right)){
			t = rotate_right(t);
			t->right->black = 0;
			t->black = 1;
		}

	// Case 2
	}else if(is_red(t->left)&&is_red(t->left->right)){
		if(is_red(t->right)){
			t->right->black = 1;
			t->black = 0;
			t->left->black = 1;
		}else if(!is_red(t->right)){
			t->left = rotate_left(t->left);
			t = rotate_right(t);
			t->right->black = 0;
			t->black = 1;
		}

	// Case 3
	}else if(is_red(t->right)&&is_red(t->right->left)){
		if(is_red(t->left)){
			t->left->black = 1;
			t->black = 0;
			t->right->black = 1;
		}else if(!is_red(t->left)){
			t->right = rotate_right(t->right);
			t = rotate_left(t);
			t->left->black = 0;
			t->black = 1;
		}

	// Case 4
	}else if(is_red(t->right)&&is_red(t->right->right)){
		if(is_red(t->left)){
			t->left->black = 1;
			t->black = 0;
			t->right->black = 1;
		}else if(!is_red(t->left)){
			t = rotate_left(t);
			t->left->black = 0;
			t->black = 1;
		}
	}

	return t;
}

int main(){
	struct rb_node *t = get_rbtree();
	t = resolve_red_pair(t);
	print_rbtree(t);
	return 0;
}
