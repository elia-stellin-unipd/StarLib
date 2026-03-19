#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <optional>

#include <QMainWindow>
#include <QPointer>

#include "Model/Config/Settings.h"
#include "Model/DataMapper/JsonFile.h"
#include "Model/Library.h"

#include "View/Info/Editor/EditInfoBase.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QWidget *_main_widget;
    QWidget *_landing_page;
    QWidget *_library_creation_form;

    Model::Config::Settings& _settings;
    Model::DataMapper::JsonFile _datamapper;

    /// @brief La libreria caricata in questo momento
    Model::Library _library;
    Ui::MainWindow *ui;

    void updateIcons();
    void statusMessage(const QString& message);

protected:
    // Eventi
    void closeEvent(QCloseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

public:
    MainWindow(Model::Config::Settings& settings, QWidget *parent = nullptr);
    ~MainWindow();

    // Funzioni per libreria
    Model::Library& getLibrary();
    void loadLibrary(const QString& path);

    // Funzioni per finestra
    void updateWindowTitle();
    void updateWindowTitle(QWeakPointer<Model::AbstractArticle> article);

    // Altre azioni
    void createNewLibrary();
    void editLibraryInfo();

signals:
    void setSearchBarFocus();

    // Richieste ///
    void requestDeleteCurrent();
    void requestOpenEditorCurrent();
    void requestNewArticle();
    void requestOpenNewLibrary(std::optional<const QString>);

    // Risultati ///
    void resultAddArticle(QWeakPointer<Model::AbstractArticle>);  // -> InfoView, SelectView
    // NOTA: necessario raw pointer
    void resultDeleteArticle(Model::AbstractArticle*);  // -> SelectView
    void resultEditArticle(QWeakPointer<Model::AbstractArticle>);
    void resultFavoriteArticle(QWeakPointer<Model::AbstractArticle>);
    void resultLoadLibrary(Model::Library&);

public slots:
    void setAutosave(bool state);

    // Richieste
    void onRequestAddArticle(Model::AbstractArticle*); // <- InfoView
    void onRequestEditArticle(QWeakPointer<Model::AbstractArticle>, QPointer<EditInfoBase>);
    void onRequestFavoriteArticle(QWeakPointer<Model::AbstractArticle>);
    void onRequestSave();

    // Risultati (perché ricevuto conferma da InfoView)
    void onResultDeleteArticle(QWeakPointer<Model::AbstractArticle>);
    void onResultEditArticle(QWeakPointer<Model::AbstractArticle>);
    void onResultOpenEditor(QWeakPointer<Model::AbstractArticle>);
    void onResultShowArticle(QWeakPointer<Model::AbstractArticle>);
    void onResultOpenNewLibrary(std::optional<const QString>);
};
#endif // MAINWINDOW_H
