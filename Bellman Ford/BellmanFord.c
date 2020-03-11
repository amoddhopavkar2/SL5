#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
	int u, v, cost;
}Edge;

int main() {
	int n, e, start, count = 0;
	int distance[20], parent[20];
	Edge edge[20];
	
	printf("\n---BELLMAN FORD---\n");
	printf("\nNo of vertices: ");
	scanf("%d",&n);
	printf("\nNo of edges: ");
	scanf("%d",&e);

	for (int i=0; i<e; i++) {
		printf("\nENTER EDGE AND ITS COST -->");
		printf("\nStart Vertex: ");
		scanf("%d",&edge[i].u);
		printf("\nEnd Vertex: ");
		scanf("%d",&edge[i].v);
		printf("\nCost: ");
		scanf("%d",&edge[i].cost);
	}

	printf("\n\nENTER THE EDGES -->\n");
	for (int i=0; i<e; i++) {
		printf("%d - %d :: %d",edge[i].u,edge[i].v,edge[i].cost);
		printf("\n");
	}

	for (int i=0; i<n; i++) {
		parent[i] = -1;
		distance[i] = 9999;
	}

	printf("\nENTER STARTING VERTEX: ");
	scanf("%d",&start);
	distance[start] = 0;
	parent[start] = start;

	for (int u=0; u<n; u++) {
		int flag = 0;
		//int count = 0;

		printf("\nNo of Hops = %d",count+1);
		printf("\n\n");
		for (int v=0; v<e; v++) {
			if (distance[edge[v].v] > distance[edge[v].u] + edge[v].cost) {
				distance[edge[v].v] = distance[edge[v].u] + edge[v].cost;
				parent[edge[v].v] = edge[v].u;
				flag = 1;
			}
		}

		for (int c=0; c<n; c++) {
			printf("d[%d] :: %d\t",c,distance[c]);
		}	

		printf("\n");
		for (int c=0; c<n; c++) {
			printf("p[%d] :: %d\t",c,parent[c]);
		}

		printf("\n\n");
		if (flag == 0) {
			break;
		}
		count++;
	}

	for (int v=0; v<e; v++) {
		if (distance[edge[v].v] > distance[edge[v].u] + edge[v].cost) {
			printf("\n\nNegative Cycle generated...");
		}
	}
	return 0;
}
