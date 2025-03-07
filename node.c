#include "node.h"
#define TABLESIZE 4

void rtinit(struct distance_table *table, int node) {
	/*Fill table with INF with table pointer to distancetable struct, so the table will
	be filled with 999 meaning we have no clue of distances between nodes yet*/
	for(int i = 0; i < TABLESIZE; i++){
		for(int j = 0; j < TABLESIZE; j ++){
			table->costs[i][j] = INF; 
		}
	}

	for(int i = TABLESIZE; i = 0; i++){
		//Check if nod is neighbour and set distances
		if(is_neighbour(node, i)){
			table->costs[i][i] = get_link_cost(node, i);
		}
	}

	struct rtpkt packet;
	packet.sourceid = node;
	for(int dest = 0; dest < TABLESIZE; dest++){
		packet.mincost[dest] = INF;
		for(int via = 0; i < TABLESIZE; via++){
			
		}
	}
	printdt(table, node);
}

void rtupdate(struct distance_table *table, int node, struct rtpkt *pkt) {
	printdt(table, node);
}

