#include <stdio.h>
#include <stdlib.h>

void back_substitution(int n,int m,float a[n][m]){
    for (int i=n-1 ; i>=0 ; i--)
    {
        if (a[i][i] != 0)
        {
            for (int k=i-1 ; k>=0 ; k--)
            {
                float l = a[k][i]/a[i][i];
                for(int j=0;j<m;j++){
                    //printf("%d %d %d\n",i,j,k);
                    a[k][j] -= l*a[i][j];
                }
            }
        }
    }
    printf("\n Echleon Matrix\n");
   for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%0.3f\t",a[i][j]);
        }
        printf("\n");
    } 
    
} 

int forward_elimination(int n,int o,float a[n][o]){
    int c=0;
    for(int i=0;i<n-1;i++){
        if(a[i][i]==0){
            for(int m=i+1;m<n;m++){
                if(a[m][i]!=0){
                    for(int b=0;b<o;b++){
                        float temp= a[i][b];
                        a[i][b] = a[m][b];
                        a[m][b] = temp;
                    }
                    break;
                }
            }
            if(a[i][i]==0) return 0;
        }
        for(int k=1;k<n-i;k++){
            float l = a[i+k][i]/a[i][i];
            for(int j=0;j<o;j++){
                a[i+k][j] -= l*a[i][j];
            }
        }
    }
   for(int i=0;i<n;i++){
       if (i<o && a[i][i]!=0) c++;
    } 
    
    return c;
}


void echleon_form(int n,int m,float a[n][m]){
    int res = forward_elimination(n,m,a);
    printf("Column Matrix");
    back_substitution(n,m,a);
    printf("\nRank of Column Space:%d\nBasis of Column space\n",res);
    for (int i=0 ; i<n ; i++)
    {
        for (int j=0 ; j<res ; j++)
        {
            printf("%0.3f\t",a[i][j]);
        }
        printf("\n");
    }
    float trans_a[m][n];
    for (int i=0 ; i<m ; i++){
        for (int j=0 ; j<n ; j++){
            trans_a[i][j] = a[j][i];
        }
    }
    printf("\n\n Transpose of a matrix (Row Matrix)");
    int res1 = forward_elimination(m,n,trans_a);
    back_substitution(m,n,trans_a);
    printf("\nRank of Row Space:%d\nBasis of Row space\n",res1);
    for (int i=0 ; i<n ; i++)
    {
        for (int j=0 ; j<res ; j++)
        {
            printf("%0.3f\t",a[i][j]);
        }
        printf("\n");
    }
    printf("\nRank of Left Null Space:%d\nBasis of Left Null Space\n",n-res1);
    float left_null_space[n][n-res1];
    if (n-res1 != 0){
    for (int i=0 ; i<n ; i++)
    {
        for (int j=0 ; j<n-res1 ; j++)
        {
            left_null_space[i][j] = 0;
        }
    }
    for (int i=0 ; i<m ; i++)
    {
        if (a[i][i] != 0)
        {
            for (int j = i+1 ; j<n ; j++)
            {
                if (a[i][j] != 0)
                {
                    left_null_space[i][n-j-1] = -a[i][j]/a[i][i];
                    left_null_space[j][n-j-1] = 1;
                }
            }
        }
    }
    for (int i=0 ; i<n ; i++)
    {
        for (int j=0 ; j<n-res ; j++)
        {
            printf ("%0.3f\t",left_null_space[i][j]);
        }
        printf("\n");
    }
    }
    else printf("\nNO LEFT NLL SPACE\n");
    printf("\nRank of Null Space:%d\nBasis of Null space\n",m-res);
    float null_space[m][m-res];
    if (m-res !=0){
    for (int i=0 ; i<m ; i++)
    {
        for (int j=0 ; j<m-res ; j++)
        {
            null_space[i][j] = 0;
        }
    }
    for (int i=0 ; i<n ; i++)
    {
        if (a[i][i] != 0)
        {
            for (int j = i+1 ; j<m ; j++)
            {
                if (a[i][j] != 0)
                {
                    null_space[i][m-j-1] = -a[i][j]/a[i][i];
                    null_space[j][m-j-1] = 1;
                }
            }
        }
    }
    for (int i=0 ; i<m ; i++)
    {
        for (int j=0 ; j<m-res ; j++)
        {
            printf ("%0.3f\t",null_space[i][j]);
        }
        printf("\n");
    }
    }
}

int main(){
    int n,m;
    printf("n m :");
    scanf("%d",&n);
    scanf("%d",&m);
    float a[n][m];
    printf("Enter the elements:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%f",&a[i][j]);
        }
    }
   /*for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++){
            printf("%f ",a[i][j]);
        }
        printf("\n");
    } 
    */
    echleon_form(n,m,a);
    return 0;
}