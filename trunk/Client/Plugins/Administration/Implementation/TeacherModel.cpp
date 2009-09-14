#include "TeacherModel.h"

 #include <QtGui>

 //#include "treeitem.h"


 TeacherModel::TeacherModel(const QString &data, QObject *parent)
     : QAbstractItemModel(parent)
 {
 }

 TeacherModel::~TeacherModel()
 {
 }

 int TeacherModel::columnCount(const QModelIndex &parent) const
 {
 }

 QVariant TeacherModel::data(const QModelIndex &index, int role) const
 {
 }

 Qt::ItemFlags TeacherModel::flags(const QModelIndex &index) const
 {
 }

 QVariant TeacherModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
 {
 }

 QModelIndex TeacherModel::index(int row, int column, const QModelIndex &parent)
             const
 {
 }

 QModelIndex TeacherModel::parent(const QModelIndex &index) const
 {

 }

 int TeacherModel::rowCount(const QModelIndex &parent) const
 {
 }

 void TeacherModel::setupModelData(const QStringList &lines)
 {
 }
