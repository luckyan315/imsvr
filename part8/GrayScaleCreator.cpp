/*
 * File     :   GrayScaleCreator.h
 * Descript :   按照一定的名称规则，生成各种灰度图片(默认512*512*32),
 *              生成的图片样式为：水平线型，垂直线型和矩形 三种
 *              其中在生成水平和垂直线型时有多张图片，数目是基于分辨率，例如：512*512的图片，水平有512张，垂直有512张
 *              因此，该类也提供一个callback函数对象，每生成一张图片，则会调用该函数对象一次
 */
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
/*
 *  Descript:  灰度图片的路径生成规则：
        fmtsavePath = "%s\\%s_%03d_%03d.bmp";  
        即：dir\type_grayscale_id.bmp   
        type: row column rect
        grayscale : 3位数字，左补充0 默认为032
        id        ：3位数字, 左补充0 递增 [001, max_rows|max_column], 矩形图形的id自己生成
 */
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
/*
 * Descript:    生成线性灰度图片
 * Param[in]    grayScale  灰度级
 *              maxRowCount 最大图片数目
 *              saveDir 图片保存目录名称，绝对目录或者相对目录
 *              type 生成线性类型： ROW  水平线型  COLUMN 垂直线型
 * Param[out]   output 最终生成的图片路径容器
 */
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
/*
 * Descript:    生成矩形灰度图片
 * Param[in]    grayScale  灰度级
 *              left, top, width, height 矩形区域
 *              saveDir 图片保存目录名称，绝对目录或者相对目录
 *              id 矩形图片的ID
 * Param[out]   output 最终生成的图片路径容器
 */
int GrayScaleCreator::RectScanImage(const int grayScale, const int left, const int top, const size_t width, const size_t height, 
                          const char * saveDir, FileNameContainer & output, size_t id)
{
    int ret = SaveOneImage(grayScale, left, top, width, height, saveDir, output, id, RECT);
    m_cb(1.0, 1.0,output);
    return ret;
}

/*
 *  Descript:   生成一个矩形区域为白色的灰度图片，并保存
 * Param[in]    grayScale  灰度级
 *              left, top, width, height 矩形区域
 *              saveDir 图片保存目录名称，绝对目录或者相对目录
 *              id 矩形图片的ID
 *              type: row column rect
 * Param[out]   output 最终生成的图片路径容器
 */
int GrayScaleCreator::SaveOneImage(const int grayScale, const int left, const int top, const size_t width, const size_t height, 
                    const char * saveDir, FileNameContainer & output, size_t id, GrayScaleCreator::LineType type)
{
    //1. Create CImage(MFC) object
    CImage saveImage;
    if(0 == saveImage.Create(m_width, m_height, m_bpp, CImage::createAlphaChannel)){
        return -2;
    }
    //2. create related view for saveImage 
    unsigned char* buffer_view = (unsigned char*)saveImage.GetBits()+(saveImage.GetPitch()*(saveImage.GetHeight()-1));
    rgba8_view_t toView = interleaved_view(saveImage.GetWidth(),saveImage.GetHeight(),(rgba8_pixel_t*)buffer_view,saveImage.GetWidth()*4);

    //3. set the rectange(left, top, width, height) with white color
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
    //4. generate file name && save it
    if(!saveImage.IsNull()){

        char buf[MAX_FILE_PATH_LEN] = {0,};            
        GetFileName(buf, MAX_FILE_PATH_LEN, (size_t)type, grayScale, (int)id, saveDir);

        saveImage.Save(buf);
        output.push_back(std::string(buf));
    }
    //5. destroy the memory resource 
    saveImage.Destroy();
    return 0;
}

