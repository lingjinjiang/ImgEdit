#ifndef IMGTOOL_H
#define IMGTOOL_H

#include <wx/image.h>

class ImgTool
{
    public:
        static void Anti(wxImage* image);
        static void Mono(wxImage* image);
        static void Enhance(wxImage* image);
        static void Equalization(wxImage* image);

    protected:

    private:
};

#endif // IMGTOOL_H
