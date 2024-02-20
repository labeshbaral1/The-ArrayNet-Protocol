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
        printf("%d\n", lastInteger);
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
    __uint8_t c = (packet[15] >> 6);
    __uint8_t tc = (packet[15] & 0x3F);

    __uint32_t calculated_checksum = (source_address + destination_address + network_port + destination_port + fragment_offset + packet_length + maximum_hop_count + c + tc);
    
     __int32_t integer;
     
        for (int i = 16; i <= packet_length - 4; i += 4) {
            integer = 0;                

            for (int j = 0; j < 4; j++) { 
                integer |= (__int32_t)packet[i + j] << ((3 - j) * 8); 
            }
            calculated_checksum += abs(integer);
        }

        if (packet_length % 4 != 0) {
            integer = 0;
            
            int start = packet_length - (packet_length % 4);

            for (int j = start; j < packet_length; j++) {
                integer |= (__int32_t)packet[j] << ((packet_length - 1 - j) * 8);
            }
            calculated_checksum += abs(integer);
        }

    calculated_checksum %=  (1 << 23) - 1;
    

    return (unsigned int) calculated_checksum;
}

unsigned int reconstruct_array_sf(unsigned char *packets[], unsigned int packets_len, int *array, unsigned int array_len) {

    unsigned int uncorrupted_integers = 0;

    //packets stores pointers to packets and has a length of packet_len (index each pointer to iterate through packets)
        //fragment_offset tells you where in the array to start writing the payload (written in bytes therefore divide by 4 to find what index to start at)
        //extract payload if checksum is valid for the packet checksum_sf(packet) == packet.checksum (use predefined checksum function and bitwise extraction)
            //start at payload index of the packet(16) and iterate by i+=4 creating 32-bit integers across packet [i : i + 4] 
            //ensure payload_index doesnt exceed packet.packet_length and array_index doesnt exceed array_len
            //store up to array_len ingegers inside of array (case to prevent storage outside of the array)
            //return the number of integers that arent corrupted
            //packet stores a 32 bit integers across 4 byte size indicies, integer array stores them in 1 index
        //else move to next packet

        //array is only accested to write integers into

    for (unsigned int packets_index = 0; packets_index < packets_len; packets_index++) {

        unsigned char *current_packet = packets[packets_index];

        __uint32_t check_sum = ((current_packet[12] & 0x7F) << 16) | (current_packet[13] << 8) | (current_packet[14]);
        __uint16_t packet_length = ((current_packet[9] & 0x03) << 12) | (current_packet[10] << 4) | (current_packet[11] >> 4);
        __uint16_t fragment_offset = (current_packet[8] << 6) | (current_packet[9] >> 2);

        unsigned int starting_index = fragment_offset / 4; // index of where to begin writing payloads into the array

        if (check_sum == compute_checksum_sf(current_packet)) {
            for (unsigned int curr_packet_byte_index = 16, array_index = starting_index; (curr_packet_byte_index < packet_length) && array_index < array_len; curr_packet_byte_index += 4, array_index++) {
                array[array_index] = (current_packet[curr_packet_byte_index] << 24) | (current_packet[curr_packet_byte_index+1] << 16) | (current_packet[curr_packet_byte_index+2] << 8) | (current_packet[curr_packet_byte_index+3]); //construct 32 bit integer and write it to the array
                uncorrupted_integers++;
            }
        }
    
    }

    return uncorrupted_integers;


}

unsigned int packetize_array_sf(int *array, unsigned int array_len, unsigned char *packets[], unsigned int packets_len,
                          unsigned int max_payload, unsigned int src_addr, unsigned int dest_addr,
                          unsigned int src_port, unsigned int dest_port, unsigned int maximum_hop_count,
                          unsigned int compression_scheme, unsigned int traffic_class)
{
    (void)array; // arry of integers pointers
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

    unsigned int valid_packets = 0;
    unsigned int integers_per_payload = 0;
    if((max_payload/4) <= array_len){
        integers_per_payload = max_payload/4;
        }

    unsigned int integer_in_final_payload = array_len % (max_payload/4);
    unsigned int array_ptr = 0;

    //take in an array of integers and turns it into payloads

    //integer_per_payload
    //integers_in_final_payload


    //payload    
    //create a new packet using malloc and store it onto the packets array of pointers
    //all packets must be of less tahn size max_payload  num of int = (max_playload / 4)

    //DONT CHANGE 
        //src, dst address
        //src, dst port
        //maximum_hop_count
        //compression_scheme
    //calculating fragment offset = integers_index * 4 (represents the starting index of the array to begin writing)
    //calculating packet_length = (integers in packet + 16 ) * 4 
    //calculating checksum = use compute_checksum_sf
    

    unsigned int number_of_packets = (array_len + (max_payload/4) - 1) / (max_payload/4); //rounds up if the last packet is not in 1 byte per element form ie performs a cieling division


        

        unsigned int packet_size;
        unsigned int fragment_offset = 0;


        for(unsigned int packets_index = 0; packets_index < number_of_packets; packets_index++){

        
        if (((packets_index != number_of_packets - 1) || (integer_in_final_payload == 0))){
            packet_size = 16 + integers_per_payload*4; 
        }
        else {
            packet_size = 16 + integer_in_final_payload*4; 
        }

        fragment_offset += 16;

        
        packets[packets_index] = malloc(packet_size);

        if(packets[packets_index]==NULL){
            break;
        }

        unsigned char *curr_packet = packets[packets_index];
        unsigned int packet_offset = 0;


        unsigned int src_addr_first24bits = src_addr >> 4;
        curr_packet[packet_offset++] = (src_addr_first24bits >> 16) & 0xFF;
        curr_packet[packet_offset++] = (src_addr_first24bits >> 8) & 0xFF;
        curr_packet[packet_offset++] = src_addr_first24bits & 0xFF;


        unsigned int src_addr_last4bits = src_addr & 0xF;
        unsigned int dst_addr_first4bits = dest_addr >> 24;
        unsigned int byte3 = (src_addr_last4bits << 4) | (dst_addr_first4bits);
        curr_packet[packet_offset++] = byte3;

        unsigned int dst_addr_trimmed = dest_addr & 0xFFFFFFFF;
        curr_packet[packet_offset++] = (dst_addr_trimmed >> 16) & 0xFF;
        curr_packet[packet_offset++] = (dst_addr_trimmed >> 8) & 0xFF;
        curr_packet[packet_offset++] = dst_addr_trimmed & 0xFF;

        unsigned int byte7 = (src_port << 4 ) | dest_port ;
        curr_packet[packet_offset++] = byte7 & 0xFF;
    
       
        unsigned int byte8 = fragment_offset >> 6;
        curr_packet[packet_offset++] = byte8 & 0xFF;

        unsigned int fragment_offset_last6bits = fragment_offset & 0x3F;
        unsigned int packet_len_first2bits = ((packet_size) >> 12 ) & 0x3;
        unsigned int byte9 = (fragment_offset_last6bits << 2) | (packet_len_first2bits);
        curr_packet[packet_offset++] = byte9 & 0xFF;

        unsigned int byte10 = ((packet_size) & 0x3F00) >> 4;
        curr_packet[packet_offset++] = byte10 & 0xFF;
    
        unsigned int packet_len_last4bits = (packet_size) & 0xF;
        unsigned int maximum_hop_first4bits = (maximum_hop_count) >> 1;
        unsigned int byte11 = (packet_len_last4bits<<4) | maximum_hop_first4bits;
        curr_packet[packet_offset++] = byte11 & 0xFF;

        unsigned int check_sum = compute_checksum_sf(curr_packet);
        unsigned int maximum_hop_last1bits = maximum_hop_count & 0x1;
        unsigned int checksum_first_7bits = check_sum >> 16;
        unsigned int byte12 = (maximum_hop_last1bits << 7) & checksum_first_7bits;
        curr_packet[packet_offset++] = byte12 & 0xFF;

        unsigned int check_sum_last16bits =  check_sum & 0xFFFF;
        curr_packet[packet_offset++] = (check_sum_last16bits >> 8) & 0xFF; 
        curr_packet[packet_offset++] = check_sum_last16bits & 0xFF;
         
        unsigned int byte15 = (compression_scheme << 6 ) | (traffic_class & 0x3F);
        curr_packet[packet_offset++] = byte15 & 0xFF;
    
        unsigned int integer;

        for(unsigned int j = 0; j < ((packet_size-16)/4); j+=1){
            integer = array[array_ptr++]; 
            curr_packet[packet_offset++] = integer & 0xFF;
        }
        

        fragment_offset += packet_size-16;


    valid_packets++;
        }
    

    
    // for (unsigned int i = 0; i < valid_packets; i++) {
    //         free(packets[i]);
    //     }       
        

    

     


    return valid_packets;
}



