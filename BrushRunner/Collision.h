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

bool HitCheckBB(D3DXVECTOR3 posA, D3DXVECTOR3 posB, D3DXVECTOR2 sizeA, D3DXVECTOR2 sizeB);	// ��`�̓����蔻��
bool HitCheckPToM(PLAYER *pP, MAP *pM);	// �v���C���[�Ƒ����̃}�b�v�̓����蔻��

#endif

