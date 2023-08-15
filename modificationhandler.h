#ifndef MODIFICATIONHANDLER_H
#define MODIFICATIONHANDLER_H

#include <QObject>

/*!
 * \brief Класс прослойка для модификации объектов фигур.
 */
class ModificationHandler : public QObject
{
	Q_OBJECT
	Q_DISABLE_COPY_MOVE(ModificationHandler);

public:
	/*!
	 * \brief Удаленный дефолтный деструткор
	 */
	ModificationHandler() = delete;

	/*!
	 * \brief Основной конструктор
	 * \param parent - указатель на родительский класс
	 */
	explicit ModificationHandler(QObject* parent = nullptr);

	/*!
	 * \brief Основной деструктор
	 */
	~ModificationHandler() override;

private:
};

#endif // MODIFICATIONHANDLER_H
