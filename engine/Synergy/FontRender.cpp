#include "FontRender.h"
#include "stb_truetype.h"
#include "Texture2D.h"
#include "SmartDraw.h"
#include <stdio.h>
#include <stdlib.h>
#include "SynUI.h"

stbtt_fontinfo fontInfo;

FontRender::FontRender(std::string path) {

    FILE* fontFile = fopen(path.c_str(), "rb");
    if (!fontFile) {
        fprintf(stderr, "Failed to open font file\n");
        return;
    }
   

    fseek(fontFile, 0, SEEK_END);
    size_t fontFileSize = ftell(fontFile);
    fseek(fontFile, 0, SEEK_SET);

    fontData = (unsigned char*)malloc(fontFileSize);
    fread(fontData, 1, fontFileSize, fontFile);
    fclose(fontFile);


    if (!stbtt_InitFont(&fontInfo, fontData, 0)) {
        fprintf(stderr, "Failed to initialize font\n");
        free(fontData);
        return;
    }

    //float fontSize = 20.0f;  // Adjust this as needed
    int bitmapWidth = 400;  // Width of your image
    int bitmapHeight = 200; // Height of your image

    // Create a buffer for rendering
    bitmap = (unsigned char*)malloc(bitmapWidth * bitmapHeight);
    memset(bitmap, 255, bitmapWidth * bitmapHeight); // Initialize the buffer with white

    // Set the text color
    unsigned char textRed = 0;
    unsigned char textGreen = 0;
    unsigned char textBlue = 0;
    // Set the position for the text
    int x = 20;
    int y = 100;


    mDraw = new SmartDraw;

}

void FontRender::DrawTextUI(std::string rtext, int dx, int dy,glm::vec4 color) {
    int b_w = 1024; /* bitmap width */
    int b_h = 128; /* bitmap height */
    int l_h = fontSize; /* line height */

    if (cache.find(rtext) == cache.end()) {
        //    std::cout << "Image3 not found in the map." << std::endl;
    }
    else {

        auto img = cache[rtext];

    //    auto draw = GameUI::mThis->GetDraw();
        //mDraw->Begin();
        auto draw = SynUI::_Draw;
        draw->DrawQuad(img, glm::vec2(dx, dy),glm::vec2(b_w, b_h),glm::vec4(1, 1, 1, 1));
       // mDraw->End(mShader);

        return;
    }

    /* create a bitmap for the phrase */
    unsigned char* bitmap = (unsigned char*)calloc(b_w * b_h, sizeof(unsigned char));

    /* calculate font scaling */
    float scale = stbtt_ScaleForPixelHeight(&fontInfo, l_h);

    char* word = (char*)rtext.c_str();

    int x = 0;

    int ascent, descent, lineGap;
    stbtt_GetFontVMetrics(&fontInfo, &ascent, &descent, &lineGap);

    ascent = roundf(ascent * scale);
    descent = roundf(descent * scale);

    int i;
    for (i = 0; i < strlen(word); ++i)
    {
        /* how wide is this character */
        int ax;
        int lsb;
        stbtt_GetCodepointHMetrics(&fontInfo, word[i], &ax, &lsb);
        /* (Note that each Codepoint call has an alternative Glyph version which caches the work required to lookup the character word[i].) */

        /* get bounding box for character (may be offset to account for chars that dip above or below the line) */
        int c_x1, c_y1, c_x2, c_y2;
        stbtt_GetCodepointBitmapBox(&fontInfo, word[i], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

        /* compute y (different characters have different heights) */
        int y = ascent + c_y1;

        /* render character (stride and offset is important here) */
        int byteOffset = x + roundf(lsb * scale) + (y * b_w);
        stbtt_MakeCodepointBitmap(&fontInfo, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, b_w, scale, scale, word[i]);

        /* advance x */
        x += roundf(ax * scale);

        /* add kerning */
        int kern;
        kern = stbtt_GetCodepointKernAdvance(&fontInfo, word[i], word[i + 1]);
        x += roundf(kern * scale);
    }


    char* nbit = (char*)malloc(b_w * b_h * 4);

    for (int y = 0; y < b_h; y++) {
        for (int x = 0; x < b_w; x++) {

            int samples = 0;

            float c = 0;
            for (int sy = -2; sy < 2; sy++) {
                for (int sx = -1; sx < 1; sx++) {

                    int ax, ay;
                    ax = x + sx;
                    ay = y + sy;
                    if (ax >= 0 && ax <= b_w && ay >= 0 && ay <= b_h) {
                        samples++;
                        int loc = (ay * b_w) + ax;
                        
                        int col = bitmap[loc];


                        c = c + ((float)col) / 255.0f;

                    }



                }


            }
            int loc = (y * b_w) + x;

            int col = bitmap[loc];

            //if (samples <= 0) samples = 1;
            //c = c / ((float)samples);
            c = ((float)(col) / 255.0f);

            loc = y * b_w * 4 + (x * 4);
            nbit[loc++] = (int)(c * 255.0f*color.x);
            nbit[loc++] = (int)(c * 255.0f*color.y);
            nbit[loc++] = (int)(c * 255.0f*color.z);
            
            float alpha = 1.0f;
            if (c < 0.1)
            {
                alpha = 0.0f;
            }
            
            nbit[loc++] = (int)(alpha * 255.0f);



        }
    }

 
    Texture2D* img = new Texture2D(nbit, b_w, b_h-5, 4);
    auto draw = SynUI::_Draw;
    //mDraw->Begin();
    draw->DrawQuad(img, glm::vec2(dx, dy), glm::vec2(b_w, b_h), glm::vec4(1, 1, 1, 1));
    //mDraw->Begin();
    //mDraw->DrawImage(img, dx, dy, b_w, b_h, 1, 1, 1, 1);
    //mDraw->End(mShader);

    cache[rtext] = img;

}

void FontRender::DrawText(std::string rtext, int dx, int dy) {

  


    int b_w = 1024; /* bitmap width */
    int b_h = 128; /* bitmap height */
    int l_h = fontSize; /* line height */

    if (cache.find(rtext) == cache.end()) {
        //    std::cout << "Image3 not found in the map." << std::endl;
    }
    else {

        auto img = cache[rtext];

       // mDraw->Begin();
       // mDraw->DrawImage(img, dx, dy, b_w, b_h, 1, 1, 1, 1);
       // mDraw->End(mShader);
        return;
    }

    /* create a bitmap for the phrase */
    unsigned char* bitmap = (unsigned char*)calloc(b_w * b_h, sizeof(unsigned char));

    /* calculate font scaling */
    float scale = stbtt_ScaleForPixelHeight(&fontInfo, l_h);

    char* word = (char*)rtext.c_str();

    int x = 0;

    int ascent, descent, lineGap;
    stbtt_GetFontVMetrics(&fontInfo, &ascent, &descent, &lineGap);

    ascent = roundf(ascent * scale);
    descent = roundf(descent * scale);

    int i;
    for (i = 0; i < strlen(word); ++i)
    {
        /* how wide is this character */
        int ax;
        int lsb;
        stbtt_GetCodepointHMetrics(&fontInfo, word[i], &ax, &lsb);
        /* (Note that each Codepoint call has an alternative Glyph version which caches the work required to lookup the character word[i].) */

        /* get bounding box for character (may be offset to account for chars that dip above or below the line) */
        int c_x1, c_y1, c_x2, c_y2;
        stbtt_GetCodepointBitmapBox(&fontInfo, word[i], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

        /* compute y (different characters have different heights) */
        int y = ascent + c_y1;

        /* render character (stride and offset is important here) */
        int byteOffset = x + roundf(lsb * scale) + (y * b_w);
        stbtt_MakeCodepointBitmap(&fontInfo, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, b_w, scale, scale, word[i]);

        /* advance x */
        x += roundf(ax * scale);

        /* add kerning */
        int kern;
        kern = stbtt_GetCodepointKernAdvance(&fontInfo, word[i], word[i + 1]);
        x += roundf(kern * scale);
    }



    //Image* img = new Image(bitmap,b_w,b_h, 1);

   // mDraw->Begin();
   // mDraw->DrawImage(img, dx, dy,b_w, b_h,1,1,1,1);
   // mDraw->End(mShader);
   // cache[rtext] = img;

}

int FontRender::Width(std::string rtext) {

    int i;
    char* word = (char*)rtext.c_str();
    int l_h = fontSize; /* line height */
    float scale = stbtt_ScaleForPixelHeight(&fontInfo, l_h);

//    char* word = (char*)rtext.c_str();

    int x = 0;

    int ascent, descent, lineGap;
    stbtt_GetFontVMetrics(&fontInfo, &ascent, &descent, &lineGap);

    ascent = roundf(ascent * scale);
    descent = roundf(descent * scale);
    for (i = 0; i < strlen(word); ++i)
    {
        /* how wide is this character */
        int ax;
        int lsb;
        stbtt_GetCodepointHMetrics(&fontInfo, word[i], &ax, &lsb);
        /* (Note that each Codepoint call has an alternative Glyph version which caches the work required to lookup the character word[i].) */

        /* get bounding box for character (may be offset to account for chars that dip above or below the line) */
        int c_x1, c_y1, c_x2, c_y2;
        stbtt_GetCodepointBitmapBox(&fontInfo, word[i], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

        /* compute y (different characters have different heights) */
        int y = ascent + c_y1;

        /* render character (stride and offset is important here) */
    //    int byteOffset = x + roundf(lsb * scale) + (y * b_w);
     //   stbtt_MakeCodepointBitmap(&fontInfo, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, b_w, scale, scale, word[i]);

        /* advance x */
        x += roundf(ax * scale);

        /* add kerning */
        int kern;
        kern = stbtt_GetCodepointKernAdvance(&fontInfo, word[i], word[i + 1]);
        x += roundf(kern * scale);
    }

    return x;

}