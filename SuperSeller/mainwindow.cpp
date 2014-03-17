#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Super Buyer/Seller");
    QMenu *mainMenu;
    QAction *addPlotAction;
    QAction *addhistogramAction;
    QMenu *helpMenu;
    QAction *aboutAction;
    QAction *aboutQtAction;

    addPlotAction = new QAction(tr("Add &plot"), this);
    addPlotAction->setShortcut(QKeySequence(tr("Ctrl+P")));
    connect(addPlotAction, SIGNAL(triggered()), this, SLOT(addPlot()));

    addhistogramAction = new QAction(tr("Add &histogram"), this);
    addhistogramAction->setShortcut(QKeySequence(tr("Ctrl+P")));
    connect(addhistogramAction, SIGNAL(triggered()), this, SLOT(addhistogram()));

    aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    mainMenu = menuBar()->addMenu(tr("&Main"));
    mainMenu->addAction(addPlotAction);
    mainMenu->addAction(addhistogramAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);
    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),
            this, SLOT(updateMenus()));
    windowMapper = new QSignalMapper(this);
    connect(windowMapper, SIGNAL(mapped(QWidget*)),
            this, SLOT(setActiveSubWindow(QWidget*)));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Super Buyer/Seller"),
            tr("<h2>Version 0.1</h2>"
               "<p>Plots and histograms of several bying/selling procedures."
               "<p>Copyright &copy; 2014 RomanAndreev and Co"));
}
void MainWindow::addPlot()
{

}

void MainWindow::addHistogram()
{

}
MainWindow::~MainWindow()
{

}
