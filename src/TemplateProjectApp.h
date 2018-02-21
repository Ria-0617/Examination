#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder\Camera.h"
#include "cinder\gl\Light.h"
#include "cinder\gl\Material.h"
#include "cinder\ImageIo.h"
#include "cinder\gl\Texture.h"
#include "cinder\ObjLoader.h"
#include <set>

using namespace ci;
using namespace ci::app;

class TemplateProjectApp : public AppNative {
	// �J����
	CameraPersp camera;
	float fov = 35.f;

	CameraOrtho ui_camera;

	// �v���C���[
	Vec3f playerPos = Vec3f(0.f, 0.f, 0.f);
	Vec3f playerRot = Vec3f(0.f, 0.f, 0.f);

	// �L�[����
	std::set<int> pressing_key;
public:
	void prepareSettings(Settings* settings);
	void setup();
	void shutdown();
	void mouseDown(ci::app::MouseEvent event);
	void mouseDrag(ci::app::MouseEvent event);
	void mouseUp(ci::app::MouseEvent event);
	void keyDown(ci::app::KeyEvent event);
	void keyUp(ci::app::KeyEvent event);
	void update();
	void draw();
};
