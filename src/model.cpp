#include "model.h"


Model::Model() : p_model(std::make_shared<ONX_Model>()) {}

void Model::Reset() {
    p_model.reset();
}

bool Model::Read(std::wstring path) {
    p_model.reset(new ONX_Model());

    if (p_model->Read(path.c_str())) {
        return true;
    }

    p_model.reset();
    return false;
}

bool Model::Write(std::wstring path, int version) {
    return p_model->Write(path.c_str(), version);
}

std::wstring Model::GetApplicationName() const {
    if (p_model.get() != nullptr) {
        return std::wstring(p_model->m_properties.m_Application.m_application_name);
    }
    return std::wstring();
}

void Model::SetApplicationName(std::wstring comments) {
    if (p_model.get() != nullptr) {
        p_model->m_properties.m_Application.m_application_name = comments.c_str();
    }
}

std::wstring Model::GetApplicationUrl() const {
    if (p_model.get() != nullptr) {
        return std::wstring(p_model->m_properties.m_Application.m_application_URL);
    }
    return std::wstring();
}

void Model::SetApplicationUrl(std::wstring s) {
    if (p_model.get() != nullptr) {
        p_model->m_properties.m_Application.m_application_URL = s.c_str();
    }
}

std::wstring Model::GetApplicationDetails() const {
    if (p_model.get() != nullptr) {
        return std::wstring(p_model->m_properties.m_Application.m_application_details);
    }
    return std::wstring();
}

void Model::SetApplicationDetails(std::wstring s) {
    if (p_model.get() != nullptr) {
        p_model->m_properties.m_Application.m_application_details = s.c_str();
    }
}

int Model::GetArchiveVersion() const {
    return p_model->m_3dm_file_version;
}

std::wstring Model::GetCreatedBy() const {
    if (p_model.get() != nullptr) {
        return std::wstring(p_model->m_properties.m_RevisionHistory.m_sCreatedBy);
    }
    return std::wstring();
}

std::wstring Model::GetLastEditedBy() const {
    if (p_model.get() != nullptr) {
        return std::wstring(p_model->m_properties.m_RevisionHistory.m_sLastEditedBy);
    }
    return std::wstring();
}

int Model::GetRevision() const {
    int revision_number = 0;
    if (p_model.get() != nullptr) {
        revision_number = p_model->m_properties.m_RevisionHistory.m_revision_count;
    }
    return revision_number;
}

void Model::SetRevision(int revision_number) {
    if (p_model.get() != nullptr) {
        p_model->m_properties.m_RevisionHistory.m_revision_count = revision_number;
    }
}

LayerTable Model::ModelLayerTable() {
    return LayerTable(p_model);
}

ObjectTable Model::ModelObjectTable() {
    return ObjectTable(p_model);
}
