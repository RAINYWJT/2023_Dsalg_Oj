#include <stdio.h>
#include <string.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <assert.h>

#define R 500
#define C 500
#define INF (1ll << 62)


double V[R][C];

struct Vertex;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1 ,0, 0};
bool vis[R][C];

typedef struct Vertex{
    int x; int y;
    double dist;
    int parentx;
    int parenty;
    Vertex* alliance;
}Vertex;

bool operator>(Vertex a, Vertex b) {
    return a.dist >= b.dist;
}

Vertex vertice[R * C] = {};

std::priority_queue<Vertex, std::vector<Vertex>, std::greater<Vertex>> sorted_vertices;

int main(int argc, char* argv[]){
    int va, r, c;
    
    scanf("%d %d %d", &va, &r, &c);
    
    double basis = 0.0;
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            
            scanf("%le", &V[i][j]);
            
            if (i == 0 && j == 0){
                basis = V[0][0];
            }
            V[i][j] = std::pow(2.0, V[i][j] - basis);
            V[i][j]/=(double)va;
            Vertex u = {.x = j, .y = i, .dist = INF, .parentx = -1, .parenty = -1, .alliance = vertice + i * c + j};
            if (i == 0 && j == 0){
                u.dist = 0;
            }
            vertice[i * c + j] = u;
            
        }
    }
    sorted_vertices.push(vertice[0]);
    while(!sorted_vertices.empty()){
        Vertex u = sorted_vertices.top();
        sorted_vertices.pop();
        int ox = u.x;
        int oy = u.y;
        if (vis[oy][ox]){
            continue; 
        }
        else{
            vis[oy][ox] = true;
        }
        for (int i=0;i<4;i++){
            int x = u.x + dx[i];
            int y = u.y + dy[i];
            if ( x >= c || x < 0 || y >= r || y < 0 ) continue;
            Vertex *v = &vertice[y * c + x];
            if (v->dist > u.dist + V[oy][ox]){
                v->dist = u.dist + V[oy][ox];
                v->parentx = u.x;
                v->parenty = u.y;
                v->alliance = v;
                sorted_vertices.push(*v);
            }
        }
    }
    printf("%.2f\n",vertice[r * c - 1].dist);
    return 0;
}