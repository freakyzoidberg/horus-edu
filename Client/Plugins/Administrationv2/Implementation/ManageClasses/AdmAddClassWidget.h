#ifndef ADMADDCLASSWIDGET_H
#define ADMADDCLASSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>

class AdmAddClassWidget : public QWidget
{
public:
    AdmAddClassWidget();

private:
    void        initUserReferent(void);

    QLabel      *_classNameLabel;
    QLineEdit   *_className;

    QLabel      *_userReferentLabel;
    QComboBox   *_userReferent;

    QPushButton *_save;
    QPushButton *_cancel;

    QVBoxLayout *_mainLayout;
};

#endif // ADMADDCLASSWIDGET_H
