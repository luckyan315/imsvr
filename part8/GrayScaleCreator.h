/*
 * File     :   GrayScaleCreator.h
 * Descript :   按照一定的名称规则，生成各种灰度图片(默认512*512*32),
 *              生成的图片样式为：水平线型，垂直线型和矩形 三种
 *              其中在生成水平和垂直线型时有多张图片，数目是基于分辨率，例如：512*512的图片，水平有512张，垂直有512张
 *              因此，该类也提供一个callback函数对象，每生成一张图片，则会调用该函数对象一次
 */
#ifndef GRAY_IMAGE_H
#define GRAY_IMAGE_H

#include <vector>
#include <atlstr.h>
#include <atlimage.h>
#include <boost/gil/gil_all.hpp>

/*
 *    函数对象， 用于GrayScaleCreator类的函数接口，可以通过继承自定义
 *    输入参数： Param[in]   cur   已经生成的张数
 *                           total 总张数
 *                           imagePathes  已经生成图片的路径
 */
struct ICBProgress
{
    virtual void operator ()(double cur, double total,const std::vector<std::string> &imagePathes) 
    {
    }
};
/*
 *   Class:     GrayScaleCreator
 *   Descript:  生成三种式样的灰度图片，并按照一定的名称格式保存
 *   名称格式：  
        fmtsavePath = "%s\\%s_%03d_%03d.bmp";  
        即：dir\type_grayscale_id.bmp   
        type: row column rect
        grayscale : 3位数字，左补充0 默认为032
        id        ：3位数字, 左补充0 递增 [001, max_rows|max_column], 矩形图形的id自己生成

 */
class GrayScaleCreator
{
public:
    static const int MAX_FILE_PATH_LEN  = 128;
    enum LineType{
        ROW = 0,
        COLUMN,
        RECT
    };
    typedef std::vector<std::string> FileNameContainer;


    GrayScaleCreator(ICBProgress & cb = ICBProgress(), int width  = 512, int height = 512, int bpp = 32);
    ~GrayScaleCreator(void);

    void SetProgressCallback(ICBProgress &cb){ m_cb = cb;}
    ICBProgress& GetProgressCallback() {return m_cb;}

    /*
     * Descript:    生成线性灰度图片
     * Param[in]    grayScale  灰度级
     *              maxRowCount 最大图片数目
     *              saveDir 图片保存目录名称，绝对目录或者相对目录
     *              type 生成线性类型： ROW  水平线型  COLUMN 垂直线型
     * Param[out]   output 最终生成的图片路径容器
     */
    int LineScanImages(const int grayScale, const int maxRowCount,const char * saveDir, FileNameContainer & output, GrayScaleCreator::LineType type = ROW);
    /*
     * Descript:    生成矩形灰度图片
     * Param[in]    grayScale  灰度级
     *              left, top, width, height 矩形区域
     *              saveDir 图片保存目录名称，绝对目录或者相对目录
     *              id 矩形图片的ID
     * Param[out]   output 最终生成的图片路径容器
     */
    int RectScanImage(const int grayScale, const int left, const int top, const size_t width, const size_t height
        , const char * saveDir, FileNameContainer & output, size_t id = 0);
    
private:
    /*
     *  Descript:  灰度图片的路径生成规则：
            fmtsavePath = "%s\\%s_%03d_%03d.bmp";  
            即：dir\type_grayscale_id.bmp   
            type: row column rect
            grayscale : 3位数字，左补充0 默认为032
            id        ：3位数字, 左补充0 递增 [001, max_rows|max_column], 矩形图形的id自己生成
     */
    inline void GetFileName(char * buf, size_t sz, size_t typeID, int grayScale, int id, const char * dir);

    /*
     *  Descript:   生成一个矩形区域为白色的灰度图片，并保存
     * Param[in]    grayScale  灰度级
     *              left, top, width, height 矩形区域
     *              saveDir 图片保存目录名称，绝对目录或者相对目录
     *              id 矩形图片的ID
     *              type: row column rect
     * Param[out]   output 最终生成的图片路径容器
     */
    int SaveOneImage(const int grayScale, const int left, const int top, const size_t width, const size_t height, 
        const char * saveDir, FileNameContainer & output, size_t id, GrayScaleCreator::LineType type);
private:
    int m_width;
    int m_height;
    int m_bpp;
    ICBProgress & m_cb;
};

#endif
