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

int size(struct node *t){
	if(t==NULL){

		/*葉は節点には含まれない*/
		return 0;

	}else{

		/*現在の節点に対して,両方の節点について再帰呼び出し*/
		/*葉に到達したら０を返すように基底を設定してある*/
		/*よって以下のような呼び出し方をすれば全体のsizeが再帰的に求まる。*/
		return 1+size(t->left)+size(t->right);

	}
}

int height(struct node *t){
	
	if(t==NULL) return 0;

	/*現在の節点の右、左の部分木の高さを比べて、*/
	/*高いほうに1足して葉に到達するまで呼び出し続けるという考え方*/
	else return height(t->left) > height(t->right) ? height(t->left)+1 : height(t->right)+1;

}

int sum(struct node *t){

	/*size関数の考え方(全部の節点をカバーできるような呼び出し方)をそのまま適応する*/
	if(t==NULL) return 0;
	else return t->data+sum(t->left)+sum(t->right);

}

int main(){
	struct node *t = get_tree();
	printf("%d\n", size(t));
	printf("%d\n", height(t));
	printf("%d\n", sum(t));
	return 0;
}
		
