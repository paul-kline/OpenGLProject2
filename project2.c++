// project2.c++: Starter for EECS 672 Project 2

#include "GLFWController.h"
#include "TEMPLATE_Subclass.h"
#include "Simpleshape.h"
#include "Column.h"
#include "Block.h"
#include "Cylinder.h"
#include "Stairs.h"
#include "HalfColumn.h"
#include "FancyColumn.h"
#include "SuperFancyColumn.h"
void set3DViewingInformation(double xyz[6])
{
	ModelView::setMCRegionOfInterest(xyz);

	//cryph::AffPoint eye, center;
	//cryph::AffVector up;

	// Set values for eye-center-up to produce a reasonable off-axis
	// view of your scene, then:

	double xmid = 0.5 * (xyz[0] + xyz[1]);
	double ymid = 0.5 * (xyz[2] + xyz[3]);
	double zmid = 0.5 * (xyz[4] + xyz[5]);
	cryph::AffPoint center(xmid, ymid, zmid);

	// 2:
	double maxDelta = xyz[1] - xyz[0];
	double delta = xyz[3] - xyz[2];
	if (delta > maxDelta){
	  maxDelta = delta;
	}
	delta = xyz[5] - xyz[4];
	if (delta > maxDelta){
	  maxDelta = delta;
	}
	double distEyeCenter = 2.0 * maxDelta;
	cryph::AffPoint eye(xmid, ymid, zmid + distEyeCenter);

	cryph::AffVector up = cryph::AffVector::yu;
	
	
	
	
	
	
	
	// Notify the ModelView of our MC->EC viewing requests:
	ModelView::setEyeCenterUp(eye, center, up);

	double zpp, zmin, zmax;

	// Set values for zpp, zmin, zmax that make sense in the context of
	// the EC system established above, then:

	zpp = -(distEyeCenter - 0.5*maxDelta);
	zmin = zpp - 1.5*maxDelta;
	zmax = zpp + maxDelta; //changed from half maxDelta
	ModelView::setProjection(PERSPECTIVE);
	ModelView::setProjectionPlaneZ(zpp);
	ModelView::setECZminZmax(zmin, zmax);
}

int main(int argc, char* argv[])
{
  
//   cryph::AffVector test(1,1,1);
//   std::cout << "before: " << test.dx << ", " << test.dy << ", " << test.dz <<"\n";
//   test = -test;
//   std::cout << "after negation: " << test.dx << ", " << test.dy << ", " << test.dz;
	ModelViewWithLighting::setShaderSources("vsh.c++", "fsh.c++");
	GLFWController c("Solomon's Temple", MVC_USE_DEPTH_BIT);
	c.reportVersions(std::cout);
	ModelViewWithLighting::setShaderSources("vsh.c++", "fsh.c++");
	// create your scene, adding things to the Controller....
	
	Column::instances = 0;
	cryph::AffPoint bottom1(-1.0,2,9);
	cryph::AffPoint top1(1,1,1);
	float color1[3] = {1,1,0};
	Column column1(bottom1,1,top1,3,color1,true);
	c.addModel(&column1);
	
	
//	std::cout << "colum1 bounds: " << bounds[0] << ", " << bounds[1] <<  bounds[2] << ", " << bounds[3] <<  bounds[4] << ", " << bounds[5] << "\n\ndone!";
	
	
	double bounds2[6];
	//stairs.getMCBoundingBox(bounds2);
//	c.addModel(&column2);
	//std::cout << "stair bounds: " << bounds2[0] << ", " << bounds2[1] <<", " <<  bounds2[2] << ", " << bounds2[3] <<", " <<   bounds2[4] << ", " << bounds2[5] << "\n\ndone!";
	
	
	//begin real project stuff;
	// base block ;
	float groundColor[3] = {0.000, 0.392, 0.000}; // dark green
	Block ground(1,200, 300, cryph::AffVector(0,1,0), cryph::AffPoint(-100,-1,0) ,cryph::AffPoint(100,-1,0), groundColor);
	c.addModel(&ground);
	
	cryph::AffPoint buildingFrontLeft(-50, 0,-80); // most important point to define!!
	cryph::AffPoint buildingFrontRight(50,0,-80); // this is fixed if stupid, but will be corrected to a ray specified by (right-left) vector. 
	cryph::AffVector buildingUpVector(0,1,0);
	float buildingHeight=30;
	float buildingWidth = 100;
	float buildingLength = 30;
	float buildingColor[3] = {0.961, 0.871, 0.702}; //wheat
	//just to check myself
	if( (buildingFrontLeft-buildingFrontRight).length() != buildingWidth){
	    cryph::AffVector v1 = buildingFrontRight-buildingFrontLeft;
	    v1.normalize();
	    v1*=buildingWidth;
	    buildingFrontRight = buildingFrontLeft + v1;
	}
	Block building(buildingHeight,buildingWidth, buildingLength, buildingUpVector, buildingFrontLeft ,buildingFrontRight, buildingColor);
	c.addModel(&building);
	
	cryph::AffPoint stairsBackCenter = (buildingFrontLeft + buildingFrontRight) /2;
	float stairWidthPercentOfBuildingFront = 0.70;
	float stairWidth = stairWidthPercentOfBuildingFront * buildingWidth;
	cryph::AffPoint stairsBackLeft = stairsBackCenter - ((buildingFrontRight - buildingFrontLeft)*stairWidthPercentOfBuildingFront)/2;
	cryph::AffPoint stairsBackRight = stairsBackCenter + ((buildingFrontRight - buildingFrontLeft)*stairWidthPercentOfBuildingFront)/2;
	cryph::AffVector towardsBuildingBack = buildingUpVector.cross((buildingFrontRight-buildingFrontLeft));
	towardsBuildingBack.normalize();
	float stairLengthPercentOfBuildingFront = 0.35;
	float stairLength = stairLengthPercentOfBuildingFront * buildingWidth;
	cryph::AffVector getUsToStairfront =  (-towardsBuildingBack)*stairLength;
	cryph::AffPoint stairFrontLeft = stairsBackLeft + getUsToStairfront;
	cryph::AffPoint stairFrontRight = stairsBackRight + getUsToStairfront;
	
	float stairHeightPercentOfBuildingHeight = 1;
	int numStairs = 9;
	float eachStepHeight = (stairHeightPercentOfBuildingHeight * buildingHeight)/numStairs; 
	
	//stairs test
	Stairs stairs(eachStepHeight, stairWidth, stairLength, buildingUpVector, stairFrontLeft ,stairFrontRight, buildingColor, 
		      eachStepHeight, numStairs, true);

	
	
	
	
	//test a half cylinder

	float color2[3] = {0,1,0};
	cryph::AffPoint startP = stairFrontLeft + (stairFrontRight - stairFrontLeft);
	float myradius = (stairFrontRight-stairFrontLeft).length();
	HalfColumn halfColumn( stairFrontLeft,myradius,(stairFrontLeft + (buildingUpVector*20)),200,color2,false,false, 3.14159/1,startP);
	double bounds[6];
	//column1.getMCBoundingBox(bounds);
	c.addModel(&halfColumn);
	/*
	  cryph::AffPoint b(0,200,0);
	   cryph::AffPoint t(0,220,0);
	   cryph::AffPoint s(5,200,0);
	   
	*///   HalfColumn halfColumn1(b , 5, t,5,color2,false,false, 3.14159 ,s);
	//c.addModel(&halfColumn1);
	//test a fancy column
	//FancyColumn(cryph::AffPoint bottom_,float bradius_, cryph::AffPoint top_, float tradius_, float color_[3], bool capped_, int numCircs_);
	FancyColumn fancyColumn(stairFrontLeft, myradius, (stairFrontLeft + (buildingUpVector*20)), myradius, color2, false, 9);
	
	
	
	
	//test super fancy column
	
	//SuperFancyColumn(float height_, float width_, cryph::AffPoint bottomLeft_,cryph::AffVector upVector_, cryph::AffVector toRightFrontVector_,float color_[3]);
	SuperFancyColumn SuperFancyColumn(buildingHeight*4,buildingWidth,buildingFrontLeft + 2*buildingFrontRight, buildingUpVector, buildingFrontRight-buildingFrontLeft, buildingColor, 10);
	//Block base (buildingHeight,buildingWidth, buildingWidth, buildingUpVector, buildingFrontLeft + 2*buildingFrontRight ,buildingFrontRight + 2*buildingFrontRight, buildingColor);
	
	//c.addModel(&base);
	
	
	
	glClearColor(1.0, 1.0, 0.70, 1.0);

	double xyz[6];
	c.getOverallMCBoundingBox(xyz);
	std::cout << "TOTAL  bounds: " << xyz[0] << ", " << xyz[1] <<", " <<  xyz[2] << ", " << xyz[3] <<", " <<   xyz[4] << ", " << xyz[5] << "\n\ndone!";
	set3DViewingInformation(xyz);

	c.run();

	return 0;
}
