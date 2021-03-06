#include "lzmalt.h"

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "LZMADecoder.h"


static LzmaDecoder   cc;
ISequentialInStream  in_stream;
ISequentialOutStream out_stream;
int decompress_lzma_alt( unsigned char* in_data, 
                          unsigned in_size, 
                          unsigned char* out_data, 
                          unsigned out_size,
                          int offset) {
//		LzmaDecoder cc;
        int RC;
	UINT64 in_size_l  = in_size;
	UINT64 out_size_l = out_size;


        InStreamInit(in_data+offset, in_size-offset);

	OutStreamInit((char *)out_data, out_size);

        LzmaDecoderConstructor(&cc);

        if ((RC = LzmaDecoderReadCoderProperties(&cc)) != S_OK)
        {
		return RC;
        }

	if (LzmaDecoderCode(&cc, &in_size_l, &out_size_l) != S_OK)
        {
		return -2;
        }

	if (out_stream.size != out_size)
        {
		return -3;
        }

        if ( out_stream.overflow )
        {
            return -4;
        }

	return 0;
}

//BRCM modification
#ifdef __KERNEL__
EXPORT_SYMBOL(decompress_lzma_7z);
#endif


