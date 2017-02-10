#pragma once

#include <QMainWindow>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:

		/**
		 * Default Constructor
		 *
		 * @param parent parent widget who will act as the parent for this widget
		 */
		explicit MainWindow(QWidget *parent = nullptr);

		/**
		 * Deconstructor
		 */
		~MainWindow();

	private slots:

		/**
		 * Signal method which will be called on every time the user changes the value
		 * of the coefficients.
		 *
		 * The method will use the quadratic equation below to solve for the roots:
		 *
		 * \f[
		 *
		 *   x = \frac{-b \pm \sqrt{b^2 - 4ac}} {2a}
		 *
		 * \f]
		 */
		void update_equation();

	private:
		Ui::MainWindow *ui;
};