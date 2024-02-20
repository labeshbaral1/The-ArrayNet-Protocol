
#include <stdio.h>
#include "../include/hw1.h"



int main(){



    int array[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, };
    unsigned char* actual_packets[3] = {0};
    unsigned int num_expected_packets = 3;
    unsigned int max_payload = 16;
    unsigned int src_addr = 123123;
    unsigned int dest_addr = 34534534;
    unsigned int src_port = 12;
    unsigned int dest_port = 13;
    unsigned int maximum_hop_count = 14;
    unsigned int compression_scheme = 0;
    unsigned int traffic_class = 15;


	const char *expected_packets[] = {
	"\x00\x1e\x0f\x32\x0e\xf4\x86\xcd\x00\x00\x02\x07\x10\xd6\x01\x0f\x00\x00\x00\x0a\x00\x00\x00\x0b\x00\x00\x00\x0c\x00\x00\x00\x0d",
	"\x00\x1e\x0f\x32\x0e\xf4\x86\xcd\x00\x40\x02\x07\x10\xd6\x21\x0f\x00\x00\x00\x0e\x00\x00\x00\x0f\x00\x00\x00\x10\x00\x00\x00\x11",
	"\x00\x1e\x0f\x32\x0e\xf4\x86\xcd\x00\x80\x02\x07\x10\xd6\x41\x0f\x00\x00\x00\x12\x00\x00\x00\x13\x00\x00\x00\x14\x00\x00\x00\x15",
	};
	
	unsigned int expected_packet_lengths[] = {32, 32, 32, };

	packetize_array_sf(array, sizeof(array) / sizeof(array[0]), actual_packets,
			sizeof(actual_packets) / sizeof(actual_packets[0]), max_payload, src_addr, dest_addr, src_port, dest_port, 
			maximum_hop_count, compression_scheme, traffic_class);

        

	// verify_packets((char **)expected_packets, actual_packets, expected_packet_lengths, num_expected_packets);

    // int arraySize = sizeof(expected_packets) / sizeof(expected_packets[0]); 

    // printf("Array elements:\n");
    // for (int i = 0; i < arraySize; i++) {
    //     print_packet_sf()
    // }

    printf("\n\n"); 

  int arraySize2 = sizeof(actual_packets) / sizeof(actual_packets[0]); 

    for (int i = 0; i < arraySize2; i++) {
        if (actual_packets[i] != NULL) {
            printf("\n");
            printf("---------- Packet %d --------------\n", i+1); 
            print_packet_sf(actual_packets[i]); 

        }
    }


    printf("-------------------\n"); 

    printf("num of packets expected %d\n", num_expected_packets);
    
    int arraySize3 = sizeof(expected_packet_lengths) / sizeof(expected_packet_lengths[0]); 

    printf("Array elements:\n");
    for (int i = 0; i < arraySize3; i++) {
        printf("%s \n", expected_packets[i]); 
    }


// Fix fragment offset
//payload
//packetlen
    }


