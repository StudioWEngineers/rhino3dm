#pragma once

#include "layer_view.h"
//#include "opennurbs_includes.h"


class LayerTable {
    std::shared_ptr<ONX_Model> m_model;

public:
    LayerTable(std::shared_ptr<ONX_Model> m);
    int Count() const;
    int Add(const class Layer &layer);
    bool DeleteById(ON_UUID id);
    bool DeleteByName(std::wstring full_name);
    bool Has(std::wstring full_name);
    const class LayerView *Get(std::wstring full_name);
    class LayerView *FindName(std::wstring name, ON_UUID parentId);
    class LayerView *FindIndex(int index);
    class LayerView *IterIndex(int index); // helper function for iterator
    class LayerView *FindId(ON_UUID id);
    class Iterator {
        public:
            Iterator(LayerTable* table, int index)
                : m_table(table), m_index(index), m_count(table->Count()) {}

            LayerView* operator*() const {
                return m_table->FindIndex(m_index);
            }

            Iterator& operator++() {
                ++m_index;
                return *this;
            }

            bool is_done() const {
                return m_index >= m_count;
            }

        private:
            LayerTable* m_table;
            int m_index;
            int m_count;
        };

        Iterator begin();
        Iterator end(); // Optional, not used in Python
    };