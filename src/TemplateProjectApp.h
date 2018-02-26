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
#include "JoyController.h"

using namespace ci;
using namespace ci::app;

class TemplateProjectApp : public AppNative {
	JoyController joy1;
	// カメラ
	CameraPersp camera;
	float fov = 35.f;
	Vec3f cameraCurrentPosition = Vec3f(0.f, 0.f, 0.f);
	Vec3f cameraPosition = Vec3f(0.f, 0.f, 0.f);

	CameraOrtho ui_camera;

	// プレイヤー
	Vec3f playerPos = Vec3f(0.f, 0.f, 0.f);
	Vec3f playerRot = Vec3f(0.f, 0.f, 0.f);

	// キー入力
	std::set<int> pressing_key;

	// template
	Color color = Color(0.f, 0.f, 0.f);

	float notMoveValue = 0.01f;

public:
	void prepareSettings(Settings* settings);
	void setup();
	void shutdown();
	void mouseDown(MouseEvent event);
	void mouseDrag(MouseEvent event);
	void mouseUp(MouseEvent event);
	void keyDown(KeyEvent event);
	void keyUp(KeyEvent event);
	void update();
	void draw();
};

Vec3f ToRadians(const Vec3f& degrees);
