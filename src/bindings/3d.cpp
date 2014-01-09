/*
 * Copyright (c) 2013 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxLua for documentation
 *
 */
#include "of3dUtils.h"
#include "ofCamera.h"
#include "ofEasyCam.h"
#include "ofMesh.h"
#include "ofNode.h"
#include "ofxLua.h"

// wrapper functions needed for overloading

void drawGrid0() {return ofDrawGrid();}
void drawGrid1(float scale) {return ofDrawGrid(scale);}
void drawGrid2(float scale, float ticks) {return ofDrawGrid(scale, ticks);}
void drawGrid3(float scale, float ticks, bool labels)
	{return ofDrawGrid(scale, ticks, labels);}
void drawGrid4(float scale, float ticks, bool labels, bool x)
	{return ofDrawGrid(scale, ticks, labels, x);}
void drawGrid5(float scale, float ticks, bool labels, bool x, bool y)
	{return ofDrawGrid(scale, ticks, labels, x, y);}

void drawGridPlane1(float scale) {ofDrawGridPlane(scale);}
void drawGridPlane2(float scale, float ticks) {ofDrawGridPlane(scale, ticks);}

void drawArrow2(const ofVec3f& start, const ofVec3f& end) {ofDrawArrow(start, end);}

void drawRotationAxes1(float radius) {ofDrawRotationAxes(radius);}
void drawRotationAxes2(float radius, float stripWidth) {ofDrawRotationAxes(radius, stripWidth);}

void cameraSetupPerspective0(ofCamera *cam) {cam->setupPerspective();}
void cameraSetupPerspective1(ofCamera *cam, bool vFlip) {cam->setupPerspective(vFlip);}
void cameraSetupPerspective2(ofCamera *cam, bool vFlip, float fov)
	{cam->setupPerspective(vFlip, fov);}
void cameraSetupPerspective3(ofCamera *cam, bool vFlip, float fov, float nearDist)
	{cam->setupPerspective(vFlip, fov, nearDist);}
void cameraSetupPerspective4(ofCamera *cam, bool vFlip, float fov, float nearDist, float farDist)
	{cam->setupPerspective(vFlip, fov, nearDist, farDist);}

float cameraGetImagePlaneDistance0(ofCamera *cam) {return cam->getImagePlaneDistance();}
void cameraBegin0(ofCamera *cam) {cam->begin();}

ofMatrix4x4 cameraGetProjectionMatrix0(ofCamera *cam)
	{return cam->getProjectionMatrix();}
ofMatrix4x4 cameraGetModelViewMatrix0(ofCamera *cam)
	{return cam->getModelViewMatrix();}
ofMatrix4x4 cameraGetModelViewProjectionMatrix0(ofCamera *cam)
	{return cam->getModelViewProjectionMatrix();}

ofVec3f cameraWorldToScreen1(ofCamera *cam, ofVec3f WorldXYZ) {return cam->worldToScreen(WorldXYZ);}
ofVec3f cameraScreenToWorld1(ofCamera *cam, ofVec3f ScreenXYZ) {return cam->screenToWorld(ScreenXYZ);}
ofVec3f cameraWorldToCamera1(ofCamera *cam, ofVec3f WorldXYZ) {return cam->worldToCamera(WorldXYZ);}
ofVec3f cameraCameraToWorld1(ofCamera *cam, ofVec3f CameraXYZ) {return cam->cameraToWorld(CameraXYZ);}

ofPoint meshGetTexCoord(ofMesh* mesh, int i)
	{return ofPoint(mesh->getTexCoord(i));}
void meshSetTexCoord(ofMesh* mesh, int i, const ofPoint& p)
	{mesh->setTexCoord(i, ofVec2f(p.x, p.y));}
void meshAddTexCoord(ofMesh* mesh, const ofPoint& p)
	{mesh->addTexCoord(ofVec2f(p.x, p.y));}
void meshSave1(ofMesh* mesh, string path)
	{mesh->save(path);}
void meshSetFromTriangles1(ofMesh *mesh,  const vector<ofMeshFace>& tris)
	{mesh->setFromTriangles(tris);}

void nodeSetParent1(ofNode *node, ofNode& parent) {node->setParent(parent);}
void nodeClearParent0(ofNode *node) {node->clearParent();}

void nodeLookAt1V(ofNode *node, const ofVec3f& lookAtPosition)
	{node->lookAt(lookAtPosition);}
void nodeLookAt1N(ofNode *node, const ofNode& lookAtNode)
	{node->lookAt(lookAtNode);}

void nodeOrbit3(ofNode *node, float longitude, float latitude, float radius)
	{node->orbit(longitude, latitude, radius);}

// luabind registration
luabind::scope register3d() {
		
	using namespace luabind;
	
	return
		
		///////////////////////////////
		/// \section of3dUtils.h
		
		def("drawAxis", &ofDrawAxis),
		
		def("drawGrid", &drawGrid0),
		def("drawGrid", &drawGrid1),
		def("drawGrid", &drawGrid2),
		def("drawGrid", &drawGrid3),
		def("drawGrid", &drawGrid4),
		def("drawGrid", &drawGrid5),
		def("drawGrid", &ofDrawGrid),
		
		def("drawGridPlane", &drawGridPlane1),
		def("drawGridPlane", &drawGridPlane2),
		def("drawGridPlane", &ofDrawGridPlane),
		
		def("drawArrow", &drawArrow2),
		def("drawArrow", &ofDrawArrow),

		def("drawRotationAxes", &drawRotationAxes1),
		def("drawRotationAxes", &drawRotationAxes2),
		def("drawRotationAxes", &ofDrawRotationAxes),
		
		
		///////////////////////////////
		/// \section ofCamera.h
		
		class_<ofCamera>("Camera")
			.def(constructor<>())
			
			.property("fov", &ofCamera::getFov, &ofCamera::setFov)
			.property("nearClip", &ofCamera::getNearClip, &ofCamera::setNearClip)
			.property("farClip", &ofCamera::getFarClip, &ofCamera::setFarClip)
			.property("lensOffset", &ofCamera::getLensOffset, &ofCamera::setLensOffset)
			.property("aspectRatio", &ofCamera::getAspectRatio, &ofCamera::setAspectRatio)
			.property("forceAspectRatio", &ofCamera::getForceAspectRatio, &ofCamera::setForceAspectRatio)
			
			.def("setupPerspective", &cameraSetupPerspective0)
			.def("setupPerspective", &cameraSetupPerspective1)
			.def("setupPerspective", &cameraSetupPerspective2)
			.def("setupPerspective", &cameraSetupPerspective3)
			.def("setupPerspective", &cameraSetupPerspective4)
			.def("setupPerspective", &ofCamera::setupPerspective)
			.def("setupOffAxisViewPortal", &ofCamera::setupOffAxisViewPortal)
			
			.property("VFlip", &ofCamera::isVFlipped, &ofCamera::setVFlip)
			
			.def("enableOrtho", &ofCamera::enableOrtho)
			.def("disableOrtho", &ofCamera::disableOrtho)
			.def("getOrtho", &ofCamera::getOrtho)
			
			.def("getImagePlaneDistance", &cameraGetImagePlaneDistance0)
			.def("getImagePlaneDistance", &ofCamera::getImagePlaneDistance)
			
			.def("begin", &cameraBegin0)
			.def("begin", &ofCamera::begin)
			.def("end", &ofCamera::end)
			
			.def("getProjectionMatrix", &cameraGetProjectionMatrix0)
			.def("getProjectionMatrix", &ofCamera::getProjectionMatrix)
			.def("getModelViewMatrix", &cameraGetModelViewMatrix0)
			.def("getModelViewMatrix", &ofCamera::getModelViewMatrix)
			.def("getModelViewProjectionMatrix", &cameraGetModelViewProjectionMatrix0)
			.def("getModelViewProjectionMatrix", &ofCamera::getModelViewProjectionMatrix)
			
			.def("worldToScreen", &cameraWorldToScreen1)
			.def("worldToScreen", &ofCamera::worldToScreen)
			.def("screenToWorld", &cameraScreenToWorld1)
			.def("screenToWorld", &ofCamera::screenToWorld)
			.def("worldToCamera", &cameraWorldToCamera1)
			.def("worldToCamera", &ofCamera::worldToCamera)
			.def("cameraToWorld", &cameraCameraToWorld1)
			.def("cameraToWorld", &ofCamera::cameraToWorld),
			
		///////////////////////////////
		/// \section ofEasyCam.h
		
		class_<ofEasyCam, ofCamera>("EasyCam")
			.def(constructor<>())
			
			.def("reset", &ofEasyCam::reset)
			
			.def("setTarget", (void(ofEasyCam::*)(const ofVec3f&)) &ofEasyCam::setTarget)
			.def("setTarget", (void(ofEasyCam::*)(ofNode&)) &ofEasyCam::setTarget)
			.def("getTarget", &ofEasyCam::getTarget)
			
			//.property("distance", &ofEasyCam::getDistance, &ofEasyCam::setDistance)
			.property("drag", &ofEasyCam::getDrag, &ofEasyCam::setDrag)
			.property("translationKey", &ofEasyCam::getTranslationKey, &ofEasyCam::setTranslationKey)
			
			.def("enableMouseInput", &ofEasyCam::enableMouseInput)
			.def("disableMouseInput", &ofEasyCam::disableMouseInput)
			.def("getMouseInputEnabled", &ofEasyCam::getMouseInputEnabled)
			
			.def("enableMouseMiddleButton", &ofEasyCam::enableMouseMiddleButton)
			.def("disableMouseMiddleButton", &ofEasyCam::disableMouseMiddleButton)
			.def("getMouseMiddleButtonEnabled", &ofEasyCam::getMouseMiddleButtonEnabled)
			
			.def("setAutoDistance", &ofEasyCam::setAutoDistance),
			
		///////////////////////////////
		/// \section ofMesh.h
		
		class_<ofMesh>("Mesh")
			.def(constructor<>())
			//.def(constructor<ofPrimitiveMode,vector<ofPoint>&>()) // TODO: needs vector
			
			.def("getMode", &ofMesh::setMode)
			.def("setMode", &ofMesh::getMode)
			
			.def("clear", &ofMesh::clear)
			
			.def("setupIndicesAuto", &ofMesh::setupIndicesAuto)
			
			.def("getVertex", &ofMesh::getVertex)
			.def("addVertex", (void(ofMesh::*)(const ofPoint&)) &ofMesh::addVertex)
			//.def("addVertices", (void(ofMesh::*)(const vector<ofPoint>&)) &ofMesh::addVertices) // TODO: needs vector
			.def("removeVertex", &ofMesh::removeVertex)
			.def("setVertex", &ofMesh::setVertex)
			.def("clearVertices", &ofMesh::clearVertices)
			
			.def("getNormal", &ofMesh::getNormal)
			.def("addNormal", (void(ofMesh::*)(const ofPoint&)) &ofMesh::addNormal)
			//.def("addNormal", (void(ofMesh::*)(const vector<ofPoint>&)) &ofMesh::addNormal) // TODO: needs vector
			.def("removeNormal", &ofMesh::removeNormal)
			.def("setNormal", &ofMesh::setNormal)
			.def("clearNormals", &ofMesh::clearNormals)
			
			.def("getColor", &ofMesh::getColor)
			.def("addColor", (void(ofMesh::*)(const ofPoint&)) &ofMesh::addColor)
			//.def("addColors", (void(ofMesh::*)(const vector<ofPoint>&)) &ofMesh::addColors) // TODO: needs vector
			.def("removeColor", &ofMesh::removeColor)
			.def("setColor", &ofMesh::setColor)
			.def("clearColors", &ofMesh::clearColors)
			
			.def("getTexCoord", &meshGetTexCoord) // need wrappers to convert ofVecf to ofPoint
			.def("addTexCoord", &meshAddTexCoord)
			//.def("addTexCoord", (void(ofMesh::*)(const vector<ofPoint>&)) &ofMesh::addTexCoord) // TODO: needs vector
			.def("removeTexCoord", &ofMesh::removeTexCoord)
			.def("setTexCoord", &meshSetTexCoord) // convert between ofVec2f and ofPoint
			.def("clearTexCoords", &ofMesh::clearTexCoords)
			
			.def("getIndex", &ofMesh::getIndex)
			.def("addIndex", (void(ofMesh::*)(const ofPoint&)) &ofMesh::addIndex)
			//.def("addIndices", (void(ofMesh::*)(const vector<ofPoint>&)) &ofMesh::addIndices) // TODO: needs vector
			.def("removeIndex", &ofMesh::removeIndex)
			.def("setIndex", (int(ofMesh::*)(int,int)) &ofMesh::setIndex)
			.def("clearIndices", &ofMesh::clearIndices)
			
			.def("addTriangle", (void(ofMesh::*)(int,int,int)) &ofMesh::addTriangle)
			
			.def("getNumVertices", &ofMesh::getNumVertices)
			.def("getNumNormals", &ofMesh::getNumNormals)
			.def("getNumColors", &ofMesh::getNumColors)
			.def("getNumTexCoords", &ofMesh::getNumTexCoords)
			.def("getNumIndices", &ofMesh::getNumIndices)
			
			//.def("getFace", &ofMesh::getFace) // TODO: needs vector
			
			.def("getCentroid", &ofMesh::getCentroid)
			
			.def("setName", &ofMesh::setName)
			
			.def("haveVerticesChanged", &ofMesh::haveVertsChanged)
			.def("haveColorsChanged", &ofMesh::haveColorsChanged)
			.def("haveNormalsChanged", &ofMesh::haveNormalsChanged)
			.def("haveTexCoordsChanged", &ofMesh::haveTexCoordsChanged)
			.def("haveIndicesChanged", &ofMesh::haveIndicesChanged)
			
			.def("hasVertices", &ofMesh::hasVertices)
			.def("hasColors", &ofMesh::hasColors)
			.def("hasNormals", &ofMesh::hasNormals)
			.def("hasTexCoords", &ofMesh::hasTexCoords)
			.def("hasIndices", &ofMesh::hasIndices)
			
			.def("drawVertices", &ofMesh::drawVertices)
			.def("drawWireframe", &ofMesh::drawWireframe)
			.def("drawFaces", &ofMesh::drawFaces)
			.def("draw", (void(ofMesh::*)(void)) &ofMesh::draw)
			
			.def("load", &ofMesh::load)
			.def("save", &meshSave1)
			.def("save", &ofMesh::save)
			
			.def("enableColors", &ofMesh::enableColors)
			.def("enableTextures", &ofMesh::enableTextures)
			.def("enableNormals", &ofMesh::enableNormals)
			.def("enableIndices", &ofMesh::enableIndices)
			
			.def("disableColors", &ofMesh::disableColors)
			.def("disableTextures", &ofMesh::disableTextures)
			.def("edisableNormals", &ofMesh::disableNormals)
			.def("disableIndices", &ofMesh::disableIndices)
			
			.def("usingColors", &ofMesh::usingColors)
			.def("usingTextures", &ofMesh::usingTextures)
			.def("usingNormals", &ofMesh::usingNormals)
			.def("usingIndices", &ofMesh::usingIndices)
			
			.def("append", &ofMesh::append)
			
			.def("setColorForIndices", &ofMesh::setColorForIndices)
			.def("getMeshForIndices", (ofMesh(ofMesh::*)(int,int) const) &ofMesh::getMeshForIndices)
			.def("getMeshForIndices", (ofMesh(ofMesh::*)(int,int,int,int) const) &ofMesh::getMeshForIndices)
			.def("mergeDuplicateVertices", &ofMesh::mergeDuplicateVertices)
			
			// TODO: needs vector
			//const vector<ofMeshFace> & getUniqueFaces() const;
			//vector<ofVec3f> getFaceNormals( bool perVetex=false) const;
			.def("setFromTriangles", &meshSetFromTriangles1)
			.def("setFromTriangles", &ofMesh::setFromTriangles)
			.def("smoothNormals", &ofMesh::smoothNormals)
			
			// ignoring the static 3d shape drawing functions, use the globals instead
			
			.def("draw", (void(ofMesh::*)(ofPolyRenderMode)) &ofMesh::draw),
			
		///////////////////////////////
		/// \section ofNode.h
		
		class_<ofNode>("Node")
			.def(constructor<>())
			
			.def("setParent", &nodeSetParent1)
			.def("setParent", &ofNode::setParent)
			.def("clearParent", &nodeClearParent0)
			.def("clearParent", &ofNode::clearParent)
			.def("getParent", &ofNode::getParent)
			
			.def("getPosition", &ofNode::getPosition)
			.def("getX", &ofNode::getX)
			.def("getY", &ofNode::getY)
			.def("getZ", &ofNode::getZ)
			
			.property("xAxis", &ofNode::getXAxis)
			.property("yAxis", &ofNode::getYAxis)
			.property("zAxis", &ofNode::getZAxis)
			
			.property("sideSir", &ofNode::getSideDir)
			.property("lookAtDir", &ofNode::getLookAtDir)
			.property("upDir", &ofNode::getUpDir)
			
			.property("pitch", &ofNode::getPitch)
			.property("heading", &ofNode::getHeading)
			.property("roll", &ofNode::getRoll)
			
			.def("getOrientationQuat", &ofNode::getOrientationQuat)
			.def("getOrientationEuler", &ofNode::getOrientationEuler)
			.def("getScale", &ofNode::getScale)
			
			.def("getLocalTransformMatrix", &ofNode::getLocalTransformMatrix)
			
			.def("getGlobalTransformMatrix", &ofNode::getGlobalTransformMatrix)
			.def("getGlobalPosition", &ofNode::getGlobalPosition)
			.def("getGlobalOrientation", &ofNode::getGlobalOrientation)
			.def("getGlobalScale", &ofNode::getGlobalScale)

			.def("setTransformMatrix", &ofNode::setTransformMatrix)
			
			.def("setPosition", (void(ofNode::*)(float,float,float)) &ofNode::setPosition)
			.def("setPosition", (void(ofNode::*)(const ofVec3f&)) &ofNode::setPosition)
			
			.def("setGlobalPosition", (void(ofNode::*)(float,float,float)) &ofNode::setGlobalPosition)
			.def("setGlobalPosition", (void(ofNode::*)(const ofVec3f&)) &ofNode::setGlobalPosition)
			
			.def("setOrientation", (void(ofNode::*)(const ofQuaternion&)) &ofNode::setOrientation)
			.def("setOrientation", (void(ofNode::*)(const ofVec3f&)) &ofNode::setOrientation)
			
			.def("setGlobalOrientation", &ofNode::setGlobalOrientation)
			
			.def("setScale", (void(ofNode::*)(float)) &ofNode::setScale)
			.def("setScale", (void(ofNode::*)(float,float,float)) &ofNode::setScale)
			.def("setScale", (void(ofNode::*)(const ofVec3f&)) &ofNode::setScale)
			
			.def("move", (void(ofNode::*)(float,float,float)) &ofNode::move)
			.def("move", (void(ofNode::*)(const ofVec3f&)) &ofNode::move)
			.def("truck", &ofNode::truck)
			.def("boom", &ofNode::boom)
			.def("dolly", &ofNode::dolly)
			
			.def("tilt", &ofNode::tilt)
			.def("pan", &ofNode::pan)
			.def("roll", &ofNode::roll)
			.def("rotate", (void(ofNode::*)(const ofQuaternion&)) &ofNode::rotate)
			.def("rotate", (void(ofNode::*)(float,const ofVec3f&)) &ofNode::rotate)
			.def("rotate", (void(ofNode::*)(float,float,float,float)) &ofNode::rotate)
			
			.def("rotateAround", (void(ofNode::*)(const ofQuaternion&,const ofVec3f&)) &ofNode::rotateAround)
			.def("rotateAround", (void(ofNode::*)(float,const ofVec3f&,const ofVec3f&)) &ofNode::rotateAround)
			
			.def("lookAt", &nodeLookAt1V)
			.def("lookAt", (void(ofNode::*)(const ofVec3f&,ofVec3f)) &ofNode::lookAt)
			.def("lookAt", &nodeLookAt1N)
			.def("lookAt", (void(ofNode::*)(const ofNode&,const ofVec3f&)) &ofNode::lookAt)
			
			.def("orbit", &nodeOrbit3)
			.def("orbit", (void(ofNode::*)(float,float,float,const ofVec3f&)) &ofNode::orbit)
			.def("orbit", (void(ofNode::*)(float,float,float,ofNode&)) &ofNode::orbit)
			
			.def("transformGL", &ofNode::transformGL)
			.def("restoreTransformGL", &ofNode::restoreTransformGL)
			
			.def("resetTransform", &ofNode::resetTransform)
			
			.def("customDraw", &ofNode::customDraw)
			.def("draw", &ofNode::draw)
	
	;
}
