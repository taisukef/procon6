// vpcdoc.h : CVpcDoc �N���X�̐錾����уC���^�[�t�F�[�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

class CVpcDoc : public CDocument
{
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CVpcDoc();
	DECLARE_DYNCREATE(CVpcDoc)

// ����
public:

// �I�y���[�V����
public:

// �C���v�������e�[�V����
public:
	virtual ~CVpcDoc();
	virtual void Serialize(CArchive& ar);	// �h�L�������g I/O �ɑ΂��ăI�[�o�[���C�h����܂��B
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:
	virtual	BOOL	OnNewDocument();

// ���b�Z�[�W �}�b�v�֐��̐������s���܂��B
protected:
	//{{AFX_MSG(CVpcDoc)
		// ���� �| ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//         ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////