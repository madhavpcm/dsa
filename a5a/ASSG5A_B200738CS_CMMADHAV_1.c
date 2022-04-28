#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int ds_makeset(  int* parent, const int x){
    if(parent[x] != -1){
        return -1;
    }
    parent[x] = x;
    return x;
}
int ds_makeset_ranked( int* rank, int* parent, const int x){
    if(parent[x] != -1){
        return -1;
    }
    parent[x] = x;
    rank[x] = 0;
    return x;
}
int ds_find_path_compression(int* parent , const int x, int* perf){
    if(parent[x] != x){
        parent[x] = ds_find_path_compression(parent, parent[x], perf);
    }
    (*perf)++;
    return parent[x];
}
int ds_find(int* parent, const int x, int* perf){
    (*perf)++;
    if(parent[x] != x){
        return parent[ds_find(parent, parent[x], perf)];
    }
    return x;
}
int ds_union_ranked(int* rank, int* parent, const int x, const int y, int i){
    int dummy=0;
    int x_,y_;
    if(i){
        x_ = ds_find_path_compression(parent, x, &dummy) ;
        y_ = ds_find_path_compression(parent, y, &dummy) ;
    }
    else{
        x_ = ds_find(parent, x, &dummy) ;
        y_ = ds_find(parent, y, &dummy) ;
    }
    if( x_ == y_ && x_ != -1 ){
        printf("%d ", x_);
        return dummy;
    }
    if(rank[x_] > rank[y_] ){
        parent[y_] = x_;
        printf("%d ", x_);
        return dummy;
    }
    else if( rank[x_] == rank[y_]){
        parent[y_] = x_;
        rank[x_]++;
        printf("%d ", x_);
        return dummy;
    }
    else{
        parent[x_] = y_;
        printf("%d ", y_);
        return dummy;
    }

}
int ds_union_unranked( int*parent, const int x, const int y, int i){
    int dummy=0;
    int x_, y_;
    if(i){
        x_ = ds_find_path_compression(parent, x, &dummy) ;
        y_ = ds_find_path_compression(parent, y, &dummy) ;
    }
    else{
        x_ = ds_find(parent, x, &dummy) ;
        y_ = ds_find(parent, y, &dummy) ;
    }
    if(x_ == -1 || y_ == -1){
        printf("-1 ");
        return dummy;
    }
    if( x_ == y_ && x_ != -1 ){
        printf("%d ", x_);
        return dummy;
    }
    else{
        parent[y_] = x_;
        printf("%d ", x_);
        return dummy;
    }
}
int main(){
    int pa[10002] = {-1};//no heuristics
    int pb[10002] = {-1};//only ranked union
    int pc[10002] = {-1};//only path compression
    int pd[10002] = {-1};//both ranked union and path compression
    memset(pa, -1, 10002* sizeof(int));/// only memset like this for 0 and -1
    memset(pb, -1, 10002* sizeof(int));
    memset(pc, -1, 10002* sizeof(int));
    memset(pd, -1, 10002* sizeof(int));
    int rb[10002] = {-1};
    int rd[10002] = {-1};
    memset(rb, -1, 10002* sizeof(int));
    memset(rd, -1, 10002* sizeof(int));
    
    char ch;
    int perf=0;
    int perfa=0;
    int perfb=0;
    int perfc=0;
    int perfd=0;
    while(EOF != (ch = fgetc(stdin))){
        if(ch == 'm'){
            int x;scanf("%d", &x);
            ds_makeset(pa, x);        
            ds_makeset_ranked(rb, pb, x);        
            ds_makeset(pc, x);        
            int rc =ds_makeset_ranked(rd, pd, x);        
            printf("%d\n" ,rc);
        }
        if(ch == 'f'){
            int x;scanf("%d", &x);
            int resa=ds_find(pa, x,&perf);
            printf("%d ", resa);
            perfa+=perf;
            perf =0;

            int resb=ds_find(pb, x,&perf);
            perfb+=perf;
            printf("%d ", resb);
            perf =0;

            int resc=ds_find_path_compression(pc, x,&perf);
            perfc+=perf;
            printf("%d ", resc);
            perf =0;

            int resd=ds_find_path_compression(pd, x,&perf);
            perfd+=perf;
            printf("%d ", resd);
            perf =0;
            printf("\n");
        }
        if(ch == 'u'){
            int x, y;scanf("%d %d", &x ,&y);
            perfa+=ds_union_unranked(pa, x, y,0);
            perfb+=ds_union_ranked(rb,pb, x, y,0);
            perfc+=ds_union_unranked(pc, x, y,1);
            perfd+=ds_union_ranked(rd,pd, x, y,1);
            printf("\n");
        }
        if(ch == 's'){
            printf("%d %d %d %d\n", perfa , perfb , perfc ,perfd);
        }
    }


    return 0;
}
