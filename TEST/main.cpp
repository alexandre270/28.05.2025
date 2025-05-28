#include <QApplication>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    qInstallMessageHandler([](QtMsgType /*type*/, const QMessageLogContext &, const QString &msg) {
        fprintf(stderr, "%s\n", msg.toUtf8().constData());
    });

    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}
