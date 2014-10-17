// project2.c++: Starter for EECS 672 Project 2

#include "GLFWController.h"
#include "TEMPLATE_Subclass.h"
#include "Simpleshape.h"
#include "Column.h"
#include "Cylinder.h"

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
	zmin = zpp - maxDelta;
	zmax = zpp + 0.5*maxDelta;
	ModelView::setProjection(PERSPECTIVE);
	ModelView::setProjectionPlaneZ(zpp);
	ModelView::setECZminZmax(zmin, zmax);
}

int main(int argc, char* argv[])
{
  
	ModelViewWithLighting::setShaderSources("vsh.c++", "fsh.c++");
	GLFWController c("GIVE ME A NICE TITLE", MVC_USE_DEPTH_BIT);
	c.reportVersions(std::cout);
	ModelViewWithLighting::setShaderSources("vsh.c++", "fsh.c++");
	// create your scene, adding things to the Controller....
	
	Column::instances = 0;
	cryph::AffPoint bottom(0.0,0.0,0.0);
	cryph::AffPoint top(1,1,1);
	float color[3] = {1,0,0};
	Column column1(bottom,1,top,1,color);
	double bounds[6];
	column1.getMCBoundingBox(bounds);
	std::cout << "colum1 bounds: " << bounds[0] << ", " << bounds[1] <<  bounds[2] << ", " << bounds[3] <<  bounds[4] << ", " << bounds[5] << "\n\n";
	c.addModel(&column1);
	//c.addModel(new Simpleshape());
	c.addModel(new Cylinder());

	glClearColor(1.0, 1.0, 0.70, 1.0);

	double xyz[6];
	c.getOverallMCBoundingBox(xyz);
	set3DViewingInformation(xyz);

	c.run();

	return 0;
}
