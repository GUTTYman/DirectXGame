#pragma once

#include<xaudio2.h>
#include<wrl.h>
#include<map>


class SoundManager
{
private:
	//Microsoft::WRL::���ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//std::���ȗ�
	template<class T1,class T2>using map = std::map<T1,T2>;
	//�`�����N�w�b�_
	struct Chunk
	{
		char id[4];		//�`�����N���Ƃ�ID
		int size;	//�`�����N�T�C�Y
	};
	//RIFF�w�b�_�`�����N
	struct RiffHeader
	{
		Chunk chunk;	//"RIFF"
		char type[4];	//"WAVE"
	};
	//FMT�`�����N
	struct FormatChunk
	{
		Chunk chunk;	//"fmt"
		WAVEFORMAT fmt;	//�g�`�t�H�[�}�b�g
	};

	struct  SoundData
	{
		//�g�`�t�H�[�}�b�g
		WAVEFORMATEX wfex{};
		//�g�`�f�[�^
		char* pBuffer;
		//�g�`�f�[�^�̃T�C�Y
		unsigned int dataSize;
	};

public:
	
	~SoundManager();
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �T�E���h�t�@�C���̓ǂݍ���
	/// </summary>
	/// <param name="number"></param>
	/// <param name="filename">Wave�t�@�C����</param>
	void LoadWave(int number, const char* filename);
	/// <summary>
	/// �T�E���h�t�@�C���̓ǂݍ��݂ƍĐ�
	/// </summary>
	/// <param name="number">�T�E���h�ԍ�</param>
	void PlayWave(int number);
private:	//�����o�ϐ�
	//XAudio2�̃C���X�^���X
	ComPtr<IXAudio2> xAudio2;
	//�}�X�^�[�{�C�X
	IXAudio2MasteringVoice* masterVoice;
	//�g�`�f�[�^�̘A�z�z��
	map<int, SoundData>soundDatas;
};

