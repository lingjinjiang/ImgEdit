#ifndef INFODLG_H
#define INFODLG_H

//(*Headers(InfoDlg)
#include <wx/dialog.h>
//*)

class InfoDlg: public wxDialog
{
	public:

		InfoDlg(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~InfoDlg();

		//(*Declarations(InfoDlg)
		//*)

	protected:

		//(*Identifiers(InfoDlg)
		//*)

	private:

		//(*Handlers(InfoDlg)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
                    