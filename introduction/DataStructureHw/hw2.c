#include<stdio.h>

struct node{
    int weight;
    int link_node[1000]; // save the points which can link
    int link_num; // numberd of the points which can link
}node[1000];
// judge visited, points' parent, queue
int visited[1000], parent[1000], wait_list[1000];
int total_cost = 0;

// use BFS build tree
void BFS(int now_node, int node_num, int packet_size){
    // the number save in the queue, queue's first, queue's last
    int wait_num = 1, wait_first = 0, insert_num = 1;
    wait_list[0] = now_node;
    visited[0] = 1;
    // while queue is not empty
    while(wait_num != 0){
        wait_num--;
        for(int i = 0; i < node[wait_list[wait_first]].link_num; i++){
            // check queue first node's friends
            int now_link_node = node[wait_list[wait_first]].link_node[i];
            if(!visited[now_link_node]){
                visited[now_link_node] = 1;
                parent[now_link_node] = wait_list[wait_first];
                wait_list[insert_num++] = now_link_node;
                wait_num++;
            }
        }
        // move next
        wait_first++;
    }
	return;
}

void calc(int node_num, int packet_size){
    // start from the last queue, and push their weight to their parent
    for(int i = node_num-1; i > 0; i--){
        int added = parent[wait_list[i]];
        node[added].weight += node[wait_list[i]].weight;
        // check packet size
        if(node[wait_list[i]].weight % packet_size != 0){
            total_cost += node[wait_list[i]].weight / packet_size + 1;
        }else{
            total_cost += node[wait_list[i]].weight / packet_size;
        }
    }
    return;
}

int main(){
    int node_num, link_num, packet_size;
    scanf("%d %d %d", &node_num, &link_num, &packet_size);
    // scan nodes
    for(int i = 0; i < node_num; i++){
        node[i].link_num = 0;
        visited[i] = 0;
        parent[i] = i;
        int temp;
        scanf("%d %d", &temp, &node[i].weight);
    }
    // scan links
    for(int i = 0; i < link_num; i++){
        int temp, node_st, node_nd;
        scanf("%d %d %d", &temp, &node_st, &node_nd);
        // make link in two structs
        int first_pos = node[node_st].link_num, second_pos = node[node_nd].link_num;
        node[node_st].link_node[first_pos] = node_nd;
        node[node_nd].link_node[second_pos] = node_st;
        node[node_st].link_num++;
        node[node_nd].link_num++;
    }
    // build tree
    BFS(0, node_num, packet_size);
    // calculate total cost
    calc(node_num, packet_size);
    // print answer
    printf("%d %d\n", node_num, total_cost);
    for(int i = 0; i < node_num; i++){
        printf("%d %d\n", i, parent[i]);
    }

    return 0;
}