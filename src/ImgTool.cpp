#include "ImgTool.h"

void ImgTool::Anti(wxImage* image)
{
    unsigned char *data = image->GetData();
    int width = image->GetWidth();
    int height = image->GetHeight();
    int x, y;
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            long pos = (y * width + x) * 3;
            data[pos] = 255 - data[pos];
            data[pos + 1] = 255 - data[pos + 1];
            data[pos + 2] = 255 - data[pos + 2];
        }
    }
}

void ImgTool::Mono(wxImage* image)
{
    unsigned char *data = image->GetData();
    int width = image->GetWidth();
    int height = image->GetHeight();
    int x, y;
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            long pos = (y * width + x) * 3;
            data[pos] = (data[pos] + data[pos + 1] + data[pos + 2]) / 3;
            data[pos + 1] = data[pos];
            data[pos + 2] = data[pos];
        }
    }
}


void ImgTool::Equalization(wxImage* image)
{

}

void ImgTool::Enhance(wxImage* image)
{
    unsigned char *data = image->GetData();
    int width = image->GetWidth();
    int height = image->GetHeight();

    int sum = width * height;
    int r[256], g[256], b[256];
    memset(r, 0, sizeof(r));
    memset(g, 0, sizeof(g));
    memset(b, 0, sizeof(b));

    int currR, currG, currB;
    int maxR, maxG, maxB;
    int minR, minG, minB;

    int x, y;
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            long pos = (y * width + x) * 3;
            currR = data[pos];
            currG = data[pos + 1];
            currB = data[pos + 2];
            ++r[currR];
            ++g[currG];
            ++b[currB];
        }
    }

    int tmp;

    // find min and max Red
    for (x = 0; x < 256; ++x)
    {
        tmp = r[x];
        if ((float)(tmp) > (float)(sum * 0.0005))
        {
            minR = x;
            break;
        }
    }

    for (x = 255; x >= 0; --x)
    {
        tmp = r[x];
        if ((float)(tmp) > (float)(sum * 0.0005))
        {
            maxR = x;
            break;
        }
    }

    // find min and max Green
    for (x = 0; x < 256; ++x)
    {
        tmp = g[x];
        if ((float)(tmp) > (float)(sum * 0.0005))
        {
            minG = x;
            break;
        }
    }

    for (x = 255; x >= 0; --x)
    {
        tmp = g[x];
        if ((float)(tmp) > (float)(sum * 0.0005))
        {
            maxG = x;
            break;
        }
    }

    // find min and max Blue
    for (x = 0; x < 256; ++x)
    {
        tmp = b[x];
        if ((float)(tmp) > (float)(sum * 0.0005))
        {
            minB = x;
            break;
        }
    }

    for (x = 255; x >= 0; --x)
    {
        tmp = b[x];
        if ((float)(tmp) > (float)(sum * 0.0005))
        {
            maxB = x;
            break;
        }
    }

    for (x = 0; x < 256; ++x)
    {
        if (x <= minR)
            r[x] = 0;
        else if (x >= maxR)
            r[x] = 255;
        else
            r[x] = 255.0f * (double)(x - minR) / (double)(maxR - minR);

        if (x <= minG)
            g[x] = 0;
        else if (x >= maxG)
            g[x] = 255;
        else
            g[x] = 255.0f * (double)(x - minG) / (double)(maxG - minG);

        if (x <= minB)
            b[x] = 0;
        else if (x >= maxB)
            b[x] = 255;
        else
            b[x] = 255.0f * (double)(x - minB) / (double)(maxB - minB);
    }

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            long pos = (y * width + x) * 3;
            data[pos] = r[(int)data[pos]];
            data[pos + 1] = g[(int)data[pos + 1]];
            data[pos + 2] = b[(int)data[pos + 2]];
        }
    }
}
