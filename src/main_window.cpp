#include "main_window.h"
#include "ui_main_window.h"

#include <cmath>
#include <complex>
#include <iostream>

#include <QString>
#include <boost/format.hpp>

MainWindow::MainWindow(QWidget *parent) :	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->a_input, &QLineEdit::textChanged, this, &MainWindow::update_equation);
	connect(ui->b_input, &QLineEdit::textChanged, this, &MainWindow::update_equation);
	connect(ui->c_input, &QLineEdit::textChanged, this, &MainWindow::update_equation);

	update_equation();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::update_equation()
{
	double a, b, c;
	bool a_ok, b_ok, c_ok;

	auto complex_to_qstring = [](const std::complex<double>& value) -> QString
	{
			const char* REAL_FORMAT    = "%1%";
			const char* COMPLEX_FORMAT = "%1% + %2%i";

			if(value.imag() == 0.0)
			{
				return QString::fromStdString((boost::format(REAL_FORMAT) % value.real()).str());
			}
			else
			{
				return QString::fromStdString((boost::format(COMPLEX_FORMAT) % value.real() % value.imag()).str());
			}
	};

	a = ui->a_input->text().toDouble(&a_ok);
	b = ui->b_input->text().toDouble(&b_ok);
	c = ui->c_input->text().toDouble(&c_ok);

	if(a_ok & b_ok & c_ok)
	{
		std::complex<double> sqrt_func = sqrt(std::complex<double>(b*b - 4*a*c));

		std::complex<double> root1 = (-b + sqrt_func) / (2*a);
		std::complex<double> root2 = (-b - sqrt_func) / (2*a);

		ui->root1_output->setText(complex_to_qstring(root1));
		ui->root2_output->setText(complex_to_qstring(root2));
	}
	else
	{
		ui->root1_output->clear();
		ui->root2_output->clear();
	}
}
