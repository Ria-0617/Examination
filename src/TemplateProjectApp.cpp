#include "TemplateProjectApp.h"


void TemplateProjectApp::prepareSettings(Settings* settings) {
	settings->setWindowSize(800, 600);
}

void TemplateProjectApp::setup()
{
	cameraPosition = playerPos + Vec3f(0.f, 0.f, -8.f);
	cameraCurrentPosition = cameraPosition;

	camera = CameraPersp(getWindowWidth(), getWindowHeight(), fov, 0.1f, 100.f);
	camera.setEyePoint(cameraPosition);
	camera.setCenterOfInterestPoint(playerPos);

	ui_camera = CameraOrtho(0.f, (float)getWindowWidth(), (float)getWindowHeight(), 0.f, -1.f, 1.f);
	ui_camera.setEyePoint(Vec3f(0.f, 0.f, 0.f));
	ui_camera.setCenterOfInterestPoint(Vec3f(0.f, 0.f, -1.f));

	playerPrevPos = playerPos;

	gl::enableAlphaBlending();
	gl::enable(GL_COLOR_MATERIAL);

	joy1.SetUp();
}

void TemplateProjectApp::shutdown() {

}

void TemplateProjectApp::update()
{
	//joy1.Debug();

	Matrix44f m;

	// 移動に合わせて自機回転
	auto diff = playerPos - playerPrevPos;
	if (diff != Vec3f(0.f, 0.f, 0.f)) {
		playerRot.y = atan2f(diff.x, diff.z) * 180.f / (float)M_PI;
		playerPrevPos = playerPos;
	}

	if (JOYERR_NOERROR == joyGetPosEx(JOYSTICKID1, &joy1.joy)) { //0番のジョイスティックの情報を見る
		// スティックを傾けていないときに動かないように
		if (joy1.StickValue(joy1.joy.dwRpos) > notMoveValue || joy1.StickValue(joy1.joy.dwRpos) < -notMoveValue ||
			joy1.StickValue(joy1.joy.dwZpos) > notMoveValue || joy1.StickValue(joy1.joy.dwZpos) < -notMoveValue)
			rotation += Vec3f(0.f, joy1.StickValue(joy1.joy.dwZpos), 0.f)*rotationSpeed;

		m = Matrix44f::createRotation(ToRadians(rotation));

		// 移動
		if (joy1.StickValue(joy1.joy.dwXpos) > notMoveValue || joy1.StickValue(joy1.joy.dwXpos) < -notMoveValue ||
			joy1.StickValue(joy1.joy.dwYpos) > notMoveValue || joy1.StickValue(joy1.joy.dwYpos) < -notMoveValue)
			playerPos += m * Vec3f(joy1.StickValue(joy1.joy.dwXpos), 0.f, joy1.StickValue(joy1.joy.dwYpos))  * speed;

		// 玉発射
		if (joy1.joy.dwButtons == 0x0020) {    // 32
			Matrix44f m = Matrix44f::createRotation(ToRadians(playerRot));

			ball.position = playerPos;
			ball.v = m.transformVec(Vec3f(0.f, 0.f, 0.5f));
			ball.time = 10;
			balls.push_back(ball);
		}
	}

	cameraPosition = playerPos + m * Vec3f(0.f, 0.f, -8.f);
	Vec3f target = playerPos + m * Vec3f(0.f, 0.f, 2.f);

	camera.setEyePoint(cameraPosition + Vec3f(0.f, 5.f, 0.f));
	camera.setCenterOfInterestPoint(target + Vec3f(0.f, 1.f, 0.f));
}

void TemplateProjectApp::draw()
{
#pragma region enable
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enable(GL_CULL_FACE);
	//gl::enable(GL_LIGHTING);
#pragma endregion
	// clear out the window with black
	gl::clear(Color(0, 0, 0));

	gl::setMatrices(camera);

	// templateField
#if 1
	for (int x = 0; x < 30; ++x) {
		for (int z = 0; z < 30; ++z) {
			color = x + z & 0x01 ? Color(0.f, 1.f, 1.f) : Color(0.f, 0.0f, 1.f);
			gl::color(color);
			gl::drawCube(Vec3f(0.f + x, -5.0f, 0.f + z), Vec3f(1.f, 0.1f, 1.f));
		}
	}
#endif	

#pragma region Player
	// プレイヤー
	gl::pushModelView();
	gl::translate(playerPos);
	gl::rotate(playerRot);
	gl::color(Color(1.f, 1.f, 1.f));
	gl::drawColorCube(Vec3f(0.f, 0.f, 0.f), Vec3f(1.f, 1.f, 1.f));
	gl::popModelView();
#pragma endregion

	// 玉
	gl::pushModelView();

	for (int i = 0; i < balls.size(); ++i) {
		balls[i].position += balls[i].v;
		balls[i].time -= 1;

		gl::drawSphere(balls[i].position, 0.5f);

		/*if (balls[i].time < 0) {
			balls.erase(balls.begin() + i-1);
		}*/
	}
	gl::popModelView();

#pragma region disable
	gl::disableDepthRead();
	gl::disableDepthWrite();
	gl::disable(GL_CULL_FACE);
	//gl::disable(GL_LIGHTING);
#pragma endregion

	gl::color(Color(1.f, 1.f, 1.f));
	gl::setMatrices(ui_camera);
}

Vec3f ToRadians(const Vec3f& degrees) {
	return degrees * M_PI / 180.f;
}

CINDER_APP_NATIVE(TemplateProjectApp, RendererGl)
