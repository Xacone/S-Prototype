#include "pcap/pcap.h"
#include <QString>
#include <QCheckBox>
#include <QTreeWidgetItem>
#include "Headers.h"

u_short ubs(u_short);
QString process_packet(pcap_t*, const u_char*);
QString eth_mac_addr_form(u_char, u_char, u_char, u_char, u_char, u_char, u_char, u_char, u_char, u_char, u_char, u_char);
QString char_tohex(u_char);
QString short_to_hex(u_short);
QString single_mac_form(u_char,u_char,u_char,u_char,u_char,u_char);
QString single_ip_addr_form(u_char ,u_char ,u_char ,u_char);
QString single_ip6_addr_form(u_short ,u_short ,u_short ,u_short, u_short ,u_short ,u_short ,u_short);
QString arp_packet_format(arp_hdr*);
QString process_application_protocol(int, const u_char*);
QString ip4_packet_format(ip4_hdr*);
QString ip4_display_ttl(ip4_hdr*);
QString process_packet(int, pcap_t*, const u_char*, struct pcap_pkthdr*, QCheckBox*, QCheckBox*, QCheckBox*, QCheckBox*, tcp_hdr*, QString*);
QString single_hex_to_bin(tcp_hdr*);
QString tcp_protoc(tcp_hdr*);
QString* http_ip_addr(ip4_hdr*);
QTreeWidgetItem* http_srv(QString*);
QString get_tcp_flags_from_bin(tcp_hdr*);
