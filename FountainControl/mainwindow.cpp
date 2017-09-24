#include <QTimer>
#include "mainwindow.h"
#include "ui_mainwindow.h"

// Конструктор.
MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::MainWindow),
		arduino("/dev/ttyUSB0") {
	ui->setupUi(this);


	if (arduino.open(QFile::ReadWrite | QFile::Text | QIODevice::Unbuffered)) {
		ui->log->setText("Пристрій /dev/ttyUSB0 успішно відкритий.");

		QTimer::singleShot(3000, [this]() {
			sendCommandToArduino("get state", false);
			QTimer::singleShot(500, [this]() {
				ui->turnOnFountain1->setEnabled(true);
				ui->turnOffFountain1->setEnabled(true);
				QByteArray state = arduino.readLine();

				if (state.contains("fountain 1: on"))
					ui->state->setText("Фонтан 1 увімкнутий.");
				else if (state.contains("fountain 1: off"))
					ui->state->setText("Фонтан 1 вимкнутий.");
				else ui->state->setText("Стан фонтанів невідомий.");
			});
		});

	} else ui->log->setText("Неможливо відкрити пристрій /dev/ttyUSB0.\n" +
						  arduino.errorString());
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::sendCommandToArduino(const QByteArray& command, bool showAnswer) {
	if (!arduino.isOpen()) {
		ui->log->setText("Пристрій /dev/ttyUSB0 не відкритий.");
		return;
	}

	arduino.write(command + "\n");
	if (showAnswer) {
		ui->turnOnFountain1->setEnabled(false);
		ui->turnOffFountain1->setEnabled(false);
		ui->log->setText("");
		QTimer::singleShot(500, [this]() {
			ui->turnOnFountain1->setEnabled(true);
			ui->turnOffFountain1->setEnabled(true);
			ui->log->setText(arduino.readLine()); // Показали відповідь з ардуїно.
		});
	}
} // sendCommandToArduino

void MainWindow::on_turnOnFountain1_clicked() { // Натиснули "Увімкнути фонтан 1".
	sendCommandToArduino("turn on fountain 1");
	ui->state->setText("Фонтан 1 увімкнутий.");
}

void MainWindow::on_turnOffFountain1_clicked() { // Натиснули "Вимкнути фонтан 1".
	sendCommandToArduino("turn off fountain 1");
	ui->state->setText("Фонтан 1 вимкнутий.");
}
