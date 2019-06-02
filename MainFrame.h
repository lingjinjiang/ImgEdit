#ifndef MAINFRAME_H
#define MAINFRAME_H

//(*Headers(MainFrame)
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/statline.h>
#include <wx/frame.h>
#include <wx/statbmp.h>
//*)
#include <wx/filedlg.h>
#include <wx/dcbuffer.h>

class MainFrame: public wxFrame
{
	public:

		MainFrame(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~MainFrame();

		//(*Declarations(MainFrame)
		wxButton* enhanceBtn;
		wxStaticLine* StaticLine2;
		wxButton* openBtn;
		wxButton* antiBtn;
		wxStaticBitmap* bitmapAfter;
		wxStaticBitmap* bitmapOrigin;
		wxButton* monoBtn;
		wxStaticLine* StaticLine1;
		wxButton* resetBtn;
		wxStaticLine* StaticLine3;
		wxPanel* mainPanel;
		wxButton* equalBtn;
		wxButton* closeBtn;
		//*)

		wxFileDialog* openFileDlg;

	protected:

		//(*Identifiers(MainFrame)
		static const long ID_BTN_OPEN;
		static const long ID_BTN_RESET;
		static const long ID_BITMAP_ORIGIN;
		static const long ID_BITMAP_AFTER;
		static const long ID_STATICLINE1;
		static const long ID_STATICLINE2;
		static const long ID_BTN_CLOSE;
		static const long ID_STATICLINE3;
		static const long ID_BTN_ANTI;
		static const long ID_BTN_MONO;
		static const long ID_BTN_ENHANCE;
		static const long ID_BTN_EQUAL;
		static const long ID_MAIN_PANEL;
		//*)

	private:

		//(*Handlers(MainFrame)
		void OnButton1Click(wxCommandEvent& event);
		void OncloseBtnClick(wxCommandEvent& event);
		void OnOpenClick(wxCommandEvent& event);
		void OnmainPanelPaint(wxPaintEvent& event);
		void OnantiBtnClick(wxCommandEvent& event);
		void OnresetBtnClick(wxCommandEvent& event);
		void OnmonoBtnClick(wxCommandEvent& event);
		void OnEnhanceBtnClick(wxCommandEvent& event);
		void OnequalBtnClick(wxCommandEvent& event);
		//*)
		void DrawBorder(wxDC* pDC);
		void DrawImg(wxDC* pDC, wxImage img);
		void DisableBtns();
		void EnableBtns();
		wxImage* imageOrigin;
        wxImage* imageAfter;
		DECLARE_EVENT_TABLE()
};

#endif
