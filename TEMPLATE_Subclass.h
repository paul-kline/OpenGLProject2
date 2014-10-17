// TEMPLATE_Subclass.h

#ifndef TEMPLATE_SUBCLASS_H
#define TEMPLATE_SUBCLASS_H

#include "ModelViewWithLighting.h"

class TEMPLATE_Subclass : public ModelViewWithLighting
{
public:
	TEMPLATE_Subclass();
	virtual ~TEMPLATE_Subclass();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
};

#endif
