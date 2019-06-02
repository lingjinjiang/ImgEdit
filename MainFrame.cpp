#include "MainFrame.h"

//(*InternalHeaders(MainFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)
#include <wx/dcbuffer.h>
#include "ImgTool.h"

//(*IdInit(MainFrame)
const long MainFrame::ID_BTN_OPEN = wxNewId();
const long MainFrame::ID_BTN_RESET = wxNewId();
const long MainFrame::ID_BITMAP_ORIGIN = wxNewId();
const long MainFrame::ID_BITMAP_AFTER = wxNewId();
const long MainFrame::ID_STATICLINE1 = wxNewId();
const long MainFrame::ID_STATICLINE2 = wxNewId();
const long MainFrame::ID_BTN_CLOSE = wxNewId();
const long MainFrame::ID_STATICLINE3 = wxNewId();
const long MainFrame::ID_BTN_ANTI = wxNewId();
const long MainFrame::ID_BTN_MONO = wxNewId();
const long MainFrame::ID_BTN_ENHANCE = wxNewId();
const long MainFrame::ID_BTN_EQUAL = wxNewId();
const long MainFrame::ID_MAIN_PANEL = wxNewId();
//*)

BEGIN_EVENT_TABLE(MainFrame,wxFrame)
	//(*EventTable(MainFrame)
	//*)
END_EVENT_TABLE()

MainFrame::MainFrame(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(MainFrame)
	Create(parent, wxID_ANY, _("Image Editor"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(1100,600));
	mainPanel = new wxPanel(this, ID_MAIN_PANEL, wxPoint(0,384), wxSize(960,600), wxTAB_TRAVERSAL, _T("ID_MAIN_PANEL"));
	openBtn = new wxButton(mainPanel, ID_BTN_OPEN, _("Open"), wxPoint(24,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_OPEN"));
	resetBtn = new wxButton(mainPanel, ID_BTN_RESET, _("Reset"), wxPoint(128,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_RESET"));
	bitmapOrigin = new wxStaticBitmap(mainPanel, ID_BITMAP_ORIGIN, wxNullBitmap, wxPoint(24,80), wxSize(512,336), wxSIMPLE_BORDER, _T("ID_BITMAP_ORIGIN"));
	bitmapAfter = new wxStaticBitmap(mainPanel, ID_BITMAP_AFTER, wxNullBitmap, wxPoint(560,80), wxSize(512,336), wxSIMPLE_BORDER, _T("ID_BITMAP_AFTER"));
	StaticLine1 = new wxStaticLine(mainPanel, ID_STATICLINE1, wxPoint(24,432), wxSize(1056,8), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	StaticLine2 = new wxStaticLine(mainPanel, ID_STATICLINE2, wxPoint(536,64), wxSize(24,368), wxLI_VERTICAL, _T("ID_STATICLINE2"));
	closeBtn = new wxButton(mainPanel, ID_BTN_CLOSE, _("Close"), wxPoint(992,544), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_CLOSE"));
	StaticLine3 = new wxStaticLine(mainPanel, ID_STATICLINE3, wxPoint(24,56), wxSize(1056,8), wxLI_HORIZONTAL, _T("ID_STATICLINE3"));
	antiBtn = new wxButton(mainPanel, ID_BTN_ANTI, _("Anti"), wxPoint(24,448), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_ANTI"));
	monoBtn = new wxButton(mainPanel, ID_BTN_MONO, _("Mono"), wxPoint(24,488), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_MONO"));
	enhanceBtn = new wxButton(mainPanel, ID_BTN_ENHANCE, _("Enhance"), wxPoint(128,448), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_ENHANCE"));
	equalBtn = new wxButton(mainPanel, ID_BTN_EQUAL, _("Equal"), wxPoint(128,488), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTN_EQUAL"));
	Center();

	Connect(ID_BTN_OPEN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainFrame::OnOpenClick);
	Connect(ID_BTN_RESET,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainFrame::OnresetBtnClick);
	Connect(ID_BTN_CLOSE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainFrame::OncloseBtnClick);
	Connect(ID_BTN_ANTI,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainFrame::OnantiBtnClick);
	Connect(ID_BTN_MONO,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainFrame::OnmonoBtnClick);
	Connect(ID_BTN_ENHANCE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainFrame::OnEnhanceBtnClick);
	Connect(ID_BTN_EQUAL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainFrame::OnequalBtnClick);
	mainPanel->Connect(wxEVT_PAINT,(wxObjectEventFunction)&MainFrame::OnmainPanelPaint,0,this);
	//*)


    wxInitAllImageHandlers();
    imageOrigin = new wxImage();
    imageAfter = new wxImage();
    openFileDlg = new wxFileDialog(this, wxT("Open image"), wxT(""), wxT(""), wxT("PNG|*.png|JPEG|*.jpeg"));

    DisableBtns();
}

MainFrame::~MainFrame()
{
	//(*Destroy(MainFrame)
	//*)
	delete imageAfter;
	delete imageOrigin;
	delete openFileDlg;
}


void MainFrame::OncloseBtnClick(wxCommandEvent& event)
{
    Close(true);
}

void MainFrame::OnOpenClick(wxCommandEvent& event)
{


    if (openFileDlg->ShowModal() == wxID_CANCEL)
    {
        return;
    }


    imageOrigin->LoadFile(openFileDlg->GetPath());
    if (!imageOrigin->IsOk())
    {
        return;
    }
    *imageAfter = imageOrigin->Copy();


    // draw image for origin bitmap
    wxBufferedPaintDC originDC(bitmapOrigin);
    DrawImg(&originDC, *imageOrigin);

    // draw image for after bitmap
    wxBufferedPaintDC afterDC(bitmapAfter);
    DrawImg(&afterDC, *imageAfter);

    EnableBtns();
}

void MainFrame::DrawBorder(wxDC* pDC)
{
    pDC->SetBrush(*wxLIGHT_GREY_BRUSH);
    pDC->DrawRectangle(pDC->GetLogicalOrigin(), pDC->GetSize());
}

void MainFrame::DrawImg(wxDC* pDC, wxImage img)
{
    wxSize dcSize = pDC->GetSize();
    int dcWidth = dcSize.GetWidth() - 2;
    int dcHeight = dcSize.GetHeight() - 2;
    int imgWidth = img.GetWidth();
    int imgHeight = img.GetHeight();
    int posX = 1;
    int posY = 1;

    float rate = (float)dcWidth / (float)dcHeight;

    if (imgWidth < rate * imgHeight) {
        rate = (float)dcHeight / (float)imgHeight;
        imgHeight = dcHeight;

        imgWidth = rate * imgWidth;

        posX = posX + (dcWidth - imgWidth) / 2;
    } else {
        rate = (float)dcWidth / (float)imgWidth;
        imgWidth = dcWidth;

        imgHeight = rate * imgHeight;
        posY = posY+ (dcHeight - imgHeight) / 2;
    }

    DrawBorder(pDC);
    img.Rescale(imgWidth, imgHeight, wxIMAGE_QUALITY_BOX_AVERAGE);
    pDC->DrawBitmap(img, wxPoint(posX, posY), true);

    //wxBitmap bitmap(img);
    //wxMemoryDC memDC(bitmap);
    //pDC->StretchBlit(posX, posY, imgWidth, imgHeight, &memDC, 0, 0, img.GetWidth(), img.GetHeight());


}

void MainFrame::OnmainPanelPaint(wxPaintEvent& event)
{
    wxBufferedPaintDC originDC(bitmapOrigin);
    DrawBorder(&originDC);

    wxBufferedPaintDC afterDC(bitmapAfter);
    DrawBorder(&afterDC);
}

void MainFrame::OnantiBtnClick(wxCommandEvent& event)
{
    if (imageAfter == NULL)
    {
        return;
    }

    ImgTool::Anti(imageAfter);


    wxBufferedPaintDC afterDC(bitmapAfter);
    DrawImg(&afterDC, *imageAfter);
}

void MainFrame::OnresetBtnClick(wxCommandEvent& event)
{
    delete imageAfter;
    imageAfter = new wxImage();
    *imageAfter = imageOrigin->Copy();
    wxBufferedPaintDC afterDC(bitmapAfter);
    DrawImg(&afterDC, *imageAfter);
}

void MainFrame::DisableBtns()
{
    resetBtn->Disable();
    antiBtn->Disable();
    monoBtn->Disable();
    enhanceBtn->Disable();
    equalBtn->Disable();
}

void MainFrame::EnableBtns()
{
    resetBtn->Enable();
    antiBtn->Enable();
    monoBtn->Enable();
    enhanceBtn->Enable();
    equalBtn->Enable();
}

void MainFrame::OnmonoBtnClick(wxCommandEvent& event)
{
    if (imageAfter == NULL)
    {
        return;
    }

    ImgTool::Mono(imageAfter);


    wxBufferedPaintDC afterDC(bitmapAfter);
    DrawImg(&afterDC, *imageAfter);
}

void MainFrame::OnequalBtnClick(wxCommandEvent& event)
{
    if (imageAfter == NULL)
    {
        return;
    }

    ImgTool::Equalization(imageAfter);


    wxBufferedPaintDC afterDC(bitmapAfter);
    DrawImg(&afterDC, *imageAfter);
}

void MainFrame::OnEnhanceBtnClick(wxCommandEvent& event)
{
    if (imageAfter == NULL)
    {
        return;
    }

    ImgTool::Enhance(imageAfter);


    wxBufferedPaintDC afterDC(bitmapAfter);
    DrawImg(&afterDC, *imageAfter);
}
