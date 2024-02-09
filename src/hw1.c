#include "hw1.h"

void print_packet_sf(unsigned char packet[])
{
    __uint32_t source_address =  (packet[0] << 20) | (packet[1] << 12) | (packet[2] << 4) | (packet[3] >> 4);
    __uint32_t destination_address =  ((packet[3] & 0x0F) << 24) | (packet[4] << 16) | (packet[5] << 8) | (packet[6]);
    __uint8_t network_port = (packet[7] >> 4); 
    __uint8_t destination_port = (packet[7] & 0x0F);
    __uint16_t fragment_offset = (packet[8] << 6) | (packet[9] >> 2);
    __uint16_t packet_length = ((packet[9] & 0x03) << 12) | (packet[10] << 4) | (packet[11] >> 4);
    __uint8_t maximum_hop_count = ((packet[11] & 0x0F) << 1) | (packet[12] >> 7);
    __uint32_t checksum = ((packet[12] & 0x7F) << 16) | (packet[13] << 8) | (packet[14]);
    __uint8_t c = (packet[15] >> 6);
    __uint8_t tc = (packet[15] & 0x3F);


    printf("Source Address: %u\n", source_address);
    printf("Destination Address: %u\n", destination_address);
    printf("Source Port: %u\n", network_port);
    printf("Destination Port: %u\n", destination_port);
    printf("Fragment Offset: %u\n", fragment_offset);
    printf("Packet Length: %u\n", packet_length);
    printf("Maximum Hop Count: %u\n", maximum_hop_count);
    printf("Checksum: %u\n", checksum);
    printf("Compression Scheme: %u\n", c);
    printf("Traffic Class: %u\n", tc);
    printf("Payload: ");


    if (packet_length <= 16) {
            printf("Packet too short to contain payload.\n");
            return;
        }

    int first = 1;
    for (int i = 16; i <= packet_length - 4; i += 4) {
        __int32_t integer = 0;                
        
        if (!first) {
            printf(" "); 
        } else {
            first = 0;
        }

        for (int j = 0; j < 4; j++) { 
            integer |= (__int32_t)packet[i + j] << ((3 - j) * 8); 
        }

        printf("%d", integer); 
    }

    if (packet_length % 4 != 0) {
        __int32_t lastInteger = 0;
        int start = packet_length - (packet_length % 4);

        for (int j = start; j < packet_length; j++) {
            lastInteger |= (__int32_t)packet[j] << ((packet_length - 1 - j) * 8);
        }
                }
    else{
        printf("\n");
    }
    
    }

unsigned int compute_checksum_sf(unsigned char packet[])
{
     __uint32_t source_address =  (packet[0] << 20) | (packet[1] << 12) | (packet[2] << 4) | (packet[3] >> 4);
    __uint32_t destination_address =  ((packet[3] & 0x0F) << 24) | (packet[4] << 16) | (packet[5] << 8) | (packet[6]);
    __uint8_t network_port = (packet[7] >> 4); 
    __uint8_t destination_port = (packet[7] & 0x0F);
    __uint16_t fragment_offset = (packet[8] << 6) | (packet[9] >> 2);
    __uint16_t packet_length = ((packet[9] & 0x03) << 12) | (packet[10] << 4) | (packet[11] >> 4);
    __uint8_t maximum_hop_count = ((packet[11] & 0x0F) << 1) | (packet[12] >> 7);
    __uint32_t real_checksum = ((packet[12] & 0x7F) << 16) | (packet[13] << 8) | (packet[14]);
    __uint8_t c = (packet[15] >> 6);
    __uint8_t tc = (packet[15] & 0x3F);

    print_packet_sf(packet);
    __uint32_t calculated_checksum = (source_address + destination_address + network_port + destination_port + fragment_offset + packet_length + maximum_hop_count + c + tc);
    
    int first = 1;
        for (int i = 16; i <= packet_length - 4; i += 4) {
            __int32_t integer = 0;                

            for (int j = 0; j < 4; j++) { 
                integer |= (__int32_t)packet[i + j] << ((3 - j) * 8); 
            }
            calculated_checksum += abs(integer);
        }

        if (packet_length % 4 != 0) {
            __int32_t lastInteger = 0;
            
            int start = packet_length - (packet_length % 4);

            for (int j = start; j < packet_length; j++) {
                lastInteger |= (__int32_t)packet[j] << ((packet_length - 1 - j) * 8);
            }
            calculated_checksum += abs(lastInteger);
        }

    calculated_checksum %=  (1 << 23) - 1;
    

    return (unsigned int) calculated_checksum;

    


}

unsigned int reconstruct_array_sf(unsigned char *packets[], unsigned int packets_len, int *array, unsigned int array_len) {
    (void)packets;
    (void)packets_len;
    (void)array;
    (void)array_len;
    return -1;
}

unsigned int packetize_array_sf(int *array, unsigned int array_len, unsigned char *packets[], unsigned int packets_len,
                          unsigned int max_payload, unsigned int src_addr, unsigned int dest_addr,
                          unsigned int src_port, unsigned int dest_port, unsigned int maximum_hop_count,
                          unsigned int compression_scheme, unsigned int traffic_class)
{
    (void)array;
    (void)array_len;
    (void)packets;
    (void)packets_len;
    (void)max_payload;
    (void)src_addr;
    (void)dest_addr;
    (void)src_port;
    (void)dest_port;
    (void)maximum_hop_count;
    (void)compression_scheme;
    (void)traffic_class;
    return -1;
}
