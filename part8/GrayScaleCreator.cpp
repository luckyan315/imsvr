#include "StdAfx.h"
#include "GrayScaleCreator.h"

using namespace boost::gil;

GrayScaleCreator::GrayScaleCreator(ICBProgress & cb, int width, int height, int bpp)
:m_width(width), m_height(height), m_bpp(bpp), m_cb(cb)
{
}

GrayScaleCreator::~GrayScaleCreator(void)
{
}

void GrayScaleCreator::GetFileName(char * buf, size_t sz, size_t typeID, int grayScale, int id, const char * dir)
{
    const char * typeName[] ={
            "row",
            "column",
            "rect"
    };
    assert(typeID >=0 && typeID <= sizeof(typeName)/sizeof(typeName[0]));
    assert(buf  && sz > 0 && grayScale >= 0 && grayScale <= 255 && id >= 0);

    const char * fmtsavePath = "%s\\%s_%03d_%03d.bmp";
    
    _snprintf_s(buf, sz, _TRUNCATE, fmtsavePath, dir, typeName[typeID], grayScale, id);
}

int GrayScaleCreator::LineScanImages(const int grayScale, const int maxRowCount, const char * saveDir, FileNameContainer & output, GrayScaleCreator::LineType type)
{
    assert(saveDir);
    int i = 0;
    
    if(maxRowCount <= 0){
        return -1;
    }
   
    for(int id = 0; id < maxRowCount; ++id )
    {
        
        if(type == ROW)
            SaveOneImage(grayScale, 0, id, m_width, 1, saveDir, output, id, type);
        else
            SaveOneImage(grayScale, id, 0, 1, m_height, saveDir, output, id, type);

        m_cb(id+1, maxRowCount,output);

    }
    return 0;
}




int GrayScaleCreator::RectScanImage(const int grayScale, const int left, const int top, const size_t width, const size_t height, 
                          const char * saveDir, FileNameContainer & output, size_t id)
{
    int ret = SaveOneImage(grayScale, left, top, width, height, saveDir, output, id, RECT);
    m_cb(1.0, 1.0,output);
    return ret;
}




int GrayScaleCreator::SaveOneImage(const int grayScale, const int left, const int top, const size_t width, const size_t height, 
                    const char * saveDir, FileNameContainer & output, size_t id, GrayScaleCreator::LineType type)
{

    CImage saveImage;
    if(0 == saveImage.Create(m_width, m_height, m_bpp, CImage::createAlphaChannel)){
        return -2;
    }
    //create related view for saveImage 
    unsigned char* buffer_view = (unsigned char*)saveImage.GetBits()+(saveImage.GetPitch()*(saveImage.GetHeight()-1));
    rgba8_view_t toView = interleaved_view(saveImage.GetWidth(),saveImage.GetHeight(),(rgba8_pixel_t*)buffer_view,saveImage.GetWidth()*4);

    int minX = left;
    int minY = m_height - top - (int)height;
    int maxX = minX +(int)width -1;
    int maxY = minY + (int)height-1;

    for (int y=0; y< toView.height(); ++y) {
        rgba8_view_t::x_iterator dst_it = toView.row_begin(y);
        for (int x=0; x<toView.width(); ++x) {
            if( x >= minX && x <= maxX && y >=minY && y <= maxY)
                dst_it[x][0] = dst_it[x][1] = dst_it[x][2] = (unsigned char) (grayScale);
            else
                dst_it[x][0] = dst_it[x][1] = dst_it[x][2] = (unsigned char) (0);
        }
    }


    //Save the image with a file name create rule
    if(!saveImage.IsNull()){

        char buf[MAX_FILE_PATH_LEN] = {0,};            
        GetFileName(buf, MAX_FILE_PATH_LEN, (size_t)type, grayScale, (int)id, saveDir);

        saveImage.Save(buf);
        output.push_back(std::string(buf));
    }
    saveImage.Destroy();
    return 0;
}

