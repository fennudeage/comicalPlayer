#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTime>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QMessageBox>
#include<QFileDialog>
#include<QMouseEvent>
#include<QAbstractButton>
#include<QWinTaskbarButton>
#include<QWinTaskbarProgress>
#include<QWinThumbnailToolBar>
#include<QWinThumbnailToolButton>
#include<QPixmap>
#include<QSystemTrayIcon>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     explicit MainWindow(QWidget *parent = 0);
static MainWindow* Interface();
int volum_falg=0,tempVolum;

    ~MainWindow();

private slots:
        void randomiz();
    void on_listView_doubleClicked(const QModelIndex &index);
    void selectmusic();
    void aboutMessage();
    void gotoGitHub();
    void updatePosition(qint64 position);
    void finish_Time(qint64 position);

    void volumrelese(qint64 position);
    void updateAnnyThing();
    void on_horizontalSlider_sliderMoved(int position);
    void on_verticalSlider_sliderMoved(int position);
    void updateTaskbar();
    void updateThumbnailToolBar();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_horizontalSlider_sliderReleased(int positon);

    void on_verticalSlider_sliderPressed();

    void on_horizontalSlider_sliderPressed(int positon);

protected:
   void closeEvent(QCloseEvent *e);
  /*  void mouseMoveEvent(QMouseEvent *e);*/
 virtual   void mousePressEvent(QMouseEvent *e);

signals:
void clicked();

private:
    bool flag=false;
    int i=0;
     Ui::MainWindow *ui;
    QMediaPlayer *Player;
    QMediaPlaylist *playlist;
    QWinTaskbarButton* taskbarbutton;
    QWinTaskbarProgress*TaskProgress;
    QWinThumbnailToolBar *ThumbnailBar;
    QWinThumbnailToolButton*lastsong;
    QWinThumbnailToolButton*pause;
    QWinThumbnailToolButton*next;
    QAbstractButton*playButton;
    QMenu*select;
    QPixmap pix;
    QMatrix mrx;
    QAction*open;
    QAction* TranAbout;
    QAction* onceLoop;
    QAction* listLoop;
    QAction*once;
    QAction*random;

    QMenu*M1;
    QMenu*M2;
    void ThumbnailBarenabel();
    void initWidget();
    void initvoluminfo();
    void createTaskbar();
    void createThumbnailToolbar();
    void creatpixmap();
    void creatTranIcon();
void mainWindowed(QSystemTrayIcon::ActivationReason reason);
void showthis();
void creatJumpList();


};

#endif // MAINWINDOW_H
