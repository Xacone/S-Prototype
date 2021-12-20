#ifndef QTABLEVIEWMODEL_H
#define QTABLEVIEWMODEL_H


#include <QTableView>
#include <QDebug>
#include <QAbstractTableModel>
#include <QStringList>
#include <iostream>
#include <QThread>
#include <QVariant>
#include <QTableWidget>


class Packets_TableModel : public QAbstractTableModel
{
    Q_OBJECT

protected:

    QList<QStringList> packets_rlist;

public:

    virtual QList<QStringList> getpackrlist() { return packets_rlist; }

    Packets_TableModel() {}
    Packets_TableModel(QObject *parent) : QAbstractTableModel(parent) {}
    Packets_TableModel(QList<QStringList> data) { packets_rlist.append(data); }
    ~Packets_TableModel() {};

    int rowCount(const QModelIndex & /*parent*/ = QModelIndex()) const override { return packets_rlist.size(); }
    int columnCount(const QModelIndex & /*parent*/ = QModelIndex()) const override { return 13; }

    bool setData(const QModelIndex &index, const QVariant &value, int role) override
    {
        if (!index.isValid() || role != Qt::EditRole) // Si n'est pas valide ---> Poubelle
            return false;

        packets_rlist[index.row()][index.column()] = value.toString();
        emit dataChanged(index, index);
        return true;
    }

    QVariant data(const QModelIndex &ind, int role) const override {

        if(!ind.isValid()) { return QVariant(); }
        if(role == Qt::DisplayRole) { return packets_rlist[ind.row()][ind.column()]; }

        if(role == Qt::BackgroundColorRole)
        {
            for(int i = -9 ; i < 9 ; i ++){
                if(index(ind.row(), ind.column()+i).data() == "ARP") { return QColor("#FFDFD3"); } else {
                 if(index(ind.row(), ind.column()+i).data() == "ICMP") { return QColor("#D0EAFA"); } else {
                   if(index(ind.row(), ind.column()+i).data() == "TCP") { return QColor("#C5D2EF"); } else {
                      if(index(ind.row(), ind.column()+i).data() == "UDP") { return QColor("#FCF5DB"); } else {

                            }
                        }
                    }
                }
            }
        }

        if(role == Qt::TextColorRole) { return QColor("#34495E"); }

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
                return "Temps";
            case 1:
                return "Taille";
            case 2:
                return "";
            case 3:
                return "";
            case 4:
                return "";
            case 5:
                return "";
            case 6:
                return "";
            case 7:
                return "";
            case 8:
                return "";
            case 9:
                return "";
            case 10:
                return "";
            case 11:
                return "";
            case 12:
                return "";
            case 13:
                return "";
            default:
                break;
            }
        } else {
            return QString("%1").arg(section);
        }
            return QVariant();
    }


    Qt::ItemFlags flags(const QModelIndex &index) const override
    {
        if(!index.isValid()) {return Qt::ItemIsEnabled; }
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }


    bool insertRows(int position, int rows, const QModelIndex &parent) override
    {

        int columns = columnCount();
        beginInsertRows(parent, position, position + rows - 1); // C'est pour le MVC...

        for (int r = 0; r < rows; ++r) {
            QStringList items;
            for (int c = 0; c < columns; ++c)
                items.append("");
            packets_rlist.insert(position, items);
        }

        endInsertRows(); // C'est pour le MVC...
        return true;
    }


    bool insertColumns(int position, int columns,const QModelIndex &parent) override
    {
        int rows = rowCount();
        beginInsertColumns(parent, position, position + columns - 1); // C'est pour le MVC...

        for (int r = 0; r < rows; ++r) {
            for (int c = position; c < columns; ++c) {
                packets_rlist[r].insert(position, "");
            }
        }

        endInsertColumns(); // C'est pour le MVC...
        return true;
    }


    bool removeRows(int position, int rows, const QModelIndex &parent) override
    {
        beginRemoveRows(parent, position, position + rows - 1);

        for (int row = 0; row < rows; ++row) {
            packets_rlist.removeAt(position);
        }

        endRemoveRows();
        return true;
    }


    bool removeColumns(int position, int columns, const QModelIndex &parent) override
    {
        int rows = rowCount();
        beginRemoveColumns(parent, position, position + columns - 1);

        for (int row = 0; row < rows; ++row) {
            for (int column = 0; column < columns; ++column) {
                packets_rlist[row].removeAt(position);
            }
        }

        endRemoveColumns();
        return true;
    }

    void free_it()
    {
        packets_rlist.clear();
    }

public slots:

    void ADD_TO_LIST(QStringList* data) {
        packets_rlist.push_back(*data);
    }

    void ADD_TO_LIST2(QList<QStringList> data) { packets_rlist.append(data); }
};

class Model_CoworkerThread : public QThread
{
    Q_OBJECT

private:
    Packets_TableModel *ptm;
public:
    Model_CoworkerThread() { ptm = new Packets_TableModel(); }
    void run() override
    {
        while(true)
        {
            emit here_is_new_ptm(ptm);
            this->thread()->sleep(1);
        }
    }

public slots:
    void here_is_new_packets(QStringList* data){
        ptm->ADD_TO_LIST(data);
    }

    void clear_ptm() { ptm->free_it();}

signals:
    void here_is_new_ptm(Packets_TableModel*);
};



#endif // QTABLEVIEWMODEL_H
