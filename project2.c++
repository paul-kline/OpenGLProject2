// project2.c++: Starter for EECS 672 Project 2

#include "GLFWController.h"
#include "TEMPLATE_Subclass.h"
#include "Simpleshape.h"
#include "Column.h"
#include "Block.h"
#include "Cylinder.h"
#include "Stairs.h"

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
	
	cryph::AffPoint bottom2(5,6,7);
	cryph::AffPoint top2(4,4,4);
	float color2[3] = {0,1,0};
	Column column2(bottom2,2,top2,2,color2,true);
	double bounds[6];
	column1.getMCBoundingBox(bounds);
	c.addModel(&column2);
//	std::cout << "colum1 bounds: " << bounds[0] << ", " << bounds[1] <<  bounds[2] << ", " << bounds[3] <<  bounds[4] << ", " << bounds[5] << "\n\ndone!";
	
	//block test;
	float color3[3] = {1.0,0.3,0.7};
	Block block1(2, 5, 2, cryph::AffVector(0,1,0), cryph::AffPoint(-4,-6,8) ,cryph::AffPoint(-4,-6,2), color3);
//	c.addModel(&block1);
	
	//stairs test
	Stairs stairs(2, 5, 2, cryph::AffVector(0,1,0), cryph::AffPoint(-4,0,8) ,cryph::AffPoint(-4,0,2), color3, 
		      0.2, 10, false);

	double bounds2[6];
	stairs.getMCBoundingBox(bounds2);
//	c.addModel(&column2);
	std::cout << "stair bounds: " << bounds2[0] << ", " << bounds2[1] <<", " <<  bounds2[2] << ", " << bounds2[3] <<", " <<   bounds2[4] << ", " << bounds2[5] << "\n\ndone!";
	
	
	glClearColor(1.0, 1.0, 0.70, 1.0);

	double xyz[6];
	c.getOverallMCBoundingBox(xyz);
	std::cout << "TOTAL  bounds: " << xyz[0] << ", " << xyz[1] <<", " <<  xyz[2] << ", " << xyz[3] <<", " <<   xyz[4] << ", " << xyz[5] << "\n\ndone!";
	set3DViewingInformation(xyz);

	c.run();

	return 0;
}
