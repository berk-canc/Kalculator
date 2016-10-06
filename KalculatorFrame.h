/**
*********************************************************************
KalculatorFrame.h
	@author		Berk Can Celebisoy (berkcan@ureach.com) -- BCC

	Header file	for	KalculatorFrame class.


Revision History
	- 01MAY04-BCC	Initial	creation

 Copyright (c) 2005	Berk C. Celebisoy, All Rights Reserved.
*********************************************************************/

#ifndef KALCULATOR_FRAME_H
#define KALCULATOR_FRAME_H
#include "wx/wxprec.h"
#include "CEL_Viewer.h"
#include "CEL.h"

class KalculatorFrame : public wxFrame
{
public:
	KalculatorFrame();
	virtual ~KalculatorFrame();

private:
	DECLARE_EVENT_TABLE()

//Variables needed to create GUI/////////////////////////////////////////////////////
	enum Button
	{
		ABOUT_MENU_ITEM, 
		COPY_MENU_ITEM, 
		PASTE_MENU_ITEM,
		BUTTON_1, 
		BUTTON_2, 
		BUTTON_3, 
		BUTTON_4, 
		BUTTON_5,
		BUTTON_6, 
		BUTTON_7, 
		BUTTON_8, 
		BUTTON_9, 
		BUTTON_0,
		BUTTON_PLUS, 
		BUTTON_MINUS, 
		BUTTON_DIVIDE, 
		BUTTON_MULTIPLY,
		BUTTON_SQRT, 
		BUTTON_PERCENTAGE, 
		BUTTON_ONE_BY_X, 
		BUTTON_EQUAL,
		BUTTON_DOT, 
		BUTTON_PLUS_MINUS, 
		BUTTON_BACKSPACE, 
		BUTTON_CLEAR,
		BUTTON_CEL, 
		STATICTEXT_DISPLAY, 
		NONE
	};

	KalculatorFrame(const KalculatorFrame& kalcFrm);			//not implemented as per design
	KalculatorFrame operator=(const KalculatorFrame& kalcFrm);	//not implemented as per design

	wxMenuBar*		m_menuBar;
	wxMenu*			m_aboutMenu;
	wxMenu*			m_editMenu;
	wxMenuItem*		m_copyMenuItem;
	wxMenuItem*		m_pasteMenuItem;
	wxStaticText*	m_display;

	//				<BUTTON NAME>			<BUTTON TYPE>
	wxButton*		m_button_1;				//NUMBER			
	wxButton*		m_button_2;				//NUMBER	
	wxButton*		m_button_3;				//NUMBER			
	wxButton*		m_button_4;				//NUMBER	
	wxButton*		m_button_5;				//NUMBER			
	wxButton*		m_button_6;				//NUMBER	
	wxButton*		m_button_7;				//NUMBER			
	wxButton*		m_button_8;				//NUMBER	
	wxButton*		m_button_9;				//NUMBER			
	wxButton*		m_button_0;				//NUMBER
	wxButton*		m_button_Plus;			//OPERATOR
	wxButton*		m_button_Minus;			//OPERATOR
	wxButton*		m_button_Divide;		//OPERATOR
	wxButton*		m_button_Multiply;		//OPERATOR
	wxButton*		m_button_Sqrt;			//OTHER
	wxButton*		m_button_Percentage;	//OTHER
	wxButton*		m_button_OneByX;		//OTHER
	wxButton*		m_button_Equal;			//OTHER
	wxButton*		m_button_Dot;			//OTHER
	wxButton*		m_button_PlusMinus;		//OTHER
	wxButton*		m_button_Backspace;		//OTHER	
	wxButton*		m_button_Clear;			//OTHER
	wxButton*		m_button_CEL;			//OTHER

	CEL_Viewer*		m_CEL_Viewer;
	const char*		m_TITLE;
	const short		m_WIDTH;
	const short		m_HEIGHT;
	wxString		m_clipboard;

//Variables to perform mathematical calculations/////////////////////////////////////
	wxString		m_result;
	long double		m_numberOne;
	long double		m_numberTwo;

//Event handling functions///////////////////////////////////////////////////////////
	void AboutMenuItemClicked(wxCommandEvent& event);			//DONE!
	void CopyMenuItemClicked(wxCommandEvent& event);			//DONE!
	void PasteMenuItemClicked(wxCommandEvent& event);			//DONE!
	void Button_1_Clicked(wxCommandEvent& event);				//DONE!
	void Button_2_Clicked(wxCommandEvent& event);				//DONE!	
	void Button_3_Clicked(wxCommandEvent& event);				//DONE!
	void Button_4_Clicked(wxCommandEvent& event);				//DONE!
	void Button_5_Clicked(wxCommandEvent& event);				//DONE!
	void Button_6_Clicked(wxCommandEvent& event);				//DONE!
	void Button_7_Clicked(wxCommandEvent& event);				//DONE!
	void Button_8_Clicked(wxCommandEvent& event);				//DONE!
	void Button_9_Clicked(wxCommandEvent& event);				//DONE!
	void Button_0_Clicked(wxCommandEvent& event);				//DONE!
	void Button_Backspace_Clicked(wxCommandEvent& event);		//DONE!
	void Button_Clear_Clicked(wxCommandEvent& event);			//DONE!
	void Button_CEL_Clicked(wxCommandEvent& event);				//DONE!
	void Button_Divide_Clicked(wxCommandEvent& event);			//DONE!
	void Button_Multiply_Clicked(wxCommandEvent& event);		//DONE!
	void Button_Minus_Clicked(wxCommandEvent& event);			//DONE!
	void Button_Plus_Clicked(wxCommandEvent& event);			//DONE!
	void Button_Sqrt_Clicked(wxCommandEvent& event);			//DONE!
	void Button_Percentage_Clicked(wxCommandEvent& event);		//DONE!
	void Button_OneByX_Clicked(wxCommandEvent& event);			//DONE!
	void Button_Equal_Clicked(wxCommandEvent& event);			//DONE!
	void Button_PlusMinus_Clicked(wxCommandEvent& event);		//DONE!
	void Button_Dot_Clicked(wxCommandEvent& event);				//DONE!
	

//Functions to keep history of clicked buttons///////////////////////////////////////
	enum LastClickedButtonType 
	{
		NUMBER, 
		OPERATOR, 
		OTHER, 
		MENU_ITEM, 
		NOTHING
	};
	
	Button					m_lastClickedButton;
	Button					m_lastClickedOperator;
	Button					m_lastClickedNumber;
	LastClickedButtonType	m_lastClickedButtonType;

	Button					GetLastClickedButton()		const;
	Button					GetLastClickedOperator()	const;
	Button					GetLastClickedNumber()		const;
	LastClickedButtonType	GetLastClickedButtonType()	const;

	void					SetLastClickedButton(const Button& button);
	void					SetLastClickedOperator(const Button& button);
	void					SetLastClickedNumber(const Button& button);
	void					SetLastClickedButtonType(const LastClickedButtonType& rButtonType);
/////////////////////////////////////////////////////////////////////////////////////
	wxString				GetDisplay_wxString()		const;
	long double				GetDisplay_long_double()	const;
	void					SetDisplay(const wxString& result);
	void					SetDisplay(const long double& result);

	void					NumberButtonClicked(const unsigned short& number);
	void					OperatorButtonClicked(const Button& button);
	void					LogBasicOperation(const Button& operatorButton);
	bool					IsFloating() const;
    void					ClearDisplay();
};

#endif	//KALCULATOR_FRAME_H