// SuperFancyColumn.c++

#include "SuperFancyColumn.h"
#include "ShaderIF.h"
#include <cmath>
#include "GLFWController.h"
#include "HalfColumn.h"
#include "Block.h"



  



SuperFancyColumn::SuperFancyColumn(float height_, float width_, cryph::AffPoint bottomLeft_,cryph::AffVector upVector_, cryph::AffVector toRightFrontVector_,float color_[3], int numFancies_){

  height = height_;
  width = width_;
  bottomLeft = bottomLeft_;
  numFancies= numFancies_;
  toRightFrontVector = toRightFrontVector_;
  toRightFrontVector.normalize(); //just in case I was silly.
  
  upVector=upVector_;
  upVector.normalize();
 color[0] = color_[0];
 color[1] = color_[1];
 color[2] = color_[2];
 
 defineSuperFancyColumn();

  black[0] =0.0; black[1] =0.0; black[2]=0.0;
 //for moving the eye.
  
  
  
};

SuperFancyColumn::~SuperFancyColumn()
{
  
}



void SuperFancyColumn::defineSuperFancyColumn()
{
  
  float blockHeightPercentage = 0.05;
  float leadingColumnHeightPercentage = 0.05;
  float fancyColumnHeightPercentage = 1 - (2*blockHeightPercentage + 2*leadingColumnHeightPercentage); // he gets the rest
  float radiusPercentOfWidth = 0.90;
  
  float blockHeight = blockHeightPercentage * height;
  float blockWidth = width;
  
  
  //Block(float height_, float width_, float length_, cryph::AffVector normal_,cryph::AffPoint frontLeftBottomCorner_,cryph::AffPoint frontRightBottomCorner_, vec3 color_)
  baseBlock = *(new Block(blockHeight, blockWidth,blockWidth, upVector, bottomLeft, bottomLeft + (blockWidth*toRightFrontVector),color));
  
  cryph::AffPoint secondBottomLeft = (bottomLeft + (upVector* (height - blockHeight)));
  cryph::AffPoint secondBottomRight = secondBottomLeft + (blockWidth*toRightFrontVector);
  topBlock = *(new Block(blockHeight,blockWidth,blockWidth, upVector, secondBottomLeft,secondBottomRight,color));
  
  //now the leader columns
  //Column(cryph::AffPoint bottom_, float bradius_, cryph::AffPoint top_, float tradius_, float color_[6], bool capped_)
  cryph::AffVector towardsBack = upVector.cross(toRightFrontVector);
  towardsBack.normalize();
    cryph::AffPoint bottom_dead_centerPoint = (bottomLeft + ((blockWidth/2)*toRightFrontVector)) + ((blockWidth/2)*towardsBack);
    cryph::AffPoint lowercolumnbottom = bottom_dead_centerPoint + (blockHeight*upVector);
    float leadingcolRadius = (radiusPercentOfWidth*blockWidth)/2;
    float smallerRadius = 0.80 * leadingcolRadius; //lets try 80% of the big one.
    float leadingcolHeight = leadingColumnHeightPercentage*height;
    
  lowerColumn= *(new Column(lowercolumnbottom, leadingcolRadius, (lowercolumnbottom + (leadingcolHeight*upVector)), smallerRadius, color, true));
  
  cryph::AffPoint topColumnBottom = lowercolumnbottom + (leadingcolHeight * upVector) + fancyColumnHeightPercentage*height*upVector ;
  topColumn = *(new Column(topColumnBottom + (leadingcolHeight*upVector) ,leadingcolRadius , topColumnBottom ,smallerRadius  ,color,true));
  
  
  //FancyColumn(cryph::AffPoint bottom_, float bradius_, cryph::AffPoint top_, float tradius_, float color_[3], bool capped_, int numCircs_){
  fancyColumn = *(new FancyColumn( (lowercolumnbottom + leadingcolHeight*upVector) , smallerRadius, topColumnBottom, smallerRadius, color,false,numFancies));
  
  
  Controller* c = GLFWController::getCurrentController();
  
  c->addModel(&baseBlock);
  c->addModel(&topBlock);
  c->addModel(&lowerColumn);
  c->addModel(&topColumn);
  
  
  
  
  
  
  
}






