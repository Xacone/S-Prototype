#ifndef EVENTSVIEW_H
#define EVENTSVIEW_H

#include "QTableViewModel.h"
#include <QScrollBar>


class EventView_TableModel : public Packets_TableModel
{
       Q_OBJECT

protected:
    QTableView *qtvp;
    EventView_TableModel *temp;

public :

    EventView_TableModel(QTableView* targ) : qtvp(targ) { qtvp->setModel(this); }

    QVariant data(const QModelIndex &ind, int role) const override {

        if(!ind.isValid()) { return QVariant(); }
        if(role == Qt::DisplayRole) { return packets_rlist[ind.row()][ind.column()]; }


        if(role == Qt::BackgroundColorRole)
        {
            for(int i = -9 ; i < 9 ; i ++){
                if(index(ind.row(), ind.column()+i).data() == "Alerte") { return QColor("#ff5148"); } else {
                 if(index(ind.row(), ind.column()+i).data() == "Warning") { return QColor("#fd9644"); } else {
                   if(index(ind.row(), ind.column()+i).data() == "Info") { return QColor("#62a8ff"); }
                    }
                }
            }
        }

        if(role == Qt::TextColorRole) { return QColor("#000000"); }

        return QVariant();
    }

    int columnCount(const QModelIndex & /*parent*/ = QModelIndex()) const override { return 9; }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override
    {
        if(role != Qt::DisplayRole) { return QVariant(); }

        if(orientation == Qt::Horizontal)
        {
            switch(section)
            {
            case 0:
                return "N°";
            case 1:
                return "Date et Heure";
            case 2:
                return "Niveau";
            case 3:
                return "Type";
            case 4:
                return "Source";
            case 5:
                return "Destination(s)";
            case 6:
                return "CVE";
            case 7:
                return "Protocole(s)";
            case 8:
                return "Détails";
            default:
                break;
            }

        } else {
            return QString("%1").arg(section);
        }
            return QVariant();
    }

public slots:
    void ADD_TO_LIST(QStringList* data) {

        QStringList newQSL = *data;
        this->packets_rlist.push_back(newQSL);
        temp = new EventView_TableModel(qtvp);
        temp->ADD_TO_LIST2(this->getpackrlist());

        if(qtvp->verticalScrollBar()->sliderPosition() == qtvp->verticalScrollBar()->maximum()) {
            qtvp->scrollToBottom();
        }

        qtvp->setModel(temp);
        data->clear();
    }
};



#endif // EVENTSVIEW_H
