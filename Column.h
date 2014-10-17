// Column.h

#ifndef COLUMN_SUBCLASS_H
#define COLUMN_SUBCLASS_H

#include "ModelViewWithLighting.h"

class Column : public ModelViewWithLighting
{
public:
	Column(cryph::AffPoint bottom_,float bradius_, cryph::AffPoint top_, float tradius_, float color_[3]);
	virtual ~Column();

	cryph::AffPoint bottom;
	cryph::AffPoint top;
	float myBounds[6];
	float color[3];
	float bradius;
	float tradius;
	static int instances;
	
	
	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	GLuint vao[1];
	GLuint vbo[2];
  
  
	cryph::AffVector defineStarter();
	void defineColumn();
	void renderColumn();
	void setBounds();
};

#endif
