#include		"EventSmallDisplayable.h"

#include		<QLabel>
#include		<QWidget>
#include		<QFrame>
#include		<QBoxLayout>

const QString	EventSmallDisplayable::pluginName() const
{
	return ("EventSmallDisplayable");
}

const QString	EventSmallDisplayable::pluginVersion() const
{
	return ("0.1");
}

QWidget			*EventSmallDisplayable::getWidget()
{// FAKE
	QWidget		*widget;
	QBoxLayout	*layout;
	QWidget		*subWidget;

	widget = new QWidget();
	layout = new QBoxLayout(QBoxLayout::TopToBottom, widget);
	subWidget = new QFrame(widget);
	new QLabel("Monday 24/11  11h00 : ENGLISH LESSON", subWidget);
	layout->addWidget(subWidget);
	subWidget = new QFrame(widget);
	new QLabel("Monday 24/11  14h00 : SPORT", subWidget);
	layout->addWidget(subWidget);
	subWidget = new QFrame(widget);
	new QLabel("Tuesday 25/11  10h00 : MATHEMATICS", subWidget);
	layout->addWidget(subWidget);
	return (widget);
}// FIN FAKE

const QString	EventSmallDisplayable::getDisplayableName() const
{
	return (tr("Incomming events"));
}

QIcon			EventSmallDisplayable::getIcon() const
{
	return (QIcon(":/agenda.png"));
}
