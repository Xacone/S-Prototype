#ifndef TCPTABLEMODEL_H
#define TCPTABLEMODEL_H
#include "QTableViewModel.h"

class Tcp_TableModel : public Packets_TableModel
{
public:
    Tcp_TableModel() {};
    Tcp_TableModel(QList<QStringList> data) { packets_rlist = data; }
    int columnCount(const QModelIndex & /* parent */ = QModelIndex()) const override {
        return 5;
    }

    QVariant data(const QModelIndex &ind, int role) const override {

        if(!ind.isValid()) { return QVariant(); }
        if(role == Qt::DisplayRole) { return packets_rlist[ind.row()][ind.column()]; }
        if(role == Qt::FontRole) { return QFont("Arial", 10, QFont::Bold); }
        if(role == Qt::TextColorRole) { return QColor(Qt::black); }

        if(role == Qt::BackgroundColorRole)
        {
            for(int i = -6 ; i < 6 ; i ++){
                if(index(ind.row(), ind.column()+i).data() == "CLOSED") { return QColor("#c0392b"); } else {
                 if(index(ind.row(), ind.column()+i).data() == "LISTEN") { return QColor("#1abc9c"); } else {
                  if(index(ind.row(), ind.column()+i).data() == "SYN-SENT") { return QColor("#f1c40f"); } else {
                   if(index(ind.row(), ind.column()+i).data() == "SYN-RECEIVED") { return QColor("#f39c12"); } else {
                    if(index(ind.row(), ind.column()+i).data() == "ESTABLISHED") { return QColor("#2ecc71"); } else {
                     if(index(ind.row(), ind.column()+i).data() == "FIN-WAIT") { return QColor("#3498db"); } else {
                      if(index(ind.row(), ind.column()+i).data() == "FIN-WAIT-1") { return QColor("#2980b9"); } else {
                       if(index(ind.row(), ind.column()+i).data() == "CLOSE-WAIT") { return QColor("#e74c3c"); } else {
                        if(index(ind.row(), ind.column()+i).data() == "CLOSING") { return QColor("#c0392b"); } else {
                         if(index(ind.row(), ind.column()+i).data() == "LAST-ACK") { return QColor("#e67e22"); } else {
                          if(index(ind.row(), ind.column()+i).data() == "TIME-WAIT") { return QColor("#82ccdd"); } else {
                           if(index(ind.row(), ind.column()+i).data() == "DELETE-TCB") { return QColor("#f5f6fa"); } else {

        }}}}}}}}}}}}}}

        return QVariant();
    }


    QVariant headerData(int section, Qt::Orientation orientation, int role) const override
    {
        if(role != Qt::DisplayRole) { return QVariant(); }

        if(orientation == Qt::Horizontal)
        {
            switch(section)
            {
            case 0:
                return "Adresse locale";
            case 1:
                return "Port local";
            case 2:
                return "Adresse distante";
            case 3:
                return "Port distant";
            case 4:
                return "Etat";
            default:
                break;
            }
        } else {
            return QString("%1").arg(section);
        }
            return QVariant();
    }

};

#endif // TCPTABLEMODEL_H
