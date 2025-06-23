/*
    src/model.h: Helper class for managing the openNURBS ONX_Model class.

    Copyright (c) 2025 Studio W Engineers

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE file.
*/
#pragma once

#include "layer_table.h"
#include "object_table.h"
#include "opennurbs_includes.h"


class Model {
public:
    Model();

    bool Read(std::wstring path);
    void Reset();
    bool Write(std::wstring path, int version);

    std::wstring GetApplicationDetails() const;
    std::wstring GetApplicationName() const;
    std::wstring GetApplicationUrl() const;
    int GetArchiveVersion() const;
    std::wstring GetCreatedBy() const;
    std::wstring GetLastEditedBy() const;
    int GetRevision() const;

    int NewRevision();
    void SetApplicationDetails(std::wstring details);
    void SetApplicationName(std::wstring name);
    void SetApplicationUrl(std::wstring url);
    void SetCreatedBy(std::wstring author);
    void SetLastEditedBy(std::wstring author);

    LayerTable ModelLayerTable();
    ObjectTable ModelObjectTable();

private:
    std::shared_ptr<ONX_Model> p_model;
};