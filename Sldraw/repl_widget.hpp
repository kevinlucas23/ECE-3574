#ifndef REPL_WIDGET_HPP
#define REPL_WIDGET_HPP

#include <QWidget>
#include <QLineEdit>
#include <QString>
#include <QVector>

class Future {
private:
	QVector<QString> future;
	int now;

public:
	Future() {
		future.push_back(QString());
		now = 0;
	}

	void add(const QString& entry) {
		future.insert(1, entry);
		now = 0;
	}

	bool up() {
		if (now + 1 < future.size()) {
			now++;
			return true;
		}

		return false;
	}

	bool down() {
		if (now - 1 >= 0) {
			now--;
			return true;
		}

		return false;
	}

	QString& present() {
		return future[now];
	}
};

class REPLWidget : public QWidget {
	Q_OBJECT

public:

	REPLWidget(QWidget* parent = nullptr);
	QLineEdit* view;
	Future see;

signals:

	void lineEntered(QString entry);

private slots:

	void changed();

	void keyPressEvent(QKeyEvent* event);
};

#endif