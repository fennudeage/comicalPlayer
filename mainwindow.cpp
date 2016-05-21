#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QStandardPaths>
#include<QTextCodec>
#include<QPixmap>
#include<QDesktopServices>
#include<QtWinExtras>
#include<QPainter>
#include<QMatrix>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
ui->setupUi(this);


    initWidget();

    createThumbnailToolbar();
    initvoluminfo();
    creatpixmap();
    creatTranIcon();
    ThumbnailBarenabel();
    creatJumpList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{

}

void MainWindow::on_pushButton_clicked()
{
   int current=playlist->currentIndex();
    if(!playlist->isEmpty()){
        if(playlist->currentIndex()-1>=0){
            playlist->setCurrentIndex(playlist->currentIndex()-1);

         Player->play();
        }
       else if(playlist->currentIndex()-1<0){
            current=0;
            playlist->setCurrentIndex(current);
            Player->play();

        }
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    if(i==0){
         flag=true;
        playlist->setCurrentIndex(0);
        QString songName=ui->listWidget->item(playlist->currentIndex())->text();
                    ui->pushButton_2->setToolTip(QStringLiteral("播放"));
                ui->label_2->setText(QStringLiteral("正在播放: ")+(songName));
                ui->label_2->setAlignment(Qt::AlignCenter);
                ui->pushButton_2->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        Player->play();

        i=1;
}
   else if(Player->state()==QMediaPlayer::PausedState){
          ui->pushButton_2->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        Player->play();
    }
    else{
        ui->pushButton_2->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        ui->pushButton_2->setToolTip(QStringLiteral("暂停"));
        Player->pause();
    }

}



void MainWindow::on_pushButton_3_clicked()
{
     int current=playlist->currentIndex();
    if(!playlist->isEmpty()){
        if(playlist->currentIndex()+1<playlist->mediaCount()){
            playlist->setCurrentIndex(playlist->currentIndex()+1);

         Player->play();

        }
       else if(playlist->currentIndex()+1>=playlist->mediaCount()){
            current=0;
            playlist->setCurrentIndex(current);
            Player->play();

        }
    }


}


void MainWindow::on_pushButton_4_clicked()
{
   if(volum_falg==0){
       tempVolum=ui->verticalSlider->value();
ui->verticalSlider->setValue(0);
Player->setVolume(0);
ui->pushButton_4->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
volum_falg=1;
   }
   else{
       ui->pushButton_4->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
       ui->verticalSlider->setValue(tempVolum);
       Player->setVolume(tempVolum);
       volum_falg=0;
   }
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    QTime playCurrentTime(0,position/60000,position/1000%60);
    ui->label_4->setText(playCurrentTime.toString(tr("mm:ss")));
    Player->setPosition(position);

     mrx.rotate(position*10);
    ui->label->setPixmap(pix.transformed(mrx,Qt::SmoothTransformation));

}

void MainWindow::on_verticalSlider_sliderMoved(int position)
{
Player->setVolume(position);
}


void MainWindow::initWidget(){

    this->setFixedSize(380,460);
    //setStyleSheet("background-color:transparent");
    //this->setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowOpacity(0.7);
   setWindowTitle(QStringLiteral("滑稽播放器"));
    ui->label->setAlignment(Qt::AlignCenter);
ui->pushButton->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
ui->pushButton_2->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
ui->pushButton_3->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
ui->pushButton->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
ui->pushButton_4->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
QtWin::resetExtendedFrame(this);
ui->pushButton->setEnabled(false);
ui->pushButton_2->setEnabled(false);
ui->pushButton_3->setEnabled(false);
ui->pushButton->setToolTip(QStringLiteral("上一首"));
ui->pushButton_2->setToolTip(QStringLiteral("播放"));
ui->pushButton_3->setToolTip(QStringLiteral("下一首"));
ui->pushButton_4->setToolTip(QStringLiteral("音量"));
ui->pushButton->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
ui->pushButton_3->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
ui->pushButton_4->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
ui->pushButton_2->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
Player=new QMediaPlayer(this);
playlist=new QMediaPlaylist(this);
Player->setPlaylist(playlist);


//ui->verticalSlider->setVisible(false);
connect(Player,SIGNAL(durationChanged(qint64)),this,SLOT(finish_Time(qint64)));
connect(Player,SIGNAL(positionChanged(qint64)),this,SLOT(updatePosition(qint64)));
connect(Player,SIGNAL(volumeChanged(int)),this,SLOT(volumrelese(qint64)));
playlist->setPlaybackMode(QMediaPlaylist::Loop);
connect(playlist,SIGNAL(currentIndexChanged(int)),this,SLOT(updateAnnyThing()));
connect(ui->action,SIGNAL(triggered(bool)),this,SLOT(selectmusic()));
connect(ui->action_2,SIGNAL(triggered()),this,SLOT(aboutMessage()));
//connect(ui->label,SIGNAL(clicked()),this,SLOT(gotoGitHub()));
}
void MainWindow::initvoluminfo(){
ui->verticalSlider->setRange(0,100);
ui->verticalSlider->setValue(50);
Player->setVolume(50);
}
void MainWindow::updatePosition(qint64 position){
    QTime playCurrentTime(0,position/60000,position/1000%60);
    ui->label_4->setText(playCurrentTime.toString(tr("mm:ss")));
    ui->horizontalSlider->setValue(position);
    mrx.rotate(abs(position%360/13));
   ui->label->setPixmap(pix.transformed(mrx,Qt::SmoothTransformation));

}

void MainWindow::updateTaskbar(){

}
void MainWindow::updateThumbnailToolBar(){

}
void MainWindow::volumrelese(qint64 position){

Player->setVolume(position);


}
void MainWindow::finish_Time(qint64 position){
    QTime playFinishTime(0,position/60000,position/1000%60);
    ui->label_3->setText(playFinishTime.toString(tr("mm:ss")));
    ui->horizontalSlider->setMaximum(position);

}
void MainWindow::updateAnnyThing(){
QString songName=ui->listWidget->item(playlist->currentIndex())->text();
if(flag){
        ui->label_2->setText(QStringLiteral("正在播放: ")+(songName));
        ui->label_2->setAlignment(Qt::AlignCenter);
}
}
void MainWindow::selectmusic(){
 QStringList fileList=QFileDialog::getOpenFileNames(this,QStringLiteral("打开音乐"),QDir::homePath(),QStringLiteral("音乐(*.mp3)"));
if(fileList.count()>0){
foreach (QString fileItem,fileList) {

        playlist->addMedia(QUrl::fromLocalFile(fileItem));
        QString listItemtext=fileItem.split('/').last();
        QString listItem2=listItemtext.split('.').front();
        ui->listWidget->addItem(listItem2);





}
ui->pushButton->setEnabled(true);
ui->pushButton_2->setEnabled(true);
ui->pushButton_3->setEnabled(true);
playlist->setCurrentIndex(0);

}


}
void MainWindow::aboutMessage(){
    QMessageBox::about(this,QStringLiteral("滑稽播放器"),QStringLiteral("欢迎访问我的Github\n www.github.com/fennudeage\n 作者：李明哲|angry_A\n 设计：李明哲|angry_A"));
 QUrl url(QString("www.github.com/fennudeage"));
 QDesktopServices::openUrl(url);

}



void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    flag=true;
   playlist->setCurrentIndex(index.row());
    Player->play();


}
void MainWindow::createThumbnailToolbar(){
    if(QtWin::isCompositionEnabled()){
    ThumbnailBar =new QWinThumbnailToolBar(this);
    ThumbnailBar->setWindow(windowHandle());
    lastsong=new QWinThumbnailToolButton(ThumbnailBar);

    lastsong->setToolTip("上一曲");
    lastsong->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    lastsong->setDismissOnClick(true);
    connect(lastsong,SIGNAL(clicked()),this,SLOT(on_pushButton_2_clicked()));
            pause= new QWinThumbnailToolButton(ThumbnailBar);
            pause->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            pause->setToolTip("播放");
            connect(pause,SIGNAL(clicked()),this,SLOT(on_pushButton_2_clicked()));
            next=new QWinThumbnailToolButton(ThumbnailBar);
            next->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
            next->setToolTip("下一首");
            connect(next,SIGNAL(clicked()),this,SLOT(on_pushButton_3_clicked()));
            ThumbnailBar->addButton(lastsong);
            ThumbnailBar->addButton(pause);
            ThumbnailBar->addButton(next);
}



}
void MainWindow::createTaskbar(){



}
void MainWindow::creatpixmap(){

    QPainter paint(this);
    paint.drawPixmap(0,0,pix);
    pix.load(":/funny_1.png");
   ui->label->setPixmap(pix);

}
void MainWindow::creatTranIcon(){

    open=new QAction(QStringLiteral("打开音乐"),this);
    TranAbout =new QAction(QStringLiteral("关于"),this);
    random=new QAction(QStringLiteral("随机播放"),this);
    QSystemTrayIcon *icon=new QSystemTrayIcon();
    icon->setToolTip("angry_A!!!!");
    icon->setIcon(QIcon(":/funny.png"));
    addAction(open);
    addAction(TranAbout);
    icon->show();
    M1=new QMenu((QWidget*)QApplication::desktop());

    M1->addAction(open);
    M1->addAction(random);
    M1->addAction(TranAbout);
    icon->setContextMenu(M1);

    connect(open,SIGNAL(triggered(bool)),this,SLOT(selectmusic()));
    connect(TranAbout,SIGNAL(triggered(bool)),this,SLOT(aboutMessage()));
    connect(random,SIGNAL(triggered(bool)),this,SLOT(randomiz()));
}
void MainWindow::mainWindowed(QSystemTrayIcon::ActivationReason reason){
    switch (reason) {

     case QSystemTrayIcon::DoubleClick:

        break;


     }



}
void MainWindow::closeEvent(QCloseEvent *e){
   e->accept();

}
void MainWindow::gotoGitHub(){

   //ui->label_3->setText("");
}
void MainWindow::mousePressEvent(QMouseEvent *e){
    int x=e->x();
    int y=e->y();
    if(e->button()==Qt::LeftButton&&x>=80&&x<=301&&y>=0&&y<=141){

        emit clicked();
    }
}
MainWindow* MainWindow::Interface(){
MainWindow*ret=new MainWindow;
if(ret==NULL){

    delete ret;
    ret=NULL;


}
return ret;
}



void MainWindow::on_horizontalSlider_sliderReleased(int position)
{
Player->setPosition(position);
}

void MainWindow::on_verticalSlider_sliderPressed()
{

}

void MainWindow::on_horizontalSlider_sliderPressed(int position)
{
    Player->setPosition(position);
}
void MainWindow::ThumbnailBarenabel(){
    if(QtWin::isCompositionEnabled()){
        QtWin::extendFrameIntoClientArea(this, -1, -1, -1, -1);
        setAttribute(Qt::WA_TranslucentBackground, true);
        setAttribute(Qt::WA_NoSystemBackground, false);

        setStyleSheet(" { background: transparent; }");
    }
    else {

            QtWin::resetExtendedFrame(this);
            setAttribute(Qt::WA_TranslucentBackground, false);
            setStyleSheet(QString("MusicPlayer { background: %1; }").arg(QtWin::realColorizationColor().name()));



}}
void MainWindow::creatJumpList(){
    QWinJumpList JList;
    JList.recent()->setVisible(true);

}
void MainWindow::randomiz(){
   playlist->Random;


}
