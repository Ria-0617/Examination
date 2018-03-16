#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder\Camera.h"
#include "cinder\gl\Light.h"
#include "cinder\gl\Material.h"
#include "cinder\ImageIo.h"
#include "cinder\gl\Texture.h"
#include "cinder\ObjLoader.h"
#include "JoyController.h"

#include <vector>

using namespace ci;
using namespace ci::app;

struct ballStatus {
	Vec3f position;
	Vec3f v;
	int time;
};

class TemplateProjectApp : public AppNative {
	// カメラ
	CameraPersp camera;
	float fov = 35.f;
	Vec3f cameraCurrentPosition = Vec3f(0.f, 0.f, 0.f);
	Vec3f cameraPosition = Vec3f(0.f, 0.f, 0.f);

	Vec3f rotation = Vec3f(0.f, 0.f, 0.f);
	float rotationSpeed = 3.f;

	CameraOrtho ui_camera;

	// プレイヤー
	Vec3f playerPos = Vec3f(0.f, 0.f, 0.f);
	Vec3f playerPrevPos;
	Vec3f playerRot = Vec3f(0.f, 0.f, 0.f);
	float speed = 0.3f;

	ballStatus ball;
	std::vector<ballStatus> balls;

	// ゲームパッド
	JoyController joy1;
	float notMoveValue = 0.05f;
	
	// template
	Color color = Color(0.f, 0.f, 0.f);

public:
	void prepareSettings(Settings* settings);
	void setup();
	void shutdown();
	void update();
	void draw();
};

Vec3f ToRadians(const Vec3f& degrees);
