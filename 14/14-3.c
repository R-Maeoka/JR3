#include <stdio.h>
#include <stdlib.h>
char buf[128];

int main(){
	int ekisu;
	scanf("%d ", &ekisu);
	int **adjmat = (int**)malloc(sizeof(int*)*ekisu);
	for(int i=0;i<ekisu;++i) adjmat[i] = (int*)malloc(sizeof(int)*ekisu);

	//2次元配列を0で初期化
	int i,j;
	for(i=0;i<ekisu;i++)
		for(j=0;j<ekisu;j++) adjmat[i][j] = 0;

	//入力
	int eki1, eki2, rosen;
	float kyori;
	while(fgets(buf,sizeof(buf),stdin)!=NULL){
		sscanf(buf, "%d:%d:%d:%f ", &eki1, &eki2, &rosen, &kyori);

		//入力に応じて隣接行列の要素を1にする
		adjmat[eki1][eki2] = adjmat[eki2][eki1] = 1;

	}

	//出力
	for(i=0;i<ekisu;i++){
		for(j=0;j<ekisu;j++)
			printf("%d", adjmat[i][j]);
		printf("\n");
	}

	return 0;
}
