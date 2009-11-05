#ifndef				__HORUSSTYLE_H__
# define			__HORUSSTYLE_H__

# include			<QPlastiqueStyle>
# include			<QString>

class				HorusStyle : public QPlastiqueStyle
{
public:
	int				pixelMetric(PixelMetric metric, const QStyleOption *option = 0, const QWidget *widget = 0) const;
	void			drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
	QRect			subElementRect(SubElement sr, const QStyleOption *opt, const QWidget *widget) const;
};

#endif
