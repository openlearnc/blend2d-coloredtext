#include <SDL2/SDL.h>
#include "blend2d.h"

#include "regex.h"
#include <iostream>
int U8_charsize(const char* character)
{
    if(character == NULL)
        return 0;

    if((unsigned char)*character <= 0x7F)
        return 1;
    else if((unsigned char)*character < 0xE0)
        return 2;
    else if((unsigned char)*character < 0xF0)
        return 3;
    else
        return 4;
    return 1;
}
/*441111*/    //#你
int getwidth(BLFont font,char*str,size_t size){
	BLGlyphBuffer buffer;
	BLTextMetrics tm;
	//BLFontMetrics fm = font.metrics();
	buffer.setUtf8Text(str,size);
	font.shape(buffer);
	font.getTextMetrics(buffer,tm);
	
	return tm.advance.x;
	
	}
	
int drawtext(BLContext ctx,BLFont font,BLPoint point,colortext*colortext,int colorlen,char*str){
		char*c = str;
		float destx = point.x;
		float desty = point.y+font.metrics().ascent+font.metrics().descent;
		float desth;
		
		//desth = font.metrics().ascent;
		desth = font.metrics().ascent+font.metrics().descent+font.metrics().lineGap;
		float newlinex = point.x;
		int d=0 ;int y = 0;
		int index = 0;
		for(int i = 0;*c!='\0';c+=U8_charsize(c)){   
		  //  d = 0; 
			//d = U8_charsize(c);
			if(*c == '\n'){
				
			destx = newlinex;
			desty += desth;
			  i++;
			   continue;
			}
			if(*c==9){
			      
			      //*c = 32;
			    destx += getwidth(font,c,U8_charsize(c));
			   i++;
			   continue;
			      
			}
	        
	        
	        d = U8_charsize(c);
		 //ctx.fillUtf8Text(BLPoint(destx,desty),font,c,U8_charsize(c));
		
		//  destx += getwidth(font,c,U8_charsize(c));
		
		    ctx.setFillStyle(BLRgba32(0,0,0,255));
		   
		//     if(d > 0){
               
        for(int e = 0; e < d;e++){
                
                
        //for(int y = 0; y <colorlen;y++){
        	if(i == colortext[y].position){
        		index = y;y++;
        	}
        //}
        	  if(i>=colortext[index].position&&i<colortext[index].position+colortext[index].range){
        	         
                   ctx.setFillStyle(colortext[index].color);
        	 }
        
        
       //dstRect = fc_render_callback(image, &srcRect, dest, destX, destY, scale.x, scale.y);
                     i++;
    
            }   
              
  //  }

     
      
      
      
      
  /*  for(int y = 0; y <colorlen;y++){
        	if(i == colortext[y].position){
        		index = y;
        	}
        }
        	  if(i>=colortext[index].position&&i<colortext[index].position+colortext[index].range){
    ctx.setFillStyle(colortext[index].color);
    
                }
     */           
               
             
                
		
			ctx.fillUtf8Text(BLPoint(destx,desty),font,c,U8_charsize(c));
		destx += getwidth(font,c,U8_charsize(c));
			
		}
		
		
		
		
	}
	
const char* U8_next(const char* string)
{
    return string + U8_charsize(string);
}
char *get_string_from_file(const char *filename)
{ 
  
    char *result;
    int size = 0;
	int i;
	SDL_RWops *rwops = SDL_RWFromFile(filename, "r");

	char c;
	while (SDL_RWread(rwops, &c, 1, 1) > 0)
	{
		++size;
	}

	result = (char *)malloc(size + 1);
	memset(result, 0, size + 1);
	SDL_RWseek(rwops, 0, RW_SEEK_SET);

	i = 0;
	while (SDL_RWread(rwops, &c, 1, 1) > 0)
	{
		result[i] = c;
		++i;
	}

	SDL_RWclose(rwops);
	return result;
}
int main(){
    SDL_Window * window;
    SDL_Renderer * renderer;
    
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
     
    }
    
    if(!(window = SDL_CreateWindow("win", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE))){
    
    }
    
    if(!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED))){
       
    }
    
    SDL_Event e;
    //SDL_Texture*texture;
   SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0,1080,2172,32,SDL_PIXELFORMAT_ARGB8888);
  
     BLImage img;
    img.createFromData(surface->w,surface->h,BL_FORMAT_PRGB32,(void*)surface->pixels,surface->w*4);
   // BLContextCreateInfo bl_cci;
   // bl_cci.threadCount = 1;
   // BLContext ctx(img,bl_cci);
   BLContext ctx;
   BLPath path;
   BLFontFace fontface;
   BLFont font;
   
  // fontface.createFromFile("/system/fonts/SysSans-Hant-Regular.ttf");
    fontface.createFromFile("/system/fonts/DroidSansFallback.ttf");
   font.createFromFace(fontface,50);
   ctx = BLContext(img);
  
  /*  ctx.setCompOp(BL_COMP_OP_DST_COPY);
    ctx.fillAll();
    
    ctx.setCompOp(BL_COMP_OP_SRC_OVER);
    ctx.setFillStyle(BLRgba32(0,0,0,255));
    ctx.fillRoundRect(50, 50, 400, 400, 50);
    
    ctx.end();
    
  //  img.writeToFile("img.png");
    */
 //   BLImageData data;
    //img.getData(&data);
    //SDL_UpdateTexture(texture, NULL, data.pixelData, int(data.stride));
  //  BLImageData data;
  
    //uint16_t *str = "dd你了bnsjkkkkajjjjs你";
    char *str1  = "你们你";
 
    uint32_t stree[ ] = {0x4f60,0x8fc7};
             // str[0] = 9;
    SDL_Rect rect = {0,0,1080,2172};
     int x = 0;
     int frame = 0;
     uint32_t then = SDL_GetTicks(),now;
     int state = 0;
     colortext color[ ] = {{3,5,{255,0,0,255}}};
     char*code = get_string_from_file("src/main.cpp");
     vector<colortext>color1 ;
     //color1.push_back({2,6,BLRgba32(255,1,0,255)});
     color1= stdd(code);
     printf("%d\n",color1[0].range);
     int xx = 100;
    while (true) {
        frame++;
        xx += 10;
       
        while (SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT)
           
                exit(0);
        }
           x++;
        if(x>360){
        	   x = 0;
        	   }
      // if(state == 0){	    
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
     
        SDL_RenderClear(renderer);
  
      
      //ctx.save();
        ctx.clearAll();
    //  ctx.setCompOp(BL_COMP_OP_DST_OVER);
// ctx.save();
/*ctx.setCompOp(BL_COMP_OP_CLEAR);
   ctx.fillAll();
ctx.setCompOp(BL_COMP_OP_SRC_OVER);
ctx.setFillStyle(BLRgba32(0,0,255,254));
 ctx.fillAll();
 ctx.setCompOp(BL_COMP_OP_SRC_OVER);
   ctx.setFillStyle(BLRgba32(126,255,255,126));
      ctx.rotate(x*M_PI/180,250,250);
    ctx.fillRoundRect(50, 50, 250, 250, 20);
    ctx.strokeCircle(60,60,60);
      ctx.restore();
    //  ctx.rotate(x*M_PI/180,200,200);
    // ctx.restore();
     //ctx.save();
     ctx.setFillStyle(BLRgba32(255,126,126,255));
    ctx.setCompOp(BL_COMP_OP_SRC_OVER);
    ctx.setFillStyle(BLRgba(255,0,0255));
    ctx.fillRoundRect(20,20,100,100,20);
   
    //path.moveTo(60,60);
    path.addBox(60,60,200,200);*/
    ctx.setFillStyle(BLRgba32(0,255,0,255));
   // ctx.fillUtf16Text(BLPoint(60,260),font,str,BLRgba32(255,0,0,255));
   ctx.setStrokeStyle(BLRgba32(0,0,255,255));
   /*ctx.setStrokeWidth(2);
        int y =0;
         int x = getwidth(font,str1,strlen(str1));
        for(int i = 0;*str1 !='\0';str1+=U8_charsize(str1),i++){
       
    / *     char*str;
        str = (char*)malloc(sizeof(char)*4);
        memset(str,0,4);
    	memcpy(str,str1,U8_charsize(str1));
        * /
        //	y+= getwidth(font,str);
        //	printf("%d\n",y);
  ctx.fillUtf8Text(BLPoint(y+60,180),font,str1,U8_charsize(str1));
        // *str1 +=U8_charsize(str1);
           y+= getwidth(font,str1,U8_charsize(str1));
           
           
      }
     // int x = getwidth(font,str1);
   
     ctx.strokeLine(60,180+font.metrics().xHeight,60+x,180+font.metrics().xHeight);
     ctx.strokeLine(60,180+font.metrics().descent-font.metrics().ascent,60+x,180+font.metrics().descent);
    //ctx.fillUtf32Text(BLPoint(200,200),font,stree,2);
    ctx.strokeLine(200,200,300,300);
    //ctx.strokePath(path,BLRgba32(255,0,0,255));
       */
   
    //drawtext(ctx,font,BLPoint(200,200),color,1,"tddd你d\nddd\n你   ggdd");
    drawtext(ctx,font,BLPoint(0,-xx),color1.data(),color1.size(),code);
   
    //ctx.setCompOp(BL_COMP_OP_DST_OVER);
    //ctx.restore();
  //ctx.end();
       //state = 1;
     //  }
   // img.writeToFile("2.png");
 //  BLImageData data;
   
   //  img.getData(&data);
    
     //  SDL_UpdateTexture(texture,NULL,data.pixelData,data.stride);
     //   SDL_SetRenderDrawColor(renderer,0,0,0,255);
   
        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,surface);
       
       
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
        
        SDL_RenderPresent(renderer);
   
       SDL_DestroyTexture(texture);
       
       
        now = SDL_GetTicks();
        if(now>then){
        	if(frame%30==0){
        	//if(((now-then)%2000)>1960){
        	
        		printf("%f\n",((double)frame*1000)/(now-then));
        		printf("%d\n",now-then);
        		frame = 0;
        		then = now;
        
        	//	img.writeToFile("ima.png");
        		}
        	
        
        	}
        //SDL_Delay(2);
     
    }
      
    //  SDL_FreeSurface(surface);
   
   
   
}