#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QButtonGroup;
class QToolButton;
class QAbstractButton;
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

	/*!
	 * \brief Вернуть указатели на список кнопок для тулбара
	 * \return
	 */
	QList<QAbstractButton*> buttons() const;

private:
	/*!
	 * \brief Создать и настроить кнопки ля ТулБара
	 */
	void createToolBarButtons();

	/*!
	 * \brief Создать новую кнопку для тулбара
	 * \param icon - путь до иконки для кнопки
	 * \param tipText - текст подсказки
	 * \return указатель на кнопку
	 */
	QToolButton* createButton(const QString& iconPath, const QString& tipText);

private:
	/*!
	 * \brief Указаетль на основную группу кнопок
	 */
	QButtonGroup* m_toolBarButtonGroup;
};

#endif // CENTRALWIDGET_H
