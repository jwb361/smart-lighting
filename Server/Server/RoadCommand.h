#pragma once
#include "dbcommand.h"

class CRoadCommand :
	public CDBCommand
{
public:
	CRoadCommand(void);
	~CRoadCommand(void);

    BOOL AddRoad(CString RoadID, CString RoadName);
	BOOL AddRoadID(CString RoadID);
	BOOL AddRoadID(CString terminalID,CString RoadID);
private:
	int GetMaxID();
};
