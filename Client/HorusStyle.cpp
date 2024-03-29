/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include	"HorusStyle.h"

#include	<QStyleOptionTab>
#include	<QPainter>

int			HorusStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
	if (metric == QStyle::PM_DockWidgetSeparatorExtent)
		return (2);
	return (QPlastiqueStyle::pixelMetric(metric, option, widget));
}

void		HorusStyle::drawControl(ControlElement element, const QStyleOption *opt, QPainter *p, const QWidget *widget) const
{
	switch (element)
	{
    case CE_TabBarTabLabel:
        if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(opt)) {
            QStyleOptionTabV3 tabV2(*tab);
            QRect tr = tabV2.rect;
			if (tabV2.shape != QTabBar::TriangularWest && tabV2.shape != QTabBar::TriangularNorth)
			{
				QPlastiqueStyle::drawControl(element, opt, p, widget);
				break;
			}
            bool verticalTabs = tabV2.shape == QTabBar::RoundedEast
                                || tabV2.shape == QTabBar::RoundedWest
                                || tabV2.shape == QTabBar::TriangularEast
                                || tabV2.shape == QTabBar::TriangularWest;

			int alignment;
			if (verticalTabs)
				alignment = Qt::AlignCenter | Qt::TextShowMnemonic;
			else
				alignment = Qt::AlignLeft | Qt::TextShowMnemonic;
            if (!styleHint(SH_UnderlineShortcut, opt, widget))
                alignment |= Qt::TextHideMnemonic;

            if (verticalTabs) {
                p->save();
                int newX, newY, newRot;
                if (tabV2.shape == QTabBar::RoundedEast || tabV2.shape == QTabBar::TriangularEast) {
                    newX = tr.width() + tr.x();
                    newY = tr.y();
                    newRot = 90;
                } else {
                    newX = tr.x();
					newY = tr.y() +  (tabV2.shape == QTabBar::TriangularWest ? 0 : tr.height());
					newRot = tabV2.shape == QTabBar::TriangularWest ? 0 : -90;
                }
                QTransform m;
                m.translate(newX, newY);
                m.rotate(newRot);
                p->setTransform(m, true);
            }
            tr = subElementRect(SE_TabBarTabText, opt, widget);

            if (!tabV2.icon.isNull()) {
				QSize iconSize;
				int iconExtent;
				if (tabV2.shape == QTabBar::TriangularWest)
					iconExtent = 32;
				else if (tabV2.shape == QTabBar::TriangularNorth)
					iconExtent = 24;
				iconSize = QSize(iconExtent, iconExtent);
                QSize tabIconSize = tabV2.icon.actualSize(iconSize,
                                                          (tabV2.state & State_Enabled) ? QIcon::Normal
                                                          : QIcon::Disabled);
                QPixmap tabIcon = tabV2.icon.pixmap(iconSize,
                                                    (tabV2.state & State_Enabled) ? QIcon::Normal
                                                                                  : QIcon::Disabled);

                int offset = 4;
                int left = opt->rect.left();
                if (tabV2.leftButtonSize.isEmpty())
                    offset += 2;
                else
                    left += tabV2.leftButtonSize.width() + (6 + 2) + 2;
                QRect iconRect = QRect(left + offset, tr.center().y() - tabIcon.height() / 2,
                            tabIconSize.width(), tabIconSize.height());
				if (tabV2.shape == QTabBar::TriangularWest)
					iconRect = QRect(tr.center().x() - tabIcon.width() / 2, 10, tabIconSize.width(), tabIconSize.height());
				else if (tabV2.shape == QTabBar::TriangularNorth)
					iconRect = QRect(4, tr.center().y() - tabIcon.height() / 2,  tabIconSize.width(), tabIconSize.height());
				if (!verticalTabs)
					iconRect = visualRect(opt->direction, opt->rect, iconRect);
				p->drawPixmap(tabV2.rect.left() + iconRect.x(), iconRect.y(), tabIcon);
            }

            drawItemText(p, tr, alignment, tab->palette, tab->state & State_Enabled, tab->text, QPalette::WindowText);
            if (verticalTabs)
                p->restore();

            if (tabV2.state & State_HasFocus) {
                const int OFFSET = 1 + pixelMetric(PM_DefaultFrameWidth);

                int x1, x2;
                x1 = tabV2.rect.left();
                x2 = tabV2.rect.right() - 1;

                QStyleOptionFocusRect fropt;
                fropt.QStyleOption::operator=(*tab);
                fropt.rect.setRect(x1 + 1 + OFFSET, tabV2.rect.y() + OFFSET,
                                   x2 - x1 - 2*OFFSET, tabV2.rect.height() - 2*OFFSET);
                drawPrimitive(PE_FrameFocusRect, &fropt, p, widget);
            }
        }
        break;
	default:
		QPlastiqueStyle::drawControl(element, opt, p, widget);
	}
}

QRect HorusStyle::subElementRect(SubElement sr, const QStyleOption *opt, const QWidget *widget) const
{
    QRect r;
	switch (sr)
	{
    case SE_TabBarTabText:
        if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(opt)) {
            QStyleOptionTabV3 tabV2(*tab);
            QRect tr = tabV2.rect;
            bool verticalTabs = tabV2.shape == QTabBar::RoundedEast
                                || tabV2.shape == QTabBar::RoundedWest
                                || tabV2.shape == QTabBar::TriangularEast
                                || tabV2.shape == QTabBar::TriangularWest;
			if (tabV2.shape == QTabBar::TriangularWest)
                tr.setRect(0, 0, tr.width(), tr.height());
            else if (verticalTabs)
                tr.setRect(0, 0, tr.height(), tr.width());
            int verticalShift = pixelMetric(QStyle::PM_TabBarTabShiftVertical, tab, widget);
            int horizontalShift = pixelMetric(QStyle::PM_TabBarTabShiftHorizontal, tab, widget);
            if (tabV2.shape == QTabBar::RoundedSouth || tabV2.shape == QTabBar::TriangularSouth)
                verticalShift = -verticalShift;
            tr.adjust(0, 0, horizontalShift, verticalShift);
            bool selected = tabV2.state & State_Selected;
            if (selected) {
                tr.setBottom(tr.bottom() - verticalShift);
                tr.setRight(tr.right() - horizontalShift);
            }

            // left widget
            if (!tabV2.leftButtonSize.isEmpty()) {
                tr.setLeft(tr.left() + 6 + 2 +
                    (verticalTabs ? tabV2.leftButtonSize.height() : tabV2.leftButtonSize.width()));
            }

            // icon
            if (!tabV2.icon.isNull()) {
                QSize iconSize = tabV2.iconSize;
                if (!iconSize.isValid()) {
                    int iconExtent = pixelMetric(PM_SmallIconSize);
                    iconSize = QSize(iconExtent, iconExtent);
                }
                QSize tabIconSize = tabV2.icon.actualSize(iconSize,
                                                          (tabV2.state & State_Enabled) ? QIcon::Normal
                                                          : QIcon::Disabled);
                int offset = 4;
                if (tabV2.leftButtonSize.isEmpty())
                    offset += 2;

				QRect iconRect = QRect(tr.left() + offset, tr.center().y() - tabIconSize.height() / 2,
                            tabIconSize.width(), tabIconSize .height());
                if (!verticalTabs)
                    iconRect = visualRect(opt->direction, opt->rect, iconRect);
				if (tabV2.shape == QTabBar::TriangularWest)
				{
					tr.setTop(40);
					tr.setBottom(60);
					tr.setLeft(2);
                                        tr.setRight(88);
					return (tr);
				}
				else if (tabV2.shape == QTabBar::TriangularNorth)
				{
					tr.setTop(9);
					tr.setBottom(19);
					tr.setLeft(tr.left() + 32);
					tr.setRight(tr.left() + 118);
					return (tr);
				}
            }
			else if (tabV2.shape == QTabBar::TriangularWest)
			{
				tr.setTop(5);
				tr.setBottom(60);
				tr.setLeft(2);
                                tr.setRight(88);
				return (tr);
			}
			else if (tabV2.shape == QTabBar::TriangularNorth)
			{
				tr.setTop(9);
				tr.setBottom(19);
				tr.setLeft(tr.left() + horizontalShift + 4);
				tr.setRight(tr.left() + 118);
				return (tr);
			}

            // right widget
            if (!tabV2.rightButtonSize.isEmpty()) {
                tr.setRight(tr.right() - 6 - 2 -
                    (verticalTabs ? tabV2.rightButtonSize.height() : tabV2.rightButtonSize.width()));
            }

            if (!verticalTabs)
                tr = visualRect(opt->direction, opt->rect, tr);
            r = tr;
        }
        break;
    default:
        return QPlastiqueStyle::subElementRect(sr, opt, widget);
    }
    return r;
}
