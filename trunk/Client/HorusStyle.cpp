#include	"HorusStyle.h"

int			HorusStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
	if (metric == QStyle::PM_DockWidgetSeparatorExtent)
		return (2);
	return (QPlastiqueStyle::pixelMetric(metric, option, widget));
}
