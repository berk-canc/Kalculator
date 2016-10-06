/**
*********************************************************************
CEL.h
	@author		Berk Can Celebisoy (berkcan@ureach.com) -- BCC

	Header file	for	CEL (Calculation Event Logs) class. This class represents the buffer of the 
	CEL_Viewer class. User interface is represented by CEL_Viewer class.


Revision History
	- 01MAY04-BCC	Initial	creation

 Copyright (c) 2005	Berk C. Celebisoy, All Rights Reserved.
*********************************************************************/

#ifndef CEL_H
#define CEL_H
#include "wx/wxprec.h"

class CEL
{
public:
	CEL();
	virtual ~CEL();

	wxString	GetCEL() const;
	void		AddLogNewLine(const wxString& text);
	void		AddLogNewLine(const long double& number);
	void		AddLogSameLine(const wxString& text);
	void		AddLogSameLine(const long double& number);
	void		ClearCEL();

private:
	CEL(const CEL& cel);			//not implemented as per design
	CEL operator=(const CEL& cel);	//not implemented as per design
	
	wxString m_buffer;
};

#endif	//CEL_H