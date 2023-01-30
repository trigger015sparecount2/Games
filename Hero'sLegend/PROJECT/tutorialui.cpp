//-------------------------
//Author:�O��q��
//�`���[�g���A�����UI����(tutorialui.cpp)
//-------------------------
#include "tutorialui.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturetutorialUi = NULL;    //�e�N�X�`���ւ̃|�C���^
RECT g_recttutoUI; //�摜�̕`��̈�
D3DXVECTOR3 g_centertuto, g_postuto; //�摜�̒��S�A�\����ꏊ
D3DXVECTOR3 g_Scaletuto;
D3DXMATRIX g_mtxtutoUi;

//����������
void InittutorialUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	g_postuto = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//PRESS
	g_centertuto = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_recttutoUI.top = 0;
	g_recttutoUI.left = 0;
	g_recttutoUI.bottom = 1024;
	g_recttutoUI.right = 2048;
	g_Scaletuto = D3DXVECTOR3(0.65f, 0.73f, 1.0f);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/tutorial.jpg",
		&g_pTexturetutorialUi);
}

//UI�̏I������
void UninittutorialUi(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturetutorialUi != NULL)
	{
		g_pTexturetutorialUi->Release();
		g_pTexturetutorialUi = NULL;
	}
}

//UI�̍X�V����
void UpdatetutorialUi(void)
{
	
}


//�`�揈��
void DrawtutorialUi(void)
{
	LPD3DXSPRITE pSprite; //�f�o�C�X�̃|�C���^
	pSprite = GetSprite();     //�f�o�C�X���擾����
	D3DXMATRIX mtxTransUI, mtxScaleUI;

	//UI�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxtutoUi);

	//�g�嗦�𔽉f
	D3DXMatrixScaling(&mtxScaleUI, g_Scaletuto.x, g_Scaletuto.y, g_Scaletuto.z);
	D3DXMatrixMultiply(&g_mtxtutoUi, &g_mtxtutoUi, &mtxScaleUI);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTransUI, g_postuto.x, g_postuto.y, g_postuto.z);
	D3DXMatrixMultiply(&g_mtxtutoUi, &g_mtxtutoUi, &mtxTransUI);

	//���[���h�}�g���b�N�X�̐ݒ�
	pSprite->SetTransform(&g_mtxtutoUi);

	//�摜�A�摜�̕`��̈�A�摜�̒��S���W�A�摜���\����ꏊ�A�F
	pSprite->Draw(g_pTexturetutorialUi, &g_recttutoUI, &g_centertuto, &g_postuto, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}