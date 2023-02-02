//---------------------------
//Author:�O��q��
//�I�u�W�F�N�g�Ǘ�(main.h)
//---------------------------
#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECTINPUT_VERSION (0x0800)
#define _CRT_SECURE_NO_WARNINGS
//�C���N���[�h�t�@�C��
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "d3dx9.h"   //�`��ɕK�v
#include "dinput.h"  //���͏����ɕK�v
#include "xaudio2.h"   //�T�E���h�֘A

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")    //�`��ɕK�v
#pragma comment(lib,"d3dx9.lib")   //[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")  //DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"dinput8.lib") //���͏����ɕK�v
#pragma comment(lib,"winmm.lib")

//�}�N����`
#define SCREEN_WIDTH (1280)												//�E�B���h�E�̕�
#define SCREEN_HEIGHT (720)												//�E�B���h�E�̍����@16:9�̃T�C�Y
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//���_�t�H�[�}�b�g

//�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	float rhw;       //1.0f�ŌŒ�
	D3DCOLOR col;    //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
} VERTEX_2D;

//���(���[�h)�̎��
typedef enum
{
	MODE_TITLE = 0,
	MODE_CHOICE,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX
} MODE;

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);	//�f�o�C�X�擾
void SetMode(MODE mode);			//���[�h�ݒ�
MODE GetMode(void);					//���[�h�擾
void DrawFPS(void);					//�t���[�����[�g�`��
#endif _MAIN_H_