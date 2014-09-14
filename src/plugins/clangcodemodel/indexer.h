/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef INDEXER_H
#define INDEXER_H

#include "clang_global.h"
#include "symbol.h"
#include "unit.h"

#include <cpptools/cppmodelmanager.h>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QScopedPointer>
#include <QtCore/QFuture>

namespace ClangCodeModel {

namespace Internal { class ClangSymbolSearcher; }

class IndexerPrivate;

class CLANG_EXPORT Indexer : public QObject
{
    Q_OBJECT

public:
    typedef CppTools::ProjectPart ProjectPart;

public:
    Indexer(QObject *parent = 0);
    ~Indexer();

    void initialize(const QString &storagePath);
    void finalize();

    void regenerate();
    void evaluateFile(const QString &fileName);
    bool isBusy() const;
    void cancel(bool waitForFinished);

    bool addFile(const QString &fileName, ProjectPart::Ptr projectPart);
    QStringList allFiles() const;
    QStringList compilationOptions(const QString &fileName) const;

    QList<Symbol> allFunctions() const;
    QList<Symbol> allClasses() const;
    QList<Symbol> allMethods() const;
    QList<Symbol> allConstructors() const;
    QList<Symbol> allDestructors() const;
    QList<Symbol> functionsFromFile(const QString &fileName) const;
    QList<Symbol> classesFromFile(const QString &fileName) const;
    QList<Symbol> methodsFromFile(const QString &fileName) const;
    QList<Symbol> constructorsFromFile(const QString &fileName) const;
    QList<Symbol> destructorsFromFile(const QString &fileName) const;
    QList<Symbol> allFromFile(const QString &fileName) const;

    void match(Internal::ClangSymbolSearcher *searcher) const;

    void runQuickIndexing(Internal::Unit::Ptr unit, const ProjectPart::Ptr &part);

signals:
    void indexingStarted(QFuture<void> future);
    void indexingFinished();

private:
    friend class IndexerPrivate;
    QScopedPointer<IndexerPrivate> m_d;
};

} // ClangCodeModel

#endif // INDEXER_H
