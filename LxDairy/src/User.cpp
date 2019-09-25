#include "User.h"

CUser::CUser()
{
    m_lstDairyTag << "普通日记" << "心得体会" << "摘抄" << "工作笔记";
}

void CUser::loadDairyList(const QList<CDairy> &lstDairy)
{
    m_lstDairy = lstDairy;
    emit dairyListChanged(m_lstDairy);
}

void CUser::appendDairy(CDairy dairy)
{
    m_lstDairy.append(dairy);
}


