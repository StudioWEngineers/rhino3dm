#include "model.h"


Model::Model() : p_model(std::make_shared<ONX_Model>()) {}


bool Model::Read(std::wstring path) {
    p_model.reset(new ONX_Model());

    if (p_model->Read(path.c_str())) {
        return true;
    }

    p_model.reset();
    return false;
}

void Model::Reset() {
    p_model.reset();
}

bool Model::Write(std::wstring path, int version) {
    return p_model->Write(path.c_str(), version);
}


std::wstring Model::GetApplicationDetails() const {
    if (p_model.get() != nullptr) {
        return std::wstring(p_model->m_properties.m_Application.m_application_details);
    }
    return std::wstring();
}

std::wstring Model::GetApplicationName() const {
    if (p_model.get() != nullptr) {
        return std::wstring(p_model->m_properties.m_Application.m_application_name);
    }
    return std::wstring();
}

std::wstring Model::GetApplicationUrl() const {
    if (p_model.get() != nullptr) {
        return std::wstring(p_model->m_properties.m_Application.m_application_URL);
    }
    return std::wstring();
}

int Model::GetArchiveVersion() const {
    if (p_model.get() != nullptr) {
        return p_model->m_3dm_file_version;
    }
    return 0;
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


int Model::NewRevision() {
    if (p_model.get() != nullptr) {
        return p_model->m_properties.m_RevisionHistory.NewRevision();
    }
    return 0;
}

void Model::SetApplicationDetails(std::wstring details) {
    if (p_model.get() != nullptr) {
        p_model->m_properties.m_Application.m_application_details = details.c_str();
    }
}

void Model::SetApplicationName(std::wstring name) {
    if (p_model.get() != nullptr) {
        p_model->m_properties.m_Application.m_application_name = name.c_str();
    }
}

void Model::SetApplicationUrl(std::wstring url) {
    if (p_model.get() != nullptr) {
        p_model->m_properties.m_Application.m_application_URL = url.c_str();
    }
}

void Model::SetCreatedBy(std::wstring author) {
    if (p_model.get() != nullptr) {
        p_model->m_properties.m_RevisionHistory.m_sCreatedBy = author.c_str();
    }
}

void Model::SetLastEditedBy(std::wstring author) {
    if (p_model.get() != nullptr) {
        p_model->m_properties.m_RevisionHistory.m_sLastEditedBy = author.c_str();
    }
}


LayerTable Model::ModelLayerTable() {
    return LayerTable(p_model);
}

ObjectTable Model::ModelObjectTable() {
    return ObjectTable(p_model);
}
