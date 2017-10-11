#include "png.h"

int main()
{
	//初始化
	png_structp  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if(info_ptr == NULL)
	{
		png_destroy_read_struct(&png_ptr,NULL,NULL);
	}

	//默认错误处理代码
	if(setjmp(png_jumbuf(png_ptr)))
	{
		png_destroy_read_struct(&png_ptr,&info_ptr,NULL);
	}

/***
PNG_TRANSFORM_IDENTITY          No transformation
PNG_TRANSFORM_STRIP_16          Strip 16-bit samples to  8 bits
PNG_TRANSFORM_STRIP_ALPHA     Discard the alpha channel
PNG_TRANSFORM_PACKING           Expand 1, 2 and 4-bit samples to bytes
PNG_TRANSFORM_PACKSWAP        Change order of packed pixels to LSB first
PNG_TRANSFORM_EXPAND            Perform set_expand()
PNG_TRANSFORM_INVERT_MONO   Invert monochrome images
PNG_TRANSFORM_SHIFT              Normalize pixels to the  sBIT depth
PNG_TRANSFORM_BGR                 Flip RGB to BGR, RGBA  to BGRA
PNG_TRANSFORM_SWAP_ALPHA     Flip RGBA to ARGB or GA to AG
PNG_TRANSFORM_INVERT_ALPHA  Change alpha from opacity to transparency
PNG_TRANSFORM_SWAP_ENDIAN   Byte-swap 16-bit samples
PNG_TRANSFORM_GRAY_TO_RGB   Expand grayscale samples to RGB (or GA to RGBA)
***/

	//高层处理
	png_read_png(png_ptr,info_ptr,PNG_TRANSFORM_STRIP_ALPHA,NULL);
	png_bytepp row_points = png_get_rows(png_ptr,info_ptr);

	//结束读取数据
	png_read_end(png_ptr,info_ptr);
	png_destroy_read_struct(&png_ptr,&info_ptr,NULL);

/**  低层调用
a)调用png_read_info函数获得图片信息。
b)根据png_transforms所指示的，调用png_set_transform设置输出格式转换的函数。
c)调用png_read_image来解码整个图片的数据到内存。
d)调用png_read_end结束图片解码。
**/

	return 0;
}
