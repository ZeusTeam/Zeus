#include "role_select.h"

RoleSelect::RoleSelect()
{
    ///��ɫ1
    m_gui.AddCtrl(new RoleSelectItem(1, false, 63, 66, "role1", 
        PicturePool::Instance()->Get("RoleSelect-Role"), 
        PicturePool::Instance()->Get("RoleSelect-RoleFocus"), NULL, NULL));
    ///��ɫ2
    m_gui.AddCtrl(new RoleSelectItem(2, false, 189, 66, "role2", 
        PicturePool::Instance()->Get("RoleSelect-Role"), 
        PicturePool::Instance()->Get("RoleSelect-RoleFocus"), NULL, NULL));
    ///������ɫ��ť
    m_gui.AddCtrl(new RoleSelectItem(3, false, 204, 509, "", PicturePool::Instance()->Get("RoleSelect-CreateRole"), NULL, NULL, NULL));
    ///�ص���ҳ��ť
    m_gui.AddCtrl(new RoleSelectItem(4, false, 1, 545, "", PicturePool::Instance()->Get("RoleSelect-RetHomePage"), NULL, NULL, NULL));
    ///����ͼƬ
    m_bgTex = PicturePool::Instance()->Get("RoleSelect-Bg");
    m_gui.SetNavMode(HGEGUI_LEFTRIGHT | HGEGUI_CYCLED);
    m_gui.SetFocus(1);
    m_cursorMouse = new hgeSprite(hgeCreate(HGE_VERSION)->Texture_Load("res\\img\\cursor_normal.png"), 0, 0, 32, 32);
    m_gui.SetCursor(m_cursorMouse);
    m_gui.Enter();
}

RoleSelect::~RoleSelect()
{
    if (m_cursorMouse)
        delete m_cursorMouse;

}

bool RoleSelect::Render()
{
    if (m_bgTex)
        m_bgTex->Render(0, 0);
    m_gui.Render();
    
    return false;
}

RoleSelectState RoleSelect::Update()
{
    int id = m_gui.Update(hgeCreate(HGE_VERSION)->Timer_GetDelta());

    switch (id)
    {
    case 1:
        return RoleSelect_EnterGame; //ѡ���ɫ
    case 2:
        return RoleSelect_EnterGame; //ѡ���ɫ ��ʼ��Ϸ
    case 3:
        return RoleSelect_CreateRole; //���봴����ɫҳ��
    case 4:
        return RoleSelect_Return; //�ص��ϸ�ҳ��
    default:
        break;
    }
    return RoleSelect_None;
}