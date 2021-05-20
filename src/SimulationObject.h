#ifndef SimulationObject_h
#define SimulationObject_h

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Shader.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;

/**
 * SimulationObject stores a geom::Source, generates the gl::BatchRef and handles the transformations and drawing of a geom::Source.
 * 
 * Example use:
geom::SourceMods slice = geom::Cube();
SimulationObject cube(slice >> geom::Translate(ci::vec3(0, 2, 0)), shader);
mSimulationObjectsMap["cube"] = cube;

* Example cube transformation:
SimulationObject* cube = &mSimulationObjectsMap["cube"];
cube->translation = ci::vec3(2 + cube->translation.x, 0, 0);
cube->rotation = angleAxis(.5f + cube->rotation.w, vec3( 0, 0, 0 ) );
cube->scale = ci::vec3(1 + cube->scale.x, 0, 0);

* Example change color:
Color redColor = Color( CM_RGB, 1, 0, 0 );
cube2->color = redColor;
 */
struct SimulationObject {

	private: // we perform additional logic when these are modified
		geom::SourceMods source; // e.g. geom::SourceMods source = geom::Cube();
		gl::GlslProgRef shader;
		gl::BatchRef batchRef;

	public:
		SimulationObject() {}
		virtual ~SimulationObject() {}
		
		SimulationObject(geom::SourceMods sourceIn) : source(sourceIn) {
			this->shader = gl::getStockShader( gl::ShaderDef().lambert().color() );
			rebuildBatchRef();
		}
		SimulationObject(geom::SourceMods sourceIn, gl::GlslProgRef shaderIn) : source(sourceIn), shader(shaderIn) {
			if (shaderIn == NULL) {
				auto colorShader = gl::ShaderDef().lambert().color();
				auto stockShader = gl::getStockShader( colorShader );
				this->shader = stockShader;
			}
			rebuildBatchRef();
		}

		void rebuildBatchRef() {
			this->batchRef = gl::Batch::create( this->source, this->shader );
		}

		gl::BatchRef getBatchRef() {
			return this->batchRef;
		}

		geom::SourceMods getSource() {
			return this->source;
		}

		void setSourceAndRebuildBatchRef(geom::SourceMods source) {
			this->source = source;
			rebuildBatchRef();
		}
		
		void setShaderAndRebuildBatchRef(gl::GlslProgRef shader) {
			this->shader = shader;
			rebuildBatchRef();
		}
		
		typedef struct SimulationObject type;

		ci::ColorA color = ci::ColorA( CM_RGB, 1, 0.5, 0.25, 1 );
		
		glm::highp_quat rotation = angleAxis( 0.f, vec3( 0, 0, 0 ) );
		ci::vec3 translation = ci::vec3(0, 0, 0);
		ci::vec3 scale = ci::vec3(1, 1, 1);

		mat4 worldPose;

		std::function<void()> preDrawFunction = NULL;

		void draw() {
			if (preDrawFunction != NULL) preDrawFunction();

			gl::multModelMatrix(this->worldPose);
			gl::translate(this->translation);
			gl::rotate(this->rotation);
			gl::scale(this->scale);
			gl::color(this->color);

			this->batchRef->draw();
		}

};

#endif