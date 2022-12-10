//��������������������������
//camera.h
//��������������������������
#ifndef _CAMERA_H_		//��d�K�[�h�C���N���[�h
#define _CAMERA_H_

#include "renderer.h"

class CObject;

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

	//�Z�b�^�[
	void SetCamera(void);
	void SetTraction(bool set) { m_bTraction = set; }

	//�Q�b�^�[
	CAMERA *GetCamera(void) { return &m_camera; }
	D3DXVECTOR3 GetWorldPosR() { return m_worldposR; }

private:
	CAMERA m_camera;
	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_worldposV;	//���_
	D3DXVECTOR3 m_worldposR;	//�����_

	bool m_bTraction;
};

#endif
