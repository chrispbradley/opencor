//==============================================================================
// Internationalisation interface
//==============================================================================

#ifndef I18NINTERFACE_H
#define I18NINTERFACE_H

//==============================================================================

#include "interface.h"

//==============================================================================

#include <QTranslator>

//==============================================================================

namespace OpenCOR {

//==============================================================================

class I18nInterface : Interface
{
    friend class MainWindow;

public:
    void setLocale(const QString &pLocale);
    void setI18nPluginName(const QString &pI18nPluginName);

protected:
    virtual void retranslateUi();

private:
    QString mI18nPluginName;

    QTranslator mTranslator;
};

//==============================================================================

}   // namespace OpenCOR

//==============================================================================

Q_DECLARE_INTERFACE(OpenCOR::I18nInterface, "OpenCOR.I18nInterface")

//==============================================================================

#endif

//==============================================================================
// End of file
//==============================================================================
