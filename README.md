# Address Aggregation README

## Introduction
Address aggregation, also known as route aggregation or supernetting, is a networking technique that involves combining multiple contiguous IP address blocks into a larger, more summarized address range. This process helps reduce the size of routing tables in routers and makes the overall routing process more efficient. Address aggregation is a fundamental concept in Internet Protocol (IP) routing and is closely associated with the management of IP address space.

This repository contains a C program that demonstrates address aggregation techniques in computer networks.

## Theoretical Concepts

### Routing Table Efficiency
The global Internet consists of a vast number of interconnected networks. Routers play a crucial role in forwarding packets between these networks. Routers use routing tables to determine the next hop for a packet based on its destination IP address. Large routing tables can lead to increased memory and processing requirements for routers. Address aggregation aims to reduce the size of these tables.

### IP Address Hierarchy
IP addresses are hierarchical, with the network portion and host portion divided by a subnet mask or prefix length. Internet Assigned Numbers Authority (IANA) allocates IP address blocks to Regional Internet Registries (RIRs), which, in turn, allocate address space to Internet Service Providers (ISPs).

### CIDR (Classless Inter-Domain Routing)
CIDR is a methodology introduced to improve the efficiency of IP address allocation and routing. Traditional IP addressing relied on classes (Class A, B, C), leading to inefficient utilization of address space and increased routing table size. CIDR introduced a flexible addressing scheme where the length of the network prefix could vary, allowing for more efficient use of IP address space.

### Subnetting and Aggregation
Subnetting involves dividing an IP address block into smaller, more manageable subnets. Address aggregation, on the other hand, combines multiple contiguous subnets into a larger, summarized address range. Aggregating addresses helps reduce the number of entries in routing tables, facilitating faster routing decisions.

### Prefix Length and Aggregated Blocks
In address aggregation, blocks of IP addresses with similar or contiguous prefixes are combined. The aggregated block has a prefix length that is shorter than those of the individual blocks being aggregated. Shorter prefix lengths represent larger address ranges, resulting in fewer routing table entries.

### Impact on Internet Routing
Address aggregation is crucial for the scalability and efficiency of the global Internet routing system. ISPs aggregate their allocated address space before advertising routes to other ISPs. This reduces the number of routes propagated across the Internet backbone.

### Benefits of Address Aggregation
- Reduced memory and processing requirements in routers.
- More efficient use of IP address space.
- Minimized convergence time in routing protocols.
- Improved scalability of the Internet routing infrastructure.

## Code Explanation

### `IPAddress` Structure
```c
typedef struct { 
    uint8_t octet[4]; 
    int prefix; 
} IPAddress;



This structure represents an IP address along with its prefix length. The octet array stores the four octets of the IP address, and the prefix variable stores the length of the prefix.

```c
int calculateTotalHosts(int prefix) { 
    return (1 << (32 - prefix)); 
}

```
```c
	calculateTotalHosts Function:
int calculateTotalHosts(int prefix) { return (1 << (32 - prefix)); }```
This function calculates the total number of hosts in a subnet based on its prefix length.
		
  
  getNextPowerOfTwo Function:
```c
int32_t getNextPowerOfTwo(uint32_t n) { uint32_t m = 0; while ((1 << m) < n) { m++; } return m; }
```
This function calculates the next power of two greater than a given number. It is used in determining the new prefix length for aggregated address ranges.
		printIPAddress Function:
void printIPAddress(IPAddress ip) { printf("%hhu.%hhu.%hhu.%hhu/%d\n", ip.octet[0], ip.octet[1], ip.octet[2], ip.octet[3], ip.prefix); }
This function prints an IP address with its prefix.
		printIPAddressRange Function:
```c
IPAddress printIPAddressRange(IPAddress ip, int numAddresses) { ... }```
This function calculates and prints the range of IP addresses within a subnet, given the starting IP address and the number of addresses required.
		printAddressAggregation Function:
void printAddressAggregation(IPAddress startIP, IPAddress endIP) { ... }

This function prints the aggregated IP address range for a group, including the start and end IP addresses.
		CustomerNode Structure:
typedef struct CustomerNode { IPAddress startIP; IPAddress endIP; struct CustomerNode* next; } CustomerNode;
This structure represents a node in a linked list. Each node contains the start and end IP addresses of a customer range, along with a pointer to the next node in the list.
		createCustomerNode Function:
```c CustomerNode* createCustomerNode(IPAddress startIP, IPAddress endIP) { ... }
```
This function dynamically allocates memory for a new CustomerNode and initializes it with the provided start and end IP addresses.
		printFirstAndLast Function:
void printFirstAndLast(CustomerNode* head) { ... }
This function prints the start and end IP addresses of the first and last customers in a linked list.
		getNextIPAddress Function:
``` cIIPAddress getNextIPAddress(IPAddress ip) { ... }```
This function calculates the next sequential IP address.
		printCustomerIPAddresses Function:
``` c
CustomerNode* printCustomerIPAddresses(IPAddress ip, int prefixLength, int numCustomers, int numAddressesPerCustomer) { ... }```
This function generates a linked list of customer IP address ranges based on the given parameters.



## TO RUN
```
gcc new.c
./a.out
```
