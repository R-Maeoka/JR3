#include <stdio.h>
#define SIZE 101

int hash(char *s){
	int i;

	/*和の数列の初項を定義*/
	int sum_mod = (int)*s%128;

	/*変数iでポインタを進める*/
	for(i=1;*(s+i)!='\0';i++){

		/*i>=1での式をコーディング*/
		sum_mod = ((sum_mod%SIZE) * 128 + (int)*(s+i))%SIZE;

	}
	return sum_mod;
}

int main(){
	char s[32];
	scanf("%[^\n]", s);
	printf("%d\n", hash(s));
	return 0;
}
