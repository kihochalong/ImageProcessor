#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QToolBar>
#include <QAction>

class ImageProcessor : public QMainWindow
{
    Q_OBJECT

public:
    ImageProcessor(QWidget *parent = nullptr);
    ~ImageProcessor();

    void createActions();
    void createMenus();
    void createToolBars();
    void loadFile(QString filename);

private slots:
    void showOpenFile();
    void getZoomOut();
    void getZoomIn();

private:
    QWidget  *central;
    QMenu    *fileMenu;
    QToolBar *fileTool;
    QImage   img;
    QString  filename;
    QLabel  *imgWin;
    QAction *openFileAction;
    QAction *exitAction;
    QAction *zoomOut;
    QAction *zoomIn;
};

#endif // IMAGEPROCESSOR_H
