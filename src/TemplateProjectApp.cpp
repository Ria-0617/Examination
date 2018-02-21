#include "TemplateProjectApp.h"


void TemplateProjectApp::prepareSettings(Settings* settings) {
	settings->setWindowSize(800, 600);
}

void TemplateProjectApp::setup()
{
	camera = CameraPersp(getWindowWidth(), getWindowHeight(), fov, 0.1f, 100.f);
	camera.setEyePoint(Vec3f(0.f, 5.f, -10.f));
	camera.setCenterOfInterestPoint(Vec3f(0.f, 0.f, 0.f));

	ui_camera = CameraOrtho(0.f, (float)getWindowWidth(), (float)getWindowHeight(), 0.f, -1.f, 1.f);
	ui_camera.setEyePoint(Vec3f(0.f, 0.f, 0.f));
	ui_camera.setCenterOfInterestPoint(Vec3f(0.f, 0.f, -1.f));

	gl::enableAlphaBlending();
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
	if (pressing_key.count(KeyEvent::KEY_UP))
		playerPos.z += 0.1f;
	if (pressing_key.count(KeyEvent::KEY_DOWN))
		playerPos.z -= 0.1f;
	if (pressing_key.count(KeyEvent::KEY_RIGHT))
		playerPos.x -= 0.1f;
	if (pressing_key.count(KeyEvent::KEY_LEFT))
		playerPos.x += 0.1f;
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

CINDER_APP_NATIVE(TemplateProjectApp, RendererGl)
