//==============================================================================
// RawView plugin
//==============================================================================

#include "rawviewplugin.h"
#include "rawviewwidget.h"

//==============================================================================

#include <QMainWindow>

//==============================================================================

namespace OpenCOR {
namespace RawView {

//==============================================================================

PLUGININFO_FUNC RawViewPluginInfo()
{
    Descriptions descriptions;

    descriptions.insert("en", "A plugin to edit files using a text editor");
    descriptions.insert("fr", "Une extension pour �diter des fichiers � l'aide d'un �diteur de texte");

    return new PluginInfo(PluginInfo::V001,
                          PluginInfo::Gui,
                          PluginInfo::Editing,
                          true,
                          QStringList() << "CoreEditing" << "QScintillaSupport",
                          descriptions);
}

//==============================================================================

Q_EXPORT_PLUGIN2(RawView, RawViewPlugin)

//==============================================================================

RawViewPlugin::RawViewPlugin()
{
    // Set our settings

    mGuiSettings->setView(GuiViewSettings::Editing);
}

//==============================================================================

QWidget * RawViewPlugin::newViewWidget(const QString &pFileName)
{
    // Create and return a raw view widget

    return new RawViewWidget(mMainWindow, pFileName);
}

//==============================================================================

QString RawViewPlugin::viewName()
{
    // Return our raw view's name

    return tr("Raw");
}

//==============================================================================

}   // namespace RawView
}   // namespace OpenCOR

//==============================================================================
// End of file
//==============================================================================
