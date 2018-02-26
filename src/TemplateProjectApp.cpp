#include "TemplateProjectApp.h"


void TemplateProjectApp::prepareSettings(Settings* settings) {
	settings->setWindowSize(800, 600);
}

void TemplateProjectApp::setup()
{
	cameraPosition = Vec3f(0.f, 0.f, -8.f) + playerPos;
	cameraCurrentPosition = cameraPosition;

	camera = CameraPersp(getWindowWidth(), getWindowHeight(), fov, 0.1f, 100.f);
	camera.setEyePoint(cameraPosition);
	camera.setCenterOfInterestPoint(playerPos);

	ui_camera = CameraOrtho(0.f, (float)getWindowWidth(), (float)getWindowHeight(), 0.f, -1.f, 1.f);
	ui_camera.setEyePoint(Vec3f(0.f, 0.f, 0.f));
	ui_camera.setCenterOfInterestPoint(Vec3f(0.f, 0.f, -1.f));

	gl::enableAlphaBlending();
	gl::enable(GL_COLOR_MATERIAL);

	joy1.SetUp();
}

void TemplateProjectApp::shutdown() {

}

void TemplateProjectApp::mouseDown(MouseEvent event)
{

}

void TemplateProjectApp::mouseDrag(MouseEvent event) {

}

void TemplateProjectApp::mouseUp(MouseEvent event) {

}

void TemplateProjectApp::keyDown(KeyEvent event) {
	pressing_key.insert(event.getCode());
}

void TemplateProjectApp::keyUp(KeyEvent event) {
	pressing_key.erase(event.getCode());
}

void TemplateProjectApp::update()
{
	//joy1.Debug();
	joy1.Update();

	if (JOYERR_NOERROR == joyGetPosEx(JOYSTICKID1, &joy1.joy)) { //0番のジョイスティックの情報を見る
		// スティックを傾けていないときに動かないように
		if (joy1.LeftStickValue().x > notMoveValue || joy1.LeftStickValue().x < -notMoveValue)
			playerPos.x += joy1.LeftStickValue().x;

		if (joy1.LeftStickValue().z > notMoveValue || joy1.LeftStickValue().z < -notMoveValue)
			playerPos.z += joy1.LeftStickValue().z;

		if (joy1.RightStickValue().x > notMoveValue || joy1.RightStickValue().x < -notMoveValue)
			playerRot.x += joy1.RightStickValue().x;

		if (joy1.RightStickValue().y > notMoveValue || joy1.RightStickValue().y < -notMoveValue)
			playerRot.y += joy1.RightStickValue().y;
	}

	// 離れようとするとついてくるカメラ
	float dist = cameraPosition.distance(playerPos);
	if (dist > 10.f) {
		Vec3f d = (cameraPosition - playerPos).normalized();
		cameraPosition = playerPos + d * 10.f;
	}

	// 余韻
	Vec3f d = cameraPosition - cameraCurrentPosition;
	cameraCurrentPosition += d * 0.01f;


	Vec3f target = playerPos + Vec3f(0.f, 0.f, 2.f);

	camera.setEyePoint(cameraCurrentPosition + Vec3f(0.f,5.f,0.f));
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

	gl::pushModelView();
	gl::translate(playerPos);
	gl::rotate(playerRot);
	gl::color(Color(1.f, 1.f, 1.f));
	gl::drawCube(Vec3f(0.f, 0.f, 0.f), Vec3f(1.f, 1.f, 1.f));
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
