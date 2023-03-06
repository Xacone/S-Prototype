#include "MainWin.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPixmap pix("C:/Sproto_V3_UTILS/sproto-splash.png");
    QSplashScreen splash(pix);

    splash.show();
    app.processEvents();

    Win win64;
    win64.show();

    //splash.finish(&win64);
    return app.exec();
}
