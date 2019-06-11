//=============================================================================
//
// �R���W����[Collision.h]
// Author : HAL���� GP12B332-19 80277 ���J���u
//
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Player.h"
#include "Map.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool HitCheckBB(D3DXVECTOR3 posA, D3DXVECTOR3 posB, D3DXVECTOR2 sizeA, D3DXVECTOR2 sizeB);	// ��`�̓����蔻��
bool HitCheckPToM(PLAYER *pP, MAP *pM);	// �v���C���[�Ƒ����̃}�b�v�̓����蔻��

float dotProduct(D3DXVECTOR3 *vl, D3DXVECTOR3 *vr);
void crossProduct(D3DXVECTOR3 *ret, D3DXVECTOR3 *vl, D3DXVECTOR3 *vr);
int hitCheck(D3DXVECTOR3 *OutPos, TRIANGLE_WK tri, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1);

#endif

