#include <stdio.h>
int image[25][25];
char code,direction;
int a,b,c,fil1,fil2;
int i,j,x,y;
int cor1,cor2,cor3,cor4,cor5,cor6,cor7,cor8;
int cord1,cord2,cord3,cord4,cord5,cord6,cord7,cord8;
int count=0;
int number=0;
int degree;


int fill(int img[25][25],int x, int y, int col){ //part1
    int curr;
    curr = img[x][y];
    img[x][y] = col;
    if (img[x-1][y-1]==curr && x-1>=0 && y-1>=0){
        fill(img, x - 1, y - 1, col);
    }
    if (img[x-1][y]==curr && x-1>=0){
        fill(img,x-1, y, col);
    }
    if (img[x-1][y+1]==curr && x-1>=0 && y+1<25){
        fill(img,x-1,y+1,col);
    }
    if (img[x][y+1]==curr && y+1<25){
        fill(img,x,y+1,col);
    }
    if (img[x+1][y+1]==curr && x+1<25 && y+1<25){
        fill(img,x+1,y+1,col);
    }
    if (img[x+1][y]==curr && x+1<25){
        fill(img,x+1,y,col);
    }
    if (img[x+1][y-1]==curr && x+1<25 && y-1>=0){
        fill(img, x+1, y-1,col);
    }
    if (img[x][y-1]==curr && y-1>=0){
        fill(img,x,y-1,col);
    }
    return 0;
}
int coppas(int img[25][25],int c1,int c2,int c3,int c4,int p1,int p2,int p3,int p4){ //part2
    int t;
    if (c3>c1){
        t=c3;
        c3=c1;
        c1=t;
    }
    if (c4>c2){
        t=c4;
        c4=c2;
        c2=t;
    }
    if (p3>p1){
        t=p3;
        p3=p1;
        p1=t;
    }
    if (p4>p2){
        t=p4;
        p4=p2;
        p2=t;
    }
    x=p3-c3;
    y=p4-c4;
    for(i=c3;i<=c1;i++){
        for (j=c4;j<=c2;j++){
            if (img[i][j]!=img[i+x][j+y]){
                count+=1;
            }
            img[i+x][j+y]=img[i][j];

        }
    }
    return 0;
}
int rotate(int img[25][25],int c1,int c2,int c3,int c4,int p1,int p2,int p3,int p4,int dir, int deg){
    if (dir=='R' || dir=='L'){
        if (deg==0){
            x=p3-c3;
            y=p4-c4;
            for(i=c1;i<=c3;i++){
                for (j=c2;j<=c4;j++){
                    if (img[i][j]!=img[i+x][j+y]){
                        number+=1;
                    }
                    img[i+x][j+y]=img[i][j];
                }
            }
        }
    }
    return 0;
}

int main(){
    for (i = 0; i < 25; i++){
        for (j = 0; j < 25; j++){
            scanf(" %d", &image[i][j]);
        }
    }
    scanf(" %c",&code);
    if (code== 'F'){
        scanf(" %d %d", &a, &b);
        scanf(" %d %d", &fil1, &fil2);
        if (a < 25 && a >= 0 && b < 25 && b >= 0){
            c = image[a][b];
        }
        if (a < 0 && b < 0){
            c = 0;
        }
        if (a < 0 && b >= 0 && b < 25){
            c = 1;
        }
        if (a < 0 && b > 24){
            c = 2;
        }
        if (a >= 0 && a < 25 && b > 24){
            c = 3;
        }
        if (a > 24 && b > 24){
            c = 4;
        }
        if (a > 24 && b >= 0 && b < 25){
            c = 5;
        }
        if (a > 24 && b < 0){
            c = 6;
        }
        if (a >= 0 && a < 25 && b < 0){
            c = 7;
        }

        fill(image, fil1, fil2, c);
        for (i=0; i<25;i++){
            for (j=0; j<25;j++){
                printf("%d ",image[i][j]);
            }
            printf("\n");
        }
    }
    if (code=='P'){
        scanf("%d %d %d %d",&cor1,&cor2,&cor3,&cor4);
        scanf("%d %d %d %d",&cor5,&cor6,&cor7,&cor8);
        coppas(image,cor1,cor2,cor3,cor4,cor5,cor6,cor7,cor8);
        for (i=0; i<25;i++){
            for (j=0; j<25;j++){
                printf("%d ",image[i][j]);
            }
            printf("\n");
        }
        printf("%d\n",count);
    }
    if (code=='R'){
        scanf(" %c %d",&direction,&degree);
        scanf("%d %d %d %d",&cord1,&cord2,&cord3,&cord4);
        scanf("%d %d %d %d",&cord5,&cord6,&cord7,&cord8);
        rotate(image,cord1,cord2,cord3,cord4,cord5,cord6,cord7,cord8,direction,degree);
        for (i=0; i<25;i++){
            for (j=0; j<25;j++){
                printf("%d ",image[i][j]);
            }
            printf("\n");
        }
        printf("%d\n",number);

    }

    return 0;
}