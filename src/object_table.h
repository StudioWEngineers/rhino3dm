/*
    src/object_table.h: Implementation details related to ObjectTable.

    Copyright (c) 2025 Studio W Engineers

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE file.
*/
#pragma once

#include <memory>
#include "opennurbs_includes.h"


class ObjectTable {
public:
    ObjectTable(std::shared_ptr<ONX_Model> model);

    //int Count() const;
    bool DeleteByUUID(ON_UUID on_uuid);
    int MaxIndex() const;
    ON_UUID Add(const double x, const double y, const double z) const;

    class Iterator {
    public:
        Iterator(ObjectTable* table);

        std::shared_ptr<ON_Geometry> operator*() const;
        Iterator& operator++();
        bool IsOver() const;

    private:
        ObjectTable* m_table;
        ONX_ModelComponentIterator m_iterator;
        mutable ON_ModelComponentReference m_current;
    };


    Iterator Begin();

private:
    std::shared_ptr<ONX_Model> m_model;
};
