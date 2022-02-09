#pragma once

#include<xaudio2.h>
#include<wrl.h>
#include<map>


class SoundManager
{
private:
	//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//std::を省略
	template<class T1,class T2>using map = std::map<T1,T2>;
	//チャンクヘッダ
	struct Chunk
	{
		char id[4];		//チャンクごとのID
		int size;	//チャンクサイズ
	};
	//RIFFヘッダチャンク
	struct RiffHeader
	{
		Chunk chunk;	//"RIFF"
		char type[4];	//"WAVE"
	};
	//FMTチャンク
	struct FormatChunk
	{
		Chunk chunk;	//"fmt"
		WAVEFORMAT fmt;	//波形フォーマット
	};

	struct  SoundData
	{
		//波形フォーマット
		WAVEFORMATEX wfex{};
		//波形データ
		char* pBuffer;
		//波形データのサイズ
		unsigned int dataSize;
	};

public:
	
	~SoundManager();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// サウンドファイルの読み込み
	/// </summary>
	/// <param name="number"></param>
	/// <param name="filename">Waveファイル名</param>
	void LoadWave(int number, const char* filename);
	/// <summary>
	/// サウンドファイルの読み込みと再生
	/// </summary>
	/// <param name="number">サウンド番号</param>
	void PlayWave(int number);
private:	//メンバ変数
	//XAudio2のインスタンス
	ComPtr<IXAudio2> xAudio2;
	//マスターボイス
	IXAudio2MasteringVoice* masterVoice;
	//波形データの連想配列
	map<int, SoundData>soundDatas;
};

