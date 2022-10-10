//����������������������������������������
//Object3D.h
//����������������������������������������
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "object.h"
#include "texture.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// ���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_3D(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//���_���[3D]�̍\���̂��`
struct VERTEX_3D
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`��
};

class CObject3D : public CObject
{
public:
	enum EBlend
	{
		BLEND_NONE = 0,
		BLEND_ADDITIVE,
		BLEND_SUBSTRUCT,
		BLEND_MAX
	};

	CObject3D();
	~CObject3D() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void SetUV(float Xtop, float Xbottom, float Ytop, float Ybottom);
	bool PlaneCollision(D3DXVECTOR3 pos, D3DXVECTOR3 Destpos, float Length, float CollisionVal);

	//�Z�b�^�[
	void SetPos(D3DXVECTOR3 pos) override { m_objpos = pos; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetCol(D3DXCOLOR col) { m_col = col; }
	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }
	void SetTexture(CTexture::TEXTURE texture) { m_texture = texture; }// �e�N�X�`���̐ݒ�
	void SetBlend(EBlend blend) { m_blend = blend; }
	void SetZBuff(_D3DCMPFUNC func) { m_Zfunc = func; }
	void SetRelease(bool set) override { m_bRelease = set; }

	//�Q�b�^�[
	D3DXVECTOR3 GetPos() override { return m_objpos; }
	D3DXVECTOR3 GetMove() { return m_move; }
	D3DXVECTOR3 GetScale() { return m_scale; }
	D3DXCOLOR GetCol() { return m_col; }
	EBlend GetBlend() { return m_blend; }
	float GetWidth() { return m_Width; }
	float GetHeight() { return m_Height; }
	bool GetRelease() override { return m_bRelease; }

private:
	CTexture::TEXTURE m_texture;	// �e�N�X�`���̗񋓌^
	D3DXVECTOR3 m_objpos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scale;
	D3DXCOLOR m_col;
	D3DXMATRIX m_mtxWorld;
	_D3DCMPFUNC m_Zfunc;
	EBlend m_blend;
	float m_Width;
	float m_Height;
	bool m_bRelease;
};

#endif