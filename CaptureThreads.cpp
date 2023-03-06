#include "CaptureThreads_FCTS.h"
#include "Headers.h"
#include <string>
#include <QString>
#include <QByteArray>
#include "intrin.h"
#include <QTime>
#include <QMutex>
#include <QRegExp>
#include <iostream>

using namespace std;

u_short ubs(u_short in)
{
    u_short out = _byteswap_ushort(in);
    return out;
}


QString char_tohex(u_char in)
{
    QString out = QString("%11").arg((int)in, 1, 16);
    if(out.size() == 1) { out.push_front(QString::number(0)); }
    return out;
}


QString short_to_hex(u_short in)
{
    QString val = QString("%1").arg((int)in, 0, 16);;
    // 0x0800 -> 2048 dec
    return val;
}

QString single_mac_form(u_char b1, u_char b2, u_char b3, u_char b4, u_char b5, u_char b6)
{
    return char_tohex(b1) + ":" + char_tohex(b2) + ":" + char_tohex(b3) + ":" + char_tohex(b4) + ":" + char_tohex(b5) + ":" + char_tohex(b6);
}

QString single_ip6_addr_form(u_short b1, u_short b2, u_short b3, u_short b4, u_short b5, u_short b6, u_short b7, u_short b8)
{
    return short_to_hex(ubs(b1)) + ":" + short_to_hex(ubs(b2)) + ":" + short_to_hex(ubs(b3)) + ":" + short_to_hex(ubs(b4)) + ":" + short_to_hex(ubs(b5)) + ":" + short_to_hex(ubs(b6)) + ":" + short_to_hex(ubs(b7)) + ":" + short_to_hex(ubs(b8));
}

QString single_ip_addr_form(u_char b1, u_char b2, u_char b3, u_char b4)
{
    return QString::number(b1) + "." + QString::number(b2) + "." + QString::number(b3) + "." + QString::number(b4);
}

QString eth_mac_addr_form(u_char b1, u_char b2, u_char b3, u_char b4, u_char b5, u_char b6, u_char b7, u_char b8, u_char b9, u_char b10, u_char b11, u_char b12)
{
    QString mac_src;
    QString mac_dst;

    mac_src = char_tohex(b1) + ":" + char_tohex(b2) + ":" + char_tohex(b3) + ":" + char_tohex(b4) + ":" + char_tohex(b5) + ":" + char_tohex(b6);
    mac_dst = char_tohex(b7) + ":" + char_tohex(b8) + ":" + char_tohex(b9) + ":" + char_tohex(b10) + ":" + char_tohex(b11) + ":" + char_tohex(b12);

    return QString(mac_src + " -> " + mac_dst).toUpper();
}

QString arp_packet_format(arp_hdr* in)
{
    if(short_to_hex(ubs(in->opcode)) == "1") {
        return "REQUEST - " + single_ip_addr_form(in->spa.oct1, in->spa.oct2, in->spa.oct3, in->spa.oct4) + " -> who has " + single_ip_addr_form(in->tpa.oct1, in->tpa.oct2, in->tpa.oct3, in->tpa.oct4) + " ?";
    } else {
        if(short_to_hex(ubs(in->opcode)) == "2") {
            return "REPLY - " + single_ip_addr_form(in->spa.oct1, in->spa.oct2, in->spa.oct3, in->spa.oct4) + " is at " + single_mac_form(in->sha.oct1, in->sha.oct2, in->sha.oct3, in->sha.oct4, in->sha.oct5, in->sha.oct6);
        }
    }
    return "ARP P_ERR";
}

QString single_hex_to_bin(const QChar in)
{
    if(in == "0") { return "0000"; } else {
        if(in == "1") { return "0001"; } else {
            if(in == "2") { return "0010"; } else {
                if(in == "3") { return "0011"; } else {
                    if(in == "4") { return "0100"; } else {
                        if(in == "5") { return "0101"; } else {
                            if(in == "6") { return "0110"; } else {
                                if(in == "7") { return "0111"; } else {
                                    if(in == "8") { return "1000"; } else {
                                        if(in == "9") { return "1001"; } else {
                                            if(in == "A") { return "1010"; } else {
                                                if(in == "B") { return "1011"; } else {
                                                    if(in == "C") { return "1100"; } else {
                                                        if(in == "D") { return "1101"; } else {
                                                            if(in == "E") { return "1110"; } else {
                                                                if(in == "F") { return "1111"; }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

    return "";
}

QString get_tcp_flags_from_bin(tcp_hdr* in)
{
    QString out;
    QString flags = char_tohex(in->flags);
    QString bin_flags;

    for(int i = 0 ; i < flags.size() ; i++)
    {
        bin_flags += single_hex_to_bin(flags.at(i).toUpper());
    }

    if(bin_flags.size() == 8)
    {
        if(bin_flags.at(7) == "1") { out += "FIN "; }
        if(bin_flags.at(6) == "1") { out += "SYN "; }
        if(bin_flags.at(5) == "1") { out += "RST "; }
        if(bin_flags.at(4) == "1") { out += "PSH "; }
        if(bin_flags.at(3) == "1") { out += "ACK "; }
        if(bin_flags.at(2) == "1") { out += "URG "; }
        if(bin_flags.at(1) == "1") { out += "ECN "; }
        if(bin_flags.at(0) == "1") { out += "CWR "; }
    }

    out.replace(out.length()-1, out.length(), "] ");

    return out;
}


QString ip4_packet_format(ip4_hdr* in) { return single_ip_addr_form(in->src.oct1,in->src.oct2,in->src.oct3,in->src.oct4) + " -> " + single_ip_addr_form(in->dst.oct1,in->dst.oct2,in->dst.oct3,in->dst.oct4); }
QString ip4_display_ttl(ip4_hdr* in) { return "TTL: " + QString::number(in->ttl); }

QString* http_ip_addr(ip4_hdr* ip_h)
{
    QString* out = new QString;
    out->push_back(single_ip_addr_form(ip_h->src.oct1, ip_h->src.oct2, ip_h->src.oct3, ip_h->src.oct4)); // IP ADDR
    return out;
}


QTreeWidgetItem* http_srv(QString* in)
{
    QTreeWidgetItem* root = new QTreeWidgetItem();
        root->setText(0, *in);
    return root;
}


QString* app_protoc(QString in)
{
    QString* out = new QString;
    QRegExp http_rx("HTTP/[0-2]{1,2}.[0-2]{1,2}");
    QRegExp rx("</.[a-z]{1,10}>");
    QRegExp rx2("<.*/[a-zA-Z]>");

    if(in.contains(http_rx) || in.mid(0,3) == "GET" || in.mid(0,4) == "HEAD" || in.mid(0,4) == "POST" || in.mid(0,3) == "PUT" || in.mid(0,6) == "DELETE" || in.contains(rx) || in.contains(rx2)) { *out += "[HTTP] "; }
    return out;
}

QString process_application_protocol(int size, const u_char* data)
{
    QString out;

    for(int i = 0 ; i < size ; i ++)
    {
        out += data[i];
        ++i;
        out += data[i];
    }

    return out;
}

QString process_packet(int index, pcap_t *handler, const u_char *pckt_data, struct pcap_pkthdr *header, QCheckBox *L1, QCheckBox *L2, QCheckBox *L3, QCheckBox *L4, tcp_hdr* last_tcp_hdr, QString* last_tcp_protoc)
{
    QString data = "";

    if(pcap_datalink(handler) == DLT_EN10MB)  // Si c'est de l'Ethernet (10/100/1000Mb/etc.)
    {
        eth_hdr* eth = new eth_hdr;

        eth = (eth_hdr *)(pckt_data);

        QString info;
        QString L1_content;
        QString L2_content;
        QString L3_content;
        QString L4_content;
        QString application_data;

        QTime curr_time = QTime::currentTime();
        QString time = "[" + QString::number(curr_time.hour()) + ":" + QString::number(curr_time.minute()) + ":" + QString::number(curr_time.second()) + ":" + QString::number(curr_time.msec()) + "] ";

        info += time;
        info += "[" + QString::number(header->len) + "] ";


        // Adresses MAC SRC -> DST
        if(L1->isChecked())
        {
            L1_content.append("[Ether] ");
            L1_content.append(eth_mac_addr_form(eth->dst.oct1, eth->dst.oct2, eth->dst.oct3, eth->dst.oct4, eth->dst.oct5, eth->dst.oct6, eth->src.oct1, eth->src.oct2, eth->src.oct3, eth->src.oct4, eth->src.oct5, eth->src.oct6));
        }

       if(short_to_hex(ubs(eth->ether_type)) == "800") // IPv4 0x0800
       {
            ip4_hdr* ip4_h;
            L2_content = "[IPv4] ";
            ip4_h = (ip4_hdr*)(pckt_data+14);

            L2_content += ip4_packet_format(ip4_h);
            L2_content += ip4_display_ttl(ip4_h);

            switch (QString::number(ip4_h->protocol).toUInt()) {
                case 1:
                {
                    icmp_hdr* icmp_h;
                    L2_content += "[ICMP] ";
                    icmp_h = (icmp_hdr*)(pckt_data + 14 + 20);
                    QString icmp_type = char_tohex(icmp_h->type);
                    QString icmp_code = char_tohex(icmp_h->code);

                    if(icmp_type == "00" && icmp_code == "00") { L2_content += "[ECHO REPLY] "; }
                    else {
                        if(icmp_type == "08" && icmp_code == "00") { L2_content += "[ECHO REQUEST] "; }
                        else {
                            if(icmp_type == "03")
                            {
                                switch(QString::number(icmp_h->code).toUInt())
                                {
                                    case 0:
                                    L2_content += "[Destination network unreachable] ";
                                    break;

                                    case 1:
                                    L2_content += "[Destination host unreachable] ";
                                    break;

                                    case 2:
                                    L2_content += "[Destination protocol unreachable] ";
                                    break;

                                    case 3:
                                    L2_content += "[Destination port unreachable] ";
                                    break;

                                    case 4:
                                    L2_content += "[Fragmentation required, and DF flag set] ";
                                    break;

                                    case 5:
                                    L2_content += "[Source route failed] ";
                                    break;

                                    case 6:
                                    L2_content += "[Destination network unknown] ";
                                    break;

                                    case 7:
                                    L2_content += "[Destination host unknown] ";
                                    break;

                                    case 8:
                                    L2_content += "[Source host isolated] ";
                                    break;

                                    case 9:
                                    L2_content += "[Network administratively prohibited] ";
                                    break;

                                    case 10:
                                    L2_content += "[Host administratively prohibited] ";
                                    break;

                                    case 11:
                                    L2_content += "[Network unreachable for ToS] ";
                                    break;

                                    case 12:
                                    L2_content += "[Host unreachable for ToS] ";
                                    break;

                                    case 13:
                                    L2_content += "[Communication administratively prohibited] ";
                                    break;

                                    case 14:
                                    L2_content += "[Host Precedence Violation] ";
                                    break;

                                    case 15:
                                    L2_content += "[Precedence cutoff in effect] ";
                                    break;
                                }
                            } else {
                                if(icmp_type == "09" && icmp_code == "00") { L2_content += "[Router Advertisement] "; }
                                else {
                                    if(icmp_type == "0a" && icmp_code == "00") { L2_content += "[Router discovery/selection/solicitation] "; }
                                    else {
                                         if(icmp_type == "0b" && icmp_code == "00") { L2_content += "[TTL expired in transit] "; }
                                         else {
                                             if(icmp_type == "0b" && icmp_code == "01") { L2_content += "[Fragment reassembly time exceeded] "; }
                                         }
                                    }
                                }
                            }
                        }
                    }

                break;
                }

                case 6:
                {
                    L3_content = "[TCP] ";
                    tcp_hdr* tcp_h;

                    int tcp_header_size;
                    const u_char* app_data;
                    tcp_h = (tcp_hdr*)(pckt_data + 14 + 20);

                    L3_content.append((QString)"[" + QString::number((int)ubs(tcp_h->sport)) + " -> " + QString::number((int)ubs(tcp_h->dport)) + "] ");
                    if(get_tcp_flags_from_bin(tcp_h) != ""){ L3_content.append((QString)"[" + get_tcp_flags_from_bin(tcp_h) + " "); }

                        QString two_digits = char_tohex(tcp_h->header_length_and_reserved);
                        two_digits.replace(two_digits.length()-1, two_digits.length(), "");

                        tcp_header_size = two_digits.toInt();
                        tcp_header_size*=4;
                        app_data = (pckt_data + 14 + 20 + tcp_header_size);

                        L3_content.append("[ACK: " + QString::number(tcp_h->ack_number) + "] ");
                        L3_content.append("[SEQ: " + QString::number(tcp_h->seq_number) + "] ");

                        if(tcp_h->ack_number == last_tcp_hdr->ack_number)
                        {
                             L3_content.append("[PREVIOUS ACK] ");
                        }

                        *last_tcp_hdr = *tcp_h;

                        L4_content.append(app_protoc((QString)(const char*)app_data));
                break;
                }

                case 17:
                    L3_content = "[UDP] ";
                break;
            }

       } else {
           if(short_to_hex(ubs(eth->ether_type)) == "806") // ARP 0x0806
           {
                arp_hdr* arp_h;

                L2_content = "[ARP] ";
                arp_h = (arp_hdr*)(pckt_data+14);
                L2_content += arp_packet_format(arp_h);

           } else {
                if(short_to_hex(ubs(eth->ether_type)) == "86dd") // IPv6 0x86dd
                {
                    L2_content = "[IPv6] ";

                } else {
                    if(short_to_hex(ubs(eth->ether_type)) == "8100") // 802.1Q 0x8100
                    {
                        L2_content = "[802.1Q] ";

                    }
                }
           }
       }

       // ICI SORTIE VERS FICHIER POUR NE PAS AVOIR L'HTML

                if(L4_content.contains("[HTTP]")) { data.append("<div style='background: #b0efeb;'>"); } else {
                    if(L4_content.contains("[Telnet]")) { data.append("<div style='background: #45aaf2;'>"); } else {
                          if(L4_content.contains("[SSH]")) { data.append("<div style='background: #cf6a87;'>"); } else {
                              if(L2_content.contains("[ICMP]")) { data.append("<div style='background: #f7d794;'>"); } else {
                                  if(L2_content.contains("[ARP]")) { data.append("<div style='background: #f8a5c2;'>"); } else {
                                      if(L4_content.contains("[FTP]")) { data.append("<div style='background: #82ccdd;'>"); } else {
                                          if(L4_content.contains("[FTP DATA]")) { data.append("<div style='background: #82ccdd;'>"); } else {
                                              if(L4_content.contains("[SMTP]")) { data.append("<div style='background: #38ada9;'>"); } else {
                                                    data.append("<div style='background: #ffffff;'>");
                                                }
                                              }
                                           }
                                       }
                                    }
                                 }
                              }
                           }


       // set_color_to_packet(L4_content, "[HTTPS]", data, "#778beb");

      data.append(QString::number(index) + ". " + info);
      if(L1->isChecked()) { data.append(L1_content.toHtmlEscaped()); }
      if(L2->isChecked()) { data.append(L2_content.toHtmlEscaped()); }
      if(L3->isChecked()) { data.append(L3_content.toHtmlEscaped()); }
      if(L4->isChecked()) { data.append(L4_content.toHtmlEscaped()); }

      data.append(application_data);
      data.append("</div>");

    } else {
        cout << " Erreur 5 " << endl;
    }

    return data;

}

