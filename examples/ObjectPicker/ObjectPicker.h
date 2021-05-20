#ifndef ObjectPicker_h
#define ObjectPicker_h

#include "../../src/CinderAppHelper.h"

using namespace std;

class ObjectPicker : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
	void updateSettingsSidebarParameters(bool updateNamesOfObjectsList);
  private:
  	CameraPersp	mCam;
	std::map<std::string, SimulationObject::type> simulationObjectsMap;
	SettingsSidebarStruct::type settingsSidebar;
	params::InterfaceGlRef settingsSidebarParameters;
	bool mPrintFps;
};
#endif