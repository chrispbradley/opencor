/*******************************************************************************

Copyright The University of Auckland

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*******************************************************************************/

//==============================================================================
// Preferences interface
//==============================================================================

#include "plugin.h"
#include "preferencesinterface.h"

//==============================================================================

#include <QRegularExpression>
#include <QSettings>

//==============================================================================

namespace OpenCOR {

//==============================================================================

extern "C" Q_DECL_EXPORT int preferencesInterfaceVersion()
{
    // Version of the preferences interface

    return 1;
}

//==============================================================================

namespace Preferences {

//==============================================================================

PreferencesWidget::PreferencesWidget(QObject *pPluginInstance, QWidget *pParent) :
    QWidget(pParent)
{
    static const QRegularExpression BeforeRegEx = QRegularExpression("^.*:");
    static const QRegularExpression AfterRegEx = QRegularExpression("Plugin$");

    mSettings = new QSettings();

    mSettings->beginGroup(SettingsPlugins);
    mSettings->beginGroup(QString(pPluginInstance->metaObject()->className()).remove(BeforeRegEx).remove(AfterRegEx));
    mSettings->beginGroup("Preferences");
}

//==============================================================================

PreferencesWidget::~PreferencesWidget()
{
    // Delete some internal objects

    delete mSettings;
}

//==============================================================================

}   // namespace Preferences
}   // namespace OpenCOR

//==============================================================================
// End of file
//==============================================================================
