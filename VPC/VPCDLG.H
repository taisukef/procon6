// vpcdlg.h : �w�b�_�[ �t�@�C��
//


/////////////////////////////////////////////////////////////////////////////
// CValueDlg �_�C�A���O

class CValueDlg : public CDialog
{
public:
	CString csMess;

// �R���X�g���N�^
public:
	CValueDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CValueDlg)
	enum { IDD = IDD_VALUE_DLG };
	int		m_value;
	//}}AFX_DATA

// �C���v�������e�[�V����
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g

	// ���b�Z�[�W�}�b�v�֐��̐���
	//{{AFX_MSG(CValueDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};