#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007
int x[100001];

int compare(const void *a, const void *b){
	return *(int *)a - *(int *)b;
}

int findSet(int a){
	if (x[a]!=a)
		x[a] = findSet(x[a]);
	return x[a];
}

void setUnion(int a,int b){
	x[findSet(a)] = findSet(b);
}

int main(){
	int y;
	scanf("%d", &y);
	while (y--){
		int n,m,a,b,i,j,count;
		unsigned long long prod;

		scanf("%d%d",&n,&m);
		
        for(i=1;i<=n;i++)
			x[i] = i;
		
        for(i=1;i<=m;i++){
			scanf("%d%d",&a,&b);
			setUnion(a,b);
		}

		for(i=1;i<=n;i++)
			findSet(i);
		
        qsort(x+1,n,sizeof(int),compare);
		
        prod = 1ULL;
		count = 0;

		for(i=1;i<=n;i++){
			for(j=(i+1);j<=n;j++)
				if(x[i]!=x[j])
					break;

			prod = (prod*(j-i)) % MOD;
			count++;
			i = j-1;
		}
		printf("%d %llu\n", count, prod);
	}
	return 0;
}