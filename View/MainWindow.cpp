#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QFrame>
#include <QGraphicsWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLabel>
#include <QMessageBox>
#include <QMimeData>
#include <QScreen>
#include <QScrollArea>
#include <QSplitter>
#include <QStackedLayout>
#include <QStyle>
#include <QWidget>
#include <QWidgetItem>

#include "Dialog/ConfirmDialogBox.h"

#include "Model/Library.h"

#include "Utils/Global.h"
#include "Utils/Style.h"

#include "View/Dialog/ErrorDialogBox.h"
#include "View/Dialog/NewLibraryDialog.h"
#include "View/Info/InfoView.h"
#include "View/Select/SelectView.h"

#include "Visitors/ArticleInfoWidget.h"
#include "Visitors/EditArticleVisitor.h"

using namespace Model;
using namespace DataMapper;
MainWindow::MainWindow(Model::Config::Settings& settings, QWidget *parent)
    : QMainWindow(parent)
    , _settings(settings)
    // _datamapper è inizializzato con costruttore a 0 argomenti
    // _library pure
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setObjectName("main-window");
    setAcceptDrops(true);

    QWidget *stack_container = new QWidget;
    QStackedLayout *main_stack = new QStackedLayout();
    stack_container->setLayout(main_stack);
    setCentralWidget(stack_container);

    // Widget principale
    QSplitter *splitter = new QSplitter();
    _main_widget = splitter;

    SelectView *select_view = new SelectView();
    select_view->setMinimumWidth(200);
    splitter->addWidget(select_view);
    splitter->setStretchFactor(0, 3);
    splitter->setCollapsible(0, false);

    InfoView *info_view = new InfoView();
    info_view->setMinimumWidth(200);
    splitter->addWidget(info_view);
    splitter->setStretchFactor(1, 2);
    splitter->setCollapsible(1, false);

    main_stack->addWidget(splitter);

    // widget per Landing Page
    _landing_page = new QWidget();

    QVBoxLayout *landing_layout = new QVBoxLayout(_landing_page);
    landing_layout->setAlignment(Qt::AlignCenter);

    QLabel *title = new QLabel("<h1>" + Utils::Global::APP_NAME + "</h1>");
    landing_layout->addWidget(title);

    QLabel *label = new QLabel(
        QString("<h2>Carica una libreria:</h2><ul>"
        "<li>Trascina un file JSON valido sulla finestra</li>"
        "<li>Crea un nuova libreria con <b>%1</b> oppure File > %2"
        "<li>Apri una libreria esistente con <b>%3</b> oppure File > %4"
        "</ul>").arg(
            ui->actionNuova_libreria->shortcut().toString(),
            ui->actionNuova_libreria->text().replace("&", ""),
            ui->actionApri_libreria->shortcut().toString(),
            ui->actionApri_libreria->text().replace("&", "")
        )
    );
    landing_layout->addWidget(label);
    main_stack->addWidget(_landing_page);
    main_stack->setCurrentWidget(_landing_page);

    // MainWindow -> SelectView
    connect(
        this, &MainWindow::setSearchBarFocus,
        select_view, &SelectView::setSearchBarFocus
    );

    // Richieste (SelectView -> InfoView)
    connect(
        select_view, &SelectView::requestDeleteArticle,
        info_view, &InfoView::onRequestDeleteArticle
    );
    connect(
        select_view, &SelectView::requestOpenEditor,
        info_view, &InfoView::onRequestOpenEditor
    );
    connect(
        select_view, &SelectView::requestNewArticle,
        info_view, &InfoView::onRequestNewArticle
    );
    connect(
        select_view, &SelectView::requestShowArticle,
        info_view, &InfoView::onRequestShowArticle
    );
    connect(
        select_view, &SelectView::requestUpdateArticle,
        info_view, &InfoView::onRequestUpdateArticle
    );
    // Risultati (InfoView -> SelectView)
    connect(
        info_view, &InfoView::resultOpenEditor,
        select_view, &SelectView::resultOpenEditor
    );
    connect(
        info_view, &InfoView::resultShowArticle,
        select_view, &SelectView::resultShowArticle
    );
    connect(
        info_view, &InfoView::resultUpdateArticle,
        select_view, &SelectView::resultUpdateArticle
    );

    // Richieste (StatusBar -> InfoView)
    connect(
        this, &MainWindow::requestDeleteCurrent,
        info_view, &InfoView::onRequestDeleteCurrent
    );
    connect(
        this, &MainWindow::requestOpenEditorCurrent,
        info_view, &InfoView::onRequestOpenEditorCurrent
    );
    connect(
        this, &MainWindow::requestNewArticle,
        info_view, &InfoView::onRequestNewArticle
    );

    // Richieste (InfoView -> MainWindow)
    connect(
        info_view, &InfoView::requestAddArticle,
        this, &MainWindow::onRequestAddArticle
    );
    connect(
        info_view, &InfoView::requestEditArticle,
        this, &MainWindow::onRequestEditArticle
    );
    connect(
        info_view, &InfoView::requestFavoriteArticle,
        this, &MainWindow::onRequestFavoriteArticle
    );
    // Risultati (MainWindow -> InfoView)
    connect(
        this, &MainWindow::resultAddArticle,
        info_view, &InfoView::onResultAddArticle
    );
    connect(
        this, &MainWindow::resultEditArticle,
        info_view, &InfoView::onResultEditArticle
    );
    connect(
        this, &MainWindow::resultFavoriteArticle,
        info_view, &InfoView::onResultFavoriteArticle
    );
    connect(
        this, &MainWindow::resultLoadLibrary,
        info_view, &InfoView::onResultLoadLibrary
    );

    // Richieste (MainWindow -> InfoView)
    connect(
        this, &MainWindow::requestOpenNewLibrary,
        info_view, &InfoView::onRequestOpenNewLibrary
    );

    // Risultati (InfoView -> MainWindow)
    connect(
        info_view, &InfoView::resultOpenNewLibrary,
        this, &MainWindow::onResultOpenNewLibrary
    );

    // Richieste (SelectView -> MainWindow)
    connect(
        select_view, &SelectView::requestFavoriteArticle,
        this, &MainWindow::onRequestFavoriteArticle
    );
    // Risultati (MainWindow -> SelectView)
    connect(
        this, &MainWindow::resultAddArticle,
        select_view, &SelectView::resultAddArticle
    );
    connect(
        this, &MainWindow::resultDeleteArticle,
        select_view, &SelectView::resultDeleteArticle
    );
    connect(
        this, &MainWindow::resultEditArticle,
        select_view, &SelectView::resultEditArticle
    );
    connect(
        this, &MainWindow::resultFavoriteArticle,
        select_view, &SelectView::resultFavoriteArticle
    );
    connect(
        this, &MainWindow::resultLoadLibrary,
        select_view, &SelectView::resultLoadLibrary
    );


    // Risultati (InfoView -> MainWindow)
    connect(
        info_view, &InfoView::resultDeleteArticle,
        this, &MainWindow::onResultDeleteArticle
    );
    connect(
        info_view, &InfoView::resultEditArticle,
        this, &MainWindow::onResultEditArticle
    );
    connect(
        info_view, &InfoView::resultOpenEditor,
        this, &MainWindow::onResultOpenEditor
    );
    connect(
        info_view, &InfoView::resultShowArticle,
        this, &MainWindow::onResultShowArticle
    );

    using namespace Utils::Style::Icons;

    // Azioni Menu bar (create con QT Designer) ///////////////////////////////////////////////////

    // Sezione Media //////
    ui->actionRimuovi->setIcon(QIcon(TRASH));
    connect(
        ui->actionRimuovi, &QAction::triggered,
        this, &MainWindow::requestDeleteCurrent
    );

    ui->actionAggiungi->setIcon(QIcon(PLUS_SOLID));
    connect(
        ui->actionAggiungi, &QAction::triggered,
        this, &MainWindow::requestNewArticle
    );

    ui->actionModifica->setIcon(QIcon(EDIT_WHITE));
    connect(
        ui->actionModifica, &QAction::triggered,
        this, &MainWindow::requestOpenEditorCurrent
    );

    ui->actionPreferiti->setIcon(QIcon(FAVORITE_WHITE));
    connect(
        ui->actionPreferiti, &QAction::triggered,
        [=]{ onRequestFavoriteArticle(info_view->getShownArticle()); }
    );

    // Sezione File //////
    ui->actionApri_libreria->setIcon(QIcon(Utils::Style::Icons::FILE));
    connect(
        ui->actionApri_libreria, &QAction::triggered,
        [=] { emit requestOpenNewLibrary(std::nullopt); }
    );

    ui->actionModifica_libreria->setIcon(QIcon(FILE_EDIT));
    connect(
        ui->actionModifica_libreria, &QAction::triggered,
        [=] { editLibraryInfo(); }
    );

    ui->actionNuova_libreria->setIcon(QIcon(FILE_NEW));
    connect(
        ui->actionNuova_libreria, &QAction::triggered,
        [=] { createNewLibrary(); }
    );

    connect(
        ui->action_Ricarica_libreria, &QAction::triggered,
        [=] { loadLibrary(_datamapper.getPath()); }
    );

    ui->actionSalva->setIcon(QIcon(FLOPPY_DISK));
    connect(
        ui->actionSalva, &QAction::triggered,
        this, &MainWindow::onRequestSave
    );

    // Sezione Edit //////
    connect(
        ui->actionRicerca, &QAction::triggered,
        [=] {
            emit setSearchBarFocus();
        }
    );

    ui->action_Salvataggio_automatico->setChecked(_settings.getAutosave());
    connect(
        ui->action_Salvataggio_automatico, &QAction::toggled,
        this, &MainWindow::setAutosave
    );

    // Sezione About //////
    connect(
        ui->actionAbout, &QAction::triggered,
        [=] {
            using namespace Utils::Style::Icons;
            using namespace Utils::Global;
            QMessageBox msgBox(
                QMessageBox::NoIcon, "About",
                QString("<b>%1 %2</b><br>"
                        "<b>Autore</b>: %3 (mat. 2101084)<br><br>"
                        "Università di Padova<br>"
                        "Laurea Triennale in Informatica<br>"
                        "Corso di Programmazione a Oggetti 2024-2025").arg(APP_NAME, VERSION, AUTHOR)
            );
            msgBox.setIconPixmap(QIcon(FAVORITE_ON).pixmap(20));
            msgBox.exec();
        }
    );

    // Carica dati delle impostazioni
    setAutosave(_settings.getAutosave());

    const QString& last_opened = _settings.getLastOpened();
    if (!last_opened.isEmpty()) {
        loadLibrary(last_opened);
    }
}

// Funzioni relative a libreria /////////////////////////////////////////////////////////////////////////////////////////////////
Library& MainWindow::getLibrary() {
    return _library;
}

void MainWindow::loadLibrary(const QString& path) {
    QStringList warning_list;

    QString old_path = _datamapper.getPath();
    // Impostazioni
    _datamapper.setPath(path);
    _settings.setLastOpened(path);

    try {
        warning_list = _datamapper.load(_library);
    }
    catch (JsonFile::FileError& e) {
        _settings.setLastOpened("");
        ErrorDialogBox error(e);
        error.exec();
        return;
    }

    emit resultLoadLibrary(_library);

    if (!warning_list.isEmpty() && path != old_path) {
        qsizetype count = warning_list.count();
        QString warning = (
            count == 1?
                QString("È stato rilevato 1 articolo corrotto nel file della libreria.")
                       : QString("Sono stati rilevati %1 articoli corrotti nel file della libreria.").arg(count)
            );

        ErrorDialogBox(warning + "\n" + warning_list.join("\n")).exec();
    }

    updateIcons();
    updateWindowTitle();

    qobject_cast<QStackedLayout*>(centralWidget()->layout())->setCurrentWidget(_main_widget);

    // Status bar
    statusMessage(
        (path == old_path? "Ricaricata" : "Caricata")
        + QString(" libreria \"%1\" con %2 elementi da %3")
            .arg(_library.getName(), QString::number(_library.getCount()), path)
    );
}

// Icona salvataggio
void MainWindow::updateIcons() {
    using namespace Utils::Style::Icons;

    bool is_loaded = _datamapper.isLoaded();
    bool disabled = _datamapper.isAutosave() || !_datamapper.hasUnsavedChanges() || !is_loaded;
    ui->actionSalva->setDisabled(disabled);
    ui->actionSalva->setIcon(disabled? QIcon(FLOPPY_DISK_GRAY) : QIcon(FLOPPY_DISK));

    ui->actionModifica_libreria->setDisabled(!is_loaded);
    ui->actionModifica_libreria->setIcon(is_loaded? QIcon(FILE_EDIT): QIcon(FILE_EDIT_GRAY));

    ui->action_Ricarica_libreria->setDisabled(!is_loaded);
}

// Titolo Finestra
void MainWindow::updateWindowTitle() {
    using namespace Utils::Global;
    setWindowTitle(
        QString("%1 - %2").arg(_library.getName(), APP_NAME)
    );
}
void MainWindow::updateWindowTitle(QWeakPointer<AbstractArticle> article) {
    if (article.isNull()) { return; }

    using namespace Utils::Global;

    setWindowTitle(QString("%1 - %2 - %3").arg(
           article.toStrongRef()->getTitle(),
            _library.getName(),
            APP_NAME
        )
    );
}

void MainWindow::statusMessage(const QString& message) {
    ui->statusbar->showMessage(message, 10000);
}

void MainWindow::editLibraryInfo() {
    QInputDialog input_dialog;
    input_dialog.setStyleSheet("* { background: #282828; } QLineEdit { background: #121212; }");
    input_dialog.setInputMode(QInputDialog::TextInput);
    input_dialog.setLabelText("Nome libreria:");
    input_dialog.setTextValue(_library.getName());
    input_dialog.exec();

    QString new_name(input_dialog.textValue());

    if (new_name == _library.getName()) { return; }

    _library.setName(new_name);
    _datamapper.setLibraryName(new_name);
    updateWindowTitle();
}

void MainWindow::createNewLibrary() {

    if (_datamapper.hasUnsavedChanges()) {
        ConfirmDialogBox confirm("Ci sono delle modifiche non salvate. Sei sicuro di voler procedere?", QMessageBox::Warning);

        if (!confirm.ask()) { return; }
    }

    NewLibraryDialog dialog = NewLibraryDialog();
    dialog.exec();

    if (dialog.result() == QDialog::Rejected) {
        return;
    }

    QString name = dialog.findChild<QLineEdit*>("new_library_name")->text();
    QString filename = dialog.findChild<QLineEdit*>("new_library_filename")->text();
    QString folder = dialog.findChild<QLineEdit*>("new_library_folder")->text();

    QDir dir(folder);
    QString library_path = dir.absoluteFilePath(filename);

    _datamapper.unload();
    _datamapper.setPath(library_path);
    _datamapper.setLibraryName(name);
    _datamapper.save();

    loadLibrary(library_path);
    emit onRequestSave(); // salva subito la libreria
    statusMessage(
        QString("Creata libreria \"%1\" (%2) con successo").arg(
            _library.getName(), _datamapper.getPath()
        )
    );
}

MainWindow::~MainWindow(){ delete ui; }

// EVENTI /////////////////////////////////////////////////////////////////////////////////
void MainWindow::closeEvent(QCloseEvent *event) {
    if (!_datamapper.hasUnsavedChanges()) return;

    ConfirmDialogBox confirm(
        "Vi sono delle modifiche non salvate. Sei sicuro di voler uscire?",
        QMessageBox::Warning);

    if (!confirm.ask()) {
        event->ignore();
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();
    if (!mimeData->hasUrls()) {
        event->ignore();
        return;
    }

    // Apri solamente il primo file della lista
    emit requestOpenNewLibrary(mimeData->urls().at(0).toLocalFile());
}


// RICHIESTE ///////////////////////////////////////////////////////////////////////
void MainWindow::setAutosave(bool state) {
    statusMessage(QString("%1 il salvataggio automatico").arg(
        state? "Attivato": "Disattivato"
    ));

    _datamapper.setAutosave(state);
    _settings.setAutosave(state);
    updateIcons();
}

void MainWindow::onRequestAddArticle(AbstractArticle *article) {
    if (!article) { return; }

    QWeakPointer<AbstractArticle> weak_ptr = _library.addArticle(article);

    try {
        _datamapper.addArticle(*article);
    }
    catch (const JsonFile::FileError& e) {
        statusMessage(QString("Impossibile salvare su disco").arg(e.what()));
        return;
    }

    updateIcons();
    emit resultAddArticle(weak_ptr);
    onResultShowArticle(weak_ptr);
    statusMessage("Articolo aggiunto con successo");
}

void MainWindow::onRequestEditArticle(
    QWeakPointer<Model::AbstractArticle> article, QPointer<EditInfoBase> form
) {
    if (article.isNull()) {
        return;
    }
    if (form.isNull()) {
        return;
    }

    QSharedPointer<AbstractArticle> shared(article.toStrongRef());
    Visitors::EditArticleVisitor visitor(form);
    shared->accept(&visitor);

    try {
        _datamapper.updateArticle(*shared.get());
    }
    catch (const JsonFile::FileError& e) {
        statusMessage(QString("Impossibile salvare su disco").arg(e.what()));
        return;
    }

    updateIcons();
    emit resultEditArticle(article);
    updateWindowTitle(article);
    statusMessage("Modifica avvenuta con successo");
}

void MainWindow::onRequestFavoriteArticle(QWeakPointer<Model::AbstractArticle> article) {
    if (article.isNull()) {
        return;
    }

    QSharedPointer<AbstractArticle> shared = article.toStrongRef();
    bool new_state = !shared->isFavorite();
    shared->setFavorite(new_state);

    try {
        _datamapper.updateArticle(*shared.get());
    }
    catch (const JsonFile::FileError& e) {
        statusMessage(QString("Impossibile salvare su disco").arg(e.what()));
        return;
    }

    updateIcons();
    emit resultFavoriteArticle(article);

    statusMessage(
        QString(new_state? "%1 aggiunto ai preferiti" : "%1 rimosso dai preferiti").arg(
            shared->getFullName()
        )
    );
}

void MainWindow::onRequestSave() {
    try {
        _datamapper.save();
    }
    catch (const JsonFile::FileError& error) {
        ErrorDialogBox(error).exec();
    }

    updateIcons();
    statusMessage("Modifiche salvate con successo");
}

// RISULTATI //////////////////////////////////////////////////////////////////////////
void MainWindow::onResultDeleteArticle(QWeakPointer<AbstractArticle> article) {
    if (!article) {
        return;
    }

    const QString& article_name = article.toStrongRef()->getFullName();
    AbstractArticle *raw_article_ptr = article.toStrongRef().get();

    try {
        _datamapper.deleteArticle(*article.toStrongRef().get());
    }
    catch (const JsonFile::FileError& e) {
        statusMessage(QString("Impossibile salvare su disco").arg(e.what()));
        return;
    }

    updateIcons();
    _library.deleteArticle(article);

    // NOTA: Inviare delete di AbstractArticle* invece che di WeakPointer, poiché nella parte
    // della GUI di select, Model::AbstractArticle* si usa solo come valore dentro la lookup_table
    emit resultDeleteArticle(raw_article_ptr);

    statusMessage(
        QString("Eliminato %1 con successo").arg(article_name)
    );
}

void MainWindow::onResultEditArticle(QWeakPointer<Model::AbstractArticle> article) {
    if (article.isNull()) {
        return;
    }

    statusMessage(
        QString("Modificato %1 con successo").arg(
            article.toStrongRef()->getFullName()
        )
    );
}


void MainWindow::onResultShowArticle(QWeakPointer<AbstractArticle> article) {
    if (!article) {
        return;
    }

    statusMessage(
        QString("Mostrato %1").arg(
            article.toStrongRef()->getFullName()
        )
    );
    updateWindowTitle(article);
}

void MainWindow::onResultOpenEditor(QWeakPointer<Model::AbstractArticle> article) {
    statusMessage(
        QString("Aperto editor per %1").arg(article.toStrongRef()->getFullName())
    );
}

void MainWindow::onResultOpenNewLibrary(std::optional<const QString> path) {
    if (_datamapper.hasUnsavedChanges()) {
        ConfirmDialogBox confirm("Vi sono delle modifiche non salvate. Vuoi salvare prima di cambiare libreria?");

        if (confirm.ask()) {
            try {
                _datamapper.save();
            }
            catch (const JsonFile::FileError& error) {
                ErrorDialogBox(error).exec();
            }
        }
    }

    if (path != std::nullopt) {
        loadLibrary(path.value());
        return;
    }

    QFileDialog file_dialog(
        this, "Apri nuova libreria",
        QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).at(0),
        "File JSON (*.json)");
    file_dialog.setFileMode(QFileDialog::ExistingFile);
    file_dialog.setViewMode(QFileDialog::Detail);
    file_dialog.exec();

    QStringList selected_files(file_dialog.selectedFiles());
    if (selected_files.isEmpty()) { return; }

    QString new_path = selected_files.at(0);
    if (new_path == _datamapper.getPath()) { return; }

    loadLibrary(new_path);
}
