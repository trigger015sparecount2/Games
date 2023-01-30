//------------------------------
//Author:�O��q��
//�Q�[��(main.cpp)
//------------------------------
#include "main.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "enemy.h"
#include "input.h"
#include "mouse.h"
#include "gamepad.h"
#include "fade.h"
#include "ui.h"
#include "rockon.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "sound.h"
#include "titleui.h"
#include "resultui.h"
#include "tutorialui.h"
#include "tutorial.h"

//�}�N����`
#define CLASS_NAME "WindowsClass"    //�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "Hero's_Legend" //�E�B���h�E�̖��O(�L���v�V������)

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawSprite(void);

//�O���[�o���ϐ�
LPDIRECT3D9 g_pD3D = NULL;             //Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL; //Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;
LPD3DXSPRITE g_pSprite = NULL;
MODE g_mode = MODE_TITLE; //���݂̃��[�h
int g_nCountFPS;

//���C���֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, PSTR lpCmdLine, int nCmdShow)
{
	//�\���̂̐ݒ�(�E�B���h�E�N���X�ւ̎w��)
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),             //WNDCLASSEX�̃������T�C�Y�̎w��
		CS_CLASSDC,                     //�\������E�B���h�E�̃X�^�C����ݒ�
		WindowProc,                     //�E�B���h�E�v���V�[�W���̃A�h���X(�֐���)���w��
		0,                              //�ʏ�͎g�p���Ȃ��̂�0���w��(�قړ���Ȃ�0)
		0,                              //�ʏ�͎g�p���Ȃ��̂�0���w��(�قړ���Ȃ�0)
		hInstance,                      //Windows�̈����̃C���X�^���X�n���h����ݒ�
		LoadIcon(NULL,IDI_APPLICATION), //�t�@�C���A�C�R���Ɏg�p����A�C�R�����w��
		LoadCursor(NULL,IDC_ARROW),     //�g�p����}�E�X�J�[�\�����w��
		(HBRUSH)(COLOR_WINDOW + 1),     //�E�B���h�E�̃N���C�A���g�̈�̔w�i�F���w��
		NULL,                           //Window�ɂ��郁�j���[��ݒ�
		CLASS_NAME,                     //�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)  //�t�@�C���A�C�R���Ɏg�p����A�C�R����ݒ�
	};
	HWND hWnd; //�E�B���h�E�n���h��(���ʎq)
	MSG msg;   //���b�Z�[�W���i�[����ϐ�
	DWORD dwFPSLastTime;
	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);
	//�E�B���h�E�̐���(������E�B���h�E���E�B���h�E�n���h���ɔ[�߂ĊǗ�����)
	hWnd = CreateWindowEx(0, //�g���E�B���h�E�X�^�C��
		CLASS_NAME,          //�E�B���h�E�N���X�̖��O
		WINDOW_NAME,         //�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW, //�E�B���h�E�X�^�C��
		CW_USEDEFAULT,       //�E�B���h�E�̍���x���W
		CW_USEDEFAULT,       //�E�B���h�E�̍���y���W
		SCREEN_WIDTH,        //�E�B���h�E�̕�
		SCREEN_HEIGHT,       //�E�B���h�E�̍���
		NULL,                //�e�E�B���h�E�̃n���h��
		NULL,                //���j���[�E�B���h�E�܂��͎q�E�B���h�E
		hInstance,           //�C���X�^���X�n���h��
		NULL);               //�E�B���h�E�쐬�f�[�^
	//����������(�E�B���h�E�𐶐����Ă���s��)(DirectX�{�̂̐������s���Ă���)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}
	dwExecLastTime = timeGetTime();
	dwFPSLastTime = timeGetTime();
	dwCurrentTime = 0;
	dwFrameCount = 0;
	//�E�B���h�E�\��
	ShowWindow(hWnd, nCmdShow); //�E�B���h�E�̕\��(�E�B���h�E�̕\����Ԃ�ݒ�)
	UpdateWindow(hWnd);         //�E�B���h�E�̔��f(�E�B���h�E�̃N���C�A���g�̈���X�V)
								//���b�Z�[�W���[�v(���b�Z�[�W�L���[���烁�b�Z�[�W���擾)
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Window�̏���
			if (msg.message == WM_QUIT)
			{//"WM_QUIT"���b�Z�[�W�������Ă����烋�[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b���ƂɎ��s
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60�b�o��
				dwExecLastTime = dwCurrentTime;
				// �X�V����
				Update();
				// �`�揈��
				Draw();
				dwFrameCount++;
			}
		}
	}
	//�I������
	Uninit();
	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return (int)msg.wParam;
}

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID; //���b�Z�[�W(YES,NO)��ID
	switch (uMsg)
	{
	case WM_DESTROY: //�E�B���h�E�j�����b�Z�[�W
					 //WM_QUIT���b�Z�[�W��Ԃ�
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN: //[ESC]�L�[�������ꂽ
					 //�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
		switch (wParam)
		{
		case VK_ESCAPE:
			//���b�Z�[�WBox�̕\��
			nID = MessageBox(hWnd, "�{���ɏI�����܂���?", "�I���m�F", MB_YESNO);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	case WM_CLOSE: //x(����)�{�^�������̃��b�Z�[�W
				   //���b�Z�[�WBox�̕\��
		nID = MessageBox(hWnd, "�{���ɏI�����܂���?", "�I���m�F", MB_YESNO);
		if (nID == IDYES)
		{
			//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
		}
		else
		{
			return 0; //0��Ԃ��Ȃ��ƏI�����Ă��܂��̂�0��Ԃ�
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//����������
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;        //�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp; //�v���[���e�[�V�����p�����[�^
								 //Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;							            // �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;	              			// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				            // �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;			            	// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		                // �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed = bWindow;						                // �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil = TRUE;						    // �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					    // �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	    // �C���^�[�o��

																	// �f�o�C�X�̐���
																	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
																	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// �J�����O���s��Ȃ�
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

																			// �T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

																			// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);
	
	D3DXCreateSprite(g_pD3DDevice, &g_pSprite);

	//�I�u�W�F�N�g������
	InitKeyboard(hInstance, hWnd);
	InitMouse(hInstance, hWnd);
	InitGamepad(hInstance, hWnd);
	InitCamera();
	InitFade(g_mode);
	InitSound(hWnd);
	PlaySound(SOUND_LABEL_BGM0);
	srand((unsigned int)time(NULL));
	SetMode(g_mode);
	SetCamera();
	return S_OK;
}

//�I������
void Uninit(void)
{
	if (g_pFont != NULL)
	{// �f�o�b�O���\���p�t�H���g��ݒ�
		g_pFont->Release();
		g_pFont = NULL;
	}
	//�I�u�W�F�N�g�I������
	UninitCamera();
	UninitKeyboard();
	UninitGamepad();
	UninitFade();
	UninitCamera();
	UninitMouse();
	UninitTitle();
	UninitGame();
	UninitResult();
	UninitSound();
	//Direct3D�f�o�C�X�J��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	if (g_pSprite != NULL)
	{
		g_pSprite->Release();
		g_pSprite = NULL;
	}
	//Direct3D�I�u�W�F�N�g�̊J��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//�X�V����
void Update(void)
{
	UpdateKeyboard();
	if (Mouse() == true)
	{
		UpdateMouse();
	}
	if (GamePad() == true)
	{
		UpdateGamepad();
	}
	UpdateFade();
	//�I�u�W�F�N�g�X�V����
	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_TUTORIAL:
		UpdateTutorial();
		break;
	case MODE_GAME:
		UpdateGame();
		break;
	case MODE_RESULT:
		UpdateResult();
		break;
	}
	UpdateCamera();
}

//�`�揈��
void Draw(void)
{
	//�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	//�`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;
		case MODE_TUTORIAL:
			DrawTutorial();
			break;
		case MODE_GAME:
			DrawGame();
			break;
		case MODE_RESULT:
			DrawResult();
			break;
		}
		//DrawFPS();
		DrawSprite();
		DrawFade();
		//�`��̏I��
		g_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//�X�v���C�g�`��
void DrawSprite(void)
{
	//�`��̊J�n
	if (SUCCEEDED(g_pSprite->Begin(NULL)))
	{
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawtitleUi();
			break;
		case MODE_TUTORIAL:
			DrawtutorialUi();
			break;
		case MODE_GAME:
			DrawUi();
			break;
		case MODE_RESULT:
			DrawresultUi();
			break;
		}
		g_pSprite->End();
	}
}

//�f�o�C�X�擾
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//�X�v���C�g�`��
LPD3DXSPRITE GetSprite(void)
{
	return g_pSprite;
}

//�F�X������`��
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];
	wsprintf(&str[0], "FPS:%d", g_nCountFPS);
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)); //�e�L�X�g�`��
	sprintf(&str[0], "\n\n�J�����̏��--------------------------------");
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[2], "\n  ���_  [ %.2f, %.2f, %.2f ]", CameraPosV().x, CameraPosV().y, CameraPosV().z);
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[3], "\n �����_ [ %.2f, %.2f, %.2f ]", CameraPosR().x, CameraPosR().y, CameraPosR().z);
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[4], "\n���_�ƒ����_�̋����F%.2f", CameraDistance());
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[5], "\n�J�����̊p�x�F%.2f", CameraRot());
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[6], "\n�J�����̖ړI�̊p�x�F%.2f", CameraRotDesh());
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[7], "\n\n���f���̏��--------------------------------");
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[9], "\n���f���̈ʒu [ %.2f, %.2f, %.2f ]", PlayerPos().x, PlayerPos().y, PlayerPos().z);
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[10], "\n   �ړ���    [ %.2f, %.2f, %.2f ]", PlayerMove(0), PlayerMove(1), PlayerMove(2));
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[11], "\n���f���̌��� : %.2f", PlayerRot());
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[12], "\n �ړI�̌���  : %.2f", PlayerRotDesh());
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[13], "\n\n���f���̑���--------------------------------");
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[15], "\n���f���̈ړ� : [��] [��] [��] [��]");
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[16], "\n�W�����v : [J]");
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	
	sprintf(&str[17], "\n\n�e�X�g--------------------------------------");
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[19], "\n���b�N�I���F%d", RockNumber());
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[20], "\n�G�̈ʒu [ %.2f, %.2f, %.2f ]", EnemyPos(0,0), EnemyPos(1,0), EnemyPos(2,0));
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[21], "\n�p�x : %.2f", PlayerLookEnemy());
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[22], "\n�J���� : [ %.2f, %.2f, %.2f, %.2f ]", Playermtx()._11, Playermtx()._12, Playermtx()._13, Playermtx()._14);
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[23], "\n�J���� : [ %.2f, %.2f, %.2f, %.2f ]", Playermtx()._21, Playermtx()._22, Playermtx()._23, Playermtx()._24);
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[24], "\n�J���� : [ %.2f, %.2f, %.2f, %.2f ]", Playermtx()._31, Playermtx()._32, Playermtx()._33, Playermtx()._34);
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[25], "\n�J���� : [ %.2f, %.2f, %.2f, %.2f ]", Playermtx()._41, Playermtx()._42, Playermtx()._43, Playermtx()._44);
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[26], "\n�t�F�[�h : %d", GetFade());
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[27], "\n���� : %.2f", PlayerPartsRot());
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	sprintf(&str[28], "\nHP : %d", PlayerHP());
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

//���[�h�̐ݒ�
void SetMode(MODE mode)
{
	StopSound();
	ResetCamera();
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_TUTORIAL:
		UninittutorialUi();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	}
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_TUTORIAL:
		InitTutorial();
		break;
	case MODE_GAME:
		InitGame();
		break;
	case MODE_RESULT:
		InitResult();
		break;
	}
	g_mode = mode;
}

//���[�h�擾
MODE GetMode(void)
{
	return g_mode;
}
