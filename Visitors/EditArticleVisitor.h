#ifndef EDITARTICLEVISITOR_H
#define EDITARTICLEVISITOR_H

#include <QFormLayout>

#include "Model/AbstractPublication.h"

#include "Visitors/ArticleVisitor.h"

namespace Visitors {
    class EditArticleVisitor: public ArticleVisitor
    {
    private:
        QWidget *form;

        void setupBaseArticle(Model::AbstractArticle&);
        void setupPublication(Model::AbstractPublication&);

    public:
        /// @brief Crea un EditArticleVisitor che modifica un articolo secondo le informazioni
        /// contenute dai widget figli di base_form.
        explicit EditArticleVisitor(QWidget* base_form);
        void visit(Model::Book& book) override;
        void visit(Model::Movie& movie) override;
        void visit(Model::MagazineIssue& magazine) override;
    };
}
#endif // EDITARTICLEVISITOR_H
