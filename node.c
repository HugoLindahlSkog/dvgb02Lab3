#include "node.h"
#define MAX_NODES 4

void rtinit(struct distance_table *table, int node) {



for(int i = 0; i < MAX_NODES; i++){
	if(is_neighbor(node, i)){
		table->costs[i][node] = table->costs[node][i];
	} else if (i == node) {
		table->costs[i][node] = 0;
	}
}


int mincost[MAX_NODES];
for(int i = 0; i < MAX_NODES; i++){
	mincost[i] = table->costs[i][node];
}

for(int destid = 0; destid < MAX_NODES; destid++){
	struct rtpkt packet;
	packet.sourceid = node;
	packet.destid = destid;
	for(int i = 0; i < MAX_NODES; i++){
		packet.mincost[i] = mincost[i];
	}
	//printf("Destid: %d, node: %d\n", destid, node);

	if(destid != node && is_neighbor(destid, node)){
	tolayer2(packet);
	}
}

	printdt(table, node);
}	
void rtupdate(struct distance_table *table, int node, struct rtpkt *pkt) {
	
	int updated = 0;

	for(int dest = 0; dest < MAX_NODES; dest++){
		if(dest == node){
			continue;
		}

		int cost_to_sender = table->costs[node][pkt->sourceid];

		if(cost_to_sender == INF){
			continue;
		}

		int new_cost = pkt->mincost[dest] + cost_to_sender;

		if(new_cost < table->costs[node][dest]){
			table->costs[node][dest] = new_cost;
			table->costs[dest][node] = new_cost;
			updated = 1;
		}
	}

	if(updated){
		for(int i = 0; i < MAX_NODES; i++){
			if(is_neighbor(node, i)){
				struct rtpkt new_pkt;
				new_pkt.sourceid = node;
				new_pkt.destid = i;

				for(int j = 0; j < MAX_NODES; j++){
					new_pkt.mincost[j] = table->costs[node][j];
					
				}
				tolayer2(new_pkt);
			}
		}
	}
	
	printdt(table, node);
}

