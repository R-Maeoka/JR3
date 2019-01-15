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

		/*put_heightで左右の部分木の高さを正しく設定する*/
		put_height(t->left);
		put_height(t->right);

		/*メンバheightの更新*/
		t->height = height(t->left)>height(t->right) ? height(t->left)+1 : height(t->right)+1;

	}
}

struct avl_node* rotate_right(struct avl_node *t){

	/*回転ができない場合はそのまま返す*/
	if(t==NULL || t->left==NULL) return t;

	/*以下回転(ポインタのつなぎかえ)*/
	struct avl_node *tmp = t->left;
	t->left = tmp->right;
	tmp->right = t;

	put_height(tmp);
	return tmp;
}

struct avl_node* rotate_left(struct avl_node *t){
	/*rotate_rightと左右対称の操作*/
	if(t==NULL || t->right==NULL) return t;
	struct avl_node *tmp = t->right;
	t->right = tmp->left;
	tmp->left = t;
	put_height(tmp);
	return tmp;
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
	struct avl_node *t;
	char c;
	scanf("%c ",&c);
	t = get_avl();
	if(c=='R')
		t = rotate_right(t);
	else if(c=='L')
		t = rotate_left(t);
	print_avl(t);
	return 0;
}
