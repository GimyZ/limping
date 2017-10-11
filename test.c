#include "png.h"

// int main()
// {
// 	//初始化
// 	png_structp  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
// 	png_infop info_ptr = png_create_info_struct(png_ptr);
// 	if(info_ptr == NULL)
// 	{
// 		png_destroy_read_struct(&png_ptr,NULL,NULL);
// 	}

// 	//默认错误处理代码
// 	if(setjmp(png_jumbuf(png_ptr)))
// 	{
// 		png_destroy_read_struct(&png_ptr,&info_ptr,NULL);
// 	}

// **
// PNG_TRANSFORM_IDENTITY          No transformation
// PNG_TRANSFORM_STRIP_16          Strip 16-bit samples to  8 bits
// PNG_TRANSFORM_STRIP_ALPHA     Discard the alpha channel
// PNG_TRANSFORM_PACKING           Expand 1, 2 and 4-bit samples to bytes
// PNG_TRANSFORM_PACKSWAP        Change order of packed pixels to LSB first
// PNG_TRANSFORM_EXPAND            Perform set_expand()
// PNG_TRANSFORM_INVERT_MONO   Invert monochrome images
// PNG_TRANSFORM_SHIFT              Normalize pixels to the  sBIT depth
// PNG_TRANSFORM_BGR                 Flip RGB to BGR, RGBA  to BGRA
// PNG_TRANSFORM_SWAP_ALPHA     Flip RGBA to ARGB or GA to AG
// PNG_TRANSFORM_INVERT_ALPHA  Change alpha from opacity to transparency
// PNG_TRANSFORM_SWAP_ENDIAN   Byte-swap 16-bit samples
// PNG_TRANSFORM_GRAY_TO_RGB   Expand grayscale samples to RGB (or GA to RGBA)
// **

// 	//高层处理
// 	png_read_png(png_ptr,info_ptr,PNG_TRANSFORM_STRIP_ALPHA,NULL);
// 	png_bytepp row_points = png_get_rows(png_ptr,info_ptr);

// 	//结束读取数据
// 	png_read_end(png_ptr,info_ptr);
// 	png_destroy_read_struct(&png_ptr,&info_ptr,NULL);

// /**  低层调用
// a)调用png_read_info函数获得图片信息。
// b)根据png_transforms所指示的，调用png_set_transform设置输出格式转换的函数。
// c)调用png_read_image来解码整个图片的数据到内存。
// d)调用png_read_end结束图片解码。
// **/

// 	return 0;
// }


#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "png.h"
#include "zlib.h"

void read_png(char *fileName)
{
	png_structp png_ptr;
	png_infop info_ptr;
	int sig_read = 0;
	png_uint_32 width,height;
	int bit_depth,color_type,interlace_type;
	FILE *fp;
	if((fp = fopen(fileName,"rb")) == NULL)
	{
		fprintf(stderr, "open file error:%s\n", fileName);
		return;
	}

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);

	if(png_ptr == NULL)
	{
		fclose(fp);
		fprintf(stderr, "init png_ptr failure\n" );
		return;
	}

	//错误处理
	if(setjmp(png_jumbuf(png_ptr)))
	{
		png_destroy_read_struct(&png_ptr,&info_ptr,NULL);
		fclose(fp);
		fprintf(stderr, "call error handle\n" );
		return;
	}

	//数据源
	png_init_io(png_ptr,fp);

	// png_set_sig_bytes(png_ptr,sig_read);

	//高层处理
#ifdef hilevel
	png_read_png(png_ptr,info_ptr,PNG_TRANSFORM_BGR,NULL);
#else
	png_read_info(png_ptr,info_ptr);

	png_get_IHDR(png_ptr,info_ptr,&width,&height,&bit_depth,&color_type,&interlace_type,NULL,NULL);

	//可选
	if (bit_depth == 16)  
    	png_set_strip_16(png_ptr);  
	if (color_type == PNG_COLOR_TYPE_PALETTE)  
	    png_set_expand(png_ptr);  
	if (bit_depth<8)  
	    png_set_expand(png_ptr);  
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))  
	    png_set_expand(png_ptr);  
	if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)  
	    png_set_gray_to_rgb(png_ptr);

	png_read_update_info(png_ptr,info_ptr);

	png_bytepp row_points[height];
	for(int row = 0;row < height;row ++)
	{
		row_points[row] = NULL;
	}

	for(int row = 0;row <height;row ++)
	{
		row_points[row] = png_malloc(png_ptr,png_get_rowbytes(png_ptr,info_ptr));
	}

	png_read_image(png_ptr,row_points);

	png_read_end(png_ptr,info_ptr);
#endif hilevel

	png_destroy_read_struct(&png_ptr,&info_ptr,NULL);
	fclose(fp);
	fprintf(stdout, "read png finished\n");
}



int main(int argc char ** argv)
{
	return 0;
}




























