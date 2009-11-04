#include	"HorusStyle.h"

#include	<QStyleOptionTab>

int			HorusStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
	if (metric == QStyle::PM_DockWidgetSeparatorExtent)
		return (2);
	return (QPlastiqueStyle::pixelMetric(metric, option, widget));
}

//void		HorusStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
//{
//	switch (element)
//	{
//	case QStyle::CE_TabBarTab:
//		{
//			QStyleOptionTab myTabOption;
//			const QStyleOptionTab *tabOption = qstyleoption_cast<const QStyleOptionTab *>(option);
//			if (tabOption)
//			{
//				myTabOption = *tabOption;
//				if (myTabOption.shape == QTabBar::RoundedNorth)
//				{
//					int pos = (qobject_cast<const QTabBar *>(widget))->count() - 1;
//					myTabOption.rect = QRect(myTabOption.rect.x() + pos * 100, myTabOption.rect.y(), 100, 100);
//				}
//			}
//			QPlastiqueStyle::drawControl(element, &myTabOption, painter, widget);
//		}
//		break;
//	default:
//		QPlastiqueStyle::drawControl(element, option, painter, widget);
//	}
//}
