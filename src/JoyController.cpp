#include "JoyController.h"


using namespace ci;
using namespace ci::app;

void JoyController::SetUp() {
	joy.dwSize = sizeof JOYINFOEX;
	joy.dwFlags = JOY_RETURNALL;

	// �Q�[���p�b�h���ڑ����Ă��邩�m�F
	for (unsigned int i = 0; i < joyGetNumDevs(); ++i) {    //�T�|�[�g����Ă���W���C�X�e�B�b�N�̐���Ԃ�
		if (JOYERR_NOERROR == joyGetPosEx(i, &joy))
			console() << i << std::endl;
	}
}

// �{�^���m�F
void JoyController::Debug() {
	if (JOYERR_NOERROR == joyGetPosEx(JOYSTICKID1, &joy)) { //0�Ԃ̃W���C�X�e�B�b�N�̏�������
		console() << "L_Xpos = " << (maxSlopNum / 2.f - joy.dwXpos) / (maxSlopNum * 5.f) << std::endl;
		console() << "L_Ypos = " << maxSlopNum / 2.0 - joy.dwYpos << std::endl;
		console() << "R_posX = " << joy.dwZpos - maxSlopNum / 2.0 << std::endl;     // �E�X�e�B�b�N��
		console() << "R_posY = " << maxSlopNum / 2.0 - joy.dwRpos << std::endl;    // �E�X�e�B�b�N�c
		console() << "R2 = " << joy.dwUpos << std::endl;    // R2
		console() << "L2 = " << joy.dwVpos << std::endl;    // L2
		console() << "Buttons = " << joy.dwButtons << std::endl;
	}
	else {
		console() << "�G���[" << std::endl;
	}
}

void JoyController::Update() {
	leftStickValue = Vec3f((maxSlopNum / 2.f - joy.dwXpos) / (maxSlopNum * 3.f),
		0.f, (maxSlopNum / 2.f - joy.dwYpos) / (maxSlopNum*3.f));

	rightStickValue = Vec3f((maxSlopNum / 2.f - joy.dwRpos) / maxSlopNum,
		(maxSlopNum / 2.f - joy.dwZpos) / maxSlopNum, 0.f);
}