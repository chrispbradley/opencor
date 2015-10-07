/*******************************************************************************

Licensed to the OpenCOR team under one or more contributor license agreements.
See the NOTICE.txt file distributed with this work for additional information
regarding copyright ownership. The OpenCOR team licenses this file to you under
the Apache License, Version 2.0 (the "License"); you may not use this file
except in compliance with the License. You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.

*******************************************************************************/

//==============================================================================
// COMBINESupport plugin
//==============================================================================

#include "combinesupportplugin.h"

//==============================================================================

namespace OpenCOR {
namespace COMBINESupport {

//==============================================================================

PLUGININFO_FUNC COMBINESupportPluginInfo()
{
    Descriptions descriptions;

    descriptions.insert("en", QString::fromUtf8("a plugin to support <a href=\"http://co.mbine.org/\">COMBINE</a>."));
    descriptions.insert("fr", QString::fromUtf8("une extension pour supporter <a href=\"http://co.mbine.org/\">COMBINE</a>."));

    return new PluginInfo("Support", false, false,
                          QStringList() << "ZIPSupport",
                          descriptions);
}

//==============================================================================

COMBINESupportPlugin::COMBINESupportPlugin()
{
    // The file types that we support
    // Note: they will get deleted by FileTypeInterface...

    mFileTypes = FileTypes() << new FileType(qobject_cast<FileTypeInterface *>(this),
                                             CombineMimeType, CombineFileExtension);
}

//==============================================================================
// File interface
//==============================================================================

FileTypes COMBINESupportPlugin::fileTypes() const
{
    // Return the file types that we support

    return mFileTypes;
}

//==============================================================================

QString COMBINESupportPlugin::fileTypeDescription(const QString &pMimeType) const
{
    // Return the description for the requested MIME type, that is as long as it
    // is for the MIME type that we support

    if (!pMimeType.compare(CombineMimeType)) {
        return tr("COMBINE Archive");
    } else {
        // Not a MIME type that we can recognise

        return QString();
    }
}

//==============================================================================
// I18n interface
//==============================================================================

void COMBINESupportPlugin::retranslateUi()
{
    // We don't handle this interface...
    // Note: even though we don't handle this interface, we still want to
    //       support it since some other aspects of our plugin are
    //       multilingual...
}

//==============================================================================

}   // namespace COMBINESupport
}   // namespace OpenCOR

//==============================================================================
// End of file
//==============================================================================