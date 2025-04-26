#include "bindings.h"

#pragma once

void initExtensionsBindings(rh3dmpymodule& m);

class BND_ONXModel {
public:
    std::shared_ptr<ONX_Model> m_model;

    BND_ONXModel();
    BND_ONXModel(ONX_Model* m);
    void Destroy();
    static BND_ONXModel* Read(std::wstring path);
    static std::string ReadNotes(std::wstring path);
    static int ReadArchiveVersion(std::wstring path);

    std::string Encode();
    std::string Encode2(const class BND_File3dmWriteOptions* options);

    //static BND_ONXModel* FromByteArray(int length, const void* buffer);
    static BND_ONXModel* Decode(std::string buffer);
    bool Write(std::wstring path, int version);
    //public bool Write(string path, File3dmWriteOptions options)
    //public bool WriteWithLog(string path, int version, out string errorLog)
    //public bool WriteWithLog(string path, File3dmWriteOptions options, out string errorLog)

    std::wstring GetStartSectionComments() const;
    void SetStartSectionComments(std::wstring comments);
    std::wstring GetApplicationName() const;
    void SetApplicationName(std::wstring name);
    std::wstring GetApplicationUrl() const;
    void SetApplicationUrl(std::wstring url);
    std::wstring GetApplicationDetails() const;
    void SetApplicationDetails(std::wstring details);
    int GetArchiveVersion() const;
    std::wstring GetCreatedBy() const;
    std::wstring GetLastEditedBy() const;
    BND_DateTime GetCreated() const;
    BND_DateTime GetLastEdited() const;
    int GetRevision() const;
    void SetRevision(int r);
    //BND_File3dmSettings Settings() { return BND_File3dmSettings(m_model); }

    //BND_ONXModel_ObjectTable Objects() { return BND_ONXModel_ObjectTable(m_model); }
    //BND_File3dmMaterialTable Materials() { return BND_File3dmMaterialTable(m_model); }
    //BND_File3dmLinetypeTable Linetypes() { return BND_File3dmLinetypeTable(m_model); }
    //BND_File3dmBitmapTable Bitmaps() { return BND_File3dmBitmapTable(m_model); }
    BND_File3dmLayerTable Layers() { return BND_File3dmLayerTable(m_model); }
    //BND_File3dmGroupTable AllGroups() { return BND_File3dmGroupTable(m_model); }
    //BND_File3dmDimStyleTable DimStyles() { return BND_File3dmDimStyleTable(m_model); }
    //BND_File3dmInstanceDefinitionTable InstanceDefinitions() { return BND_File3dmInstanceDefinitionTable(m_model); }
    //BND_File3dmViewTable Views() { return BND_File3dmViewTable(m_model, false); }
    //BND_File3dmViewTable NamedViews() { return BND_File3dmViewTable(m_model, true); }
    //BND_File3dmPlugInDataTable PlugInData() { return BND_File3dmPlugInDataTable(m_model); }
    //BND_File3dmStringTable Strings() { return BND_File3dmStringTable(m_model); }
    //BND_File3dmEmbeddedFileTable EmbeddedFiles() { return BND_File3dmEmbeddedFileTable(m_model); }
    //BND_File3dmRenderContentTable RenderContent() { return BND_File3dmRenderContentTable(m_model); }

    //std::wstring Dump() const;
    //std::wstring DumpSummary() const;
    //public void DumpToTextLog(TextLog log)
    BND_TUPLE GetEmbeddedFilePaths();
    std::vector<std::wstring> GetEmbeddedFilePaths2();
    std::string GetEmbeddedFileAsBase64(std::wstring path);
    std::string GetEmbeddedFileAsBase64Strict(std::wstring path, bool strict);
    std::wstring RdkXml() const;

    static bool ReadTest(std::wstring filepath);
};
