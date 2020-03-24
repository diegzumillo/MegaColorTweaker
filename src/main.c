#include <genesis.h>
#include "../inc/Input.h"
#include "../res/sprite.h"

#define POSX 175
#define POSY 190

//things we want to test:
Sprite* sprite1;
Image* img1;
Image* img2;


//interface vars
Sprite* palSp0;
Sprite* palSp1;
Sprite* palSp2;
Sprite* palSp3;

Sprite* downArrowSp;
Sprite* rightArrowSp;

u8 palSel = 0;
u8 colSel = 0;

void Controls();
void SelPal();
void SelCol();

//a little helped function to print numbers on the screen
char* itoa2(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

int main(){

    // initialization
    VDP_setScreenWidth320();

    // init sprites engine
    SPR_init(80, 0, 0);
		
	JOY_init();
    JOY_setEventHandler( &InputHandler );

    VDP_setPalette(PAL1, spritedef1.palette->data);
    sprite1 = SPR_addSprite(&spritedef1, 50, 50, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
    // VDP_setPalette(PAL2, imgdef1.palette->data);
    // img1 = VDP_drawImageEx(PLAN_A, &imgdef1,)
    // VDP_setPalette(PAL3, imgdef2.palette->data);
    // img2 = SPR_addSprite(&imgdef2, 50, 50, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

    VDP_setPalette(PAL2, imgdef1.palette->data);
    VDP_setPalette(PAL3, imgdef2.palette->data);
    int ind = TILE_USERINDEX;
    VDP_drawImageEx(PLAN_A, &imgdef1, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, DMA);
    ind += imgdef1.tileset->numTile;
    VDP_drawImageEx(PLAN_B, &imgdef2, TILE_ATTR_FULL(PAL3, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, DMA);
    ind += imgdef2.tileset->numTile;

    VDP_clearTileMapRect(PLAN_A, 0, 22, 40,8);
    VDP_clearTileMapRect(PLAN_B, 0, 22, 40,8);

    //"interface"
    VDP_setPalette(PAL0, rightArrowSpDef.palette->data);
    palSp0 = SPR_addSprite(&palSpriteDef, POSX, POSY, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    palSp1 = SPR_addSprite(&palSpriteDef, POSX, POSY + 9, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
    palSp2 = SPR_addSprite(&palSpriteDef, POSX, POSY + 18, TILE_ATTR(PAL2, TRUE, FALSE, FALSE));
    palSp3 = SPR_addSprite(&palSpriteDef, POSX, POSY + 27, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));

    rightArrowSp = SPR_addSprite(&rightArrowSpDef, POSX - 8, POSY, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    downArrowSp = SPR_addSprite(&downArrowSpDef, POSX, POSY - 8, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    SelPal();
    SelCol();

    while(TRUE){
        
        Controls();

        ResetInputFlags();
        SPR_update();
        VDP_waitVSync();
    }
    return 0;
}

void Controls(){
    
    if(btndown_Up){
        if(palSel==0)
            palSel = 3;
        else
            palSel--;
        SelPal();
    }else if(btndown_Down){
        if(palSel==3)
            palSel = 0;
        else
            palSel++;
        SelPal();
    }

    if(btndown_Left){
        if(colSel==0)
            colSel = 15;
        else
            colSel--;
        SelCol();
    }else if(btndown_Right){
        if(colSel==15)
            colSel = 0;
        else
            colSel++;
        SelCol();
    }

    u16 selection = colSel + palSel * 16;
    u16 curColor = PAL_getColor(selection);
    //u16 comp1 = (curColor & 0xF000) >> 12;
    u16 blue = ((curColor & 0x0F00) >> 8)>>1;
    u16 green = ((curColor & 0x00F0) >> 4)>>1;
    u16 red = (curColor & 0x000F)>>1;
    // u16 comp1 = (curColor) >> 6;
    // u16 comp2 = (curColor & 0x0038) >> 3;
    // u16 comp3 = (curColor & 0x0007) ;

    
    if(btndown_A){
        if(blue == 0){
            blue = 7;
        }else
            blue--;
        
    }else if(btndown_X){
        if(blue == 7)
            blue = 0;
        else
            blue++;
    }
    if(btndown_B){
        if(green == 0)
            green = 7;
        else
            green--;
        
    }else if(btndown_Y){
        if(green == 7)
            green = 0;
        else 
            green++;
    }
    if(btndown_C){
        if(red == 0)
            red = 7;
        else
            red--;
        
    }else if(btndown_Z){
        if(red == 7)
            red = 0;
        else 
            red++;
    }

    //u16 newColor = (blue << 8)|(green << 4)|(red);
    u16 newColor = (blue << 9)|(green << 5)|(red<<1);

    
    PAL_setColor(selection, newColor);

    char blah[5];
    //curColor = sizeof(u16);
    VDP_clearTextLine(27);
    VDP_clearTextLine(26);
    
    VDP_drawText(itoa2((blue)/7.0f*255.0f , blah),5,27);
    VDP_drawText(itoa2((green)/7.0f*255.0f , blah),10,27);
    VDP_drawText(itoa2((red)/7.0f*255.0f , blah),15,27);

    VDP_drawText("B",5,26);
    VDP_drawText("G",10,26);
    VDP_drawText("R",15,26);

}

void SelPal(){   
    SPR_setPosition(rightArrowSp, POSX-8, POSY + palSel*9);
}

void SelCol(){
    SPR_setPosition(downArrowSp, POSX + colSel * 8 , POSY -8);
}