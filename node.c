#include "node.h"
#define MAX_NODES 4

void rtinit(struct distance_table *table, int node) {
	// Tables are already initialized
	struct rtpkt pkt;
	pkt.sourceid = node;

    for(int i = 0; i < MAX_NODES; i++){
		pkt.mincost[i] = table->costs[i][node];
	}
	
	for(int i = 0; i < MAX_NODES; i++){
		if(is_neighbor(node, i)){
			pkt.destid = i;
			tolayer2(pkt);
		}
	}

	printdt(table, node);
}

void rtupdate(struct distance_table *table, int node, struct rtpkt *pkt) {
	int source = pkt->sourceid;
	int updated = 0;

	for(int i = 0; i < MAX_NODES; i++){
		int new_cost = pkt->mincost[i] + table->costs[source][node];
		if(new_cost < table->costs[i][node]){
			table->costs[i][node] = new_cost;
			updated = 1;
		}
	}

	if(updated){
		struct rtpkt new_pkt;
		new_pkt.sourceid = node;
		for(int i = 0; i < MAX_NODES; i++){
			new_pkt.mincost[i] = table->costs[i][node];
		}
		for(int i = 0; i < MAX_NODES; i++){
			if(is_neighbor(node, i)){
				new_pkt.destid = 1;
				tolayer2(new_pkt);
			}
		}
	}

	//printdt(table, node);
}

