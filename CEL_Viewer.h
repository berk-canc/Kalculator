/**
*********************************************************************
CEL_Viewer.h
	@author		Berk Can Celebisoy (berkcan@ureach.com) -- BCC

	Header file	for	CEL_Viewer class. CEL_Viewer is the user visible part of Kalculator's CEL 
	functionality. CEL class represents CEL_Viewer's buffer.


Revision History
	- 01MAY04-BCC	Initial	creation

 Copyright (c) 2005	Berk C. Celebisoy, All Rights Reserved.
*********************************************************************/

#ifndef CEL_VIEWER_H
#define CEL_VIEWER_H
#include "CEL.h"
#include "wx/wxprec.h"

class CEL_Viewer : public wxFrame
{
public:
	CEL_Viewer(wxFrame* frame, const wxSize& size, const wxString& title);
	virtual ~CEL_Viewer();
	CEL mCEL;
	wxString	GetDisplay() const;
	void		SetDisplay(const wxString& text);
	void		ShowLastEnteredLog(); //shows the very bottom of m_pDisplay

private:
	DECLARE_EVENT_TABLE()

	enum Button 
	{
		BUTTON_SAVE, 
		BUTTON_CLEAR, 
		DISPLAY, 
		SCROLLBAR
	};

	CEL_Viewer();										//not implemented as per design
	CEL_Viewer(const CEL_Viewer& celViewer);			//not implemented as per design
	CEL_Viewer operator=(const CEL_Viewer& celViewer);	//not implemented as per design

	wxButton*		m_saveButton;
	wxButton*		m_clearButton;
	wxTextCtrl*		m_CEL_Display;
	const wxString	m_title;

	void Button_Save_Clicked(wxCommandEvent& event);
	void Button_Clear_Clicked(wxCommandEvent& event);
	//over-ride the implementation of top-right X button
	void HideWindow(wxCommandEvent& event);
};

#endif	//CEL_VIEWER_H