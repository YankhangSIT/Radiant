//---------------------------------------------------------
// file:	button.h
// author:	Lua Wei Xiang Darren, Jing Song
// email:	weixiangdarren.lua@digipen.edu, jingsong.wei@digipen.edu
// brief:	Header file containing function prototypes and declarations related to buttons
//
// Copyright 2022 DigiPen, All rights reserved.
//---------------------------------------------------------


/*Variable declarations that can be set to choose how much to increase the button size when hovered over*/
float buttonWidthOffset;
float buttonHeightOffset;

void Button(char *string, float posX, float posY, float txtPosX, float txtPosY, float width, float height, int colorRed, int colorBlue, int colourGreen, int textRed, int textBlue, int textGreen, int alpha);
void TriButton(float posX1, float posY1, float posX2, float posY2, float posX3, float posY3, float degree, float txtPosX, float txtPosY, int colorRed, int colorBlue, int colourGreen, int textRed, int textBlue, int textGreen, int alpha);
void sliderBox(float posX, float posY, int width, int height, int colorRed, int colorBlue, int colourGreen, int alpha);
void sliderBar(float posX, float posY, int width, int height, int colorRed, int colorBlue, int colourGreen, int alpha);

