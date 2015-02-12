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
// CellML file class
//==============================================================================

#ifndef CELLMLFILE_H
#define CELLMLFILE_H

//==============================================================================

#include "cellmlfileissue.h"
#include "cellmlfilerdftriple.h"
#include "cellmlfileruntime.h"
#include "cellmlsupportglobal.h"

//==============================================================================

#include <QDomElement>
#include <QMap>

//==============================================================================

namespace OpenCOR {
namespace CellMLSupport {

//==============================================================================

static const auto Cellml_1_0_Namespace = QStringLiteral("http://www.cellml.org/cellml/1.0#");
static const auto Cellml_1_1_Namespace = QStringLiteral("http://www.cellml.org/cellml/1.1#");
static const auto CmetaIdNamespace     = QStringLiteral("http://www.cellml.org/metadata/1.0#");
static const auto MathmlNamespace      = QStringLiteral("http://www.w3.org/1998/Math/MathML");
static const auto RdfNamespace         = QStringLiteral("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
static const auto XlinkNamespace       = QStringLiteral("http://www.w3.org/1999/xlink");
static const auto XmlNamespace         = QStringLiteral("http://www.w3.org/XML/1998/namespace");

//==============================================================================

class CELLMLSUPPORT_EXPORT CellmlFile
{
public:
    enum Version {
        Cellml_1_0,
        Cellml_1_1
    };

    explicit CellmlFile(const QString &pFileName);
    ~CellmlFile();

    iface::cellml_api::Model * model();

    iface::rdf_api::DataSource * rdfDataSource();

    bool load();
    bool reload();

    bool save(const QString &pNewFileName = QString());

    bool isValid();
    bool isValid(const QString &pFileName, const QString &pFileContents,
                 CellmlFileIssues &pIssues);

    bool isModified() const;
    void setModified(const bool &pModified) const;

    CellmlFileIssues issues() const;

    CellmlFileRuntime * runtime();

    QString fileName() const;
    void setFileName(const QString &pFileName);

    CellmlFileRdfTriples & rdfTriples();
    CellmlFileRdfTriples rdfTriples(iface::cellml_api::CellMLElement *pElement) const;

    CellmlFileRdfTriple * rdfTriple(iface::cellml_api::CellMLElement *pElement,
                                    const CellmlFileRdfTriple::ModelQualifier &pModelQualifier,
                                    const QString &pResource,
                                    const QString &pId) const;
    CellmlFileRdfTriple * rdfTriple(iface::cellml_api::CellMLElement *pElement,
                                    const CellmlFileRdfTriple::BioQualifier &pBioQualifier,
                                    const QString &pResource,
                                    const QString &pId) const;

    CellmlFileRdfTriple * addRdfTriple(iface::cellml_api::CellMLElement *pElement,
                                       const CellmlFileRdfTriple::ModelQualifier &pModelQualifier,
                                       const QString &pResource,
                                       const QString &pId);
    CellmlFileRdfTriple * addRdfTriple(iface::cellml_api::CellMLElement *pElement,
                                       const CellmlFileRdfTriple::BioQualifier &pBioQualifier,
                                       const QString &pResource,
                                       const QString &pId);

    bool removeRdfTriple(iface::cellml_api::CellMLElement *pElement,
                         const CellmlFileRdfTriple::ModelQualifier &pModelQualifier,
                         const QString &pResource, const QString &pId);
    bool removeRdfTriple(iface::cellml_api::CellMLElement *pElement,
                         const CellmlFileRdfTriple::BioQualifier &pBioQualifier,
                         const QString &pResource, const QString &pId);

    QString xmlBase();

    bool exportTo(const QString &pFileName, const Version &pVersion);
    bool exportTo(const QString &pFileName,
                  const QString &pUserDefinedFormatFileName);

private:
    QString mFileName;

    ObjRef<iface::cellml_api::Model> mModel;

    ObjRef<iface::rdf_api::RDFAPIRepresentation> mRdfApiRepresentation;
    ObjRef<iface::rdf_api::DataSource> mRdfDataSource;

    CellmlFileRdfTriples mRdfTriples;

    bool mValid;

    CellmlFileIssues mIssues;

    CellmlFileRuntime *mRuntime;

    bool mLoadingNeeded;
    bool mValidNeeded;
    bool mRuntimeUpdateNeeded;

    QMap<QString, QString> mImportContents;

    QStringList mUsedCmetaIds;

    void reset();

    void retrieveImports(iface::cellml_api::Model *pModel,
                         QList<iface::cellml_api::CellMLImport *> &pImportList,
                         QStringList &pImportXmlBaseList,
                         const QString &pXmlBase);

    bool fullyInstantiateImports(iface::cellml_api::Model *pModel,
                                 CellmlFileIssues &pIssues);

    bool doLoad(const QString &pFileName, const QString &pFileContents,
                ObjRef<iface::cellml_api::Model> *pModel,
                CellmlFileIssues &pIssues);

    void retrieveCmetaIdsFromCellmlElement(iface::cellml_api::CellMLElement *pElement);
    void clearCmetaIdsFromCellmlElement(const QDomElement &pElement,
                                        const QStringList &pUsedCmetaIds);

    bool doIsValid(iface::cellml_api::Model *pModel, CellmlFileIssues &pIssues);

    CellmlFileRdfTriple * rdfTriple(iface::cellml_api::CellMLElement *pElement,
                                    const QString &pQualifier,
                                    const QString &pResource,
                                    const QString &pId) const;

    QString rdfTripleSubject(iface::cellml_api::CellMLElement *pElement);
};

//==============================================================================

}   // namespace CellMLSupport
}   // namespace OpenCOR

//==============================================================================

#endif

//==============================================================================
// End of file
//==============================================================================
