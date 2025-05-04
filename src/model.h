#include "opennurbs_includes.h"
#include "layer_table.h"

#pragma once

class BND_ONXModel {
public:
    ///@name Public member variables
    ///@{
    std::shared_ptr<ONX_Model> p_model;

    ///@}
    ///@name Life Cycle
    ///@{

    /**
    * Default constructor
    */
    BND_ONXModel();

    /**
    * Constructor using Opennurbs model
    */
    BND_ONXModel(ONX_Model* m);

    /**
    * Destructor
    */
    void Destroy();
    ///@}

    static BND_ONXModel* Read(std::wstring path);
    static std::string ReadNotes(std::wstring path);
    static int ReadArchiveVersion(std::wstring path);

    bool Write(std::wstring path, int version);

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
    //BND_DateTime GetCreated() const;
    //BND_DateTime GetLastEdited() const;
    int GetRevision() const;
    void SetRevision(int revision_number);
    BND_File3dmLayerTable LayerTable();
};