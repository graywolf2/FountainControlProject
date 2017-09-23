#include "mainwindow.h"
#include "ui_mainwindow.h"

// Конструктор.
MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::MainWindow),
		arduino("/dev/ttyUSB0") {
	ui->setupUi(this);

	if (arduino.open(QFile::Text))
		ui->log->setText("Пристрій /dev/ttyUSB0 успішно відкритий.");
	else ui->log->setText("Неможливо відкрити пристрій /dev/ttyUSB0.");
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_turnOnFountain1_clicked() { // Натиснули "Увімкнути фонтан 1".
	if (!arduino.isOpen()) {
		ui->log->setText("Пристрій /dev/ttyUSB0 не відкритий.");
		return;
	}

	arduino.write("turn on fountain 1\n"); // Надсилаємо команду в ардуїно.
	ui->log->setText(arduino.readLine()); // Показали відповідь з ардуїно.
}

void MainWindow::on_turnOffFountain1_clicked() { // Натиснули "Вимкнути фонтан 1".
	if (!arduino.isOpen()) {
		ui->log->setText("Пристрій /dev/ttyUSB0 не відкритий.");
		return;
	}

	arduino.write("turn off fountain 1\n"); // Надсилаємо команду в ардуїно.
	ui->log->setText(arduino.readLine()); // Показали відповідь з ардуїно.
}
