#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class Test;
QT_END_NAMESPACE

class CentralWidget : public QWidget
{
	Q_OBJECT
public:
	/*!
	 * \brief Основной конструктор
	 * \param parent - указатель на родительский класс
	 */
	explicit CentralWidget(QWidget* parent = nullptr);

signals:
};

#endif // CENTRALWIDGET_H
