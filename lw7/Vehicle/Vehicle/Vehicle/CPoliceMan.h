#pragma once
#include "IPoliceMan.h"
#include "CPersonImpl.h"

class CPoliceMan : public CPersonImpl<IPoliceMan>
{
public:
	CPoliceMan(std::string name, std::string departmentName)
		: CPersonImpl(name)
		, m_departmentName(departmentName)
	{}

	std::string GetDepartmentName() const;
private:
	std::string m_departmentName;
};