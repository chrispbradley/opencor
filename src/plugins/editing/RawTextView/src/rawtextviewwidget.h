/*******************************************************************************

Copyright (C) The University of Auckland

OpenCOR is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OpenCOR is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*******************************************************************************/

//==============================================================================
// Raw Text view widget
//==============================================================================

#pragma once

//==============================================================================

#include "viewwidget.h"

//==============================================================================

#include <QMap>

//==============================================================================

namespace OpenCOR {

//==============================================================================

namespace EditorWidget {
    class EditorWidget;
}   // namespace EditorWidget

//==============================================================================

namespace RawTextView {

//==============================================================================

class RawTextViewWidget : public Core::ViewWidget
{
    Q_OBJECT

public:
    explicit RawTextViewWidget(QWidget *pParent);

    virtual void loadSettings(QSettings *pSettings);
    virtual void saveSettings(QSettings *pSettings) const;

    virtual void retranslateUi();

    bool contains(const QString &pFileName) const;

    void initialize(const QString &pFileName, const bool &pUpdate = true);
    void finalize(const QString &pFileName);

    void fileReloaded(const QString &pFileName);
    void fileRenamed(const QString &pOldFileName, const QString &pNewFileName);

    EditorWidget::EditorWidget * editorWidget(const QString &pFileName) const;

    virtual QWidget * widget(const QString &pFileName);

    virtual QList<QWidget *> statusBarWidgets() const;

private:
    bool mNeedLoadingSettings;
    QString mSettingsGroup;

    EditorWidget::EditorWidget *mEditor;
    QMap<QString, EditorWidget::EditorWidget *> mEditors;
};

//==============================================================================

}   // namespace RawTextView
}   // namespace OpenCOR

//==============================================================================
// End of file
//==============================================================================
