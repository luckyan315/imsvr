#ifndef GRAY_IMAGE_H
#define GRAY_IMAGE_H

#include <vector>
#include <atlstr.h>
#include <atlimage.h>
#include <boost/gil/gil_all.hpp>

struct ICBProgress
{
    virtual void operator ()(double cur, double total,const std::vector<std::string> &imagePathes) 
    {
    }
};

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


    //grayScale , saveDir, output
    int LineScanImages(const int grayScale, const int maxRowCount,const char * saveDir, FileNameContainer & output, GrayScaleCreator::LineType type = ROW);
    int RectScanImage(const int grayScale, const int left, const int top, const size_t width, const size_t height
        , const char * saveDir, FileNameContainer & output, size_t id = 0);
    
private:
    inline void GetFileName(char * buf, size_t sz, size_t typeID, int grayScale, int id, const char * dir);

    int SaveOneImage(const int grayScale, const int left, const int top, const size_t width, const size_t height, 
        const char * saveDir, FileNameContainer & output, size_t id, GrayScaleCreator::LineType type);
private:
    int m_width;
    int m_height;
    int m_bpp;
    ICBProgress & m_cb;
};

#endif
