#include "node.h"
<<<<<<< HEAD
#define TABLESIZE 4

void rtinit(struct distance_table *table, int node) {
	/*Fill table with INF with table pointer to distancetable struct, so the table will
	be filled with 999 meaning we have no clue of distances between nodes yet*/
	for(int i = 0; i < TABLESIZE; i++){
		for(int j = 0; j < TABLESIZE; j ++){
			table->costs[i][j] = INF; 
		}
	}

	for(int i = 0; i < TABLESIZE; i++){
		//Check if nod is neighbour and set distances
		if(is_neighbor(node, i)){
			table->costs[i][node] = table->costs[node][i];
		}
	}
	//for sending routingupdates to neigbours
	struct rtpkt packet;
	packet.sourceid = node; //node that sends
	
	//if the costs are less than inf than then value is new
	for(int dest = 0; dest < TABLESIZE; dest++){
		packet.mincost[dest] = INF;
		for(int via = 0; via < TABLESIZE; via++){
			if(table->costs[dest][via] < packet.mincost[dest]){
				packet.mincost[dest] = table->costs[dest][via];
			}
		}
	}

	for(int i = 0; i < TABLESIZE; i++){
		if(is_neighbor(node, i)){
			packet.destid = i;
			tolayer2(packet);
		}
	}
	printdt(table, node);
=======
#define MAX_NODES 4

void rtinit(struct distance_table *table, int node) {



for(int i = 0; i < MAX_NODES; i++){
	if(is_neighbor(node, i)){
		table->costs[i][node] = table->costs[node][i];
	} else if (i == node) {
		table->costs[i][node] = 0;
	}
>>>>>>> master
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

