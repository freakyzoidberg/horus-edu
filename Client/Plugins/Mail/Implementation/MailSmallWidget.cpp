#include					"MailSmallWidget.h"

#include					<QListView>
#include					<QBoxLayout>
#include					<QSortFilterProxyModel>

#include					"../../../../Common/Data.h"

MailSmallWidget::MailSmallWidget(MailDataPlugin *mailPlugin) : _mailPlugin(mailPlugin)
{
	QBoxLayout				*layout;
	QSortFilterProxyModel	*filter;
	QListView				*view;

	layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	layout->setMargin(0);
	layout->setSpacing(0);
	view = new QListView(this);
	layout->addWidget(view);
	filter = new QSortFilterProxyModel(this);
	filter->setSourceModel(mailPlugin->listModel());
	filter->setFilterRole(Data::FILTER_ROLE);
	filter->setFilterFixedString("INBOX");
	view->setModel(filter);
}
