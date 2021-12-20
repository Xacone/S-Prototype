#include "MainWin.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Win win64;
    win64.show();

    return app.exec();
}
