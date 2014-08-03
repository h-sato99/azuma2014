/*******************************************************************************
**  �t�@�C����  �FBluetooth.c
**  �T�v        �FBluetooth����N���X
**  �ڍ�        �FBluetooth�Ɋւ��鐧����s��
*******************************************************************************/

#include "device/Bluetooth.h"

#define C_PASS_KEY          "0005" /* Bluetooth�ʐM�p�p�X�L�[ */


void Bluetooth_init(Bluetooth* this)
{
	this->passKey = C_PASS_KEY;
}

void Bluetooth_start(Bluetooth* this)
{

	// NXT��Bluetooth�ʐM�̃X���[�u�f�o�C�X�Ƃ��ď��������A�}�X�^�[�f�o�C�X
	// �iPC�ANXT�}�X�^�[�f�o�C�X�j�Ƃ̐ڑ����m������
	ecrobot_init_bt_slave(this->passKey);
}

BOOL Bluetooth_checkConnection(Bluetooth* this)
{
	SINT status;

	// �ڑ����m�����Ă��邩�m�F
	status = ecrobot_get_bt_status();

	if(status == BT_STREAM)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


/*------------------------------------------------------------------------------
--  �֐���      �FBluetooth_terminate
--  �T�v        �FBluetooth�ʐM�̏I���������s���i�B
--              �FnxtOSEK���񋟂��Ă���f�o�C�X�I���p�t�b�N�֐����ŕK���Ăяo��
--              �F���ƁB
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
void Bluetooth_terminate(Bluetooth* this)
{
	// Bluetooth�ʐM���I��
	ecrobot_term_bt_connection();
}

// �ȍ~�̓����[�g�X�^�[�g�p
/*------------------------------------------------------------------------------
--  �֐���      �FBluetooth_receive
--  �T�v        �FBuletooth����̃f�[�^����M����
--              �F
--  ����        �Fchar		��M�f�[�^
--  �߂�l      �F��M�f�[�^�̒���
------------------------------------------------------------------------------*/
unsigned int Bluetooth_receive(Bluetooth* this, char* buf)
{
	return ecrobot_read_bt(buf, 0, BT_MAX_RX_BUF_SIZE);
}


/*------------------------------------------------------------------------------
--  �֐���      �FBluetooth_send
--  �T�v        �FBuletooth����̃f�[�^�𑗐M����
--              �F
--  ����        �F�Ȃ�
--  �߂�l      �F�Ȃ�
------------------------------------------------------------------------------*/
int Bluetooth_send(Bluetooth* this, char* buf, unsigned int len)
{
	return ecrobot_send_bt(buf, 0, len);
}


