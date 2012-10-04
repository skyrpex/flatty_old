#include "Application.h"

Application::Application(int argc, char **argv) :
    QApplication(argc, argv)
{
    setOrganizationName("Remacu");
    setApplicationName("Flatty");
    setApplicationVersion("0.0");
}
