#include "node.h"
#include <string.h>
#define MAX_NODES 4

void sendpkt(struct distance_table *table, int node) {
    struct rtpkt packet;
    packet.sourceid = node;

    for (int neighbor = 0; neighbor < MAX_NODES; neighbor++) {
        if (!is_neighbor(node, neighbor)) continue;

        packet.destid = neighbor;

        int *node_costs = table->costs[node];
        for (int i = 0; i < MAX_NODES; i++) {
            packet.mincost[i] = node_costs[i];
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

    int *node_costs = table->costs[node];

    for (int dest = 0; dest < MAX_NODES; dest++) {
        int current_cost = node_costs[dest];
        int cost_via_source = table->costs[node][pkt->sourceid] + pkt->mincost[dest];

        table->costs[pkt->sourceid][dest] = pkt->mincost[dest];

        if (cost_via_source < current_cost) {
            node_costs[dest] = cost_via_source;
            updated = 1;
        }
    }

    if (updated) {
        sendpkt(table, node);
    }

    printdt(table, node);
}



