#include <stdio.h>
#include <stdlib.h>
int main(){
    int n; printf("Enter number of lines: "); if(scanf("%d",&n)!=1) return 1;
    for(int i=1;i<=n;i++){
        for(int s=0;s<n-i;s++) printf(" ");
        for(int j=1;j<=2*i-1;j++) printf("%d", i%10);
        printf("\n");
    }
    return 0;
}
