#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define R 200
#define C 200
#define INF (1ll << 62)

double V[R][C];

struct Vertex;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1 ,0, 0};
int vis[R][C];

typedef struct Vertex{
    int x; 
    int y;
    double dist;
    int parentx;
    int parenty;
    struct Vertex* ver;
}Vertex;

int compare(Vertex a, Vertex b) {
    return a.dist >= b.dist;
}

Vertex vertice[R * C] = {};

typedef struct Node {
    Vertex data;
    struct Node* next;
}Node;

Node* sorted_vertices = NULL;

void push(Vertex v) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = v;
    new_node->next = NULL;
    if (sorted_vertices == NULL || compare(sorted_vertices->data, v)) {
        new_node->next = sorted_vertices;
        sorted_vertices = new_node;
    }
    else {
        Node* current = sorted_vertices;
        while (current->next != NULL && compare(v, current->next->data)) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

Vertex pop() {
    Node* temp = sorted_vertices;
    Vertex v = temp->data;
    sorted_vertices = sorted_vertices->next;
    free(temp);
    return v;
}

int empty() {
    return sorted_vertices == NULL;
}

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
            V[i][j] = pow(2.0, V[i][j] - basis);
            V[i][j]/=(double)va;
            Vertex u = {.x = j, .y = i, .dist = INF, .parentx = -1, .parenty = -1, .ver = vertice + i * c + j};
            if (i == 0 && j == 0){
                u.dist = 0;
            }
            vertice[i * c + j] = u;
            
        }
    }
    push(vertice[0]);
    while(!empty()){
        Vertex u = pop();
        int ox = u.x;
        int oy = u.y;
        if (vis[oy][ox]){
            continue; 
        }
        else{
            vis[oy][ox] = 1;
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
                v->ver = v;
                push(*v);
            }
        }
    }
    printf("%.2f\n",vertice[r * c - 1].dist);
    return 0;
}


/*
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define R 200
#define C 200
#define INF (1ll << 62)

double V[R][C];

struct Vertex;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1 ,0, 0};
int vis[R][C];

typedef struct Vertex{
    int x; int y;
    double dist;
    int parentx;
    int parenty;
    struct Vertex* ver;
}Vertex;

int compare(const void* a, const void* b) {
    Vertex* v1 = (Vertex*)a;
    Vertex* v2 = (Vertex*)b;
    return v1->dist > v2->dist;
}

Vertex vertice[R * C] = {};

typedef struct PriorityQueue {
    Vertex* data[R * C];
    int size;
}PriorityQueue;

void init(PriorityQueue* pq) {
    pq->size = 0;
}

int empty(PriorityQueue* pq) {
    return pq->size == 0;
}

void push(PriorityQueue* pq, Vertex* v) {
    pq->data[pq->size] = v;
    pq->size++;
    int i = pq->size - 1;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (compare(pq->data[p], pq->data[i])) {
            Vertex* temp = pq->data[p];
            pq->data[p] = pq->data[i];
            pq->data[i] = temp;
            i = p;
        }
        else {
            break; 
        }
    }
}

void pop(PriorityQueue* pq) {
    if (empty(pq)) return; 
    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;
    int i = 0;
    while (i < pq->size) {
        int l = 2 * i + 1; 
        int r = 2 * i + 2; 
        int min = i; 
        if (l < pq->size && compare(pq->data[min], pq->data[l])) {
            min = l;
        }
        if (r < pq->size && compare(pq->data[min], pq->data[r])) {
            min = r;
        }
        if (min != i) {
            Vertex* temp = pq->data[min];
            pq->data[min] = pq->data[i];
            pq->data[i] = temp;
            i = min; 
        }
        else {
            break; 
        }
    }
}

Vertex* top(PriorityQueue* pq) {
    if (empty(pq)) return NULL; 
    return pq->data[0];
}

void dijkstra(PriorityQueue* sorted_vertices, int r, int c){
    push(sorted_vertices, &vertice[0]);
    while(!empty(sorted_vertices)){
        Vertex* u = top(sorted_vertices);
        pop(sorted_vertices);
        int ox = u->x;
        int oy = u->y;
        if (vis[oy][ox]){
            continue; 
        }
        else{
            vis[oy][ox] = 1;
        }
        for (int i=0;i<4;i++){
            int x = u->x + dx[i];
            int y = u->y + dy[i];
            if ( x >= c || x < 0 || y >= r || y < 0 ) continue;
            Vertex *v = &vertice[y * c + x];
            if (v->dist > u->dist + V[oy][ox]){
                v->dist = u->dist + V[oy][ox];
                v->parentx = u->x;
                v->parenty = u->y;
                v->ver = v;
                push(sorted_vertices, v);
            }
        }
    }
}

int main(){
    int v, r, c;
    scanf("%d %d %d", &v, &r, &c);
    double basis = 0.0;
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            scanf("%le", &V[i][j]);
            if (i == 0 && j == 0){
                basis = V[0][0];
            }
            V[i][j] = pow(2.0, V[i][j] - basis);
            V[i][j]/=(double)v;
            Vertex u = {.x = j, .y = i, .dist = INF, .parentx = -1, .parenty = -1, .ver = vertice + i * c + j};
            if (i == 0 && j == 0){
                u.dist = 0;
            }
            vertice[i * c + j] = u;
            
        }
    }
    PriorityQueue sorted_vertices;
    init(&sorted_vertices);
    dijkstra(&sorted_vertices, r, c);
    printf("%.2f\n",vertice[r * c - 1].dist);
    return 0;
}

*/