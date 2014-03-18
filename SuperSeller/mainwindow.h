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
#include <QtWidgets>
#include "mdichild.h"
#include "plotchild.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();
private slots:
    void about();
    void addPlot();
    void addHistogram();
    void setActiveSubWindow(QWidget *window);
    void updateWindowMenu();

private:
    MdiChild *activeMdiChild();
    QMenu *windowMenu;
    QAction *closeAct;
    QAction *closeAllAct;
    QAction *tileAct;
    QAction *cascadeAct;
    QAction *nextAct;
    QAction *previousAct;
    QAction *separatorAct;
    QMdiArea *mdiArea;    
    QSignalMapper *windowMapper;    

};

#endif // MAINWINDOW_H
