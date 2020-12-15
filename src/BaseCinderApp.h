#ifndef BaseCinderApp_h
#define BaseCinderApp_h

#include "./SimulationObject.h"
#include "./Sidebar.h"

class BaseCinderApp : public App {
	public:
		void setup() override;
		void update() override;
		void draw() override;
		void draw(bool clearCanvas);
		void resize();
		std::map<std::string, SimulationObject::type>* getSimulationObjectsMap();
	
	protected:
		CameraPersp	mCam;
		std::map<std::string, SimulationObject::type> mSimulationObjectsMap;
		SettingsSideBarStruct::type settingsSideBar;
};

std::map<std::string, SimulationObject::type>* BaseCinderApp::getSimulationObjectsMap() {
	return &(this->mSimulationObjectsMap);
}

void BaseCinderApp::draw(bool skipClearCanvas) {
	if (!skipClearCanvas) gl::clear( Color( 0.5, 0.5, 0.5 ) ); // this is required
	BaseCinderApp::draw();
}

// call gl::clear() if you are calling draw() directly. 
void BaseCinderApp::draw()
{ // this is called every frame per second per window
	gl::setMatrices( mCam );
	
	for ( const auto &mSimulationObjectsKeyValuePair : mSimulationObjectsMap )
	{
		// pushes and pops model, replaces gl::pushModelMatrix(); and gl::popModelMatrix(); 
		gl::ScopedModelMatrix scpModelMtx;

		// grab the SimulationObject and call its draw metod
			// string objectName = mSimulationObjectsKeyValuePair.first;
		SimulationObject object = mSimulationObjectsKeyValuePair.second;
		object.draw();
	}
}

void BaseCinderApp::setup()
{
	// mCam.lookAt( vec3( -15, -5, -2 ), vec3( 0, 0.5f, 0 ) );
}

void BaseCinderApp::resize()
{
	this->mCam.setAspectRatio( getWindowAspectRatio() ); // helps keep the drawn objects' scale when the GUI window is resized.
}

void BaseCinderApp::update()
{}

#endif