#include <stdio.h>
#include <stdlib.h>

struct student { int id; char name[32]; int score; };
typedef struct student datatype;
struct node { datatype data; struct node *left, *right; };

void bst_insert(struct node *t, struct student d){
	struct node *tmp = t, *p = t, *new = (struct node*)malloc(sizeof(struct node));
	new->data = d; new->left = new->right = t->left;
	while(p!=t->left){
		tmp = p; p = (p->data.id > d.id ? p->left : p->right);
	}
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

void find_info(struct node *t, int id){
	t->left->data.id = id;
	struct node *p = t->right;
	while(p->data.id != t->left->data.id){
		p = p->data.id>id ? p->left : p->right;
	}

	/*前にやった配列の探索と同じで、tが自分で設定した番兵に戻ってきてしまっていたら見つからなかったということ*/
	p==t->left ? printf("Not found.\n") : printf("%s,%d\n", p->data.name, p->data.score);
	return;
}

int main(){
	char buf[128], c;
	int id;
	struct node *t = (struct node*)malloc(sizeof(struct node)),
		     *dummy = (struct node*)malloc(sizeof(struct node));
	struct student st;
	t->left = t->right = dummy->left = dummy->right = dummy;
	while(fgets(buf,sizeof(buf),stdin)!=NULL){
		sscanf(buf,"%d%c", &id, &c);
		if(c==','){
			sscanf(buf,"%d,%[^,],%d",&st.id,st.name,&st.score);
			bst_insert(t, st);
		}
	}
	print_bst(t);
	find_info(t, id);
	return 0;
}
