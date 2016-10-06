/**
*********************************************************************
KalculatorFrame.cpp
	@author		Berk Can Celebisoy (berkcan@ureach.com) -- BCC

	Imptementation file	for	KalculatorFrame class. 


Revision History
	- 01MAY04-BCC	Initial	creation
	- 05APR05-BCC	Removed IsFloating funtion. IsFloating is now a member of KalculatorUtils class

 Copyright (c) 2005	Berk C. Celebisoy, All Rights Reserved.
*********************************************************************/

#include "KalculatorFrame.h"
#include "KalculatorException.h"
#include "KalculatorUtils.h"
#include <sstream>
#include <Math.h>

using namespace std;

BEGIN_EVENT_TABLE(KalculatorFrame, wxFrame)
	EVT_MENU(ABOUT_MENU_ITEM,		AboutMenuItemClicked)
	EVT_MENU(COPY_MENU_ITEM,		CopyMenuItemClicked)
	EVT_MENU(PASTE_MENU_ITEM,		PasteMenuItemClicked)
	EVT_BUTTON(BUTTON_1,			Button_1_Clicked)
	EVT_BUTTON(BUTTON_2,			Button_2_Clicked)
	EVT_BUTTON(BUTTON_3,			Button_3_Clicked)
	EVT_BUTTON(BUTTON_4,			Button_4_Clicked)
	EVT_BUTTON(BUTTON_5,			Button_5_Clicked)
	EVT_BUTTON(BUTTON_6,			Button_6_Clicked)
	EVT_BUTTON(BUTTON_7,			Button_7_Clicked)
	EVT_BUTTON(BUTTON_8,			Button_8_Clicked)
	EVT_BUTTON(BUTTON_9,			Button_9_Clicked)
	EVT_BUTTON(BUTTON_0,			Button_0_Clicked)
	EVT_BUTTON(BUTTON_BACKSPACE,	Button_Backspace_Clicked)
	EVT_BUTTON(BUTTON_CLEAR,		Button_Clear_Clicked)
	EVT_BUTTON(BUTTON_CEL,			Button_CEL_Clicked)
	EVT_BUTTON(BUTTON_DIVIDE,		Button_Divide_Clicked)
	EVT_BUTTON(BUTTON_MULTIPLY,		Button_Multiply_Clicked)
	EVT_BUTTON(BUTTON_MINUS,		Button_Minus_Clicked)
	EVT_BUTTON(BUTTON_PLUS,			Button_Plus_Clicked)	
	EVT_BUTTON(BUTTON_SQRT,			Button_Sqrt_Clicked)
	EVT_BUTTON(BUTTON_PERCENTAGE,	Button_Percentage_Clicked)
	EVT_BUTTON(BUTTON_ONE_BY_X,		Button_OneByX_Clicked)
	EVT_BUTTON(BUTTON_EQUAL,		Button_Equal_Clicked)
	EVT_BUTTON(BUTTON_PLUS_MINUS,	Button_PlusMinus_Clicked)
	EVT_BUTTON(BUTTON_DOT,			Button_Dot_Clicked)
END_EVENT_TABLE()

/**
*********************************************************************
KalculatorFrame::KalculatorFrame

    KalculatorFrame default constructor.

    @param void
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
KalculatorFrame::KalculatorFrame() :
	wxFrame(
		(wxFrame*) NULL, 
		-1, 
		"", 
		wxDefaultPosition, 
		wxDefaultSize, 
		wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION, 
		""), 
	m_WIDTH(275), 
	m_HEIGHT(250), 
	m_TITLE("Kalculator"), 
	m_result("0"), 
	m_numberOne(0), 
	m_numberTwo(0), 
	m_lastClickedButton(NONE),
	m_lastClickedOperator(NONE), 
	m_lastClickedNumber(NONE), 
	m_lastClickedButtonType(NOTHING), 
	m_clipboard("0")
{
	wxFont font(10, wxMODERN, wxNORMAL, wxBOLD);
	//Button colors
	const		wxColour RED  (	150, 0,   0   );
	const		wxColour GREEN(	0,   150, 0   );
	const		wxColour BLUE (	0,   0,   150 );
	const short WIDGET_GAP	= 2;	//gap between widgets
	const short PANEL_GAP	= 6;	//gap between mainPanel and other panels

	this->SetSize(m_WIDTH, m_HEIGHT);
	this->CentreOnScreen();
	this->SetTitle(m_TITLE);

	//create and set menuBar////////////////////////////////////////////////////////////
	m_menuBar		= new wxMenuBar();
	
	m_editMenu		= new wxMenu();
	m_aboutMenu		= new wxMenu();

	m_copyMenuItem	= new wxMenuItem(m_editMenu, COPY_MENU_ITEM, "Copy");
	m_pasteMenuItem	= new wxMenuItem(m_editMenu, PASTE_MENU_ITEM, "Paste");

	m_editMenu->Append(m_copyMenuItem);
	m_editMenu->Append(m_pasteMenuItem);
	m_aboutMenu->Append(ABOUT_MENU_ITEM, "About...");
	
	m_menuBar->Append(m_editMenu, "Edit");
	m_menuBar->Append(m_aboutMenu, "Help");

	m_pasteMenuItem->Enable(false);
	
	this->SetMenuBar(m_menuBar);
	////////////////////////////////////////////////////////////////////////////////////

	//Create sizers
	wxBoxSizer*  pMainPanelSizer	= new wxBoxSizer(wxVERTICAL);
	wxBoxSizer*  pPanel_1_Sizer		= new wxBoxSizer(wxVERTICAL);
	wxGridSizer* pPanel_2_Sizer		= new wxGridSizer(1, 3, 0, 0);
	wxGridSizer* pPanel_3_Sizer		= new wxGridSizer(1, 5, 0, 0);
	wxGridSizer* pPanel_4_Sizer		= new wxGridSizer(1, 5, 0, 0);	
	wxGridSizer* pPanel_5_Sizer		= new wxGridSizer(1, 5, 0, 0);
	wxGridSizer* pPanel_6_Sizer		= new wxGridSizer(1, 5, 0, 0);

	//panels to hold widgets. First one is the top panel.
	wxPanel* pMainPanel				= new wxPanel(this);
	wxPanel* pPanel_1				= new wxPanel(pMainPanel);	
	wxPanel* pPanel_2				= new wxPanel(pMainPanel);	
	wxPanel* pPanel_3				= new wxPanel(pMainPanel);	
	wxPanel* pPanel_4				= new wxPanel(pMainPanel);	
	wxPanel* pPanel_5				= new wxPanel(pMainPanel);	
	wxPanel* pPanel_6				= new wxPanel(pMainPanel);

	//Panel coloring for debugging...
	//pPanel_1->SetBackgroundColour( wxColour(255, 0, 0) );
	//pPanel_2->SetBackgroundColour( wxColour(255, 255, 0) );
	//pPanel_3->SetBackgroundColour( wxColour(255, 255, 255) );
	//pPanel_4->SetBackgroundColour( wxColour(0, 255, 0) );
	//pPanel_5->SetBackgroundColour( wxColour(0, 0, 255) );
	//pPanel_6->SetBackgroundColour( wxColour(255, 0, 255) );

	//Widget contained in panel 1 //////////////////////////////////////////////////////
	m_display				= new wxStaticText(	pPanel_1, 
												STATICTEXT_DISPLAY, 
												"0", 
												wxDefaultPosition, 
												wxDefaultSize,
												wxST_NO_AUTORESIZE | wxSIMPLE_BORDER | wxTE_RIGHT);
	
	//Widgets contained in panel 2 /////////////////////////////////////////////////////
	m_button_Backspace		= new wxButton(pPanel_2, BUTTON_BACKSPACE, "Backspace");	
	m_button_Clear			= new wxButton(pPanel_2, BUTTON_CLEAR, "Clear");	
	m_button_CEL			= new wxButton(pPanel_2, BUTTON_CEL, "CEL");		

	//Widgets contained in panel 3 /////////////////////////////////////////////////////
	m_button_7				= new wxButton(pPanel_3, BUTTON_7, "7");
	m_button_8				= new wxButton(pPanel_3, BUTTON_8, "8");
	m_button_9				= new wxButton(pPanel_3, BUTTON_9, "9");
	m_button_Divide			= new wxButton(pPanel_3, BUTTON_DIVIDE, "/");	
	m_button_Sqrt			= new wxButton(pPanel_3, BUTTON_SQRT, "sqrt");
	
	//Widgets contained in panel 4 /////////////////////////////////////////////////////	
	m_button_4				= new wxButton(pPanel_4, BUTTON_4, "4");
	m_button_5				= new wxButton(pPanel_4, BUTTON_5, "5");
	m_button_6				= new wxButton(pPanel_4, BUTTON_6, "6");
	m_button_Multiply		= new wxButton(pPanel_4, BUTTON_MULTIPLY, "*");
	m_button_Percentage		= new wxButton(pPanel_4, BUTTON_PERCENTAGE, "%");
	
	//Widgets contained in panel 5 /////////////////////////////////////////////////////
	m_button_1				= new wxButton(pPanel_5, BUTTON_1, "1");
	m_button_2				= new wxButton(pPanel_5, BUTTON_2, "2");
	m_button_3				= new wxButton(pPanel_5, BUTTON_3, "3");
	m_button_Minus			= new wxButton(pPanel_5, BUTTON_MINUS, "-");
	m_button_OneByX			= new wxButton(pPanel_5, BUTTON_ONE_BY_X, "1/x");	
	
	//Widgets contained in panel 6 /////////////////////////////////////////////////////
	m_button_0				= new wxButton(pPanel_6, BUTTON_0, "0");
	m_button_PlusMinus		= new wxButton(pPanel_6, BUTTON_PLUS_MINUS, "+/-");
	m_button_Dot			= new wxButton(pPanel_6, BUTTON_DOT, ".");
	m_button_Plus			= new wxButton(pPanel_6, BUTTON_PLUS, "+");
	m_button_Equal			= new wxButton(pPanel_6, BUTTON_EQUAL, "=");

	//set buttons' fonts////////////////////////////////////////////////////////////////
	m_button_0->SetFont(font);
	m_button_1->SetFont(font);
	m_button_2->SetFont(font);
	m_button_3->SetFont(font);
	m_button_4->SetFont(font);
	m_button_5->SetFont(font);
	m_button_6->SetFont(font);
	m_button_7->SetFont(font);
	m_button_8->SetFont(font);
	m_button_9->SetFont(font);
	m_button_Backspace->SetFont(font);
	m_button_CEL->SetFont(font);
	m_button_Divide->SetFont(font);
	m_button_Multiply->SetFont(font);
	m_button_Plus->SetFont(font);
	m_button_Minus->SetFont(font);
	m_button_Equal->SetFont(font);
	m_button_Sqrt->SetFont(font);
	m_button_Percentage->SetFont(font);
	m_button_OneByX->SetFont(font);
	m_button_PlusMinus->SetFont(font);
	m_button_Dot->SetFont(font);
	m_button_Clear->SetFont(font);

	//change display's font//////////////////////////////////////////////////////////
	m_display->SetFont(font);

	//need this function call to fit the text in the m_pDisplay//////////////////////
	m_display->SetSize( m_display->GetBestSize() );

	//set widgets' colours///////////////////////////////////////////////////////////
	m_display->SetBackgroundColour( wxColour(255, 255, 255) );
	m_button_Backspace->SetForegroundColour(GREEN);
	m_button_Clear->SetForegroundColour(GREEN);
	m_button_CEL->SetForegroundColour(GREEN);
	m_button_0->SetForegroundColour(BLUE);			
	m_button_1->SetForegroundColour(BLUE);	
	m_button_2->SetForegroundColour(BLUE);			
	m_button_3->SetForegroundColour(BLUE);	
	m_button_4->SetForegroundColour(BLUE);			
	m_button_5->SetForegroundColour(BLUE);	
	m_button_6->SetForegroundColour(BLUE);			
	m_button_7->SetForegroundColour(BLUE);	
	m_button_8->SetForegroundColour(BLUE);			
	m_button_9->SetForegroundColour(BLUE);	
	m_button_Divide->SetForegroundColour(RED);		
	m_button_Multiply->SetForegroundColour(RED);	
	m_button_Plus->SetForegroundColour(RED);		
	m_button_Minus->SetForegroundColour(RED);	
	m_button_Equal->SetForegroundColour(RED);
	m_button_Sqrt->SetForegroundColour(GREEN);
	m_button_Percentage->SetForegroundColour(GREEN);
	m_button_OneByX->SetForegroundColour(GREEN);
	m_button_PlusMinus->SetForegroundColour(GREEN);
	m_button_Dot->SetForegroundColour(GREEN);

	//Add widgets to panel_1_Sizer///////////////////////////////////////////////////
	pPanel_1_Sizer->Add(m_display, 0, wxEXPAND | wxALL, WIDGET_GAP);
	//Add widgets to panel_2_Sizer///////////////////////////////////////////////////
	pPanel_2_Sizer->Add(m_button_Backspace, 1, wxEXPAND | wxALL, WIDGET_GAP);
	pPanel_2_Sizer->Add(m_button_Clear, 1, wxEXPAND | wxALL, WIDGET_GAP);
	pPanel_2_Sizer->Add(m_button_CEL, 1, wxEXPAND | wxALL, WIDGET_GAP);
	//Add widgets to panel_3_Sizer///////////////////////////////////////////////////
	pPanel_3_Sizer->Add(m_button_7, 1, wxEXPAND | wxALL, WIDGET_GAP);
	pPanel_3_Sizer->Add(m_button_8, 1, wxEXPAND | wxALL, WIDGET_GAP);
	pPanel_3_Sizer->Add(m_button_9, 1, wxEXPAND | wxALL, WIDGET_GAP);
	pPanel_3_Sizer->Add(m_button_Divide, 1, wxEXPAND | wxALL, WIDGET_GAP);
	pPanel_3_Sizer->Add(m_button_Sqrt, 1, wxEXPAND | wxALL, WIDGET_GAP);	
	//Add widgets to panel_4_Sizer///////////////////////////////////////////////////
	pPanel_4_Sizer->Add(m_button_4, 1, wxEXPAND | wxALL, WIDGET_GAP);
	pPanel_4_Sizer->Add(m_button_5, 1, wxEXPAND | wxALL, WIDGET_GAP);
	pPanel_4_Sizer->Add(m_button_6, 1, wxEXPAND | wxALL, WIDGET_GAP);
	pPanel_4_Sizer->Add(m_button_Multiply, 1, wxEXPAND | wxALL, WIDGET_GAP);
	pPanel_4_Sizer->Add(m_button_Percentage, 1, wxEXPAND | wxALL, WIDGET_GAP);	
	//Add widgets to panel_5_Sizer///////////////////////////////////////////////////
	pPanel_5_Sizer->Add(m_button_1, 1, wxEXPAND | wxALL, WIDGET_GAP);
	pPanel_5_Sizer->Add(m_button_2, 1, wxEXPAND | wxALL, WIDGET_GAP);
	pPanel_5_Sizer->Add(m_button_3, 1, wxEXPAND | wxALL, WIDGET_GAP);
	pPanel_5_Sizer->Add(m_button_Minus, 1, wxEXPAND | wxALL, WIDGET_GAP);
	pPanel_5_Sizer->Add(m_button_OneByX, 1, wxEXPAND | wxALL, WIDGET_GAP);	
	//Add widgets to panel_6_Sizer///////////////////////////////////////////////////
	pPanel_6_Sizer->Add(m_button_0, 1, wxEXPAND | wxALL, WIDGET_GAP);
	pPanel_6_Sizer->Add(m_button_PlusMinus, 1, wxEXPAND | wxALL, WIDGET_GAP);
	pPanel_6_Sizer->Add(m_button_Dot, 1, wxEXPAND | wxALL, WIDGET_GAP);
	pPanel_6_Sizer->Add(m_button_Plus, 1, wxEXPAND | wxALL, WIDGET_GAP);
	pPanel_6_Sizer->Add(m_button_Equal, 1, wxEXPAND | wxALL, WIDGET_GAP);	
	//Add panels to mainPanelSizer///////////////////////////////////////////////////
	pMainPanelSizer->Add(pPanel_1, 1, wxTOP | wxLEFT | wxRIGHT | wxEXPAND, PANEL_GAP);
	pMainPanelSizer->Add(pPanel_2, 1, wxLEFT | wxRIGHT | wxEXPAND, PANEL_GAP);
	pMainPanelSizer->Add(pPanel_3, 1, wxLEFT | wxRIGHT | wxEXPAND, PANEL_GAP);
	pMainPanelSizer->Add(pPanel_4, 1, wxLEFT | wxRIGHT | wxEXPAND, PANEL_GAP);
	pMainPanelSizer->Add(pPanel_5, 1, wxLEFT | wxRIGHT | wxEXPAND, PANEL_GAP);
	pMainPanelSizer->Add(pPanel_6, 1, wxBOTTOM | wxLEFT | wxRIGHT | wxEXPAND, PANEL_GAP);
	
	//Set sizers/////////////////////////////////////////////////////////////////////
	pMainPanel->SetSizer(pMainPanelSizer);
	pPanel_1->SetSizer(pPanel_1_Sizer);
	pPanel_2->SetSizer(pPanel_2_Sizer);
	pPanel_3->SetSizer(pPanel_3_Sizer);
	pPanel_4->SetSizer(pPanel_4_Sizer);
	pPanel_5->SetSizer(pPanel_5_Sizer);
	pPanel_6->SetSizer(pPanel_6_Sizer);

	m_CEL_Viewer = new CEL_Viewer(this, this->GetSize(), "CEL");	
}

/**
*********************************************************************
KalculatorFrame::~KalculatorFrame

    KalculatorFrame destructor.

    @param void
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
KalculatorFrame::~KalculatorFrame()
{
}


////////////////////////////////////////////////////////////////////////////////////
//START: Event handling functions.//////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


/**
*********************************************************************
KalculatorFrame::CopyMenuItemClicked

    Event handling function for 'Copy' menu item click. Copies the text in display into 
	Kalculator's clipboard, not system clipboard!

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::CopyMenuItemClicked(wxCommandEvent& event)
{
	m_clipboard = GetDisplay_wxString();

	if(m_pasteMenuItem->IsEnabled() == false)
	{
		m_pasteMenuItem->Enable(true);
	}

	//////////////////////////////////////////////////////////////////////////////////
	//log the event
	m_CEL_Viewer->mCEL.AddLogSameLine("Value copied to clipboard: ");
	m_CEL_Viewer->mCEL.AddLogSameLine(m_clipboard);
	m_CEL_Viewer->mCEL.AddLogNewLine("");
	//display the event
	m_CEL_Viewer->SetDisplay( m_CEL_Viewer->mCEL.GetCEL() );
	m_CEL_Viewer->ShowLastEnteredLog();
	//////////////////////////////////////////////////////////////////////////////////

	SetLastClickedButton(COPY_MENU_ITEM);
	SetLastClickedButtonType(MENU_ITEM);
}

/**
*********************************************************************
KalculatorFrame::PasteMenuItemClicked

    Event handling function for 'Paste' menu item click. Pastes Kalculator's clipboard's (not the system 
	clipboard) buffer to display.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::PasteMenuItemClicked(wxCommandEvent& event)
{
	SetDisplay(m_clipboard);

	//////////////////////////////////////////////////////////////////////////////////
	//log the event
	m_CEL_Viewer->mCEL.AddLogSameLine("Value pasted from clipboard: ");
	m_CEL_Viewer->mCEL.AddLogSameLine(m_clipboard);
	m_CEL_Viewer->mCEL.AddLogNewLine("");
	//display the event
	m_CEL_Viewer->SetDisplay( m_CEL_Viewer->mCEL.GetCEL() );
	m_CEL_Viewer->ShowLastEnteredLog();
	//////////////////////////////////////////////////////////////////////////////////

	SetLastClickedButton(PASTE_MENU_ITEM);
	SetLastClickedButtonType(MENU_ITEM);
}

/**
*********************************************************************
KalculatorFrame::AboutMenuItemClicked

    Event handling function for 'About' menu item click. Displays an About dialog box.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::AboutMenuItemClicked(wxCommandEvent& event)
{
	KalculatorUtils::ShowDialog(this, 
								ABOUT_MSG, 
								"About Kalculator...", 
								wxOK | wxICON_INFORMATION | wxCENTRE);

	SetLastClickedButton(ABOUT_MENU_ITEM);
	SetLastClickedButtonType(MENU_ITEM);
}

/**
*********************************************************************
KalculatorFrame::Button_1_Clicked

    Event handling function for '1' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_1_Clicked(wxCommandEvent& event)
{
	NumberButtonClicked(1);
}

/**
*********************************************************************
KalculatorFrame::Button_2_Clicked

    Event handling function for '2' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_2_Clicked(wxCommandEvent& event)
{
	NumberButtonClicked(2);
}

/**
*********************************************************************
KalculatorFrame::Button_3_Clicked

    Event handling function for '3' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_3_Clicked(wxCommandEvent& event)
{
	NumberButtonClicked(3);
}

/**
*********************************************************************
KalculatorFrame::Button_4_Clicked

    Event handling function for '4' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_4_Clicked(wxCommandEvent& event)
{
	NumberButtonClicked(4);
}

/**
*********************************************************************
KalculatorFrame::Button_5_Clicked

    Event handling function for '5' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_5_Clicked(wxCommandEvent& event)
{
	NumberButtonClicked(5);
}

/**
*********************************************************************
KalculatorFrame::Button_6_Clicked

    Event handling function for '6' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_6_Clicked(wxCommandEvent& event)
{
	NumberButtonClicked(6);
}

/**
*********************************************************************
KalculatorFrame::Button_7_Clicked

    Event handling function for '7' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_7_Clicked(wxCommandEvent& event)
{
	NumberButtonClicked(7);
}

/**
*********************************************************************
KalculatorFrame::Button_8_Clicked

    Event handling function for '8' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_8_Clicked(wxCommandEvent& event)
{
	NumberButtonClicked(8);
}

/**
*********************************************************************
KalculatorFrame::Button_9_Clicked

    Event handling function for '9' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_9_Clicked(wxCommandEvent& event)
{
	NumberButtonClicked(9);
}

/**
*********************************************************************
KalculatorFrame::Button_0_Clicked

    Event handling function for '0' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_0_Clicked(wxCommandEvent& event)
{
	NumberButtonClicked(0);
}


/**
*********************************************************************
KalculatorFrame::Button_Backspace_Clicked

    Event handling function for 'Backspace' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_Backspace_Clicked(wxCommandEvent& event)
{
	if(GetDisplay_wxString() != "0")
	{
		m_result.RemoveLast();

		if(		m_result == "" 
			||	m_result == "-")
		{
			m_result = "0";
		}

		SetDisplay(m_result);

		SetLastClickedButton(BUTTON_BACKSPACE);
		SetLastClickedButtonType(OTHER);
	}
}


/**
*********************************************************************
KalculatorFrame::Button_Clear_Clicked

    Event handling function for 'Clear' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_Clear_Clicked(wxCommandEvent& event)
{
	ClearDisplay();
	m_result = "0";
	m_numberOne = 0;
	m_numberTwo = 0;
	SetDisplay(0);

	//////////////////////////////////////////////////////////////////////////////////
	//log the event
	m_CEL_Viewer->mCEL.AddLogSameLine( "Kalculator display cleared." );
	m_CEL_Viewer->mCEL.AddLogNewLine("");
	//display the event
	m_CEL_Viewer->SetDisplay( m_CEL_Viewer->mCEL.GetCEL() );
	m_CEL_Viewer->ShowLastEnteredLog();
	//////////////////////////////////////////////////////////////////////////////////

	SetLastClickedButton(BUTTON_CLEAR);
	SetLastClickedButtonType(OTHER);
}


/**
*********************************************************************
KalculatorFrame::Button_CEL_Clicked

    Event handling function for 'CEL' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_CEL_Clicked(wxCommandEvent& event)
{
	if(m_CEL_Viewer->IsShown() == false)
	{
		m_CEL_Viewer->Show(true);

		SetLastClickedButton(BUTTON_CEL);
		SetLastClickedButtonType(OTHER);
	}
}


/**
*********************************************************************
KalculatorFrame::Button_Divide_Clicked

    Event handling function for '/' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_Divide_Clicked(wxCommandEvent& event)
{
	OperatorButtonClicked(BUTTON_DIVIDE);
}


/**
*********************************************************************
KalculatorFrame::Button_Multiply_Clicked

    Event handling function for '*' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_Multiply_Clicked(wxCommandEvent& event)
{
	OperatorButtonClicked(BUTTON_MULTIPLY);
}


/**
*********************************************************************
KalculatorFrame::Button_Plus_Clicked

    Event handling function for '+' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_Plus_Clicked(wxCommandEvent& event)
{
	OperatorButtonClicked(BUTTON_PLUS);
}


/**
*********************************************************************
KalculatorFrame::Button_Minus_Clicked

    Event handling function for '-' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_Minus_Clicked(wxCommandEvent& event)
{
	OperatorButtonClicked(BUTTON_MINUS);
}


/**
*********************************************************************
KalculatorFrame::Button_Sqrt_Clicked

    Event handling function for 'sqrt' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_Sqrt_Clicked(wxCommandEvent& event)
{
	if(GetDisplay_long_double() >= 0)
	{
		SetDisplay( sqrt(GetDisplay_long_double()) );
		m_result = GetDisplay_wxString();

		//////////////////////////////////////////////////////////////////////////////////
		//log the event
		m_CEL_Viewer->mCEL.AddLogSameLine( "sqrt(" );
		m_CEL_Viewer->mCEL.AddLogSameLine( GetDisplay_long_double() * GetDisplay_long_double() );
		m_CEL_Viewer->mCEL.AddLogSameLine( ") = " );
		m_CEL_Viewer->mCEL.AddLogSameLine( GetDisplay_wxString() );
		m_CEL_Viewer->mCEL.AddLogNewLine("");
		//display the event
		m_CEL_Viewer->SetDisplay( m_CEL_Viewer->mCEL.GetCEL() );
		m_CEL_Viewer->ShowLastEnteredLog();
		//////////////////////////////////////////////////////////////////////////////////

		SetLastClickedButton(BUTTON_SQRT);
		SetLastClickedButtonType(OTHER);
	}
	if (GetDisplay_long_double() < 0)
	{
		KalculatorUtils::ShowDialog(this, 
									SQRT_MSG,
									"Kalculator", 
									wxOK | wxICON_EXCLAMATION | wxCENTRE);

		//////////////////////////////////////////////////////////////////////////////////
		//log the event
		m_CEL_Viewer->mCEL.AddLogSameLine("Invalid function input. Square root of negative numbers cannot be taken.");
		m_CEL_Viewer->mCEL.AddLogNewLine("");
		//display the event
		m_CEL_Viewer->SetDisplay( m_CEL_Viewer->mCEL.GetCEL() );
		m_CEL_Viewer->ShowLastEnteredLog();
		//////////////////////////////////////////////////////////////////////////////////
	}
}


/**
*********************************************************************
KalculatorFrame::Button_Percentage_Clicked

    Event handling function for '%' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_Percentage_Clicked(wxCommandEvent& event)
{
	if(GetLastClickedButton() != BUTTON_PERCENTAGE)
	{
		m_numberTwo = GetDisplay_long_double();

		SetDisplay( (m_numberOne*m_numberTwo) / 100 );
		m_result = GetDisplay_wxString();

		//////////////////////////////////////////////////////////////////////////////////
		//log the event
		m_CEL_Viewer->mCEL.AddLogSameLine(m_numberOne);
		m_CEL_Viewer->mCEL.AddLogSameLine(" % ");
		m_CEL_Viewer->mCEL.AddLogSameLine(m_numberTwo);
		m_CEL_Viewer->mCEL.AddLogSameLine(" = ");
		m_CEL_Viewer->mCEL.AddLogSameLine( GetDisplay_wxString() );
		m_CEL_Viewer->mCEL.AddLogNewLine("");
		//display the event
		m_CEL_Viewer->SetDisplay( m_CEL_Viewer->mCEL.GetCEL() );
		m_CEL_Viewer->ShowLastEnteredLog();
		//////////////////////////////////////////////////////////////////////////////////

		SetLastClickedButton(BUTTON_PERCENTAGE);
		SetLastClickedButtonType(OTHER);
	}
}


/**
*********************************************************************
KalculatorFrame::Button_OneByX_Clicked

    Event handling function for '1/x' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_OneByX_Clicked(wxCommandEvent& event)
{
	if(GetDisplay_long_double() == 0)
	{
		KalculatorUtils::ShowDialog(this, 
									DIVIDE_BY_ZERO_MSG,
									"Kalculator", 
									wxOK | wxICON_EXCLAMATION | wxCENTRE);

		//////////////////////////////////////////////////////////////////////////////////
		//log the event
		m_CEL_Viewer->mCEL.AddLogSameLine("Invalid function input. Cannot divide by 0.");
		m_CEL_Viewer->mCEL.AddLogNewLine("");
		//display the event
		m_CEL_Viewer->SetDisplay( m_CEL_Viewer->mCEL.GetCEL() );
		m_CEL_Viewer->ShowLastEnteredLog();
		//////////////////////////////////////////////////////////////////////////////////
	}
	else
	{
		SetDisplay( 1 / GetDisplay_long_double() );
	
		m_result = GetDisplay_wxString();

		//////////////////////////////////////////////////////////////////////////////////
		//log the event
		m_CEL_Viewer->mCEL.AddLogSameLine("1 / ");
		m_CEL_Viewer->mCEL.AddLogSameLine( 1 / GetDisplay_long_double() );
		m_CEL_Viewer->mCEL.AddLogSameLine(" = ");
		m_CEL_Viewer->mCEL.AddLogSameLine( GetDisplay_wxString() );
		m_CEL_Viewer->mCEL.AddLogNewLine("");
		//display the event
		m_CEL_Viewer->SetDisplay( m_CEL_Viewer->mCEL.GetCEL() );
		m_CEL_Viewer->ShowLastEnteredLog();
		//////////////////////////////////////////////////////////////////////////////////
		
		SetLastClickedButton(BUTTON_ONE_BY_X);
		SetLastClickedButtonType(OTHER);
	}
}


/**
*********************************************************************
KalculatorFrame::Button_Equal_Clicked

    Event handling function for '=' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_Equal_Clicked(wxCommandEvent& event)
{
	if(	   GetLastClickedButtonType() == NUMBER 
		|| GetLastClickedButton()	  == BUTTON_EQUAL 
		|| GetLastClickedButton()	  == BUTTON_PERCENTAGE 
		|| GetLastClickedButton()	  == COPY_MENU_ITEM 
		|| GetLastClickedButton()	  == PASTE_MENU_ITEM)
	{
		Button operatorButton = GetLastClickedOperator();

		if(GetLastClickedButtonType() == NUMBER)	//normal calculation: 4+2=6
		{
			m_numberTwo = GetDisplay_long_double();
		}
		
		if(GetLastClickedButton() == BUTTON_EQUAL)	//fast calculation:	4+2=8=10=12=14...
		{
			m_numberOne = GetDisplay_long_double();
		}
		
		if(GetLastClickedButton() == BUTTON_PERCENTAGE)
		{
			m_numberTwo = GetDisplay_long_double();
		}
		
		if(	   GetLastClickedButton() == COPY_MENU_ITEM 
			|| GetLastClickedButton() == PASTE_MENU_ITEM)
		{
			m_numberTwo = GetDisplay_long_double();
		}		

		switch(operatorButton)
		{
		case BUTTON_PLUS:
			SetDisplay(m_numberOne + m_numberTwo);
			LogBasicOperation(BUTTON_PLUS);
			break;
		case BUTTON_MINUS:
			SetDisplay(m_numberOne - m_numberTwo);
			LogBasicOperation(BUTTON_MINUS);
			break;
		case BUTTON_MULTIPLY:
			SetDisplay(m_numberOne * m_numberTwo);
			LogBasicOperation(BUTTON_MULTIPLY);
			break;
		case BUTTON_DIVIDE:
			if(m_numberTwo == 0)
			{
				KalculatorUtils::ShowDialog(this, 
											DIVIDE_BY_ZERO_MSG,
											"Kalculator", 
											wxOK | wxICON_EXCLAMATION | wxCENTRE);
				
				//this block is same as Clear_Button_Clicked except for 
				//logging event and logging last clicked button
				ClearDisplay();
				m_result = "0";
				m_numberOne = 0;
				m_numberTwo = 0;
				SetDisplay(0);

				//////////////////////////////////////////////////////////////////////////////////
				//log the event
				m_CEL_Viewer->mCEL.AddLogSameLine("Invalid function input. Cannot divide by 0.");
				m_CEL_Viewer->mCEL.AddLogNewLine("");
				//display the event
				m_CEL_Viewer->SetDisplay( m_CEL_Viewer->mCEL.GetCEL() );
				m_CEL_Viewer->ShowLastEnteredLog();
				//////////////////////////////////////////////////////////////////////////////////
				
				break;
			}
			else
			{
				SetDisplay(m_numberOne / m_numberTwo);
				LogBasicOperation(BUTTON_DIVIDE);
				break;
			}
		default:
			try
			{
				throw KalculatorException(__FILE__, __LINE__);
			}
			catch(...)
			{
				//decide what to do?
			}
		}//end of switch

		m_result = GetDisplay_wxString();
		SetLastClickedButton(BUTTON_EQUAL);
		SetLastClickedButtonType(OTHER);
	}
}


/**
*********************************************************************
KalculatorFrame::Button_PlusMinus_Clicked

    Event handling function for '+/-' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_PlusMinus_Clicked(wxCommandEvent& event)
{
	SetDisplay( GetDisplay_long_double() * (-1) );
	
	m_result = GetDisplay_wxString();

	//////////////////////////////////////////////////////////////////////////////////
	//log the event
	m_CEL_Viewer->mCEL.AddLogSameLine( GetDisplay_long_double() * (-1) );
	m_CEL_Viewer->mCEL.AddLogSameLine(" * -1 = ");
	m_CEL_Viewer->mCEL.AddLogSameLine( GetDisplay_wxString() );
	m_CEL_Viewer->mCEL.AddLogNewLine("");
	//display the event
	m_CEL_Viewer->SetDisplay( m_CEL_Viewer->mCEL.GetCEL() );
	m_CEL_Viewer->ShowLastEnteredLog();
	//////////////////////////////////////////////////////////////////////////////////

	SetLastClickedButton(BUTTON_PLUS_MINUS);
	SetLastClickedButtonType(OTHER);
}


/**
*********************************************************************
KalculatorFrame::Button_Dot_Clicked

    Event handling function for '.' button click.

    @param  wxCommandEvent&		Used by the framework.
    @return N/A
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::Button_Dot_Clicked(wxCommandEvent& event)
{
	if(KalculatorUtils::IsFloating( GetDisplay_wxString() ) == false)
	{
		m_result = GetDisplay_wxString() + ".";
		SetDisplay(m_result);

		SetLastClickedButton(BUTTON_DOT);
		SetLastClickedButtonType(OTHER);
	}
}


////////////////////////////////////////////////////////////////////////////////////
//END: Event handling functions.////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////
//START: Functions to keep history of clicked buttons.///////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


/**
*********************************************************************
KalculatorFrame::GetLastClickedButton

    Returns the last clicked button.

    @param  void
    @return KalculatorFrame::Button		Enumerated constant for returned button.
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
KalculatorFrame::Button KalculatorFrame::GetLastClickedButton() const
{
	return m_lastClickedButton;
}

/**
*********************************************************************
KalculatorFrame::GetLastClickedNumber

    Returns the last clicked number button.

    @param  void
    @return KalculatorFrame::Button		Enumerated constant for returned number button.
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
KalculatorFrame::Button KalculatorFrame::GetLastClickedNumber() const
{
	return m_lastClickedNumber;
}

/**
*********************************************************************
KalculatorFrame::GetLastClickedOperator

    Returns the last clicked operator button.

    @param  void
    @return KalculatorFrame::Button		Enumerated constant for returned operator button.
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
KalculatorFrame::Button KalculatorFrame::GetLastClickedOperator() const
{
	return m_lastClickedOperator;
}

/**
*********************************************************************
KalculatorFrame::LastClickedButtonType

    Returns the last clicked button type.

    @param  void
    @return KalculatorFrame::LastClickedButtonType		Enumerated constant for last clicked button type.
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
KalculatorFrame::LastClickedButtonType KalculatorFrame::GetLastClickedButtonType() const
{
	return m_lastClickedButtonType;
}

/**
*********************************************************************
KalculatorFrame::SetLastClickedButton

    Sets the last clicked button.

    @param  KalculatorFrame::Button&		Enumerated constant for returned button.
    @return void
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::SetLastClickedButton(const KalculatorFrame::Button& button)
{
	m_lastClickedButton = button;
}


/**
*********************************************************************
KalculatorFrame::SetLastClickedNumber

    Sets the last clicked number button to specified button.

    @param  const KalculatorFrame::Button&		Enumerated constant to set.
    @return void
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::SetLastClickedNumber(const KalculatorFrame::Button& button)
{
	m_lastClickedNumber = button;
}


/**
*********************************************************************
KalculatorFrame::SetLastClickedOperator

    Sets the last clicked operator button to specified button.

    @param  const KalculatorFrame::Button&		Enumerated constant to set.
    @return void
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::SetLastClickedOperator(const KalculatorFrame::Button& button)
{
	m_lastClickedOperator = button;
}


/**
*********************************************************************
KalculatorFrame::SetLastClickedButtonType

    Sets the last clicked button type to specified operator button type.

    @param  const KalculatorFrame::LastClickedButtonType&		Enumerated constant to set.
    @return void
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::SetLastClickedButtonType(const LastClickedButtonType& buttonType)
{
	m_lastClickedButtonType = buttonType;
}


/////////////////////////////////////////////////////////////////////////////////////
//END: Functions to keep history of clicked buttons./////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


/**
*********************************************************************
KalculatorFrame::GetDisplay_wxString

    Returns Kalculator's display in string format.

    @param  void
    @return wxString		Kalculator's display in wxString format.
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
wxString KalculatorFrame::GetDisplay_wxString() const
{
	return m_display->GetLabel();
}


/**
*********************************************************************
KalculatorFrame::GetDisplay_long_double

    Returns Kalculator's display in long double format.

    @param  void
    @return wxString		Kalculator's display in long double format.
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
long double KalculatorFrame::GetDisplay_long_double() const
{	
	try
	{
		return (long double) atof( m_display->GetLabel() );
	}
	catch(...)
	{
		//An exception will never be thrown. Because all possible arguments to atof() are valid. 
		//Assuming n is the number on the display; it can be in the following forms of display:  
		//	n, -n, n., n.n		For example: 1, -2, 3., 4.5
		//All versions of n can be safely passed to atof(). Therefore atof() will return safely.
		KalculatorUtils::ShowDialog((wxWindow*) NULL,	//not using 'this' because this is const function 
									EXCEPTION_MSG,
									"Kalculator", 
									wxOK | wxICON_ERROR | wxCENTRE);

		//////////////////////////////////////////////////////////////////////////////////
		//log the event
		m_CEL_Viewer->mCEL.AddLogSameLine("Unhandled Exception.");
		m_CEL_Viewer->mCEL.AddLogNewLine("");
		//display the event
		m_CEL_Viewer->SetDisplay( m_CEL_Viewer->mCEL.GetCEL() );
		m_CEL_Viewer->ShowLastEnteredLog();
		//////////////////////////////////////////////////////////////////////////////////

		return 0;
	}
}


/**
*********************************************************************
KalculatorFrame::SetDisplay

    Sets Kalculator's display to specified string.

    @param  const wxString&		String to set Kalculator's display.
    @return void
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::SetDisplay(const wxString& result)
{
	m_display->SetLabel(result);
}


/**
*********************************************************************
KalculatorFrame::SetDisplay

    Sets Kalculator's display to specified string.

    @param  const long double&		long double to set Kalculator's display.
    @return void
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::SetDisplay(const long double& result)
{
	try
	{
		ostringstream oStream;
		oStream << result;

		wxString result_wxString( oStream.str().c_str() );
		m_display->SetLabel(result_wxString);

		oStream.flush();
	}
	catch (...)
	{
		//An exception will never be thrown. SetDisplay() is always called with valid arguments, so far.
		KalculatorUtils::ShowDialog(this, 
									EXCEPTION_MSG,
									"Kalculator", 
									wxOK | wxICON_ERROR | wxCENTRE);

		//////////////////////////////////////////////////////////////////////////////////
		//log the event
		m_CEL_Viewer->mCEL.AddLogSameLine("Unhandled Exception.");
		m_CEL_Viewer->mCEL.AddLogNewLine("");
		//display the event
		m_CEL_Viewer->SetDisplay( m_CEL_Viewer->mCEL.GetCEL() );
		m_CEL_Viewer->ShowLastEnteredLog();
		//////////////////////////////////////////////////////////////////////////////////
	}
}


/**
*********************************************************************
KalculatorFrame::NumberButtonClicked

    Routine to follow when a number button is clicked.

    @param  const unsigned short&		Number of the clicked button.
    @return void
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::NumberButtonClicked(const unsigned short& number)
{
	if(		number >= 0 
		&&	number <= 9)
	{
		wxString number_wxString;
		Button button;

		switch(number)
		{
		case 0:
			number_wxString = "0";
			button = BUTTON_0;
			break;
		case 1:
			number_wxString = "1";
			button = BUTTON_1;
			break;	
		case 2:
			number_wxString = "2";
			button = BUTTON_2;
			break;	
		case 3:
			number_wxString = "3";
			button = BUTTON_3;
			break;	
		case 4:
			number_wxString = "4";
			button = BUTTON_4;
			break;	
		case 5:
			number_wxString = "5";
			button = BUTTON_5;
			break;	
		case 6:
			number_wxString = "6";
			button = BUTTON_6;
			break;	
		case 7:
			number_wxString = "7";
			button = BUTTON_7;
			break;	
		case 8:
			number_wxString = "8";
			button = BUTTON_8;
			break;	
		case 9:
			number_wxString = "9";
			button = BUTTON_9;
			break;
		default:
			try
			{
				throw KalculatorException(__FILE__, __LINE__);
			}
			catch(...)
			{
				//decide what to do?
			}
		}

		if(		GetLastClickedButtonType() == OPERATOR 
			||	GetLastClickedButton() == NONE 
			||			(  GetLastClickedButton() == BUTTON_SQRT 
						|| GetLastClickedButton() == BUTTON_PERCENTAGE 
						|| GetLastClickedButton() == BUTTON_ONE_BY_X 
						|| GetLastClickedButton() == BUTTON_PLUS_MINUS 
						|| GetLastClickedButton() == BUTTON_EQUAL) )
		{
			m_result = number_wxString;
			SetDisplay(m_result);
		}
		else
		{
			if(		GetLastClickedButtonType() == NUMBER 
				||	GetLastClickedButtonType() == OTHER 
				||	GetLastClickedButtonType() == MENU_ITEM)
			{
				if(		number					== 0 
					&&	GetDisplay_wxString()	== "0")
				{
					m_result = "0";
					SetDisplay(m_result);
				}
				else
				{
					if( (GetDisplay_wxString() == "0") )
					{
						m_result = number_wxString;
						SetDisplay(m_result);
					}
					else
					{
						if( (GetDisplay_wxString() != "0") )
						{
							m_result = GetDisplay_wxString() + number_wxString;
							SetDisplay(m_result);
						}
					}
				}
			}
		}

		SetLastClickedButton(button);
		SetLastClickedNumber(button);
		SetLastClickedButtonType(NUMBER);
	}
}


/**
*********************************************************************
KalculatorFrame::OperatorButtonClicked

    Routine to follow when an operator button is clicked.

    @param  const Button&		Operator button clicked.
    @return void
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::OperatorButtonClicked(const Button& button)
{
	m_numberOne = GetDisplay_long_double();

	switch(button)
	{
	case BUTTON_PLUS:
		SetLastClickedOperator(BUTTON_PLUS);
		SetLastClickedButton(BUTTON_PLUS);
		break;
	case BUTTON_MINUS:
		SetLastClickedOperator(BUTTON_MINUS);
		SetLastClickedButton(BUTTON_MINUS);
		break;
	case BUTTON_MULTIPLY:
		SetLastClickedOperator(BUTTON_MULTIPLY);
		SetLastClickedButton(BUTTON_MULTIPLY);
		break;
	case BUTTON_DIVIDE:
		SetLastClickedOperator(BUTTON_DIVIDE);
		SetLastClickedButton(BUTTON_DIVIDE);
		break;
	default:
		try
		{
			throw KalculatorException(__FILE__, __LINE__);
		}
		catch(...)
		{
			//decide what to do?
		}
	}

	SetLastClickedButtonType(OPERATOR);
}


/**
*********************************************************************
KalculatorFrame::ClearDisplay

    Clears Kalculator's display.

    @param  void
    @return void
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::ClearDisplay()
{
	m_display->Clear();
}


/**
*********************************************************************
KalculatorFrame::LogBasicOperation

    Logs the event to CEL.

    @param  const Button&		Button which generated the event to be logged.
    @return void
    @throw  N/A


Revision History
	- 01MAY04-BCC	Initial	creation
*********************************************************************/
void KalculatorFrame::LogBasicOperation(const Button& operatorButton)
{
	m_CEL_Viewer->mCEL.AddLogSameLine(m_numberOne);

	switch(operatorButton)
	{
	case BUTTON_PLUS:		 
		m_CEL_Viewer->mCEL.AddLogSameLine(" + ");
		m_CEL_Viewer->mCEL.AddLogSameLine(m_numberTwo);
		m_CEL_Viewer->mCEL.AddLogSameLine(" = ");
		m_CEL_Viewer->mCEL.AddLogSameLine(m_numberOne + m_numberTwo);
		break;
	case BUTTON_MINUS:
		m_CEL_Viewer->mCEL.AddLogSameLine(" - ");
		m_CEL_Viewer->mCEL.AddLogSameLine(m_numberTwo);
		m_CEL_Viewer->mCEL.AddLogSameLine(" = ");
		m_CEL_Viewer->mCEL.AddLogSameLine(m_numberOne - m_numberTwo);
		break;
	case BUTTON_MULTIPLY:
		m_CEL_Viewer->mCEL.AddLogSameLine(" * ");
		m_CEL_Viewer->mCEL.AddLogSameLine(m_numberTwo);
		m_CEL_Viewer->mCEL.AddLogSameLine(" = ");
		m_CEL_Viewer->mCEL.AddLogSameLine(m_numberOne * m_numberTwo);
		break;
	case BUTTON_DIVIDE:
		m_CEL_Viewer->mCEL.AddLogSameLine(" / ");
		m_CEL_Viewer->mCEL.AddLogSameLine(m_numberTwo);
		m_CEL_Viewer->mCEL.AddLogSameLine(" = ");
		m_CEL_Viewer->mCEL.AddLogSameLine(m_numberOne / m_numberTwo);
		break;
	default:
		try
		{
			throw KalculatorException(__FILE__, __LINE__);
		}
		catch(...)
		{
			//decide what to do?
		}
	}

	m_CEL_Viewer->mCEL.AddLogNewLine("");
	//set log to the display of the CEL_Frame
	m_CEL_Viewer->SetDisplay( m_CEL_Viewer->mCEL.GetCEL() );
	m_CEL_Viewer->ShowLastEnteredLog();
}