#include "StudentModel.h"

 StudentModel::StudentModel(const QString &data, QObject *parent)
     : QAbstractItemModel(parent)
 {
 }

 StudentModel::~StudentModel()
 {
 }

 int StudentModel::columnCount(const QModelIndex &parent) const
 {
 }

 QVariant StudentModel::data(const QModelIndex &index, int role) const
 {
 }

 Qt::ItemFlags StudentModel::flags(const QModelIndex &index) const
 {
 }

 QVariant StudentModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
 {
 }

 QModelIndex StudentModel::index(int row, int column, const QModelIndex &parent)
             const
 {
 }

 QModelIndex StudentModel::parent(const QModelIndex &index) const
 {

 }

 int StudentModel::rowCount(const QModelIndex &parent) const
 {
 }

 void StudentModel::setupModelData(const QStringList &lines)
 {
 }
