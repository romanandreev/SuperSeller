#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QMessageBox>
#include <QComboBox>
class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void about();
    void addPlot();
    void addHistogram();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QMdiArea *mdiArea;
    QSignalMapper *windowMapper;

};

#endif // MAINWINDOW_H
