#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define ROSENZU "rosenzu.txt"
#define SETMAX 10600
char buf[256];
int dist[SETMAX];
int prev[SETMAX];
int hop[SETMAX];

struct node { int eki, rosen, kyori; struct node *next; };
struct set { int elements[SETMAX]; int size; };

void init_set(struct set* p, int n, int e)
{
    int j = 0;
    int i = 0;
    p->size = n - 1;
    while (i < n) {
        if (i != e) {
            p->elements[j] = i;
            j++;
        }
        i++;
    }
}

int delete_min(struct set *p){
	if(p->size==0) return -1;
	else{
		int i, min_index = 0;
		for(i=0;i<p->size;i++){
			if(dist[p->elements[min_index]] > dist[p->elements[i]]) min_index = i;
			else if(dist[p->elements[min_index]] == dist[p->elements[i]]){
				if(hop[p->elements[min_index]] > hop[p->elements[i]]) min_index = i;
				else if(hop[p->elements[min_index]] == hop[p->elements[i]]){
					if(prev[p->elements[min_index]] > prev[p->elements[i]]) min_index = i;
				}
			}
		}
		int min = p->elements[min_index];
		p->elements[min_index] = p->elements[p->size-1];
		p->size--;
		return min;
	}
}

void add_edge(struct node *adjlist[], int eki1, int eki2, int rosen, int kyori){
	struct node *new1 = (struct node*)malloc(sizeof(struct node));
	new1->eki = eki1; new1->rosen = rosen; new1->kyori = kyori;
	new1->next = adjlist[eki2]; adjlist[eki2] = new1;
	struct node *new2 = (struct node*)malloc(sizeof(struct node));
	new2->eki = eki2; new2->rosen = rosen; new2->kyori = kyori;
	new2->next = adjlist[eki1]; adjlist[eki1] = new2;
	return;
}

int dijkstra_path(struct node *adjlist[], int eki1, int eki2, int ekisu){
	int i;

	// 1
	for(i=0;i<SETMAX;i++){
		if(i==eki1) dist[i] = hop[i] = 0;
		else dist[i] = hop[i] = INT_MAX;
	}

	// 2
	int cur = eki1;
	struct set unknown;
	init_set(&unknown, ekisu, eki1);

	// 3
	while(unknown.size!=0 || cur!=eki2){
		if(cur<0) break;

		// i
		struct node *p = adjlist[cur];
		for(;p!=NULL;p=p->next){
			int min_sub = dist[p->eki]; //curに隣接する駅への最短距離候補
			int kyori_sub = dist[cur] + p->kyori; //cur経由での距離
			if(min_sub > kyori_sub){
				dist[p->eki] = kyori_sub;
				hop[p->eki] = hop[cur] + 1;
				prev[p->eki] = cur;
			}else if(min_sub==kyori_sub && hop[p->eki]>hop[cur]+1){
				dist[p->eki] = kyori_sub;					
				hop[p->eki] = hop[cur] + 1;
				prev[p->eki] = cur;
		        }else if(min_sub==kyori_sub && hop[p->eki]==hop[cur]+1 && prev[p->eki]>cur){
				dist[p->eki] = kyori_sub;
				hop[p->eki] = hop[cur] + 1;
				prev[p->eki] = cur;
			}
		}

		// ii
		cur = delete_min(&unknown);
	}

	// 4
	return dist[eki2];
}

int main(){
	int eki, eki1, eki2, rosen, ekisu, i, kyori;
	FILE *fp = fopen(ROSENZU,"r");
	fscanf(fp, "%d ", &ekisu);
	struct node *adjlist[ekisu];
	for(i=0;i<ekisu;++i) adjlist[i] = NULL;
	while(fgets(buf,sizeof(buf),fp)!=NULL) {
		sscanf(buf, "%d:%d:%d:%d ", &eki1, &eki2, &rosen, &kyori);
		add_edge(adjlist, eki1, eki2, rosen, kyori);
	}
	fclose(fp);
	scanf("%d %d ", &eki1, &eki2);
	kyori = dijkstra_path(adjlist, eki1, eki2, ekisu);
	printf("%d:", kyori);
	eki = eki2;
	for(i=0;i<hop[eki2];++i) {
		printf(" %d <-", eki);
		eki = prev[eki];
	}
	if(eki!=eki1) { fprintf(stderr,"hop or prev is invalid.\n"); exit(1); }
	printf(" %d\n", eki);
	return 0;
}
