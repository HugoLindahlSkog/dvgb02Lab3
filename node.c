#include "node.h"
#define MAX_NODES 4

void rtinit(struct distance_table *table, int node) {
	// Tables are already initialized
    for(int i = 0; i < MAX_NODES; i++){
		for(int j = 0; j < MAX_NODES; j++){
			table->costs[i][j] = INF;
		}
	}

	table->costs[node][node] = 0;

	/*for(int i = 0; i < MAX_NODES; i++){
		table->costs[node][i] = tolayer2(pkt);
	}*/

	printdt(table, node);
}

void rtupdate(struct distance_table *table, int node, struct rtpkt *pkt) {
	printdt(table, node);
}

