/***************************************************************
 * Name:      ImgEditApp.cpp
 * Purpose:   Code for Application Class
 * Author:    lingjinjiang (lingjinjiang@gmail.com)
 * Created:   2019-05-08
 * Copyright: lingjinjiang ()
 * License:
 **************************************************************/

#include "ImgEditApp.h"
#include "MainFrame.h"

IMPLEMENT_APP(ImgEditApp);

bool ImgEditApp::OnInit()
{
    MainFrame *frame = new MainFrame(NULL);
    frame->Show(true);
    return true;

}
