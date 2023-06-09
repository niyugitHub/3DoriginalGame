#pragma once
#include <unordered_map>
#include <string>

/// <summary>
/// SEの管理を行うシングルトンクラス
/// </summary>
class SoundManager
{
private:
	// 変更したサウンド情報をファイルに書き込む
	struct SoundConfigInfo
	{
		char signature[5];			// "SND_"
		float version;				// 1.0
		unsigned short volumeSE;	// 0〜255	
		unsigned short volumeBGM;	// 0〜255
	};

	unsigned short volumeSE_ = 255;
	unsigned short volumeBGM_ = 255;

	std::unordered_map<std::string, int> nameAndHandleTable_;
	int LoadSoundFile(const char* fileName);

	// シングルトンパターンなのでコンストラクタはprivateに置く
	SoundManager();

	// コピーも代入も禁止する
	SoundManager(const SoundManager&) = delete;			// コピーコンストラクタ
	void operator = (const SoundManager&) = delete;		// 代入も禁止

	void LoadSoundConfig();
public:
	~SoundManager();
	/// <summary>
	/// SoundManager使用者はGetInstance()を通した参照からしか利用できない
	/// </summary>
	/// <returns></returns>
	static SoundManager& GetInstance()
	{
		// 唯一の実態
		static SoundManager instance;

		// それの参照を返す
		return instance;
	}

	/// <summary>
	/// 指定のサウンドを鳴らす
	/// </summary>
	/// <param name="name">サウンド名</param>
	void Play(const char* name);
	void PlayMusic(const char* path);

	/// <summary>
	/// SEのボリュームを設定する
	/// </summary>
	/// <param name="volume"></param>
	void SetSEVolume(unsigned short volume);
	int GetSEVolume() const ;

	/// <summary>
	/// BGMのボリュームを設定する
	/// </summary>
	/// <param name="volume"></param>
	void SetBGMVolume(unsigned short volume);
	 int GetBGMVolume() const ;

	 /// <summary>
	 /// BGMの現在の鳴らす音量の割合
	 /// </summary>
	 /// <param name="rate">音量の割合(一時的なもの0.0〜1.0)</param>
	 void SetBGMRate(float rate);

	// サウンドを全部一時停止する
	void StopBGMAndSE();

	// サウンド情報をセーブ
	void SaveSoundConfig();
};