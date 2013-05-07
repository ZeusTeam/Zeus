#include "cpicturexml_parse.h"

CPictureXMLParse* Singleton<CPictureXMLParse>::m_pInst = NULL;

CPictureXMLParse::CPictureXMLParse()
{
}

CPictureXMLParse::~CPictureXMLParse()
{
    _Close();
}

void CPictureXMLParse::_Close()
{
    if (!m_mapPiture.empty())
    {
        for (auto it = m_mapPiture.begin(); it != m_mapPiture.end(); it++)
        {
            delete it->second;
        }
    }
}

int CPictureXMLParse::Size() const
{
    return m_mapPiture.size();
}

bool CPictureXMLParse::Empty() const
{
    return m_mapPiture.empty();
}

bool CPictureXMLParse::LoadXML(const std::string& strPath)
{
    TiXmlDocument XmlParse;

    if (strPath.empty())
    {
        return false;
    }

    if (XmlParse.LoadFile(strPath.c_str()))
    {
        return _Parse(XmlParse);
    }
    return true;
}

bool CPictureXMLParse::_Parse(TiXmlDocument& TinyXML)
{
    TiXmlElement* tiRoot = TinyXML.RootElement();
    if (!tiRoot)
    {
        return false;
    }
    std::string sRootName = tiRoot->Value();
    if (sRootName != PICTURE_ROOT_GAME)
    {
        return false;
    }
    TiXmlNode* tiFirst = tiRoot->FirstChild(PICTURE_GAME);
    if (tiFirst == NULL)
    {
        return false;
    }

     for (TiXmlElement* tiPicture = tiFirst->ToElement();
        tiPicture != NULL;
        tiPicture = tiPicture->NextSiblingElement())//读取当下元素中的所有属性
     {
         CPictureXMLObject* pPicture = new CPictureXMLObject;
         if(utils::GetXmlStrAttributeA(tiPicture, ID_OBJECT, pPicture->PictureId)
             && utils::GetXmlStrAttributeA(tiPicture, PICTURE_PATH, pPicture->PicturePath)
             && utils::GetXmlStrAttributeA(tiPicture, TYPE_OBJECT, pPicture->PictureType)
            )
         {
            utils::GetXmlIntAttribute(tiPicture, PICTURE_POSX, pPicture->Posx);
            utils::GetXmlIntAttribute(tiPicture, PICTURE_POSY, pPicture->Posy);
            utils::GetXmlIntAttribute(tiPicture, HEIGHT_OBJECT, pPicture->Hight);
            utils::GetXmlIntAttribute(tiPicture, WIDTH_OBJECT, pPicture->Width);
            m_mapPiture[pPicture->PictureId] = pPicture;
         }
     }
     return true;
}


CPictureXMLObject* CPictureXMLParse::Get(std::string nId) const
{
    auto it = m_mapPiture.find(nId);
    if (it == m_mapPiture.end())
    {
        return NULL;
    }
    return it->second;
}

const MapPitureList::const_iterator CPictureXMLParse::Begin() const
{
    return m_mapPiture.begin();
}

const MapPitureList::const_iterator CPictureXMLParse::End() const
{
    return m_mapPiture.end();
}