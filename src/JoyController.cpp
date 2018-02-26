#include "JoyController.h"


using namespace ci;
using namespace ci::app;

void JoyController::SetUp() {
	joy.dwSize = sizeof JOYINFOEX;
	joy.dwFlags = JOY_RETURNALL;

	// ゲームパッドが接続しているか確認
	for (unsigned int i = 0; i < joyGetNumDevs(); ++i) {    //サポートされているジョイスティックの数を返す
		if (JOYERR_NOERROR == joyGetPosEx(i, &joy))
			console() << i << std::endl;
	}
}

// ボタン確認
void JoyController::Debug() {
	if (JOYERR_NOERROR == joyGetPosEx(JOYSTICKID1, &joy)) { //0番のジョイスティックの情報を見る
		console() << "L_Xpos = " << (maxSlopNum / 2.f - joy.dwXpos) / (maxSlopNum * 5.f) << std::endl;
		console() << "L_Ypos = " << maxSlopNum / 2.0 - joy.dwYpos << std::endl;
		console() << "R_posX = " << joy.dwZpos - maxSlopNum / 2.0 << std::endl;     // 右スティック横
		console() << "R_posY = " << maxSlopNum / 2.0 - joy.dwRpos << std::endl;    // 右スティック縦
		console() << "R2 = " << joy.dwUpos << std::endl;    // R2
		console() << "L2 = " << joy.dwVpos << std::endl;    // L2
		console() << "Buttons = " << joy.dwButtons << std::endl;
	}
	else {
		console() << "エラー" << std::endl;
	}
}

void JoyController::Update() {
	leftStickValue = Vec3f((maxSlopNum / 2.f - joy.dwXpos) / (maxSlopNum * 3.f),
		0.f, (maxSlopNum / 2.f - joy.dwYpos) / (maxSlopNum*3.f));

	rightStickValue = Vec3f((maxSlopNum / 2.f - joy.dwRpos) / maxSlopNum,
		(maxSlopNum / 2.f - joy.dwZpos) / maxSlopNum, 0.f);
}