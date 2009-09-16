#ifndef				__HORUSSTYLE_H__
# define			__HORUSSTYLE_H__

# include			<QPlastiqueStyle>
# include			<QString>

class				HorusStyle : public QPlastiqueStyle
{
public:
	int				pixelMetric(PixelMetric metric, const QStyleOption *option = 0, const QWidget *widget = 0) const;
};

#endif
