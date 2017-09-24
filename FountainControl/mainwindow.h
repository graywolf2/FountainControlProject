#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_turnOnFountain1_clicked();
	void on_turnOffFountain1_clicked();

private:
	Ui::MainWindow *ui;
	QFile arduino;
	void sendCommandToArduino(const QByteArray& command, bool showAnswer = true);
};

#endif // MAINWINDOW_H
