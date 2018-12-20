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

void find_info(struct node *t, int id){

	/*tがNULLなら見つからなかったということ*/
	if(t==NULL) printf("Not found.\n");

	/*見つかった場合の処理*/
	else if(t->data.id == id) printf("%s,%d\n", t->data.name, t->data.score);

	else{
		/*現在の節点を根とする部分木に対して、二分探索木の探索アルゴリズムを適応*/
		/*idが根の値より小さいなら左、大きいなら右の部分木を探索する*/
		t->data.id > id ? find_info(t->left, id) : find_info(t->right, id);

	}
}

int main(){
	int id;
	struct node *t = get_tree();
	scanf("%d ", &id);
	find_info(t,id);
	return 0;
}
