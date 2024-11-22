#include<stdio.h>
#include<stdlib.h>

struct packet {
    int time;
    int size;
} p[50];

int main() {
    int i, n, m, k = 0;
    int bsize, bfilled, outrate;
    
    printf("\nEnter the number of packets: ");
    scanf("%d", &n);
    
    printf("\nEnter packets in the order of arrival time (time size):\n");
    for(i = 0; i < n; i++) {
        printf("Enter time and size: ");
        scanf("%d %d", &p[i].time, &p[i].size);
    }
    
    printf("\nEnter the bucket size: ");
    scanf("%d", &bsize);
    
    printf("\nEnter the output rate: ");
    scanf("%d", &outrate);
    
    m = p[n-1].time; // Last packet's time
    i = 1;  // Time starts at 1
    k = 0;  // Index for packets
    bfilled = 0;  // Initial bucket size is 0
    
    // Simulate the time slots
    while(i <= m || bfilled != 0) {
        printf("\nAt time %d:\n", i);
        
        // Check if any packet arrives at the current time
        while(k < n && p[k].time == i) {
            if(bsize >= bfilled + p[k].size) {
                bfilled += p[k].size; // Insert the packet into the bucket
                printf("%d byte packet inserted into the bucket\n", p[k].size);
            } else {
                printf("%d byte packet discarded (not enough space)\n", p[k].size);
            }
            k++; // Move to the next packet
        }

        // Handle the transmission from the bucket
        if(bfilled == 0) {
            printf("No packet to transmit.\n");
        } else {
            if(bfilled >= outrate) {
                bfilled -= outrate; // Transfer the output rate of bytes
                printf("%d bytes transferred\n", outrate);
            } else {
                printf("%d bytes transferred (bucket emptied)\n", bfilled);
                bfilled = 0; // Bucket is empty
            }
        }

        // Show the current number of bytes in the bucket
        printf("Packets in the bucket: %d bytes\n", bfilled);

        // Increment time and continue the process
        i++;
    }
    
    return 0;
}
