//--------------------------
//Author:�O��q��
//�u���b�N�̏���(block.cpp)
//--------------------------
#include "player.h"
#include "block.h"
#include "input.h"
#include "sound.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBlock[BLOCK_MAX] = {}; //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL; //���_�o�b�t�@�ւ̃|�C���^
Block g_aBlock[MAX_BLOCK];	//�u���b�N

//����������
HRESULT InitBlock(void)
{
	int nCntBlock;
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();     //�f�o�C�X���擾����

	//��񃊃Z�b�g
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].Startpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].Maxmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].BlockType = BLOCK_NORMAL;
		g_aBlock[nCntBlock].nTime = 0;
		g_aBlock[nCntBlock].nMaxTime = 0;
		g_aBlock[nCntBlock].fWidth = 50.0f;
		g_aBlock[nCntBlock].fHeight = 20.0f;
		g_aBlock[nCntBlock].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/block000.jpg",
		&g_pTextureBlock[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/upfloor.png",
		&g_pTextureBlock[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/downfloor.png",
		&g_pTextureBlock[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/iceblock.png",
		&g_pTextureBlock[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/carryblock.png",
		&g_pTextureBlock[4]);
	D3DXCreateTextureFromFile(pDevice,
		"data/Texture/warphole.png",
		&g_pTextureBlock[5]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D *pVtx; //���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
	return S_OK;
}

//�I������
void UninitBlock(void)
{
	int nCntBlock;
	for (nCntBlock = 0; nCntBlock < BLOCK_MAX; nCntBlock++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBlock[nCntBlock] != NULL)
		{
			g_pTextureBlock[nCntBlock]->Release();
			g_pTextureBlock[nCntBlock] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//�X�V����
void UpdateBlock(void)
{
	int nCntBlock;
	bool bJump = false;
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//�u���b�N���g���邩
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//���ԉ��Z
			g_aBlock[nCntBlock].nTime++;
			
			//���Ԃ������ȉ�
			if (g_aBlock[nCntBlock].nTime <= g_aBlock[nCntBlock].nMaxTime / 2)
			{
				//�㉺���E�Ɉړ�������
				g_aBlock[nCntBlock].move.x += g_aBlock[nCntBlock].Maxmove.x / 30;
				if (g_aBlock[nCntBlock].move.x > g_aBlock[nCntBlock].Maxmove.x)
				{
					g_aBlock[nCntBlock].move.x = g_aBlock[nCntBlock].Maxmove.x;
				}
				g_aBlock[nCntBlock].move.y += g_aBlock[nCntBlock].Maxmove.y / 30;
				if (g_aBlock[nCntBlock].move.y > g_aBlock[nCntBlock].Maxmove.y)
				{
					g_aBlock[nCntBlock].move.y = g_aBlock[nCntBlock].Maxmove.y;
				}
			}
			//���Ԃ��������߂��Ă�
			else if (g_aBlock[nCntBlock].nTime < g_aBlock[nCntBlock].nMaxTime)
			{
				//�㉺���E�Ɉړ�������
				g_aBlock[nCntBlock].move.x -= g_aBlock[nCntBlock].Maxmove.x / 30;
				if (g_aBlock[nCntBlock].move.x < -g_aBlock[nCntBlock].Maxmove.x)
				{
					g_aBlock[nCntBlock].move.x = -g_aBlock[nCntBlock].Maxmove.x;
				}
				g_aBlock[nCntBlock].move.y -= g_aBlock[nCntBlock].Maxmove.y / 30;
				if (g_aBlock[nCntBlock].move.y < -g_aBlock[nCntBlock].Maxmove.y)
				{
					g_aBlock[nCntBlock].move.y = -g_aBlock[nCntBlock].Maxmove.y;
				}
			}
			//���ԉ߂����烊�Z�b�g������
			else if (g_aBlock[nCntBlock].nTime >= g_aBlock[nCntBlock].nMaxTime)
			{
				g_aBlock[nCntBlock].nTime = 0;
			}

			//������u���b�N���X�^�[�g����艺�ɂ���
			if (g_aBlock[nCntBlock].BlockType == BLOCK_DOWN && g_aBlock[nCntBlock].pos.y > g_aBlock[nCntBlock].Startpos.y)
			{
				//��Ɉړ�������
				g_aBlock[nCntBlock].move.y -= 1.0f;
				if (g_aBlock[nCntBlock].move.y < -3.0f)
				{
					g_aBlock[nCntBlock].move.y = -3.0f;
				}
			}
			//�オ��u���b�N���X�^�[�g������ɂ���
			else if (g_aBlock[nCntBlock].BlockType == BLOCK_UP && g_aBlock[nCntBlock].pos.y < g_aBlock[nCntBlock].Startpos.y)
			{
				//���Ɉړ�������
				g_aBlock[nCntBlock].move.y += 1.0f;
				if (g_aBlock[nCntBlock].move.y > 3.0f)
				{
					g_aBlock[nCntBlock].move.y = 3.0f;
				}
			}

			//������u���b�N���X�^�[�g������ɂ���A�܂��͏オ��u���b�N���X�^�[�g����艺�ɂ���
			if (g_aBlock[nCntBlock].BlockType == BLOCK_DOWN && g_aBlock[nCntBlock].pos.y < g_aBlock[nCntBlock].Startpos.y ||
				g_aBlock[nCntBlock].BlockType == BLOCK_UP && g_aBlock[nCntBlock].pos.y > g_aBlock[nCntBlock].Startpos.y)
			{
				//�㉺�Ɉړ��������ꏊ���X�^�[�g���Ɠ����ɂ���
				g_aBlock[nCntBlock].move.y = 0.0f;
				g_aBlock[nCntBlock].pos.y = g_aBlock[nCntBlock].Startpos.y;
			}

			//pos�ǉ�
			g_aBlock[nCntBlock].pos += g_aBlock[nCntBlock].move;
			
			//�^�ׂ�u���b�N�̏ꍇ�A���ړ��𖳂���
			if (g_aBlock[nCntBlock].BlockType == BLOCK_CARRY)
			{
				g_aBlock[nCntBlock].move.x = 0.0f;
			}

			//���_�o�b�t�@��������
			VERTEX_2D *pVtx;
			g_pVtxBuffBlock->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += nCntBlock * 4;
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			g_pVtxBuffBlock->Unlock();
		}
	}
}

//�`�揈��
void DrawBlock(void)
{
	int nCntBlock;
	LPDIRECT3DDEVICE9 pDevice;                    //�f�o�C�X�̃|�C���^
	pDevice = GetDevice();                        //�f�o�C�X���擾����
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);               //���_�t�H�[�}�b�g�̐ݒ�
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			switch (g_aBlock[nCntBlock].BlockType)
			{
			case BLOCK_NORMAL:
				pDevice->SetTexture(0, g_pTextureBlock[0]); //�e�N�X�`���̐ݒ�
				break;
			case BLOCK_UP:
				pDevice->SetTexture(0, g_pTextureBlock[1]); //�e�N�X�`���̐ݒ�
				break;
			case BLOCK_DOWN:
				pDevice->SetTexture(0, g_pTextureBlock[2]); //�e�N�X�`���̐ݒ�
				break;
			case BLOCK_ICE:
				pDevice->SetTexture(0, g_pTextureBlock[3]); //�e�N�X�`���̐ݒ�
				break;
			case BLOCK_CARRY:
				pDevice->SetTexture(0, g_pTextureBlock[4]); //�e�N�X�`���̐ݒ�
				break;
			case BLOCK_WARP:
				pDevice->SetTexture(0, g_pTextureBlock[5]); //�e�N�X�`���̐ݒ�
				break;
			}
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntBlock * 4,  //�J�n����n�_�̃C���f�b�N�X
				2); //�`�悷��v���~�e�B�u��
		}
	}
}

//�u���b�N���Z�b�e�B���O����
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXVECTOR3 Maxmove, int nMaxTime, BLOCKTYPE BlockType)
{
	int nCntBlock;
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//�g��Ȃ��ꍇ
		if (g_aBlock[nCntBlock].bUse == false)
		{
			//�ݒ肵���Ƃ���ɂ���
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].Startpos = pos;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].bUse = true;
			g_aBlock[nCntBlock].Maxmove = Maxmove;
			g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBlock[nCntBlock].nMaxTime = nMaxTime;
			g_aBlock[nCntBlock].nTime = 0;
			g_aBlock[nCntBlock].BlockType = BlockType;
			VERTEX_2D *pVtx;
			g_pVtxBuffBlock->Lock(0, 0, (void **)&pVtx, 0);
			pVtx += nCntBlock * 4;
			pVtx[0].pos = D3DXVECTOR3(pos.x, pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x, pos.y + fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHeight, 0.0f);
			if (BlockType == BLOCK_NORMAL || BlockType == BLOCK_ICE)
			{
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(fWidth / 20, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, fHeight / 20);
				pVtx[3].tex = D3DXVECTOR2(fWidth / 20, fHeight / 20);
			}
			else
			{
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			g_pVtxBuffBlock->Unlock();
			break;
		}
	}
}

//�S���g�p���Ȃ��悤�ɂ���
void ResetBlock(void)
{
	int nCntBlock;
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].bUse = false;
	}
}

//�u���b�N�Ƃ̓����蔻��
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, D3DXVECTOR3 *pBlockMove, int nType)
{
	Block *pBlock;
	D3DXVECTOR3 WarpPos;
	bool bLand = false;
	pBlock = &g_aBlock[0];
	int nCntBlock;
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		//�g���Ă�u���b�N
		if (pBlock->bUse == true)
		{
			//�v���C���[�̏ꍇ
			if (nType == 0)
			{
				//�u���b�N�ƍ��E���������Ă���
				if (pPos->x - fWidth < pBlock->pos.x + pBlock->fWidth && pBlock->pos.x < pPos->x + fWidth)
				{
					//�u���b�N�̏㑤�ɂԂ�����(�����)�Ƃ�
					if (pPosOld->y - 5.0f <= pBlock->pos.y && pBlock->pos.y <= pPos->y)
					{
						//���n����A�X�u���b�N�������ꍇ��true�ɂ���
						bLand = true;
						pMove->y = 0.0f;
						if (pBlock->BlockType == BLOCK_ICE)
						{
							IcePlayer(true);
						}
						else
						{
							IcePlayer(false);
						}

						//������u���b�N�̏ꍇ�A�u���b�N�𗎂Ƃ�
						if (pBlock->BlockType == BLOCK_DOWN)
						{
							pBlock->move.y = 4.0f;
							//���ȏ㗎���Ă�����A��~������
							if (pBlock->pos.y >= pBlock->Maxmove.y)
							{
								pBlock->move.y = 1.0f;
								pBlock->pos.y = pBlock->Maxmove.y;
							}
						}
						//�オ��u���b�N�̏ꍇ�A�u���b�N���グ��
						else if (pBlock->BlockType == BLOCK_UP)
						{
							pBlock->move.y = -4.0f;
							//���ȏ㗎���Ă�����A��~������
							if (pBlock->pos.y <= pBlock->Maxmove.y)
							{
								pBlock->move.y = -1.0f;
								pBlock->pos.y = pBlock->Maxmove.y;
							}
						}

						//�v���C���[�́u�u���b�N�̈ړ��ʁv�ɑ������
						pBlockMove->x = pBlock->move.x;
						pBlockMove->y = pBlock->move.y;
						pPos->y = pBlock->pos.y;
					}
					//�u���b�N�̉����ɂԂ������Ƃ�
					else if (pBlock->pos.y + pBlock->fHeight >= pPos->y - fHeight &&
						pBlock->pos.y + pBlock->fHeight <= pPosOld->y - fHeight)
					{
						//�u���b�N�̍����ɂԂ������Ƃ�
						if (pBlock->pos.x <= pPos->x + fWidth && pPos->x + (fWidth / 2) <= pBlock->pos.x)
						{
							//���̈ړ��ʂ�0�ɂ���A���ꏊ�������Ɉړ�������
							pMove->x = 0.0f;
							pPos->x = pBlock->pos.x - fWidth;
						}
						//�u���b�N�̉E���ɂԂ������Ƃ�
						else if (pPos->x - fWidth <= pBlock->pos.x + pBlock->fWidth && pBlock->pos.x + pBlock->fWidth <= pPos->x - (fWidth / 2))
						{
							//���̈ړ��ʂ�0�ɂ���A���ꏊ�������Ɉړ�������
							pMove->x = 0.0f;
							pPos->x = pBlock->pos.x + pBlock->fWidth + fWidth;
						}
						else
						{
							//�c�̈ړ��ʂ�1.0f�ɂ���A�ꏊ�������Ɉړ�������
							pMove->y = 1.0f;
							pPos->y = pBlock->pos.y + pBlock->fHeight + fHeight + 1.0f;
							pBlockMove->x = 0.0f;
							pBlockMove->y = 0.0f;
							PlaySound(SOUND_LABEL_BLOCKCLASH);
						}
					}
				}

				//�u���b�N�̏c���������Ă�
				if (pPos->y - fHeight < pBlock->pos.y + pBlock->fHeight && pBlock->pos.y < pPos->y)
				{
					//�u���b�N�̍��ɂԂ������Ƃ�
					if (pBlock->pos.x <= pPos->x + fWidth && pPosOld->x + fWidth <= pBlock->pos.x)
					{
						if (pBlock->BlockType == BLOCK_WARP) //���[�v�z�[���ɓ������Ƃ��A���[�v������
						{
							WarpPos = WarpBlock(pBlock->nMaxTime);
							pPos->x = WarpPos.x + pBlock->fWidth + fWidth + 5.0f;
							pPos->y = WarpPos.y + pBlock->fHeight - 1.0f;
							pMove->y = 0.0f;
							pPosOld = pPos;
						}
						else //����ȊO�̃u���b�N�ɓ��������Ƃ�
						{
							pMove->x = 0.0f;
							pPos->x = pBlock->pos.x - fWidth;
							if (pBlock->BlockType == BLOCK_CARRY) //�L�����[�u���b�N��������
							{
								pBlock->move.x = 0.8f;
							}
						}
					}
					//�u���b�N�̉E�ɂԂ������Ƃ�
					if (pPos->x - fWidth <= pBlock->pos.x + pBlock->fWidth && pBlock->pos.x + pBlock->fWidth <= pPosOld->x - fWidth)
					{
						if (pBlock->BlockType == BLOCK_WARP) //���[�v�z�[���ɓ������Ƃ��A���[�v������
						{
							WarpPos = WarpBlock(pBlock->nMaxTime);
							pPos->x = WarpPos.x - fWidth - 5.0f;
							pPos->y = WarpPos.y + pBlock->fHeight - 1.0f;
							pPosOld = pPos;
							pMove->y = 0.0f;
						}
						else //����ȊO�̃u���b�N�ɓ��������Ƃ�
						{
							pMove->x = 0.0f;
							pPos->x = pBlock->pos.x + pBlock->fWidth + fWidth;
							if (pBlock->BlockType == BLOCK_CARRY) //�L�����[�u���b�N��������
							{
								pBlock->move.x = -0.8f;
							}
						}
					}
				}
			}
			//�藠���̏ꍇ
			else if (nType == 1)
			{
				//�u���b�N�ɓ�������
				if (pPos->x - (fWidth / 2) <= pBlock->pos.x + pBlock->fWidth && pBlock->pos.x <= pPos->x + (fWidth / 2) &&
					pPos->y - (fHeight / 2) <= pBlock->pos.y + pBlock->fHeight && pBlock->pos.y <= pPos->y + (fHeight / 2))
				{
					if (pBlock->BlockType == BLOCK_WARP)
					{
						if (pBlock->pos.x <= pPos->x + fWidth / 2 && pPosOld->x + fWidth / 2 <= pBlock->pos.x) //���[�v�z�[���̍����Ɏh�������Ƃ��A�E���ɏo��
						{
							WarpPos = WarpBlock(pBlock->nMaxTime);
							pPos->x = WarpPos.x + pBlock->fWidth + fWidth + 5.0f;
							pPos->y = WarpPos.y - (pBlock->pos.y - pPos->y);
							pPosOld = pPos;
						}
						else if (pPos->x - fWidth / 2 <= pBlock->pos.x + pBlock->fWidth && pBlock->pos.x + pBlock->fWidth <= pPosOld->x - fWidth / 2) //���[�v�]�[���̉E���Ɏh�������Ƃ������ɏo��
						{
							WarpPos = WarpBlock(pBlock->nMaxTime);
							pPos->x = WarpPos.x - fWidth - 5.0f;
							pPos->y = WarpPos.y - (pBlock->pos.y - pPos->y);
							pPosOld = pPos;
						}
					}
					//���[�v�ȊO�̃u���b�N
					else
					{
						//���̏�ɗ��߂�
						pMove->x = 0.0f;
						pMove->y = 0.0f;
						pPos->x += pBlock->move.x;
						if (pBlock->BlockType != BLOCK_DOWN)
						{
							pPos->y += pBlock->move.y;
						}
						else if (pBlock->Startpos.y < pBlock->pos.y && pBlock->pos.y < pBlock->Maxmove.y)
						{
							pPos->y += pBlock->move.y - 1.0f;
						}
						bLand = true;
					}
				}
			}
		}
	}
	return bLand;
}

//���[�v����
D3DXVECTOR3 WarpBlock(int nMaxTime)
{
	int nCntBlock;
	D3DXVECTOR3 pos;
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//�g���Ă�
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (g_aBlock[nCntBlock].BlockType == BLOCK_WARP)
			{
				//�ő厞��(�Ή����鐔��)�������������1�����������ƈ�v����A�܂��͍ő厞�Ԃ���������1�����������ƈ�v����
				if (nMaxTime % 2 == 0 && nMaxTime + 1 == g_aBlock[nCntBlock].nMaxTime ||
					nMaxTime % 2 == 1 && nMaxTime - 1 == g_aBlock[nCntBlock].nMaxTime)
				{
					pos = g_aBlock[nCntBlock].pos;
					break;
				}
			}
		}
	}
	PlaySound(SOUND_LABEL_WARP);
	return pos;
}