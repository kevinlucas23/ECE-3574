#ifndef QT_INTERPRETER_HPP
#define QT_INTERPRETER_HPP

#include <string>

#include <QObject>
#include <QString>
#include <QGraphicsItem>

#include "interpreter.hpp"

class QtInterpreter : public QObject, private Interpreter {
	Q_OBJECT

public:

	QtInterpreter(QObject* parent = nullptr);
	void preload(std::string filename);
	void notready();

signals:

	void drawGraphic(QGraphicsItem* item);

	void info(QString message);

	void error(QString message);

	void cleari();

	void clearing();

public slots:

	void parseAndEvaluate(QString entry);

protected:
	void draw();
};

#endif