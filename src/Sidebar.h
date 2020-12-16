#ifndef SidebarStruct_h
#define SidebarStruct_h

#include "./SimulationObject.h"

/**
 * SettingsSideBarStruct handles displaying a list of SimulationObject(s) created in CinderSimulationApp and returning a pointer to the current selectedObject.
*/
struct SettingsSideBarStruct {
	public:
		SettingsSideBarStruct() {};
		typedef struct SettingsSideBarStruct type;

		std::vector<std::string> namesOfObjects;

		SimulationObject* selectedObject = NULL;

		int selectedObjectIndex = 0;

		void setSelectedObject(std::map<std::string, SimulationObject::type>* simulationObjectsMap) {
			if (this->namesOfObjects.size() > 0)
				this->selectedObject = &simulationObjectsMap->at(this->namesOfObjects[this->selectedObjectIndex]);
		}

		SimulationObject* getSelectedObject() {
            return this->selectedObject;
		}

		void updateNamesOfObjectsList(std::map<std::string, SimulationObject::type>* simulationObjectsMap) {
			this->namesOfObjects.clear();
			for ( const auto &simulationObjectsKeyValuePair : *simulationObjectsMap )
			{
				std::string objectName = simulationObjectsKeyValuePair.first;
				this->namesOfObjects.push_back(objectName);
			}
			setSelectedObject(simulationObjectsMap);
		}
};

void prepareSettingsSideBar(App::Settings *settings)
{
	settings->setHighDensityDisplayEnabled();
}

#endif