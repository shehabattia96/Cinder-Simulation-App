#ifndef Simple_h
#define Simple_h
#include "cinder/params/Params.h"

#include "../../src/CinderAppHelper.h"

using namespace std;

class Simple : public App {
  public:
	void setup() override;
	void draw() override;
	void resize();
  private:
  	CameraPersp	mCam;
	std::map<std::string, SimulationObject::type> simulationObjectsMap;
};
#endif