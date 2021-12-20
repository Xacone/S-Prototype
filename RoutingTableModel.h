#ifndef ROUTINGTABLEMODEL_H
#define ROUTINGTABLEMODEL_H
#include "QTableViewModel.h"

class Routing_TableModel : public Packets_TableModel
{
public:
    Routing_TableModel() {};
    Routing_TableModel(QList<QStringList> data) { packets_rlist = data; }
    int columnCount(const QModelIndex & /* parent */ = QModelIndex()) const override {
        return 8;
    }

    QVariant data(const QModelIndex &ind, int role) const override {

        if(!ind.isValid()) { return QVariant(); }
        if(role == Qt::DisplayRole) { return packets_rlist[ind.row()][ind.column()]; }
        if(role == Qt::FontRole) { return QFont("Arial", 10, QFont::Bold); }
        if(role == Qt::TextColorRole) { return QColor(Qt::black); }

        if(role == Qt::BackgroundColorRole)
        {
            for(int i = -9 ; i < 9 ; i ++){
                if(index(ind.row(), ind.column()+i).data() == "Local") { return QColor("#B5DDC2"); } else {
                 if(index(ind.row(), ind.column()+i).data() == "Route statique établie lors de la configuration") { return QColor("#F2E3CF"); } else {
                   if(index(ind.row(), ind.column()+i).data() == "Redirection ICMP") { return QColor("#E3F0CE"); }
                    }
                }
            }

        }
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
                return "Destination";
            case 1:
                return "Masque";
            case 2:
                return "Prochain saut";
            case 3:
                return "Index";
            case 4:
                return "Type";
            case 5:
                return "Protocole/Type";
            case 6:
                return "Métrique";
            case 7:
                return "Âge";
            default:
                break;
            }
        } else {
            return QString("%1").arg(section);
        }
            return QVariant();
    }
};

#endif // ROUTINGTABLEMODEL_H
