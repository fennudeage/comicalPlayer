#include "mainwindow.h"
#include <QApplication>
#include<QTextCodec>
#include<QIcon>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w=MainWindow::Interface();
    w->show();


/*a.setApplicationName("MusicPlayer");

a.setOrganizationDomain("qt-project.org");
a.setApplicationDisplayName("QtWinExtras Music Player");
*///a.setOrganizationName("QtWinExtras");
a.setWindowIcon(QIcon(":/funny.png"));

return a.exec();
    delete w;


}
