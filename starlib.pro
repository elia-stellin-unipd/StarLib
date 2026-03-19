QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/AbstractArticle.cpp \
    Model/AbstractPublication.cpp \
    Model/Book.cpp \
    Model/Config/Settings.cpp \
    Model/Converter/JsonConverter.cpp \
    Model/Converter/JsonReader.cpp \
    Model/Converter/JsonVisitor.cpp \
    Model/DataMapper/JsonFile.cpp \
    Model/Library.cpp \
    Model/MagazineIssue.cpp \
    Model/MediaRuntime.cpp \
    Model/Movie.cpp \
    Model/Search/Query.cpp \
    Utils/Layout.cpp \
    Utils/Style.cpp \
    View/Dialog/ConfirmDialogBox.cpp \
    View/Dialog/ErrorDialogBox.cpp \
    View/Dialog/NewLibraryDialog.cpp \
    View/FavoriteButton.cpp \
    View/Form/FormGenerator.cpp \
    View/Form/FormValidator.cpp \
    View/Info/Editor/EditInfoBase.cpp \
    View/Info/Editor/EditPageContainer.cpp \
    View/Info/InfoBase.cpp \
    View/Info/InfoPageContainer.cpp \
    View/Info/InfoView.cpp \
    View/Info/NewArticlePage.cpp \
    View/Info/PageContainer.cpp \
    View/Layouts/FlowLayout.cpp \
    View/MainWindow.cpp \
    View/Select/ArticlePreviewBase.cpp \
    View/Select/NewArticleButton.cpp \
    View/Select/ResultGridWidget.cpp \
    View/Select/SearchBarWidget.cpp \
    View/Select/SelectView.cpp \
    Visitors/ArticleEditInfoWidget.cpp \
    Visitors/ArticleInfoWidget.cpp \
    Visitors/ArticlePreviewWidget.cpp \
    Visitors/EditArticleVisitor.cpp \
    Visitors/QueryMatchVisitor.cpp \
    main.cpp

HEADERS += \
    Model/AbstractArticle.h \
    Model/AbstractPublication.h \
    Model/Book.h \
    Model/Config/Settings.h \
    Model/Converter/JsonConverter.h \
    Model/Converter/JsonReader.h \
    Model/Converter/JsonVisitor.h \
    Model/DataMapper/JsonFile.h \
    Model/Library.h \
    Model/MagazineIssue.h \
    Model/MediaRuntime.h \
    Model/Movie.h \
    Model/Search/Query.h \
    Utils/Global.h \
    Utils/Layout.h \
    Utils/Style.h \
    View/Dialog/ConfirmDialogBox.h \
    View/Dialog/ErrorDialogBox.h \
    View/Dialog/NewLibraryDialog.h \
    View/FavoriteButton.h \
    View/Form/FormGenerator.h \
    View/Form/FormValidator.h \
    View/Info/Editor/EditInfoBase.h \
    View/Info/Editor/EditPageContainer.h \
    View/Info/InfoBase.h \
    View/Info/InfoPageContainer.h \
    View/Info/InfoView.h \
    View/Info/NewArticlePage.h \
    View/Info/PageContainer.h \
    View/Layouts/FlowLayout.h \
    View/MainWindow.h \
    View/Select/ArticlePreviewBase.h \
    View/Select/NewArticleButton.h \
    View/Select/ResultGridWidget.h \
    View/Select/SearchBarWidget.h \
    View/Select/SelectView.h \
    Visitors/ArticleConstVisitor.h \
    Visitors/ArticleEditInfoWidget.h \
    Visitors/ArticleInfoWidget.h \
    Visitors/ArticlePreviewWidget.h \
    Visitors/ArticleVisitor.h \
    Visitors/EditArticleVisitor.h \
    Visitors/QueryMatchVisitor.h

FORMS += \
    View/MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    assets/stylesheet.qss

RESOURCES += \
    resources.qrc
