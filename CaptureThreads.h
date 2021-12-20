#ifndef CAPTURETHREADS_H
#define CAPTURETHREADS_H

#include <QThread>
#include <QString>
#include "pcap.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTime>
#include <Windows.h>
#include <QDebug>
#include "DetectionEngine.h"
#include <QCheckBox>
#include <QLineEdit>
#include <iostream>
#include "Headers.h"
#include <QTimer>
#include <QPalette>
#include <QRegExp>

// void format_packet();

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

class Capture_WorkerThread : public QThread
{
    Q_OBJECT
private:

    int i = 0;
    int j = 0;
    DetectionEngine *DE;

    //JsonWax jwax;

    QString dev_index;
    std::string dev_name;
    QTreeWidgetItem* device_widget_item;

    char* ERRBUFF[PCAP_ERRBUF_SIZE];
    struct bpf_program bpfprog;
    const char* filtre = "icmp";
    struct pcap_pkthdr *pckt_header;
    const u_char *pckt_data;
    u_int netmask;

    pcap_if* pcap_dev;

    pcap_t* handler;
    tcp_hdr* last_tcp_hdr;

    /* ------------ Protocols / Packets Info ------------ */
    eth_hdr* eth_h;
    ip4_hdr* ip4_h;
    ip6_hdr* ip6_h;
    tcp_hdr* tcp_h;
        QString tcp_info;
        QString two_digits;
        int tcp_header_size;
    udp_hdr* udp_h;
    icmp_hdr* icmp_h;
    arp_hdr* arp_h;

    QString ethertype;

    QTime curr_time;
    QString time;
    QString info;
    QString application_data;
    QString icmp_type;
    QString icmp_code;
    int pcap_next_packet;
    u_char* IP6_content;
    QString IP6_HL;

    QString app_data;

    QStringList* packet;

    int milisecs;

    // HTTP
    QString* http_target;
    QString http_hdr_qstr;
    QTreeWidgetItem *http_brief_data;
    QRegExp http_rx = (QRegExp)"HTTP/[0-2]{1,2}.[0-2]{1,2}";
    QRegExp rx = (QRegExp)"</.[a-z]{1,10}>";
    QRegExp rx2 = (QRegExp)"<.*/[a-zA-Z]>";

public:

    Capture_WorkerThread(pcap_if* device, QTreeWidgetItem* item, QString index, std::string dev_n) : dev_index(index), dev_name(dev_n), device_widget_item(item), pcap_dev(device) {
        std::cout << "Appel constructeur CWT" << std::endl;
        last_tcp_hdr = new tcp_hdr;
        DE = new DetectionEngine();
    }

    inline ~Capture_WorkerThread() {
        delete filtre;
        delete pcap_dev;
    }

    inline void regulateur_de_vitesse()
    {
        if(milisecs == QTime::currentTime().msec()) { this->thread()->usleep(21); }
        curr_time = QTime::currentTime();
        milisecs = curr_time.msec();
    }

    inline void run() override
    {
        handler = pcap_open(dev_name.c_str(), 65536, PCAP_OPENFLAG_PROMISCUOUS, 100, NULL, *ERRBUFF);

        QString data;
        QString data_to_send_to_http_brief;

        QList<QString> connexion_en_attente_d_acquitement;
        QList<QString> connexions_etablies;

        // TODO
        if(handler != NULL)     // Les erreurs seront affichées plus tard dans une QDialog !!!!!
        {
            while(true)
            {
                pcap_next_packet = pcap_next_ex(handler, &pckt_header, &pckt_data);
                if(pcap_datalink(handler) == DLT_EN10MB && pcap_next_packet > 0)
                {
                    if(device_widget_item->checkState(0))
                    {
                        PROCESS_ETHERNET_PACKET(handler, pckt_data, pckt_header, last_tcp_hdr);
                    }
                }
            }
        }
    }


    inline void apply_a_filter(QString filter, pcap_t* handler, QLineEdit* QLE)
    {
        // Récupérer le masque mask
        if(pcap_dev->addresses != NULL)
        {
            netmask = ((struct sockaddr_in *)(pcap_dev->addresses->netmask))->sin_addr.S_un.S_addr;
        } else {
            netmask = 0xffffff; // 255.255.255.0
        }

        // Compile filter
        int compile_filter = pcap_compile(handler, &bpfprog, filter.toStdString().c_str(), 1, netmask);
            if(compile_filter < 0) { QLE->setStyleSheet("background-color: #ff4d4d; border: 1px solid #7f8c8d; border-radius: 5px;"); std::cerr << "Erreur de filtrage." << std::endl; } else {
                 QLE->setStyleSheet("background-color: #3ae374; border: 1px solid #7f8c8d; border-radius: 5px;");
                 emit here_is_a_valid_filter_to_store(filter);
            }

        // Set filter
        int set_filter = pcap_setfilter(handler, &bpfprog);
        if(set_filter < 0) { std::cerr << "Erreur d'application de filtrage." << std::endl; }
    }

signals:

    void ready();
    void go(pcap_t*, const u_char*, struct pcap_pkthdr*, tcp_hdr*);
    void packet_notify();
    void test_signal(QTreeWidgetItem*, QString);
    void label_increment();
    void send_to_http_brief(QTreeWidgetItem*, QString);
    void send_to_http_srv_chart(QString);
    void send_http_code(QString);
    void here_is_packet_nbr(qreal);
    void here_is_tcp_flx(qreal);
    void here_is_udp_flx(qreal);
    void here_is_packet_size(qreal);
    void here_is_final_packet(QString);
    void SEND_TO_CAP_TABLE(QStringList*);
    void here_is_a_valid_filter_to_store(QString);
    void SEND_TO_EVENTS_SIG(QStringList*);

public slots:

    void SEND_TO_EVENTS(QStringList* in) {
        emit(SEND_TO_EVENTS_SIG(in));
    }

    inline void PROCESS_ETHERNET_PACKET(pcap_t* handler, const u_char *pckt_data, struct pcap_pkthdr *header, tcp_hdr* last_tcp_hdr)
    {
            emit ready();
            packet = new QStringList;
            // Index

            // Date et heure
            curr_time = QTime::currentTime();
            time = QString::number(curr_time.hour()) + ":" + QString::number(curr_time.minute()) + ":" + QString::number(curr_time.second());
            packet->append(time);

            // Taille
            packet->append(QString::number(header->len));

            // Couche 2 -> Statique -> Ethernet
            eth_h = (eth_hdr*)(pckt_data);
            packet->append("Ether");
            packet->append(eth_mac_addr_form(eth_h->dst.oct1, eth_h->dst.oct2, eth_h->dst.oct3, eth_h->dst.oct4, eth_h->dst.oct5, eth_h->dst.oct6, eth_h->src.oct1, eth_h->src.oct2, eth_h->src.oct3, eth_h->src.oct4, eth_h->src.oct5, eth_h->src.oct6));

            // Couche 3 -> Variable
            ethertype = short_to_hex(ubs(eth_h->ether_type));

            if(ethertype == "800" || ethertype == "86dd") //IPv4 0x800 ou IPv6 0x86dd
            {
                u_char protoc = NULL;
                const u_char* delimit = NULL;

                if(ethertype == "800" ) //IPv4
                {
                    ip4_h = (ip4_hdr*)(pckt_data+14);
                    packet->append("IPv4");
                    packet->append (ip4_packet_format(ip4_h));
                    packet->append(ip4_display_ttl(ip4_h));
                    delimit = pckt_data + 14 + 20;
                    protoc = ip4_h->protocol;

                } else {
                    if(ethertype == "86dd") //IPv6
                    {
                        packet->append("IPv6");
                        ip6_h = (ip6_hdr*)(pckt_data + 14);
                        packet->append(single_ip6_addr_form(ip6_h->src.oct1, ip6_h->src.oct2, ip6_h->src.oct3, ip6_h->src.oct4, ip6_h->src.oct5, ip6_h->src.oct6, ip6_h->src.oct7, ip6_h->src.oct8) + " -> " + single_ip6_addr_form(ip6_h->dst.oct1, ip6_h->dst.oct2, ip6_h->dst.oct3, ip6_h->dst.oct4, ip6_h->dst.oct5, ip6_h->dst.oct6, ip6_h->dst.oct7, ip6_h->dst.oct8));
                        protoc = ip6_h->next_header;
                        IP6_HL = "HL: " + QString::number(ip6_h->hop_limit);
                        packet->append(IP6_HL);

                        delimit = pckt_data + 14 + 40;
                    }
                }

                switch((int)protoc)
                {
                    case 1: // ICMP
                    {
                        packet->append("ICMP");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        break;
                    }

                    case 6: // TCP
                    {
                        tcp_h = (tcp_hdr*)delimit;

                        packet->append("TCP");
                        packet->append(QString::number((int)ubs(tcp_h->sport)) + " -> " + QString::number((int)ubs(tcp_h->dport)));

                        if(get_tcp_flags_from_bin(tcp_h) != "") { tcp_info = "[" + get_tcp_flags_from_bin(tcp_h); } else { tcp_info = "[ NULL ] "; }
                        tcp_info += "[SEQ: " + QString::number(tcp_h->seq_number) + "  ACK: " + QString::number(tcp_h->ack_number) + "] ";
                        if(tcp_h->ack_number != 0 && last_tcp_hdr->ack_number == tcp_h->ack_number) { tcp_info += " [ACK Précédent] "; }
                        packet->append(tcp_info);

                        two_digits = char_tohex(tcp_h->header_length_and_reserved);
                        two_digits.replace(two_digits.length()-1, two_digits.length(), "");
                        tcp_header_size = two_digits.toInt();
                        tcp_header_size *= 4;
                        app_data = (char*)(delimit + tcp_header_size);
                        *last_tcp_hdr = *tcp_h;

                        /* ----------------------------- Application ----------------------------- */

                        // HTTP
                        if((app_data.contains(http_rx) || app_data.contains(rx) || app_data.contains(rx2)) && app_data.at(1) != "*" && !app_data.contains("M-SEARCH * HTTP/1.1"))
                        {
                           if(ethertype == "800")
                           {
                               http_target = http_ip_addr(ip4_h);
                           } else if(ethertype == "86dd" && (int)ubs(tcp_h->sport) != 443) {
                                *http_target = single_ip6_addr_form(ip6_h->src.oct1, ip6_h->src.oct2, ip6_h->src.oct3, ip6_h->src.oct4, ip6_h->src.oct5, ip6_h->src.oct6, ip6_h->src.oct7, ip6_h->src.oct8);
                           }

                           http_target->append(":");

                           if(tcp_h->sport)
                           {
                               http_target->append(QString::number((long)ubs(tcp_h->sport)));
                           }


                           http_brief_data = new QTreeWidgetItem;
                           http_brief_data = http_srv(http_target);

                           emit send_to_http_brief(http_brief_data, app_data.toHtmlEscaped());
                           emit send_to_http_srv_chart(*http_target);
                           emit send_http_code(app_data.mid(9,10));
                           packet->append("HTTP");

                        } else { // HTTPS
                            if((int)ubs(tcp_h->dport) == 443 || (int)ubs(tcp_h->sport) == 443)
                            { packet->append("HTTPS"); } else { // DNS
                                if((int)ubs(tcp_h->dport) == 53) { packet->push_back("DNS"); }
                            }
                        }

                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");

                        break;
                    }

                    case 17:
                    {
                        packet->push_back("UDP");
                        udp_h = (udp_hdr*)delimit;
                        packet->push_back(QString::number((int)ubs(udp_h->sport)) + " -> " + QString::number(((int)ubs(udp_h->dport))));
                        //std::cout << (int)ubs(udp_h->length) << std::endl;
                        app_data = (char*)delimit + 8;

                        // SSDP
                        if(app_data.contains("M-SEARCH *") || app_data.contains("ssdp")) { packet->push_back("SSDP"); } else {
                            // DNS
                            if((int)ubs(udp_h->dport) == 53) { packet->push_back("DNS"); }
                        }


                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");

                        break;
                    }

                default:
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");

                    break;
                }


            } else if(ethertype == "806") // ARP 0x0806
                {
                    arp_h = (arp_hdr*)(pckt_data+14);
                    packet->append("ARP");
                    packet->append(arp_packet_format(arp_h));

                    // Bourrage pour couleur
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");
                    packet->append(" ");
                } else if(ethertype == "893a" || ethertype == "887b" || ethertype == "88e1") //IEEE-1905.1-Control
                    {
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                        packet->append(" ");
                    }

            emit packet_notify();
            emit label_increment();
            emit here_is_packet_nbr((qreal)i);
            emit here_is_packet_size((qreal)header->len);
            emit SEND_TO_CAP_TABLE(packet);

        }

    inline void apply_filter(QString data, QLineEdit* QLE) { std::cout <<  data.toStdString() << std::endl; apply_a_filter(data, handler, QLE); }


};

#endif // CAPTURETHREADS_H
