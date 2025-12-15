#include "imageprocessor.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>

ImageProcessor::ImageProcessor(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("影像處理"));

    central = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(central);

    imgWin = new QLabel();
    QPixmap *initPixmap = new QPixmap(300, 200);
    initPixmap->fill(QColor(255, 255, 255));

    imgWin->resize(300, 200);
    imgWin->setScaledContents(true);
    imgWin->setPixmap(*initPixmap);

    mainLayout->addWidget(imgWin);
    setCentralWidget(central);

    createActions();
    createMenus();
    createToolBars();

}

ImageProcessor::~ImageProcessor() {

}
void ImageProcessor::createActions() {
    openFileAction = new QAction(QStringLiteral("開啟檔案&O"), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(QStringLiteral("開啟影像檔案"));
    connect(openFileAction, SIGNAL(triggered()),
            this, SLOT(showOpenFile()));

    exitAction = new QAction(QStringLiteral("結束&E"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(QStringLiteral("退出程式"));
    connect(exitAction, SIGNAL(triggered()),
            this, SLOT(close()));

}
void ImageProcessor::createMenus() {
    fileMenu = menuBar()->addMenu(QStringLiteral("檔案&F"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(exitAction);
}
void ImageProcessor::createToolBars() {
    fileTool = addToolBar("file");
    fileTool->addAction(openFileAction);
}
void ImageProcessor::loadFile(QString filename) {
    qDebug() << QString("file name:%1").arg(filename);
    QByteArray ba = filename.toLatin1();
    printf("FN:%s\n", (char *) ba.data());

    img.load(filename);
    imgWin->setPixmap(QPixmap::fromImage(img));

}
void ImageProcessor::showOpenFile() {
    filename = QFileDialog::getOpenFileName(
        this,
        QStringLiteral("開啟影像"),
        tr("."),
        "bmp(*.bmp);;png(*.png);;jpeg(*.jpg)"
        );

    if (!filename.isEmpty())
    {
        if (img.isNull())
        {
            loadFile(filename);
        }
        else
        {
            ImageProcessor *newIPWin = new ImageProcessor();
            newIPWin->show();
            newIPWin->loadFile(filename);
        }
    }

}
