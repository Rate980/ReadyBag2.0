#ifndef __SCREEN_MAIN_H__
#define __SCREEN_MAIN_H__
#include <SPIFFS.h>
#include <M5GFX.h>
#include <FS.h>

// いまの状態
// Nobalだと緑
// Alertだと赤
// NotScanだと灰色
// MainState::Nomalなどで指定
// auto {変数名} = MainState::Nomal;
// ↑こんなんじでいける
// {関数}(MainState::Nomal) ←こんなんでもいい
enum class MainState
{
    Nomal,
    Alert,
    NotScan,
};

// どれが選択されているか
// MainSelection::Addなどで指定
// auto {変数名} = MainSelection::Add;
// ↑こんなんじでいける
// {関数}(MainSelection::Add) ←こんなんでもいい
enum class MainSelection
{
    Add,
    Bell,
    Setting,
};

// main画面を描画するやつ
// 何回でも呼んで大丈夫
// 選択が変わったらもっかい呼ぶ
void drawMainScreen(fs::FS &fs, M5GFX *display, MainState state, MainSelection selection);
#endif
