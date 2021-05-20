#ifndef SidebarStruct_h
#define SidebarStruct_h

#include "./SimulationObject.h"

/**
 * SettingsSidebarStruct handles displaying a list of SimulationObject(s) created in CinderSimulationApp and returning a pointer to the current selectedObject.
*/
struct SettingsSidebarStruct {
	public:
		SettingsSidebarStruct() {};
		typedef struct SettingsSidebarStruct type;

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

void prepareSettingsSidebar(App::Settings *settings)
{
	settings->setHighDensityDisplayEnabled();
}

#endif