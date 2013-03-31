/* This file is automatically generated from CeVAS.idl
 * DO NOT EDIT DIRECTLY OR CHANGES WILL BE LOST!
 */
#ifndef _GUARD_IFACE_CeVAS
#define _GUARD_IFACE_CeVAS
#include "cda_compiler_support.h"
#ifdef MODULE_CONTAINS_CeVAS
#define PUBLIC_CeVAS_PRE CDA_EXPORT_PRE
#define PUBLIC_CeVAS_POST CDA_EXPORT_POST
#else
#define PUBLIC_CeVAS_PRE CDA_IMPORT_PRE
#define PUBLIC_CeVAS_POST CDA_IMPORT_POST
#endif
#include "Ifacexpcom.hxx"
#include "IfaceDOM_APISPEC.hxx"
#include "IfaceMathML_content_APISPEC.hxx"
#include "IfaceCellML_APISPEC.hxx"
namespace iface
{
  namespace cellml_services
  {
    PUBLIC_CeVAS_PRE
    class  PUBLIC_CeVAS_POST ConnectedVariableSet
     : public virtual iface::XPCOM::IObject
    {
    public:
      static const char* INTERFACE_NAME() { return "cellml_services::ConnectedVariableSet"; }
      virtual ~ConnectedVariableSet() {}
      virtual already_AddRefd<iface::cellml_api::CellMLVariable>  sourceVariable() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual uint32_t length() throw(std::exception&)  = 0;
      virtual already_AddRefd<iface::cellml_api::CellMLVariable>  getVariable(uint32_t index) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_CeVAS_PRE
    class  PUBLIC_CeVAS_POST CeVAS
     : public virtual iface::XPCOM::IObject
    {
    public:
      static const char* INTERFACE_NAME() { return "cellml_services::CeVAS"; }
      virtual ~CeVAS() {}
      virtual std::wstring modelError() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual already_AddRefd<iface::cellml_api::CellMLComponentIterator>  iterateRelevantComponents() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual already_AddRefd<iface::cellml_services::ConnectedVariableSet>  findVariableSet(iface::cellml_api::CellMLVariable* aVariable) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual uint32_t length() throw(std::exception&)  = 0;
      virtual already_AddRefd<iface::cellml_services::ConnectedVariableSet>  getVariableSet(uint32_t index) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_CeVAS_PRE
    class  PUBLIC_CeVAS_POST CeVASBootstrap
     : public virtual iface::XPCOM::IObject
    {
    public:
      static const char* INTERFACE_NAME() { return "cellml_services::CeVASBootstrap"; }
      virtual ~CeVASBootstrap() {}
      virtual already_AddRefd<iface::cellml_services::CeVAS>  createCeVASForModel(iface::cellml_api::Model* aModel) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
  };
};
#undef PUBLIC_CeVAS_PRE
#undef PUBLIC_CeVAS_POST
#endif // guard
