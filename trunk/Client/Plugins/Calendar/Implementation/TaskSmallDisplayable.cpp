#include		"TaskSmallDisplayable.h"

#include		<QLabel>
#include		<QWidget>
#include		<QFrame>
#include		<QBoxLayout>

const QString	TaskSmallDisplayable::pluginName() const
{
	return ("TaskSmallDisplayable");
}

const QString	TaskSmallDisplayable::pluginVersion() const
{
	return ("0.1");
}

QWidget			*TaskSmallDisplayable::getWidget()
{// FAKE
	QWidget		*widget;
	QBoxLayout	*layout;
	QWidget		*subWidget;

	widget = new QWidget();
	layout = new QBoxLayout(QBoxLayout::TopToBottom, widget);
	subWidget = new QFrame(widget);
	new QLabel("History Homework due on  24/11", subWidget);
	layout->addWidget(subWidget);
	subWidget = new QFrame(widget);
	new QLabel("Prepare Physics Exam for  25/11", subWidget);
	layout->addWidget(subWidget);
	subWidget = new QFrame(widget);
	new QLabel("Geographic Homework due on  27/11", subWidget);
	layout->addWidget(subWidget);
	subWidget = new QFrame(widget);
	new QLabel("Prepare English Exam for  28/11", subWidget);
	layout->addWidget(subWidget);
	subWidget = new QFrame(widget);
	new QLabel("English speak due on  30/11", subWidget);
	layout->addWidget(subWidget);
	return (widget);
}// FIN FAKE

const QString	TaskSmallDisplayable::getDisplayableName() const
{
	return (tr("Task list"));
}

QIcon			TaskSmallDisplayable::getIcon() const
{
	return (QIcon(":/schedule_256.png"));
}
