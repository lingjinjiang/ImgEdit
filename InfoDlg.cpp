#include "InfoDlg.h"

//(*InternalHeaders(InfoDlg)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(InfoDlg)
//*)

BEGIN_EVENT_TABLE(InfoDlg,wxDialog)
	//(*EventTable(InfoDlg)
	//*)
END_EVENT_TABLE()

InfoDlg::InfoDlg(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(InfoDlg)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(400,115));
	Move(wxDefaultPosition);
	//*)
}

InfoDlg::~InfoDlg()
{
	//(*Destroy(InfoDlg)
	//*)
}

                                