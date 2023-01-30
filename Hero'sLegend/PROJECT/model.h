//---------------------------
//Author:�O��q��
//���f��(model.h)
//---------------------------
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"

//�v���g�^�C�v�錾
HRESULT InitModel(void);		//������
void UninitModel(void);			//�I��
void UpdateModel(void);			//�X�V
void DrawModel(void);			//�`��
float ModelPos(int nRot);		//pos�擾
float ModelRot(void);			//rot�擾
void ModelMoveX(void);			//���f���ړ�X
void ModelMoveZ(void);			//���f���ړ�Z
void ModelMoveXslow(void);		//���f���ړ��x������X
void ModelMoveZslow(void);		//���f���ړ��x������Z
float ModelMove(int nRot);		//�ړ�
float ModelRotDesh(void);		//�ړI�̕����ݒ�
float ModelMinSize(int nRot);	//�ŏ��T�C�Y�擾
float ModelMaxSize(int nRot);	//�ő�T�C�Y�擾
#endif _MODEL_H_