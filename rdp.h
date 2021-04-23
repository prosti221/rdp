#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>                                                          
#include <netinet/in.h> 

typedef struct __attribute__((packed)) Packet{
    unsigned char flags; //0x01-->connect request  0x02-->terminate connection  0x04-->data packet  0x08-->ACK  0x10-->accept connect   0x20-->refuse connect
    unsigned char pktseq; //Sequence number of packet
    unsigned char ackseq; //Sequence number ACK-ed by packet
    unsigned char unassigned;
    int sender_id;
    int recv_id;
    int metadata;
    char payload[0]; //Maximum of 1000 bytes
}Packet;

typedef struct Connection{
    int client_id, server_id; //server id is 0
    char packet_seq; //Last packet recived
    struct sockaddr_in client_addr; //recv_addr -> client
}Connection;

Packet *create_packets(char* data_bfr, int *total_packets); //Takes a data buffer from file and splits it into packets.

char *serialize(Packet *packet, unsigned int *size);

struct Packet *de_serialize(char *d, unsigned int size);

struct Connection *rdp_accept(int *sockfd, Connection **connections, int *connected); //Listens for connection requests and sends accept/refuse connection packet back

void write_file(Packet *packets); //Takes collection of packets and writes to file

void send_ACK(int *sockfd, int recv_ID, int sender_ID, int packet_nb, struct sockaddr_in *dest); //sends ACK

void wait_ACK(int *sockfd,  char *serial,int recv_ID, int sender_ID, int packet_nb, struct sockaddr_in *resend); //Waits for ACK

int wait_rdp_accept(int *sockfd, char *serial, int recv_ID, struct sockaddr_in *resend); //Client waits for rdp_accept response, returns 0 if accepted, returns -1 if refused.

void print_packet(Packet *packet);

void print_connection(Connection *c);


