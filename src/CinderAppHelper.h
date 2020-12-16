#ifndef CinderSimulationApp_h
#define CinderSimulationApp_h

#include "./SimulationObject.h"
#include "./Sidebar.h"

void onDraw(CameraPersp& mCam, bool skipClearCanvas) {
	if (!skipClearCanvas) gl::clear( Color( 0.5, 0.5, 0.5 ) ); // this is required
	gl::setMatrices( mCam );
}

void drawSimulationObjects(std::map<std::string, SimulationObject::type>& simulationObjectsMap)
{	
	for ( const auto &simulationObjectsKeyValuePair : simulationObjectsMap )
	{
		// pushes and pops model, replaces gl::pushModelMatrix(); and gl::popModelMatrix(); 
		gl::ScopedModelMatrix scpModelMtx;

		// grab the SimulationObject and call its draw metod
			// string objectName = simulationObjectsKeyValuePair.first;
		SimulationObject object = simulationObjectsKeyValuePair.second;
		object.draw();
	}
}

void onResizeWindow(CameraPersp& mCam)
{
	mCam.setAspectRatio( getWindowAspectRatio() ); // helps keep the drawn objects' scale when the GUI window is resized.
}

#endif