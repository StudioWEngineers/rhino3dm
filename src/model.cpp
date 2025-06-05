#include "model.h"
//#include "base64.h"

Model::Model()
{
  p_model.reset(new ONX_Model());
}

Model::Model(ONX_Model* m)
{
  p_model.reset(m);
}

void Model::Destroy() {
    ONX_Model* model = p_model.get();
    if(model) {
        delete model;
    }
    p_model.reset();
}

Model* Model::Read(std::wstring path)
{
  ONX_Model* m = new ONX_Model();
  if (!m->Read(path.c_str()))
  {
    delete m;
    return nullptr;
  }
  return new Model(m);
}

std::string Model::ReadNotes(std::wstring path) {
  std::string str;
  FILE* fp = ON::OpenFile(path.c_str(), L"rb");
  if (fp) {
    ON_BinaryFile file(ON::archive_mode::read3dm, fp);
    int version = 0;
    ON_String comments;
    bool rc = file.Read3dmStartSection(&version, comments);
    if (rc)
    {
      ON_3dmProperties prop;
      file.Read3dmProperties(prop);
      if (prop.m_Notes.IsValid())
      {
        ON_String s = prop.m_Notes.m_notes;
        str = s;
      }
    }
    ON::CloseFile(fp);
  }
  return str;
}

int Model::ReadArchiveVersion(std::wstring path)
{
  FILE* fp = ON::OpenFile(path.c_str(), L"rb");
  if (fp)
  {
    ON_BinaryFile file(ON::archive_mode::read3dm, fp);
    int version = 0;
    ON_String comment_block;
    bool rc = file.Read3dmStartSection(&version, comment_block);
    if (rc)
    {
      ON::CloseFile(fp);
      return version;
    }
    ON::CloseFile(fp);
  }
  return 0;
}

bool Model::Write(std::wstring path, int version) {
    return p_model->Write(path.c_str(), version);
}

std::wstring Model::GetStartSectionComments() const
{
  ON_wString comments = p_model->m_sStartSectionComments;
  return std::wstring(comments);
}

void Model::SetStartSectionComments(std::wstring comments)
{
  ON_wString wcomments = comments.c_str();
  p_model->m_sStartSectionComments = wcomments;
}

const int idxApplicationName = 0;
const int idxApplicationUrl = 1;
const int idxApplicationDetails = 2;
const int idxCreatedBy = 3;
const int idxLastCreatedBy = 4;

//RH_C_FUNCTION void ONX_Model_GetString(const ONX_Model* pConstModel, int which, ON_wString* pString)
void ONX_Model_GetString(const ONX_Model* pConstModel, int which, ON_wString* pString)
{
  if (pConstModel && pString)
  {
    switch (which)
    {
    case idxApplicationName:
      *pString = (pConstModel->m_properties.m_Application.m_application_name);
      break;
    case idxApplicationUrl:
      *pString = (pConstModel->m_properties.m_Application.m_application_URL);
      break;
    case idxApplicationDetails:
      *pString = (pConstModel->m_properties.m_Application.m_application_details);
      break;
    case idxCreatedBy:
      *pString = (pConstModel->m_properties.m_RevisionHistory.m_sCreatedBy);
      break;
    case idxLastCreatedBy:
      *pString = (pConstModel->m_properties.m_RevisionHistory.m_sLastEditedBy);
      break;
    }
  }
}

//RH_C_FUNCTION void ONX_Model_SetString(ONX_Model* pModel, int which, const wchar_t* str)
void ONX_Model_SetString(ONX_Model* pModel, int which, const wchar_t* str)
{
  ON_wString _str = str;

  if (pModel)
  {
    switch (which)
    {
    case idxApplicationName:
      pModel->m_properties.m_Application.m_application_name = _str;
      break;
    case idxApplicationUrl:
      pModel->m_properties.m_Application.m_application_URL = _str;
      break;
    case idxApplicationDetails:
      pModel->m_properties.m_Application.m_application_details = _str;
      break;
    case idxCreatedBy:
      pModel->m_properties.m_RevisionHistory.m_sCreatedBy = _str;
      break;
    case idxLastCreatedBy:
      pModel->m_properties.m_RevisionHistory.m_sLastEditedBy = _str;
      break;
    }
  }
}

std::wstring Model::GetApplicationName() const
{
  ON_wString s;
  ONX_Model_GetString(p_model.get(), idxApplicationName, &s);
  return std::wstring(s);
}
void Model::SetApplicationName(std::wstring comments)
{
  ONX_Model_SetString(p_model.get(), idxApplicationName, comments.c_str());
}
std::wstring Model::GetApplicationUrl() const
{
  ON_wString s;
  ONX_Model_GetString(p_model.get(), idxApplicationUrl, &s);
  return std::wstring(s);
}
void Model::SetApplicationUrl(std::wstring s)
{
  ONX_Model_SetString(p_model.get(), idxApplicationUrl, s.c_str());
}
std::wstring Model::GetApplicationDetails() const
{
  ON_wString s;
  ONX_Model_GetString(p_model.get(), idxApplicationDetails, &s);
  return std::wstring(s);
}
void Model::SetApplicationDetails(std::wstring s)
{
  ONX_Model_SetString(p_model.get(), idxApplicationDetails, s.c_str());
}
int Model::GetArchiveVersion() const
{
  return p_model->m_3dm_file_version;
}
std::wstring Model::GetCreatedBy() const
{
  ON_wString s;
  ONX_Model_GetString(p_model.get(), idxCreatedBy, &s);
  return std::wstring(s);
}
std::wstring Model::GetLastEditedBy() const
{
  ON_wString s;
  ONX_Model_GetString(p_model.get(), idxLastCreatedBy, &s);
  return std::wstring(s);
}
//BND_DateTime Model::GetCreated() const
//{
//  return CreateDateTime(p_model->m_properties.m_RevisionHistory.m_create_time);
//}
//BND_DateTime Model::GetLastEdited() const
//{
//  return CreateDateTime(p_model->m_properties.m_RevisionHistory.m_last_edit_time);
//}

//RH_C_FUNCTION int ONX_Model_GetRevision(const ONX_Model* pConstModel)
int ONX_Model_GetRevision(const ONX_Model* pConstModel)
{
  int rc = 0;
  if (pConstModel)
    rc = pConstModel->m_properties.m_RevisionHistory.m_revision_count;
  return rc;
}

//RH_C_FUNCTION void ONX_Model_SetRevision(ONX_Model* pModel, int rev)
void ONX_Model_SetRevision(ONX_Model* pModel, int rev)
{
  if (pModel)
    pModel->m_properties.m_RevisionHistory.m_revision_count = rev;
}

int Model::GetRevision() const
{
  return ONX_Model_GetRevision(p_model.get());
}
void Model::SetRevision(int revision_number) {
    ONX_Model_SetRevision(p_model.get(), revision_number);
}

LayerTable Model::ModelLayerTable() {
    return LayerTable(p_model);
}

ObjectTable Model::ModelObjectTable() {
    return ObjectTable(p_model);
}

// --------------------- Iterator helpers ------- //
//template <typename IT, typename ET>
//struct PyBNDIterator {
//  PyBNDIterator(const IT table, py::object ref)
//    : seq(table), ref(ref) {}
//
//  ET next() {
//    if(index>=seq.Count()) throw py::stop_iteration();
//    return const_cast<IT>(seq).IterIndex(index++);
//  }
//
//  const IT seq;
//  py::object ref;
//  int index = 0;
//};


