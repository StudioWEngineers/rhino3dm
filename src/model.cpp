#include "bindings.h"
#include "base64.h"

// TODO: Move some of this functionality into core opennurbs
static bool SeekPastCompressedBuffer(ON_BinaryArchive& archive)
{
  if (!archive.ReadMode())
    return false;

  bool rc = false;
  char method = 0;
  unsigned int buffer_crc0 = 0;

  size_t sizeof__outbuffer;
  if (!archive.ReadCompressedBufferSize(&sizeof__outbuffer))
    return false;

  if (0 == sizeof__outbuffer)
    return true;

  if (!archive.ReadInt(&buffer_crc0)) // 32 bit crc of uncompressed buffer
    return false;

  if (!archive.ReadChar(&method))
    return false;

  if (method != 0 && method != 1)
    return false;

  switch (method)
  {
  case 0: // uncompressed
    rc = archive.SeekForward(sizeof__outbuffer);
    break;
  case 1: // compressed
    {
    ON__UINT32 tcode = 0;
    ON__INT64  big_value = 0;
    rc = archive.BeginRead3dmBigChunk(&tcode, &big_value);
    if (rc)
      rc = archive.EndRead3dmChunk();
    }
    break;
  }

  return rc;
}


BND_TUPLE BND_ONXModel::GetEmbeddedFilePaths()
{
  ON_ClassArray<ON_wString> paths;
  ON_SimpleArray<ONX_Model_UserData*>& userdata_table = m_model->m_userdata_table;
  for (int i = 0; i < userdata_table.Count(); i++)
  {
    ONX_Model_UserData* ud = userdata_table[i];
    if (ud && m_model->GetRDKEmbeddedFilePaths(*ud, paths))
    //if (ud && GetRDKEmbeddedFileHelper(*ud, paths, nullptr, nullptr, false))
      break;
  }
  int count = paths.Count();

  BND_TUPLE rc = CreateTuple(count);
  for (int i = 0; i < count; i++)
  {
    std::wstring path(paths[i].Array());
    SetTuple(rc, i, path);
  }
  return rc;
}

std::vector<std::wstring> BND_ONXModel::GetEmbeddedFilePaths2()
{
  ON_ClassArray<ON_wString> paths;
  ON_SimpleArray<ONX_Model_UserData*>& userdata_table = m_model->m_userdata_table;
  for (int i = 0; i < userdata_table.Count(); i++)
  {
    ONX_Model_UserData* ud = userdata_table[i];
    if (ud && m_model->GetRDKEmbeddedFilePaths(*ud, paths))
    //if (ud && GetRDKEmbeddedFileHelper(*ud, paths, nullptr, nullptr, false))
      break;
  }
  int count = paths.Count();

  std::vector<std::wstring> rc;
  for (int i = 0; i < count; i++)
  {
    std::wstring path(paths[i].Array());
    rc.push_back(path);
  }
  return rc;
}

///////////////////////////////////////////////

BND_ONXModel::BND_ONXModel()
{
  m_model.reset(new ONX_Model());
}

BND_ONXModel::BND_ONXModel(ONX_Model* m)
{
  m_model.reset(m);
}

void BND_ONXModel::Destroy() {
    ONX_Model* model = m_model.get();
    if(model) {
        delete model;
    }
    m_model.reset(nullptr);
}

BND_ONXModel* BND_ONXModel::Read(std::wstring path)
{
  ONX_Model* m = new ONX_Model();
  if (!m->Read(path.c_str()))
  {
    delete m;
    return nullptr;
  }
  return new BND_ONXModel(m);
}

std::string BND_ONXModel::ReadNotes(std::wstring path)
{
  std::string str;
  FILE* fp = ON::OpenFile(path.c_str(), L"rb");
  if (fp)
  {
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

int BND_ONXModel::ReadArchiveVersion(std::wstring path)
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

bool BND_ONXModel::Write(std::wstring path, int version) {
    return m_model->Write(path.c_str(), version);
}

std::wstring BND_ONXModel::GetStartSectionComments() const
{
  ON_wString comments = m_model->m_sStartSectionComments;
  return std::wstring(comments);
}
void BND_ONXModel::SetStartSectionComments(std::wstring comments)
{
  ON_wString wcomments = comments.c_str();
  m_model->m_sStartSectionComments = wcomments;
}

const int idxApplicationName = 0;
const int idxApplicationUrl = 1;
const int idxApplicationDetails = 2;
const int idxCreatedBy = 3;
const int idxLastCreatedBy = 4;

RH_C_FUNCTION void ONX_Model_GetString(const ONX_Model* pConstModel, int which, ON_wString* pString)
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

RH_C_FUNCTION void ONX_Model_SetString(ONX_Model* pModel, int which, const wchar_t* str)
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

std::wstring BND_ONXModel::GetApplicationName() const
{
  ON_wString s;
  ONX_Model_GetString(m_model.get(), idxApplicationName, &s);
  return std::wstring(s);
}
void BND_ONXModel::SetApplicationName(std::wstring comments)
{
  ONX_Model_SetString(m_model.get(), idxApplicationName, comments.c_str());
}
std::wstring BND_ONXModel::GetApplicationUrl() const
{
  ON_wString s;
  ONX_Model_GetString(m_model.get(), idxApplicationUrl, &s);
  return std::wstring(s);
}
void BND_ONXModel::SetApplicationUrl(std::wstring s)
{
  ONX_Model_SetString(m_model.get(), idxApplicationUrl, s.c_str());
}
std::wstring BND_ONXModel::GetApplicationDetails() const
{
  ON_wString s;
  ONX_Model_GetString(m_model.get(), idxApplicationDetails, &s);
  return std::wstring(s);
}
void BND_ONXModel::SetApplicationDetails(std::wstring s)
{
  ONX_Model_SetString(m_model.get(), idxApplicationDetails, s.c_str());
}
int BND_ONXModel::GetArchiveVersion() const
{
  return m_model->m_3dm_file_version;
}
std::wstring BND_ONXModel::GetCreatedBy() const
{
  ON_wString s;
  ONX_Model_GetString(m_model.get(), idxCreatedBy, &s);
  return std::wstring(s);
}
std::wstring BND_ONXModel::GetLastEditedBy() const
{
  ON_wString s;
  ONX_Model_GetString(m_model.get(), idxLastCreatedBy, &s);
  return std::wstring(s);
}
BND_DateTime BND_ONXModel::GetCreated() const
{
  return CreateDateTime(m_model->m_properties.m_RevisionHistory.m_create_time);
}
BND_DateTime BND_ONXModel::GetLastEdited() const
{
  return CreateDateTime(m_model->m_properties.m_RevisionHistory.m_last_edit_time);
}

RH_C_FUNCTION int ONX_Model_GetRevision(const ONX_Model* pConstModel)
{
  int rc = 0;
  if (pConstModel)
    rc = pConstModel->m_properties.m_RevisionHistory.m_revision_count;
  return rc;
}

RH_C_FUNCTION void ONX_Model_SetRevision(ONX_Model* pModel, int rev)
{
  if (pModel)
    pModel->m_properties.m_RevisionHistory.m_revision_count = rev;
}

int BND_ONXModel::GetRevision() const
{
  return ONX_Model_GetRevision(m_model.get());
}
void BND_ONXModel::SetRevision(int r)
{
  ONX_Model_SetRevision(m_model.get(), r);
}


// --------------------- Iterator helpers ------- //
template <typename IT, typename ET>
struct PyBNDIterator {
  PyBNDIterator(const IT table, py::object ref)
    : seq(table), ref(ref) {}

  ET next() {
    if(index>=seq.Count()) throw py::stop_iteration();
    return const_cast<IT>(seq).IterIndex(index++);
  }

  const IT seq;
  py::object ref;
  int index = 0;
};

void ModelBindings(rh3dmpymodule& m)
{


  py::class_<BND_ONXModel>(m, "File3dm")
    .def(py::init<>())
    .def_static("Read", &BND_ONXModel::Read, py::arg("path"))
    .def_static("ReadNotes", &BND_ONXModel::ReadNotes, py::arg("path"))
    .def_static("ReadArchiveVersion", &BND_ONXModel::ReadArchiveVersion, py::arg("path"))
//#if !defined(NANOBIND)
//    .def_static("FromByteArray", [](py::buffer b) {
//      py::buffer_info info = b.request();
//      return BND_ONXModel::FromByteArray(static_cast<int>(info.size), info.ptr);
//    })
// #endif
    .def("Write", &BND_ONXModel::Write, py::arg("path"), py::arg("version")=0)
    //.def_property("StartSectionComments", &BND_ONXModel::GetStartSectionComments, &BND_ONXModel::SetStartSectionComments)
    //.def_property("ApplicationName", &BND_ONXModel::GetApplicationName, &BND_ONXModel::SetApplicationName)
    //.def_property("ApplicationUrl", &BND_ONXModel::GetApplicationUrl, &BND_ONXModel::SetApplicationUrl)
    //.def_property("ApplicationDetails", &BND_ONXModel::GetApplicationDetails, &BND_ONXModel::SetApplicationDetails)
    //.def_property_readonly("ArchiveVersion", &BND_ONXModel::GetArchiveVersion)
    //.def_property_readonly("Created", &BND_ONXModel::GetCreated)
    //.def_property_readonly("CreatedBy", &BND_ONXModel::GetCreatedBy)
    //.def_property_readonly("LastEdited", &BND_ONXModel::GetLastEdited)
    //.def_property_readonly("LastEditedBy", &BND_ONXModel::GetLastEditedBy)
    //.def_property("Revision", &BND_ONXModel::GetRevision, &BND_ONXModel::SetRevision)
    //.def_property_readonly("Settings", &BND_ONXModel::Settings)
    //.def_property_readonly("Objects", &BND_ONXModel::Objects)
    //.def_property_readonly("Materials", &BND_ONXModel::Materials)
    //.def_property_readonly("Linetypes", &BND_ONXModel::Linetypes)
    //.def_property_readonly("Bitmaps", &BND_ONXModel::Bitmaps)
    .def_property_readonly("Layers", &BND_ONXModel::Layers)
    //.def_property_readonly("Groups", &BND_ONXModel::AllGroups)
    //.def_property_readonly("DimStyles", &BND_ONXModel::DimStyles)
    //.def_property_readonly("InstanceDefinitions", &BND_ONXModel::InstanceDefinitions)
    //.def_property_readonly("Views", &BND_ONXModel::Views)
    //.def_property_readonly("NamedViews", &BND_ONXModel::NamedViews)
    //.def_property_readonly("PlugInData", &BND_ONXModel::PlugInData)
    //.def_property_readonly("Strings", &BND_ONXModel::Strings)
    //.def_property_readonly("EmbeddedFiles", &BND_ONXModel::EmbeddedFiles)
    //.def_property_readonly("RenderContent", &BND_ONXModel::RenderContent)
    //.def("Encode", &BND_ONXModel::Encode)
    //.def("Encode", &BND_ONXModel::Encode2)
    //.def("Decode", &BND_ONXModel::Decode)
    //.def("EmbeddedFilePaths", &BND_ONXModel::GetEmbeddedFilePaths)
    //.def("EmbeddedFilePaths2", &BND_ONXModel::GetEmbeddedFilePaths2)
    //.def("GetEmbeddedFileAsBase64", &BND_ONXModel::GetEmbeddedFileAsBase64)
    //.def("GetEmbeddedFileAsBase64", &BND_ONXModel::GetEmbeddedFileAsBase64Strict)
    //.def("RdkXml", &BND_ONXModel::RdkXml)
    ;
}
