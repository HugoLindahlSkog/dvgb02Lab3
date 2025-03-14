#include "node.h"
#include <string.h>
#define MAX_NODES 4

void sendpkt(struct distance_table *table, int node){
	struct rtpkt packet;
	packet.sourceid = node;

	for(int neighbor = 0; neighbor < MAX_NODES; neighbor++){
		if(!is_neighbor(node, neighbor)) continue;

		packet.destid = neighbor;

		for(int i = 0; i < MAX_NODES; i++){
			packet.mincost[i] = table->costs[node][i];
		}
		tolayer2(packet);
	}
}


void rtinit(struct distance_table *table, int node) {

	sendpkt(table, node);
	printdt(table, node);
}	
void rtupdate(struct distance_table *table, int node, struct rtpkt *pkt) {

	int updated = 0;
	int new_cost[MAX_NODES][MAX_NODES];

	memcpy(new_cost, table->costs, sizeof(new_cost));

	for(int dest = 0; dest < MAX_NODES; dest++){
		//if(dest == node) continue;

		
		
		int current_cost = table->costs[node][dest];
		int cost_via_source = table->costs[node][pkt->sourceid] + pkt->mincost[dest];

		table->costs[pkt->sourceid][dest] = pkt->mincost[dest];

		if(cost_via_source < current_cost){
			new_cost[node][dest] = cost_via_source;
			updated = 1;
		}

		
		
	}

	if(updated){
		memcpy(table->costs, new_cost, sizeof(new_cost));
		sendpkt(table, node);
	}
		printdt(table, node);
}

	


