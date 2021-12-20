#ifndef HEADERS_H
#define HEADERS_H
#include "pcap.h"

// Header -> hdr
// Address -> addr

typedef struct IP4_Address ip4_addr;
typedef struct IP6_Address ip6_addr;
typedef struct MAC_Address mac_addr;

typedef struct Ethernet_header eth_hdr;

typedef struct IPv4_Header ip4_hdr;
typedef struct IPv6_Header ip6_hdr;
typedef struct ICMP_Header icmp_hdr;
typedef struct TCP_Header tcp_hdr;
typedef struct ARP_Header arp_hdr;
typedef struct UDP_Header udp_hdr;

       /* ----------------------------------------------------- */

struct foo { unsigned char:2; };
struct IP6_F32 { u_int Version : 4; u_int Prio_Traffic_Class : 8; u_int Flow_Label : 20; };

struct MAC_Address
{
    u_char oct1;
    u_char oct2;
    u_char oct3;
    u_char oct4;
    u_char oct5;
    u_char oct6;
};

struct IP4_Address
{
    u_char oct1;
    u_char oct2;
    u_char oct3;
    u_char oct4;
};

struct IP6_Address
{
    u_short oct1;
    u_short oct2;
    u_short oct3;
    u_short oct4;
    u_short oct5;
    u_short oct6;
    u_short oct7;
    u_short oct8;
};

       /* ----------------------------------------------------- */


struct Ethernet_header
{
    mac_addr src;
    mac_addr dst;
    u_short ether_type;
};

struct IPv4_Header
{
    u_char version_hl; // Version and header length
    u_char tos; // Type of service
    u_short total_length;
    u_short identification;
    u_short flg_fragment_offset; // Flags and fragment offset 3 + 13
    u_char ttl;
    u_char protocol;
    u_short header_checksum;
    ip4_addr src;
    ip4_addr dst;
};

struct IPv6_Header // HS
{
    IP6_F32 f32;
    u_short payload_length;
    u_char next_header;
    u_char hop_limit;
    IP6_Address src;
    IP6_Address dst;
};

struct ICMP_Header
{
    u_char type;
    u_char code;
    u_short checksum;
    u_int padding;
};

struct ARP_Header
{
    u_short hardware_type;
    u_short protoc_type;
    u_char hardware_size;
    u_char protocol_size;
    u_short opcode;
    mac_addr sha;
    ip4_addr spa;
    mac_addr tha;
    ip4_addr tpa;
};

struct UDP_Header
{
    u_short sport;
    u_short dport;
    u_short length;
    u_short checksum;
};

typedef struct TCP_header_options
{
    u_char oct1;
    u_char oct2;
    u_char oct3;
} tcp_options;

struct TCP_Header
{
    u_short sport;
    u_short dport;
    u_int seq_number;
    u_int ack_number;
    u_char header_length_and_reserved;
    u_char flags; // Includes CWR & ECE
    u_short window_size;
    u_short tcp_checksum;
    u_short urgent_pointer;
    tcp_options options;
    u_char padding;
};


#endif // HEADERS_H
