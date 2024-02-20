
#include <stdio.h>
#include "../include/hw1.h"



int main(){


   int array[] = {17, 89, 42, 631, 52, 77, 89, 100, 125, -6, 823, 800, 1024, 1025, 9, 1888, 0, -17, 19, 9999999, -888888, 723, 1000, 1111, -99, -95, 55, };
    unsigned char* actual_packets[4] = {0};
    unsigned int num_expected_packets = 4;
    unsigned int max_payload = 20;
    unsigned int src_addr = 93737;
    unsigned int dest_addr = 10973;
    unsigned int src_port = 11;
    unsigned int dest_port = 6;
    unsigned int maximum_hop_count = 25;
    unsigned int compression_scheme = 3;
    unsigned int traffic_class = 14;

 
    const char *expected_packets[] = {
	"\x00\x16\xe2\x90\x00\x2a\xdd\xb6\x00\x00\x02\x4c\x81\x9c\xa4\xce\x00\x00\x00\x11\x00\x00\x00\x59\x00\x00\x00\x2a\x00\x00\x02\x77\x00\x00\x00\x34",
	"\x00\x16\xe2\x90\x00\x2a\xdd\xb6\x00\x50\x02\x4c\x81\x9b\x06\xce\x00\x00\x00\x4d\x00\x00\x00\x59\x00\x00\x00\x64\x00\x00\x00\x7d\xff\xff\xff\xfa",
	"\x00\x16\xe2\x90\x00\x2a\xdd\xb6\x00\xa0\x02\x4c\x81\xa7\xee\xce\x00\x00\x03\x37\x00\x00\x03\x20\x00\x00\x04\x00\x00\x00\x04\x01\x00\x00\x00\x09",
	"\x00\x16\xe2\x90\x00\x2a\xdd\xb6\x00\xf0\x02\x4c\x9a\x37\xa5\xce\x00\x00\x07\x60\x00\x00\x00\x00\xff\xff\xff\xef\x00\x00\x00\x13\x00\x98\x96\x7f",
	};
	unsigned int expected_packet_lengths[] = {36, 36, 36, 36, };

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


