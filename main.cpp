#include <Novice.h>
#include <stdio.h>
#include "Player.h"

const char kWindowTitle[] = "LC1C_12_スズキ_ユイト";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1440, 900);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Player player;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		player.Update(keys, preKeys);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// 背景の描画
		Novice::DrawBox(0, 0, 1440, 900, 0.0f, BLACK, kFillModeSolid);

		// プレイヤーの描画
		player.Draw();

		// ボスの外側の円
		Novice::DrawEllipse
		(
			640,
			360,
			190,
			190,
			0.0f,
			0xFF2040FF,
			kFillModeWireFrame
		);

		// 白い眼球
		Novice::DrawEllipse
		(
			640,
			360,
			78,
			78,
			0.0f,
			WHITE,
			kFillModeSolid
		);

		// 赤い瞳
		Novice::DrawEllipse
		(
			640,
			360,
			32,
			32,
			0.0f,
			0xFF2040FF,
			kFillModeSolid
		);

		// 目の上下の輪郭
		for (int i = -180; i < 180; i++)
		{
			float x1 = static_cast<float>(i);
			float x2 = static_cast<float>(i + 1);

			float y1 = 90.0f * (1.0f - (x1 * x1) / (180.0f * 180.0f));
			float y2 = 90.0f * (1.0f - (x2 * x2) / (180.0f * 180.0f));

			// 上側の曲線
			Novice::DrawLine
			(
				static_cast<int>(640 + x1),
				static_cast<int>(360 - y1),
				static_cast<int>(640 + x2),
				static_cast<int>(360 - y2),
				0xFF2040FF
			);

			// 下側の曲線
			Novice::DrawLine
			(
				static_cast<int>(640 + x1),
				static_cast<int>(360 + y1),
				static_cast<int>(640 + x2),
				static_cast<int>(360 + y2),
				0xFF2040FF
			);
		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
