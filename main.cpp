#include "View/MainWindow.h"

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QJsonDocument>
#include <QStandardPaths>

#include "Model/Config/Settings.h"

#include "Utils/Style.h"
#include "Utils/Global.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Nome app
    app.setApplicationDisplayName(Utils::Global::APP_NAME);
    app.setApplicationName(Utils::Global::APP_NAME);
    app.setApplicationVersion(Utils::Global::VERSION);

    // Carica stylesheet
    app.setStyleSheet(Utils::Style::load(":/assets/style/main.qss"));

    // Icona
    app.setWindowIcon(QIcon(":/assets/icons/app-icon.png"));

    // Carica impostazioni
    Model::Config::Settings settings;
    settings.init();

    // Finestra principale
    MainWindow main_window(settings);
    main_window.show();

    return app.exec();
}
