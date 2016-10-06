/**
*********************************************************************
CEL_Viewer.cpp
	@author		Berk Can Celebisoy (berkcan@ureach.com) -- BCC

	Imptementation file	for	CEL_Viewer class. 


Revision History
	- 01MAY04-BCC	Initial	creation

 Copyright (c) 2005	Berk C. Celebisoy, All Rights Reserved.
*********************************************************************/

#include "CEL_Viewer.h"
#include "KalculatorUtils.h"
#include "KalculatorException.h"

BEGIN_EVENT_TABLE(CEL_Viewer, wxFrame)
	EVT_BUTTON(BUTTON_SAVE,  Button_Save_Clicked)	
	EVT_BUTTON(BUTTON_CLEAR, Button_Clear_Clicked)
	EVT_CLOSE(               HideWindow)	//over-ride the implementation of top-right X button
END_EVENT_TABLE()

/**
*********************************************************************
CEL_Viewer::CEL_Viewer

    CEL_Viewer constructor.

    @param wxFrame*				Actual frame that is visible on screen.
	@param const wxSize&		Size of frame.
	@param const wxString&		Title of frame,
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
CEL_Viewer::CEL_Viewer(wxFrame* frame, const wxSize& size, const wxString& title) :
	wxFrame(
			frame, 
			-1, 
			"", 
			wxDefaultPosition, 
			wxDefaultSize, 
			wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxRESIZE_BORDER, 
			""), 
	m_title("------Calculation Event Logs------\n\n")
{
	wxFont font(9, wxMODERN, wxNORMAL, wxBOLD);

	this->SetSize(size);
	this->SetTitle(title);
	this->SetSizeHints(	size.GetWidth(), size.GetHeight(), 
						(size.GetWidth() +(size.GetWidth() /2) ), 
						(size.GetHeight()+(size.GetHeight()/3) ) );
	
	//Create panel(s)
	wxPanel* pPanel	= new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize, wxEXPAND);

	//Create widgets
	m_CEL_Display	= new wxTextCtrl(pPanel, DISPLAY, m_title, wxDefaultPosition, wxDefaultSize, wxTE_DONTWRAP | wxTE_MULTILINE | wxTE_READONLY);
	m_saveButton	= new wxButton(pPanel, BUTTON_SAVE, "Save");
	m_clearButton	= new wxButton(pPanel, BUTTON_CLEAR, "Clear");

	m_CEL_Display->SetBackgroundColour( wxColour(255, 255, 255) );
	m_CEL_Display->SetFont(font);
	//change font for buttons
	font.SetPointSize(10);
	m_saveButton->SetFont(font);
	m_clearButton->SetFont(font);

	//Create sizers
	wxBoxSizer* pDisplaySizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* pButtonSizer  = new wxBoxSizer(wxHORIZONTAL);	

	//For below 2 lines: 
	//	0 = dont expand default orientation (horizontal)
	//	wxALL = border all over
	//	6 = border thickness
	pButtonSizer->Add(m_saveButton, 0, wxALL, 6);
	pButtonSizer->Add(m_clearButton, 0, wxALL, 6);
	//	1 = expand on default orientation (vertical)
	//	wxEXPAND = expand all directions
	pDisplaySizer->Add(m_CEL_Display, 1, wxEXPAND);
	//	0 = do not expand m_pButtonSizer horizontally
	//	wxCENTER = Center buttonSizer
	//	also add buttonSizer to displaySizer. It will add to the bottom since displaySizer is horizontal
	pDisplaySizer->Add(pButtonSizer, 0, wxCENTER);

	pPanel->SetSizer(pDisplaySizer);
}

/**
*********************************************************************
CEL_Viewer::~CEL_Viewer

    CEL_Viewer destructor.

    @param  void
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
CEL_Viewer::~CEL_Viewer()
{

}

/**
*********************************************************************
CEL_Viewer::Button_Save_Clicked

    Event handling function for 'Save' button click. Opens a save dialog for user to save the log to 
	a file in disk.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void CEL_Viewer::Button_Save_Clicked(wxCommandEvent& event)
{
	int userInput;
	bool isSaved;
	wxFileDialog* saveDialog = new wxFileDialog(this, 
												"Save CEL...", 
												"", 
												"*.log", 
												"Log files (*.log)|*.log|Text files (*.txt)|*.txt|All files (*.*)|*.*", 
												wxSAVE | wxOVERWRITE_PROMPT, wxDefaultPosition);	
	
	userInput = saveDialog->ShowModal();

	//user saves the files
	if(userInput == wxID_OK)
	{
		isSaved = m_CEL_Display->SaveFile( saveDialog->GetPath() );

		//CEL is saved, show confirmation dialog
		if(isSaved == true)
		{
			KalculatorUtils::ShowDialog(this, 
										CEL_SAVE_SUCCESS_MSG, 
										"Kalculator", 
										wxOK | wxICON_INFORMATION | wxCENTRE);

			//////////////////////////////////////////////////////////////////////////////////
			//log the event
			mCEL.AddLogSameLine("CEL saved successfully.");
			mCEL.AddLogNewLine("");
			//display the event
			SetDisplay( mCEL.GetCEL() );
			ShowLastEnteredLog();
			//////////////////////////////////////////////////////////////////////////////////
		}
		//CEL couldn't be saved, show error dialog
		else 		
		{
			KalculatorUtils::ShowDialog(this, 
										CEL_SAVE_FAILURE_MSG, 
										"Kalculator", 
										wxOK | wxICON_ERROR | wxCENTRE);

			//////////////////////////////////////////////////////////////////////////////////
			//log the event
			mCEL.AddLogSameLine("Saving CEL failed.");
			mCEL.AddLogNewLine("");
			//display the event
			SetDisplay( mCEL.GetCEL() );
			ShowLastEnteredLog();
			//////////////////////////////////////////////////////////////////////////////////
		}

		saveDialog->Destroy();
	}
	//user doesn't save the file
	else if(userInput == wxCANCEL)
	{
		//do nothing...
	}
}

/**
*********************************************************************
CEL_Viewer::Button_Clear_Clicked

    Event handling function for 'Clear' button click. Deletes CEL's buffer and clears CEL_Viewer's 
	display.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void CEL_Viewer::Button_Clear_Clicked(wxCommandEvent& event)
{
	mCEL.ClearCEL();
	m_CEL_Display->SetValue(m_title);
	mCEL.AddLogSameLine("CEL cleared.");
	mCEL.AddLogNewLine("");
	SetDisplay( mCEL.GetCEL() );
}

/**
*********************************************************************
CEL_Viewer::HideWindow

    Event handling function of frame's close event.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void CEL_Viewer::HideWindow(wxCommandEvent& event)
{
	this->Show(false);
}

/**
*********************************************************************
CEL_Viewer::GetDisplay

    Returns current text in CEL_Viewer's display.

    @param  void
    @return wxString	String of CEL_Viewer's display.
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
wxString CEL_Viewer::GetDisplay() const
{
	return m_CEL_Display->GetValue();
}

/**
*********************************************************************
CEL_Viewer::GetDisplay

    Sets CEL_Viewer's display to specified string.

    @param  const wxString&		String to set CEL_Viewer's display.
    @return void
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void CEL_Viewer::SetDisplay(const wxString& text)
{
	m_CEL_Display->SetValue(m_title);
	m_CEL_Display->AppendText(text);
}

/**
*********************************************************************
CEL_Viewer::ShowLastEnteredLog

    Sets CEL_Viewer's display to specified string.

    @param  void		Scroll CEL_Viewer's display to the very bottom.
    @return void
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void CEL_Viewer::ShowLastEnteredLog()
{
	m_CEL_Display->ShowPosition( m_CEL_Display->GetLastPosition() );
}