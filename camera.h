//��������������������������
//camera.h
//��������������������������
#ifndef _CAMERA_H_		//��d�K�[�h�C���N���[�h
#define _CAMERA_H_

#include "renderer.h"

class CCamera
{
public:
	struct CAMERA
	{
		D3DXVECTOR3 posV;			//���_
		D3DXVECTOR3 posVDest;		//�ړI�̎��_
		D3DXVECTOR3 posR;			//�����_
		D3DXVECTOR3 posRDest;		//�ړI�̒����_
		D3DXVECTOR3 vecU;			//������x�N�g��
		D3DXVECTOR3 rot;			//����
		D3DXVECTOR3 rotDest;		//�ړI�̌���
		D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
		D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
		float fDistance;			//���_���璍���_�̋���
	};

	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	CAMERA GetCamera(void) { return m_camera; }

private:
	CAMERA m_camera;
};

#endif
