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
		if(is_neighbor(node, i)){
			table->costs[i][i] = get_link_cost(node, i);
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
}

void rtupdate(struct distance_table *table, int node, struct rtpkt *pkt) {
	printdt(table, node);
}

