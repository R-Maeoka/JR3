#include <stdio.h>
#include <stdlib.h>
char buf[128];

struct student { int id; char name[32]; int score; };
typedef struct student datatype;
struct avl_node { datatype data; struct avl_node *left, *right; int height; };

struct avl_node* get_avl(){
	struct avl_node *t;
	if(fgets(buf,sizeof(buf),stdin)==NULL || buf[0]=='.')
		return NULL;
	else {
		t = (struct avl_node*)malloc(sizeof(struct avl_node));
		sscanf(buf,"[%d]%d,%[^,],%d",&t->height,&t->data.id,t->data.name,&t->data.score);
		t->left = get_avl();
		t->right = get_avl();
		return t;
	}
}

int height(struct avl_node *t){
	return t==NULL ? 0 : t->height;
}

void put_height(struct avl_node *t){
	if(t==NULL) return;
	else{
		put_height(t->left);
		put_height(t->right);
		t->height = height(t->left)>height(t->right) ? height(t->left)+1 : height(t->right)+1;
	}
}

struct avl_node* rotate_right(struct avl_node *t){
	if(t==NULL || t->left==NULL) return t;
	struct avl_node *tmp = t->left;
	t->left = tmp->right;
	tmp->right = t;
	put_height(tmp);
	return tmp;
}

struct avl_node* rotate_left(struct avl_node *t){
	if(t==NULL || t->right==NULL) return t;
	struct avl_node *tmp = t->right;
	t->right = tmp->left;
	tmp->left = t;
	put_height(tmp);
	return tmp;
}

struct avl_node* balance(struct avl_node *t){
	int dif = height(t->left) - height(t->right); //左右の部分木の高さの差
	if(dif==-1||dif==0||dif==1) return t;
	else if(dif==2){
		if(height(t->left->left)<height(t->left->right)) t->left = rotate_left(t->left);
		t = rotate_right(t);
	}else if(dif==-2){
		if(height(t->right->right)<height(t->right->left)) t->right = rotate_right(t->right);
		t = rotate_left(t);
	}else{

		/*左右の木の高さの差が3以上のとき、この問題の許容する入力ではない。*/
		fprintf(stderr, "Invalid input for this question.\n"); exit(0); //エラー出力

	}
	return t;
}

void print_avl(struct avl_node *t){
	if(t==NULL)
		printf(".\n");
	else {
		printf("[%d]%d,%s,%d\n",t->height,t->data.id,t->data.name,t->data.score);
		print_avl(t->left);
		print_avl(t->right);
	}
}

int main(){
	struct avl_node *t = get_avl();
	t = balance(t);
	print_avl(t);
	return 0;
}
