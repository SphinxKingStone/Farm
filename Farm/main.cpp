#include <QApplication>
#include "interface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);;


    Interface * window = new Interface;
    window->show();


    return a.exec();
}

/*
  QString injectorLibPath()
{
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
    // get path of shared library containing the qtInspectorInit entry
    // point. See notes about this in CMakeLists.txt
    return PlatformUtils::binaryPath(reinterpret_cast<void*>(&qtInspectorInit));
#else
    return "lib/QtInspector.dll";
#endif
}
*/
