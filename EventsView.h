#ifndef EVENTSVIEW_H
#define EVENTSVIEW_H

#include "QTableViewModel.h"
#include <QScrollBar>
#include <QDate>

class EventView_TableModel : public Packets_TableModel
{
       Q_OBJECT

private:
    QTableView *qtvp;
    EventView_TableModel *temp;

public :

    EventView_TableModel(QTableView* targ) : qtvp(targ) {
        qtvp->setModel(this);
    }

    QList<QStringList> Details; // Exception !!

    QVariant data(const QModelIndex &ind, int role) const override {

        if(!ind.isValid()) { return QVariant(); }
        if(role == Qt::DisplayRole) { return packets_rlist[ind.row()][ind.column()]; }

        if(role == Qt::BackgroundColorRole)
        {
            for(int i = -9 ; i < 9 ; i ++){
               if(index(ind.row(), ind.column()+i).data() == "Alerte") { return QColor("#E54C38"); } else {
                 if(index(ind.row(), ind.column()+i).data() == "Warning") { return QColor("#ffbc93"); } else {
                   if(index(ind.row(), ind.column()+i).data() == "Info") { return QColor("#BCECE6"); }
                    }
                }
            }
        }

        if(role == Qt::TextColorRole) { return QColor("#2f3640"); }

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

    void ADD_TO_LIST(QStringList* data, QStringList _details_) {

        Details.append(_details_);

        QStringList newQSL = *data;
        this->packets_rlist.push_back(newQSL);
        temp = new EventView_TableModel(qtvp);
        if(temp != NULL) { delete temp; }


        // ***** IL Y'A PROBLEME ICI : REUTILISATION DE LA MEMOIRE APRES SA LIBERATION ***** //

        // temp->ADD_TO_LIST2(this->getpackrlist()); // Voilaaa la redef

        if(qtvp->verticalScrollBar()->sliderPosition() == qtvp->verticalScrollBar()->maximum()) {
            qtvp->scrollToBottom();
        }

        qtvp->setModel(temp);
        data->clear();
    }
};


#endif // EVENTSVIEW_H
