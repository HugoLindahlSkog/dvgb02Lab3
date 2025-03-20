#include "node.h"
#include <string.h>
#define MAX_NODES 4

//skapa ett packet och skicka till grannar
void sendpkt(struct distance_table *table, int node) {
    struct rtpkt packet;
    packet.sourceid = node; 

    for (int neighbor = 0; neighbor < MAX_NODES; neighbor++) {
        if (!is_neighbor(node, neighbor)) continue; //om inte nodarna är grannar

        packet.destid = neighbor; //nod som ska ta emot paket

        int *node_costs = table->costs[node]; //hämta nodens distanser till andra noder
        for (int i = 0; i < MAX_NODES; i++) {
            packet.mincost[i] = node_costs[i]; //minsta kostnader till packetet
        }

        tolayer2(packet); //send packet
    }
}
//skicka initiala routinginfo till grannar och skriver ut tabellen
void rtinit(struct distance_table *table, int node) {
    sendpkt(table, node);
    printdt(table, node);
}    
//kollar om vägen blir kortare, isåfall updatera tabellen 
void rtupdate(struct distance_table *table, int node, struct rtpkt *pkt) {
    int updated = 0;

    int *node_costs = table->costs[node]; //nodens kostnad

    //hämta information
    for (int dest = 0; dest < MAX_NODES; dest++) {
        int current_cost = node_costs[dest];
        int cost_via_source = table->costs[node][pkt->sourceid] + pkt->mincost[dest];

        //updatera med inkommande
        table->costs[pkt->sourceid][dest] = pkt->mincost[dest];
        //om kortare, updatera
        if (cost_via_source < current_cost) {
            node_costs[dest] = cost_via_source;
            updated = 1;
        }
    }
    //om ändring, skicka updaterade till grannar
    if (updated) {
        sendpkt(table, node);
    }

    printdt(table, node);
}



