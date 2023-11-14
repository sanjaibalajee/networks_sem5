#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint8_t octet[4];
    int prefix;
} IPAddress;


int calculateTotalHosts(int prefix){
    return (1 << (32 - prefix));
}
uint32_t getNextPowerOfTwo(uint32_t n) {
    uint32_t m = 0;
    while ((1 << m) < n) {
        m++;
    }
    return m;
}


void printIPAddress(IPAddress ip){
    printf("%hhu.%hhu.%hhu.%hhu/%d\n", ip.octet[0], ip.octet[1], ip.octet[2], ip.octet[3], ip.prefix);
}


IPAddress printIPAddressRange(IPAddress ip, int numAddresses) {
    int newPrefix = 32 - getNextPowerOfTwo(numAddresses);
    uint32_t startAddress = (ip.octet[0] << 24) | (ip.octet[1] << 16) | (ip.octet[2] << 8) | ip.octet[3];
    uint32_t endAddress = startAddress + numAddresses - 1;
    endAddress |= (1 << (32 - newPrefix)) - 1;
    IPAddress startIP;
    startIP.octet[0] = (startAddress >> 24) & 0xFF;
    startIP.octet[1] = (startAddress >> 16) & 0xFF;
    startIP.octet[2] = (startAddress >> 8) & 0xFF;
    startIP.octet[3] = startAddress & 0xFF;
    IPAddress endIP;
    endIP.octet[0] = (endAddress >> 24) & 0xFF;
    endIP.octet[1] = (endAddress >> 16) & 0xFF;
    endIP.octet[2] = (endAddress >> 8) & 0xFF;
    endIP.octet[3] = endAddress & 0xFF;
    // printf("Start IP address: %hhu.%hhu.%hhu.%hhu/%d\n", startIP.octet[0], startIP.octet[1], startIP.octet[2], startIP.octet[3], newPrefix);
    // printf("End IP address: %hhu.%hhu.%hhu.%hhu/%d\n", endIP.octet[0], endIP.octet[1], endIP.octet[2], endIP.octet[3], newPrefix);
    endIP.prefix = newPrefix;
    return endIP;
}
void printAddressAggregation(IPAddress startIP, IPAddress endIP) {
    printf("Group IP addresses:\n");
    printf("+------------------------+\n");
    printf("| Start IP: %hhu.%hhu.%hhu.%hhu/%d |\n", startIP.octet[0], startIP.octet[1], startIP.octet[2], startIP.octet[3], startIP.prefix);
    printf("| End IP:   %hhu.%hhu.%hhu.%hhu/%d |\n", endIP.octet[0], endIP.octet[1], endIP.octet[2], endIP.octet[3], endIP.prefix);
    printf("+------------------------+\n");
}

typedef struct CustomerNode {
    IPAddress startIP;
    IPAddress endIP;
    struct CustomerNode* next;
} CustomerNode;

CustomerNode* createCustomerNode(IPAddress startIP, IPAddress endIP) {
    CustomerNode* node = malloc(sizeof(CustomerNode));
    node->startIP = startIP;
    node->endIP = endIP;
    node->next = NULL;
    return node;
}
void printFirstAndLast(CustomerNode* head) {
    int count = 0;
    if (head == NULL) {
        return;
    }
    
    CustomerNode* current = head;
    printf("Customer IP addresses:\n");
    printf("Customer 1:\n");
    printf("+------------------------+\n");
    printf("| Start IP: %hhu.%hhu.%hhu.%hhu/%d |\n", current->startIP.octet[0], current->startIP.octet[1], current->startIP.octet[2], current->startIP.octet[3], current->startIP.prefix);
    printf("| End IP:   %hhu.%hhu.%hhu.%hhu/%d |\n", current->endIP.octet[0], current->endIP.octet[1], current->endIP.octet[2], current->endIP.octet[3], current->endIP.prefix);
    printf("+------------------------+\n");
    
    while (current->next != NULL) {
        count++;
        current = current->next;
    }
    printf("Customer %d:\n", count + 1);
    
    printf("+------------------------+\n");
    printf("| Start IP: %hhu.%hhu.%hhu.%hhu/%d |\n", current->startIP.octet[0], current->startIP.octet[1], current->startIP.octet[2], current->startIP.octet[3], current->startIP.prefix);
    printf("| End IP:   %hhu.%hhu.%hhu.%hhu/%d |\n", current->endIP.octet[0], current->endIP.octet[1], current->endIP.octet[2], current->endIP.octet[3], current->endIP.prefix);
    printf("+------------------------+\n");
}



IPAddress getNextIPAddress(IPAddress ip) {
    IPAddress nextIP;
    nextIP.octet[0] = ip.octet[0];
    nextIP.octet[1] = ip.octet[1];
    nextIP.octet[2] = ip.octet[2];
    nextIP.octet[3] = ip.octet[3] + 1;
    nextIP.prefix = ip.prefix;

    // Handle overflow of octet[3]
    if (nextIP.octet[3] == 0) {
        nextIP.octet[2] += 1;
        if (nextIP.octet[2] == 0) {
            nextIP.octet[1] += 1;
            if (nextIP.octet[1] == 0) {
                nextIP.octet[0] += 1;
            }
        }
    }

    return nextIP;
}

typedef struct {
    int numCustomers;
    int numofAddressesPerCustomer;
} GroupInfo;


CustomerNode* printCustomerIPAddresses(IPAddress ip, int prefixLength, int numCustomers, int numAddressesPerCustomer) {
    uint32_t baseAddress = (ip.octet[0] << 24) | (ip.octet[1] << 16) | (ip.octet[2] << 8) | ip.octet[3];
    CustomerNode* head = NULL;
    CustomerNode* tail = NULL;

    for (int i = 0; i < numCustomers; i++) {
        IPAddress customerIP;
        customerIP.octet[0] = (baseAddress >> 24) & 0xFF;
        customerIP.octet[1] = (baseAddress >> 16) & 0xFF;
        customerIP.octet[2] = (baseAddress >> 8) & 0xFF;
        customerIP.octet[3] = baseAddress & 0xFF;
        customerIP.prefix = prefixLength;

        IPAddress endIP;
        endIP.octet[0] = ((baseAddress + numAddressesPerCustomer - 1) >> 24) & 0xFF;
        endIP.octet[1] = ((baseAddress + numAddressesPerCustomer - 1) >> 16) & 0xFF;
        endIP.octet[2] = ((baseAddress + numAddressesPerCustomer - 1) >> 8) & 0xFF;
        endIP.octet[3] = (baseAddress + numAddressesPerCustomer - 1) & 0xFF;
        endIP.prefix = prefixLength;

        CustomerNode* node = createCustomerNode(customerIP, endIP);

        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }

        baseAddress += numAddressesPerCustomer;
    }

    return head;
}

int main(){
    // get input
    IPAddress ip;
    printf("Enter IP address and prefix: ");
    scanf("%hhu.%hhu.%hhu.%hhu/%d", &ip.octet[0], &ip.octet[1], &ip.octet[2], &ip.octet[3], &ip.prefix);
    int numAddresses = calculateTotalHosts(ip.prefix);
    printIPAddressRange(ip, numAddresses);
    int numGroups;
    printf("Enter the number of groups: ");
    scanf("%d", &numGroups);

      GroupInfo groupInfo[numGroups];

    // Get the number of customers and addresses per customer for each group
    for (int i = 0; i < numGroups; i++) {
        printf("Enter the number of customers for group %d: ", i + 1);
        scanf("%d", &groupInfo[i].numCustomers);
        printf("Enter the number of addresses per customer for group %d: ", i + 1);
        scanf("%d", &groupInfo[i].numofAddressesPerCustomer);
    }

    // Print address aggregations
    printf("\nAddress Aggregations:\n");
    int aggtotal=0;
    int check=0;
    IPAddress startStart;
    IPAddress endEnd;
    for (int i = 0; i < numGroups; i++) {
        int totalAddressOfGroup = groupInfo[i].numCustomers * groupInfo[i].numofAddressesPerCustomer;
        int newPrefix = 32 - getNextPowerOfTwo(totalAddressOfGroup);

        IPAddress newIP = printIPAddressRange(ip, totalAddressOfGroup);
        ip.prefix = newPrefix;
        IPAddress startIP = ip;
        if(check==0){
            startStart=startIP;
            check=1;
        }

        IPAddress endIP = newIP;
        printf("For Group %d:\n", i + 1);
        printAddressAggregation(startIP, endIP);
        newPrefix=32 - getNextPowerOfTwo(groupInfo[i].numofAddressesPerCustomer);
        CustomerNode* head = printCustomerIPAddresses(ip, newPrefix,  groupInfo[i].numCustomers, groupInfo[i].numofAddressesPerCustomer);
        printFirstAndLast(head);
        printf("====================================\n");
        aggtotal+=groupInfo[i].numCustomers*groupInfo[i].numofAddressesPerCustomer;



        ip = getNextIPAddress(newIP);
        endEnd=newIP;
    }
    int finalPrefix=32 - getNextPowerOfTwo(aggtotal);
    printf("Final Prefix: %d\n",finalPrefix);
    printf("Final Address Aggregation:\n");
    // print startstart and endend 
    startStart.prefix=finalPrefix;
    endEnd.prefix=finalPrefix;
    printIPAddress(startStart);
    printIPAddress(endEnd);

    return 0;
}